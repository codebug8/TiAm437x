#ifndef   _AM437X_PWM_H_
#define   _AM437X_PWM_H_

#include  "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

/*注：
  有些寄存器是2个字节
*/

typedef struct {
	uint32_t IDVER;         //0h
	uint32_t SYSCONFIG;     //4h
	uint32_t CLKCONFIG;		//8h
	uint32_t CLKSTATUS;     //Ch
}PWMSS_Typedef;

typedef struct {
	uint32_t TSCTR;          //0h
	uint32_t CTRPHS;  		 //4h
	uint32_t CAP1;   	     //8h
	uint32_t CAP2;           //Ch
	uint32_t CAP3;           //10h
	uint32_t CAP4;           //14h
	uint32_t RESERVED0[4]; 	 //18h

	uint16_t ECCTL1;         //28h
	uint16_t ECCTL2;         //2Ah

	uint16_t ECEINT;         //2Ch
	uint16_t ECFLG;          //2Eh

	uint16_t ECCLR;          //30h
	uint16_t ECFRC;          //32h

	uint32_t RESERVED1[10];  //34h
	uint32_t REVID;          //5Ch
}PWMSS_ECAP_Typedef;


typedef struct {
	uint32_t QPOSCNT;     	 //0h  
	uint32_t QPOSINIT;    	 //4h  
	uint32_t QPOSMAX;     	 //8h  
	uint32_t QPOSCMP;     	 //Ch  
	uint32_t QPOSILAT;    	 //10h 
	uint32_t QPOSSLAT;    	 //14h 
	uint32_t QPOSLAT;     	 //18h 
	uint32_t QUTMR;       	 //1Ch 
	uint32_t QUPRD;       	 //20h 

	uint16_t QWDTMR;      	 //24h 
	uint16_t QWDPRD;      	 //26h

	uint16_t QDECCTL;     	 //28h 
	uint16_t QEPCTL;      	 //2Ah 

	uint16_t QCAPCTL;     	 //2Ch 
	uint16_t QPOSCTL;     	 //2Eh 

	uint16_t QEINT;       	 //30h 
	uint16_t QFLG;        	 //32h 

	uint16_t QCLR;        	 //34h 
	uint16_t QFRC;        	 //36h 

	uint16_t QEPSTS;      	 //38h 
	uint16_t QCTMR;       	 //3Ah 

	uint16_t QCPRD;       	 //3Ch 
	uint16_t QCTMRLAT;    	 //3Eh 

	uint32_t QCPRDLAT;    	 //40h 
}PWMSS_EQEP_Typedef;

typedef struct {
	uint16_t TBCTL;    		 //0h    
	uint16_t TBSTS;    		 //2h 

	uint16_t TBPHSHR;  		 //4h    
	uint16_t TBPHS;    		 //6h 

	uint16_t TBCNT;    		 //8h    
	uint16_t TBPRD;    		 //Ah 

	uint16_t RESERVED0[1];   //Ch
	uint16_t CMPCTL;   		 //Eh 
 
	uint16_t CMPAHR;   		 //10h   
	uint16_t CMPA;     		 //12h

	uint16_t CMPB;     		 //14h   
	uint16_t AQCTLA;   		 //16h 

	uint16_t AQCTLB;   		 //18h   
	uint16_t AQSFRC;   		 //1Ah

	uint16_t AQCSFRC;  		 //1Ch   
	uint16_t DBCTL;    		 //1Eh

	uint16_t DBRED;    		 //20h   
	uint16_t DBFED;    		 //22h 

	uint32_t TZSEL;    		 //24h 

	uint16_t TZCTL;    		 //28h   
	uint16_t TZEINT;   		 //2Ah  

	uint16_t TZFLG;    		 //2Ch   
	uint16_t TZCLR;    		 //2Eh 

	uint16_t TZFRC;    		 //30h   
	uint16_t ETSEL;    		 //32h   	
}PWMSS_EPWM_Typedef;


#define PWMSS0         		((volatile PWMSS_Typedef *)PWMSS0_BASE)
#define PWMSS0_ECAP         ((volatile PWMSS_ECAP_Typedef *)PWMSS0_ECAP_BASE)
#define PWMSS0_EQEP         ((volatile PWMSS_EQEP_Typedef *)PWMSS0_EQEP_BASE)
#define PWMSS0_EPWM         ((volatile PWMSS_EPWM_Typedef *)PWMSS0_EPWM_BASE)

#define PWMSS1         		((volatile PWMSS_Typedef *)PWMSS1_BASE)
#define PWMSS1_ECAP         ((volatile PWMSS_ECAP_Typedef *)PWMSS0_ECAP_BASE)
#define PWMSS1_EQEP         ((volatile PWMSS_EQEP_Typedef *)PWMSS0_EQEP_BASE)
#define PWMSS1_EPWM         ((volatile PWMSS_EPWM_Typedef *)PWMSS0_EPWM_BASE)

#define PWMSS2         		((volatile PWMSS_Typedef *)PWMSS2_BASE)
#define PWMSS2_ECAP         ((volatile PWMSS_ECAP_Typedef *)PWMSS2_ECAP)
#define PWMSS2_EQEP         ((volatile PWMSS_EQEP_Typedef *)PWMSS2_EQEP)
#define PWMSS2_EPWM         ((volatile PWMSS_EPWM_Typedef *)PWMSS2_EPWM)

#define PWMSS3         		((volatile PWMSS_Typedef *)PWMSS3_BASE)
#define PWMSS3_EPWM         ((volatile PWMSS_EPWM_Typedef *)PWMSS3_EPWM)

#define PWMSS4         		((volatile PWMSS_Typedef *)PWMSS4_BASE)
#define PWMSS4_EPWM         ((volatile PWMSS_EPWM_Typedef *)PWMSS4_EPWM)

#define PWMSS5         		((volatile PWMSS_Typedef *)PWMSS5_BASE)
#define PWMSS5_EPWM         ((volatile PWMSS_EPWM_Typedef *)PWMSS5_EPWM)

#endif
