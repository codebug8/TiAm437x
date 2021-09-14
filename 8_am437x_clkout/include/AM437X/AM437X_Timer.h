#ifndef   _AM437X_TIMER_H_
#define   _AM437X_TIMER_H_

#include  "AM437X_DataType.h"
#include  "AM437X_Mapping.h"

typedef struct {
	uint32_t TIDR;          //00h
	uint32_t RESERVED0[3];  //04h
	uint32_t TIOCP_CFG;		//10h
	uint32_t RESERVED1[3];  //14H
	uint32_t IRQ_EOI;		//20h
	uint32_t IRQSTS_RAW;	//24h
	uint32_t IRQSTS;		//28h
	uint32_t IRQEN_SET;		//2ch
	uint32_t IRQEN_CLR;		//30h
	uint32_t IRQWAKEEN;		//34h
	uint32_t TCLR;			//38h
	uint32_t TCRR;			//3ch
	uint32_t TLDR;			//40h
	uint32_t TTGR;			//44h
	uint32_t TWPS;			//48h
	uint32_t TMAR;			//4ch
	uint32_t TCAR1;			//50h
	uint32_t TSICR;			//54h
	uint32_t TCAR2;			//58h
}DMTIMER_Typedef;

typedef struct {
	uint32_t TIDR;          //00h
	uint32_t RESERVED0[3];  //04h
	uint32_t TIOCP_CFG;     //10h
	uint32_t TISTAT;        //14h
	uint32_t TISR;          //18h
	uint32_t TIER;          //1ch
	uint32_t TWER;          //20h
	uint32_t TCLR;          //24h
	uint32_t TCRR;          //28h
	uint32_t TLDR;          //2ch
	uint32_t TTGR;          //30h
	uint32_t TWPS;          //34h
	uint32_t TMAR;          //38h
	uint32_t TCAR1;         //3ch
	uint32_t TSICR;         //40h
	uint32_t TCAR2;         //44h
	uint32_t TPIR;          //48h
	uint32_t TNIR;          //4ch
	uint32_t TCVR;          //50h
	uint32_t TOCR;          //54h
	uint32_t TOWR;          //58h
}DMTIMER1_Typedef;

typedef struct {
	uint32_t YNCNT_REV;     //00h
	uint32_t SYSCONFIG;     //04h
	uint32_t RESERVED0[2];  //08h
	uint32_t CR;            //10h
}SYNCTIMER32K_Typedef; 


typedef struct {
	uint32_t WIDR; 
	uint32_t RESERVED0[3]; 
	uint32_t WDSC;  
	uint32_t WDST;  
	uint32_t WISR;  
	uint32_t WIER; 
	uint32_t RESERVED1[1];   
	uint32_t WCLR;  
	uint32_t WCRR;  
	uint32_t WLDR;  
	uint32_t WTGR;  
	uint32_t WWPS;
	uint32_t RESERVED2[3];   
	uint32_t WDLY;  
	uint32_t WSPR;  
	uint32_t RESERVED3[2]; 
	uint32_t WIRQSTATRAW;  
	uint32_t WIRQSTAT;  
	uint32_t WIRQENSET;  
	uint32_t WIRQENCLR; 
}WDT1_Typedef;


typedef struct {
	uint32_t SECONDS_REG;         //00h
	uint32_t MINUTES_REG;         //04h
	uint32_t HOURS_REG;           //08h
	uint32_t DAYS_REG;            //0Ch
	uint32_t MONTHS_REG;          //10h
	uint32_t YEARS_REG;           //14h
	uint32_t WEEKS_REG;           //18h
	uint32_t RESERVED0[1]; 	      //1Ch
	uint32_t ALARM_SECONDS_REG;   //20h
	uint32_t ALARM_MINUTES_REG;   //24h
	uint32_t ALARM_HOURS_REG;     //28h
	uint32_t ALARM_DAYS_REG;      //2Ch
	uint32_t ALARM_MONTHS_REG;    //30h
	uint32_t ALARM_YEARS_REG;     //34h
	uint32_t RESERVED1[2]; 	      //38h
	uint32_t CTRL_REG;            //40h
	uint32_t STS_REG;             //44h
	uint32_t INTRS_REG;           //48h
	uint32_t COMP_LSB_REG;        //4Ch
	uint32_t COMP_MSB_REG;        //50h
	uint32_t OSC_REG;             //54h
    uint32_t RESERVED2[2]; 	      //58h
	uint32_t SCRATCH0_REG;        //60h
	uint32_t SCRATCH1_REG;        //64h
	uint32_t SCRATCH2_REG;        //68h
	uint32_t KICK0R;              //6Ch
	uint32_t KICK1R;              //70h
	uint32_t REVISION;            //74h
	uint32_t SYSCONFIG;           //78h
	uint32_t IRQWAKEEN;           //7Ch
	uint32_t ALARM2_SECONDS_REG;  //80h
	uint32_t ALARM2_MINUTES_REG;  //84h
	uint32_t ALARM2_HOURS_REG;    //88h
	uint32_t ALARM2_DAYS_REG;     //8Ch
	uint32_t ALARM2_MONTHS_REG;   //90h
	uint32_t ALARM2_YEARS_REG;    //94h
	uint32_t PMIC;                //98h
	uint32_t DEBOUNCE;            //9Ch
}RTCSS_Typedef;

#define   DMTIMER0   		((volatile DMTIMER_Typedef *)DMTIMER0_BASE)  
#define   DMTIMER1_1MS   	((volatile DMTIMER1_Typedef *)DMTIMER1_1MS_BASE)  
#define   DMTIMER2   		((volatile DMTIMER_Typedef *)DMTIMER2_BASE)  
#define   DMTIMER3   		((volatile DMTIMER_Typedef *)DMTIMER3_BASE)  
#define   DMTIMER4   		((volatile DMTIMER_Typedef *)DMTIMER4_BASE)  
#define   DMTIMER5   		((volatile DMTIMER_Typedef *)DMTIMER5_BASE)  
#define   DMTIMER6   		((volatile DMTIMER_Typedef *)DMTIMER6_BASE)  
#define   DMTIMER7   		((volatile DMTIMER_Typedef *)DMTIMER7_BASE)  
#define   DMTIMER8  		((volatile DMTIMER_Typedef *)DMTIMER8_BASE)  
#define   DMTIMER9   		((volatile DMTIMER_Typedef *)DMTIMER9_BASE)  
#define   DMTIMER10  		((volatile DMTIMER_Typedef *)DMTIMER10_BASE)  
#define   DMTIMER11  		((volatile DMTIMER_Typedef *)DMTIMER11_BASE) 
                              
#define   SYNCTIMER32K 	    ((volatile SYNCTIMER32K_Typedef *)SYNCTIMER_BASE)
                               
#define   WDT1 	        	((volatile WDT1_Typedef *)WDT1_BASE)
                              
#define   RTCSS 	        ((volatile RTCSS_Typedef *)RTCSS_BASE)

#endif
