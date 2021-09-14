#ifndef   _AM437X_MMC_H_
#define   _AM437X_MMC_H_

#include  "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

typedef struct {
	uint32_t RESERVED0[44];       //000h
	uint32_t SYSCONFIG;           //110h 
	uint32_t SYSSTATUS;           //114h
	uint32_t RESERVED1[3];        //118h
	uint32_t CSRE;                //124h
	uint32_t SYSTEST;             //128h
	uint32_t CON;                 //12Ch
	uint32_t PWCNT;               //130h
	uint32_t RESERVED2[33];       //134h
	uint32_t SDMASA;              //200h
	uint32_t BLK;                 //204h
	uint32_t ARG;                 //208h
	uint32_t CMD;                 //20Ch
	uint32_t RSP10;               //210h
	uint32_t RSP32;               //214h
	uint32_t RSP54;               //218h
	uint32_t RSP76;               //21Ch
	uint32_t DATA;                //220h
	uint32_t PSTATE;              //224h
	uint32_t HCTL;                //228h
	uint32_t SYSCTL;              //22Ch
	uint32_t STAT;                //230h
	uint32_t IE;                  //234h
	uint32_t ISE;                 //238h
	uint32_t AC12;                //23Ch
	uint32_t CAPA;                //240h
	uint32_t RESERVED3[1];        //244h
	uint32_t CUR_CAPA;            //248h
	uint32_t RESERVED4[1];        //24Ch
	uint32_t FE;                  //250h
	uint32_t ADMAES;              //254h
	uint32_t ADMASAL;             //258h
	uint32_t ADMASAH;             //25Ch
	uint32_t RESERVED5[27];       //260h
	uint32_t REV;                 //2FCh
}MMCSD_Typedef;


#define   MMCSD0 	        ((volatile MMCSD_Typedef *)MMCSD0_BASE)
#define   MMCSD1 	        ((volatile MMCSD_Typedef *)MMCSD1_BASE)
#define   MMCSD2 	        ((volatile MMCSD_Typedef *)MMCSD2_BASE)

#endif
