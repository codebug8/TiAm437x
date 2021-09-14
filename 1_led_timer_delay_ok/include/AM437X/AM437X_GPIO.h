#ifndef   _AM437X_GPIO_H_
#define   _AM437X_GPIO_H_

#include  "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

typedef struct {
	uint32_t 			REVISION;               //00h 	 
	uint32_t 			RESERVED0[3];  		    //04h  
	uint32_t 			SYSCONFIG; 			    //10h 
	uint32_t 			RESERVED1[3];  		    //14h 
	uint32_t 			EOI; 					//20h 
	uint32_t 			IRQSTS_RAW_0;			//24h 
	uint32_t 			IRQSTS_RAW_1; 		    //28h 
	uint32_t 			IRQSTS_0; 				//2Ch 
	uint32_t 			IRQSTS_1;				//30h 
	uint32_t 			IRQSTS_SET_0; 		    //34h 
	uint32_t 			IRQSTS_SET_1; 		    //38h 
	uint32_t 			IRQSTS_CLR_0; 		    //3Ch 
	uint32_t 			IRQSTS_CLR_1; 		    //40h 
	uint32_t 			IRQWAKEN_0; 			//44h 
	uint32_t 			IRQWAKEN_1; 			//48h 
	uint32_t 			RESERVED2[50]; 		  	//4Ch 
	uint32_t 			SYSSTS;				    //114h
	uint32_t 			RESERVED3[6];  		  	//118h
	uint32_t 			CTRL;					//130h
	uint32_t 			OE;					    //134h
	uint32_t 			DATAIN; 				//138h
	uint32_t 			DATAOUT;				//13Ch
	uint32_t 			LEVELDETECT0; 		    //140h
	uint32_t 			LEVELDETECT1; 		    //144h
	uint32_t 			RISINGDETECT; 		    //148h
	uint32_t 			FALLINGDETECT; 		    //14Ch
	uint32_t 			DEBOUNCEN; 			    //150h
	uint32_t 			DEBOUNCINGTIME; 	    //154h
	uint32_t 			RESERVED4[14];  		//158h
	uint32_t 			CLRDATAOUT; 			//190h
	uint32_t 			SETDATAOUT; 			//194h
}GPIO_Typedef;

#define   GPIO0  	    ((volatile GPIO_Typedef *)GPIO0_BASE)  
#define   GPIO1  	    ((volatile GPIO_Typedef *)GPIO1_BASE)  
#define   GPIO2  	    ((volatile GPIO_Typedef *)GPIO2_BASE)  
#define   GPIO3  	    ((volatile GPIO_Typedef *)GPIO3_BASE)  
#define   GPIO4  	    ((volatile GPIO_Typedef *)GPIO4_BASE)  
#define   GPIO5  	    ((volatile GPIO_Typedef *)GPIO5_BASE)  

#endif


