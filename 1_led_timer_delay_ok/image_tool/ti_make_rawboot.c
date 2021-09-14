
/* weidongshan */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct ti_TOC_item
{
    unsigned int start;  // 0x000000A0
    unsigned int size;   // 0x00000050
    unsigned int flags;  // 0 
    unsigned int align;  // 0
    unsigned int loadaddr;  // 0
    unsigned char filename[12]; // "CHSETTINGS"
}ti_TOC_item;

typedef struct ti_GP_header
{
    unsigned int size;
    unsigned int loadaddr;
}ti_GP_header;


/* ./a.out  0x40300000    infile.bin   outfile.bin */
int main (int argc, char *argv[])
{
    FILE *in_fp, *out_fp;
    long image_size = 0;
    ti_GP_header    hdr;
    int i = 0, len;
    unsigned int extra;
    char dummy[4] = {0,0,0,0};
    char *boot; 

	ti_TOC_item toc1, toc2;
	char toc_buffer[512];
	unsigned int *pmagic;


    if (argc < 4)
    {
        /* expect : tiimage </path/to/boot.bin> <path/to/place/modified/boot.bin> */
        printf("Usage : \n");
        printf("create the file for sd/mmc raw mode \n");
        printf("%s <load addr> <infile.bin> <outfile.bin>\n", argv[0]);
        return -1;
    }


    in_fp = fopen(argv[2], "rb+");
    if(!in_fp) {
        printf("Error opening input image file!\n");
        return -1;
    }


    out_fp = fopen(argv[3], "wb+");
    if(!out_fp) {
        printf("Error opening/creating out image file!\n");
        return -1;
    }

	printf("sizeof ti_TOC_item = %d\n", (int)sizeof(ti_TOC_item));


    /* Calcualte the size of the input image and rewind to the begin of file */
    fseek(in_fp, 0, SEEK_END);
    image_size = ftell(in_fp);

 

    rewind(in_fp);
    /* Size of  new image is actual bin image size + header */
    hdr.size = image_size + sizeof(hdr);
    hdr.loadaddr = strtoul(argv[1], NULL, 0);

	memset(toc_buffer, 0, 512);

	memset(&toc1, 0, 32);
	toc1.start  = 0x000000A0;
	toc1.size   = 0x00000050;
	strcpy(toc1.filename, "CHSETTINGS");
	
	memset(&toc2, 0xff, 32);
	memcpy(toc_buffer, &toc1, 32);
	memcpy(toc_buffer+32, &toc2, 32);
	
	pmagic = (unsigned int *)&toc_buffer[0xA0];
	*pmagic = 0xC0C0C0C1;

	pmagic = (unsigned int *)&toc_buffer[0xA4];
	*pmagic = 0x00000100;
  
    /* Insert the gp header */
    fwrite(&toc_buffer, sizeof(toc_buffer), 1, out_fp);

    /* Insert the gp header */
    fwrite(&hdr, sizeof(hdr), 1, out_fp);

    /* Insert the actual image */
    for(i = 0; i < image_size ; i++) {
        unsigned char temp;
        fread(&temp, sizeof(temp), 1, in_fp);
        fwrite(&temp, sizeof(temp), 1, out_fp);
    }
    printf("\n");

    fclose(out_fp);
    fclose(in_fp);

    return 0;
}


