#ifndef   _AM437X_HDQ1W_H_
#define   _AM437X_HDQ1W_H_

#include  "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

typedef struct {
	uint32_t 	REVISION;           //00h 	 
	uint32_t 	TX_DATA;  		    //04h  
	uint32_t 	RX_DATA; 			//10h 
	uint32_t 	HDQ1W_CTRL_STS;  	//14h 
	uint32_t 	INT_STS; 	        //20h 
	uint32_t 	SYSCONFIG;			//24h 
	uint32_t 	SYSSTS;			    //24h 
}HDQ1W_Typedef;


#define   HDQ1W  	    ((volatile HDQ1W_Typedef *)HDQ1W_BASE)  

#endif
