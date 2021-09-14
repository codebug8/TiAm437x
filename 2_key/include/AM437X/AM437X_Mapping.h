#ifndef  __AM437X_MAPPING_H__
#define  __AM437X_MAPPING_H__

/*注：
同名的基地址都在后面注释了，并加了适当标记，做了相应的区分；
20170801：第一次完成
修正：
*/

#define  GPMC0_BASE	                0x00000000 //8-/16-bit External Memory (Ex/R/W) 
#define  QSPI1_BASE	                0x30000000 //QSPI CS0 Maddrspace 1 space
#define  MPU_ROM_PUBLIC_BASE	    0x40030000
#define  MPU_RAM_BASE	            0x402F0000
#define  OCMCRAM_BASE	            0x40300000
#define  MPU_L2_CACHE_BASE	        0x40500000
#define  L3F_CFG_FAST_BASE	        0x44000000
#define  L3S_CFG_SLOW_BASE	        0x44800000
#define  L4_WKUP_BASE	            0x44C00000 //L4 Wakeup Peripheral (see L4_WKUP table)
#define  MCASP0_DATA_BASE	        0x46000000
#define  MCASP1_DATA_BASE	        0x46400000
#define  MMCSD2_BASE	            0x47810000
#define  QSPI0_BASE	                0x47900000 //QSPI MMR Maddrspace 0 space
#define  L4_PER_BASE	            0x48000000 //L4 Peripheral (see L4_PER table)
#define  EDMA3CC_BASE	            0x49000000
#define  EDMA3TC0_BASE	            0x49800000
#define  EDMA3TC1_BASE	            0x49900000
#define  EDMA3TC2_BASE	            0x49A00000
#define  L4_FAST_BASE	            0x4A000000 //L4 Fast Peripheral (see L4_FAST table)
#define  DEBUGSS0_BASE	            0x4B000000 //Debug Subsystem region
#define  EMIF0_BASE	                0x4C000000 //EMIF0 Configuration registers
#define  GPMC1_BASE	                0x50000000 //GPMC Configuration registers
#define  PRU_ICSS1_BASE	            0x54400000
#define  ADC1_DMA_BASE	            0x54800000 //ADC1 DMA Port
#define  ADC0_DMA_BASE	            0x54C00000 //ADC0 DMA Port
#define  GFX_BASE	                0x56000000
#define  EMIF1_BASE	                0x80000000 //8-/16-/32-bit External Memory (Ex/R/W) 
#define  L4_WKUP_AP_BASE	        0x44C00000 //Address/Protection (AP)
#define  L4_WKUP_LA_BASE	        0x44C00800 //Link Agent (LA)
#define  L4_WKUP_REG0_BASE	        0x44C01000 //Initiator Port (IP0)
#define  L4_WKUP_REG1_BASE	        0x44C01400 //Initiator Port (IP1)
#define  PRCM_BASE	                0x44DF0000
#define  PRM_IRQ_BASE	            0x44DF0000
#define  PRM_MPU_BASE	            0x44DF0300
#define  PRM_GFX_BASE	            0x44DF0400
#define  PRM_RTC_BASE	            0x44DF0524
#define  PRM_CEFUSE_BASE	        0x44DF0700
#define  PRM_PER_BASE	            0x44DF0800
#define  PRM_WKUP_BASE	            0x44DF2000
#define  CM_WKUP_BASE	            0x44DF2800
#define  PRM_DEVICE_BASE	        0x44DF4000
#define  CM_DEVICE_BASE	            0x44DF4100
#define  CM_DPLL_BASE	            0x44DF4200
#define  CM_MPU_BASE	            0x44DF8300
#define  CM_GFX_BASE	            0x44DF8400
#define  CM_RTC_BASE                0x44DF8500
#define  CM_CEFUSE_BASE	            0x44DF8700
#define  CM_PER_BASE	            0x44DF8800
#define  DMTIMER0_BASE	            0x44E05000
#define  GPIO0_BASE	                0x44E07000
#define  UART0_BASE	                0x44E09000
#define  I2C0_BASE	                0x44E0B000
#define  ADC0_BASE	                0x44E0D000 //ADC0 Registers
#define  CONTROL_MODULE_BASE	    0x44E10000
#define  DMTIMER1_1MS_BASE	        0x44E31000
#define  WDT1_BASE	                0x44E35000
#define  RTCSS_BASE	                0x44E3E000
#define  DEBUGSS1_BASE	            0x44E40000 //Debug Registers
#define  SYNCTIMER_BASE	            0x44E86000
#define  L4_PER_AP_BASE	            0x48000000 //Address/Protection (AP)
#define  L4_PER_LA_BASE	            0x48000800 //Link Agent (LA)
#define  L4_PER_REG0_BASE	        0x48001000 //Initiator Port (IP0)
#define  L4_PER_REG1_BASE	        0x48001400 //Initiator Port (IP1)
#define  L4_PER_REG2_BASE	        0x48001800 //Initiator Port (IP2)
#define  L4_PER_REG3_BASE	        0x48001C00 //Initiator Port (IP3)
#define  UART1_BASE	                0x48022000
#define  UART2_BASE	                0x48024000
#define  I2C1_BASE	                0x4802A000
#define  MCSPI0_BASE	            0x48030000
#define  MCASP0_CFG_BASE	        0x48038000
#define  MCASP1_CFG_BASE	        0x4803C000
#define  DMTIMER2_BASE	            0x48040000
#define  DMTIMER3_BASE	            0x48042000
#define  DMTIMER4_BASE	            0x48044000
#define  DMTIMER5_BASE	            0x48046000
#define  DMTIMER6_BASE	            0x48048000
#define  DMTIMER7_BASE	            0x4804A000
#define  GPIO1_BASE	                0x4804C000
#define  MMCSD0_BASE	            0x48060000
#define  ELM_BASE	                0x48080000
#define  MAILBOX0_BASE	            0x480C8000
#define  SPINLOCK_BASE	            0x480CA000
#define  OCP_WP_NOC_BASE	        0x4818C000
#define  I2C2_BASE	                0x4819C000
#define  MCSPI1_BASE	            0x481A0000
#define  MCSPI2_BASE	            0x481A2000
#define  MCSPI3_BASE	            0x481A4000
#define  UART3_BASE	                0x481A6000
#define  UART4_BASE	                0x481A8000
#define  UART5_BASE	                0x481AA000
#define  GPIO2_BASE	                0x481AC000
#define  GPIO3_BASE	                0x481AE000
#define  DMTIMER8_BASE	            0x481C1000
#define  DCAN0_BASE	                0x481CC000
#define  DCAN1_BASE	                0x481D0000
#define  MMCSD1_BASE	            0x481D8000
#define  MPU_SCU_BASE	            0x48240000
#define  MPU_INTC_BASE	            0x48240100
#define  MPU_GBL_TIMER_BASE	        0x48240200
#define  MPU_PRV_TIMERS_BASE	    0x48240600
#define  MPU_INT_DIST_BASE	        0x48241000
#define  MPU_PL310_BASE	            0x48242000
#define  MPU_WAKEUP_GEN_BASE	    0x48281000
#define  MPU_AXI2OCP_BASE	        0x482A0000
#define  PWMSS0_BASE	            0x48300000
#define  PWMSS0_ECAP_BASE	        0x48300100
#define  PWMSS0_EQEP_BASE	        0x48300180
#define  PWMSS0_EPWM_BASE	        0x48300200
#define  PWMSS1_BASE	            0x48302000
#define  PWMSS1_ECAP_BASE	        0x48302100
#define  PWMSS1_EQEP_BASE	        0x48302180
#define  PWMSS1_EPWM_BASE	        0x48302200
#define  PWMSS2_BASE	            0x48304000
#define  PWMSS2_ECAP_BASE	        0x48304100
#define  PWMSS2_EQEP_BASE	        0x48304180
#define  PWMSS2_EPWM_BASE	        0x48304200
#define  PWMSS3_BASE	            0x48306000
#define  PWMSS3_EPWM_BASE	        0x48306200
#define  PWMSS4_BASE	            0x48308000
#define  PWMSS4_EPWM_BASE	        0x48308200
#define  PWMSS5_BASE	            0x4830A000
#define  PWMSS5_EPWM_BASE	        0x4830A200
#define  GPIO4_BASE	                0x48320000
#define  GPIO5_BASE	                0x48322000
#define  VPFE0_BASE	                0x48326000
#define  VPFE1_BASE	                0x48328000
#define  DSS_TOP_BASE	            0x4832A000
#define  DSS_DISPC_BASE	            0x4832A400
#define  DSS_RFBI_BASE	            0x4832A800
#define  DMTIMER9_BASE	            0x4833D000
#define  DMTIMER10_BASE	            0x4833F000
#define  DMTIMER11_BASE	            0x48341000
#define  MCSPI4_BASE	            0x48345000
#define  HDQ1W_BASE	                0x48347000
#define  ADC1_BASE	                0x4834C000 //ADC1 Registers
#define  USB0_CONTROL_BASE	        0x48380000
#define  USB0_PHY_BASE	            0x483A8000
#define  USB1_CONTROL_BASE	        0x483C0000
#define  USB1_PHY_BASE	            0x483E8000
#define  L4_FAST_AP_BASE	        0x4A000000 //Address/Protection(AP)
#define  L4_FAST_LA_BASE	        0x4A000800 //Link Agent(LA)
#define  L4_FAST_REG_BASE	        0x4A001000
#define  CPSW_BASE	                0x4A100000
#define  CPSW_PORT_BASE	            0x4A100100
#define  CPSW_CPDMA_BASE	        0x4A100800
#define  CPSW_STATS_BASE	        0x4A100900
#define  CPSW_STATERAM_BASE	        0x4A100A00
#define  CPSW_CPTS_BASE	            0x4A100C00
#define  CPSW_ALE_BASE	            0x4A100D00
#define  CPSW_SL1_BASE	            0x4A100D80
#define  CPSW_SL2_BASE	            0x4A100DC0
#define  CPSW_MDIO_BASE	            0x4A101000
#define  CPSW_WR_BASE	            0x4A101200
#define  CPSW_CPPI_RAM_BASE	        0x4A102000

#endif

