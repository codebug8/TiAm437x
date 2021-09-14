#include "AM437X/AM437X_SOC.h"
#include "i2c.h"
#include "uart.h"
#include "printf.h"
#include "int.h" 
#include "delay.h" 

#ifdef GPIO_I2C

static void i2c_delay(volatile int time)
{
    time = time*1;//可用来调整传输速度
    for (; time > 0; time--);
}

 void SDA(char x)
{
	GPIO3->OE &= ~(0x01<<5);
		
    if(x) {
		GPIO3->DATAOUT |=  (0x01<<5);
    } 
    else {
		GPIO3->DATAOUT &= ~(0x01<<5);
    }     
}

 void SCL(char x)
{
	GPIO3->OE &= ~(0x01<<6);
	//GPIO3->SETDATAOUT |= (0x01<<6);

    if(x) {
        GPIO3->DATAOUT |=  (0x01<<6);
    } 
    else {
		GPIO3->DATAOUT &= ~(0x01<<6);
    }     
}

static char GET_SDA(void)
{
	GPIO3->OE |= (0x01<<5);
	
    return (GPIO3->DATAIN & (0x01<<5)?1:0);
}


void i2c_init(void)
{

    PRCM_CM_PER_GPIO3_CLKCTRL  |= (0x02<<0);

    //gpio3_5->I2C0_SDA;gpio3_6->I2C0_SCL;GPIO3_7->WP
	//CTRL_CONF_I2C0_SDA ;
	//CTRL_CONF_I2C0_SCL ;

	GPIO3->OE      &= ~(0x01<<7 | 0x01<<6 | 0x01<<5);
	GPIO3->DATAOUT |=  (0x01<<7 | 0x01<<6 | 0x01<<5);
}

void i2c_start(void)
{
    SCL(1);
    i2c_delay(1);
    
    SDA(1);
    i2c_delay(1);
    SDA(0);
    i2c_delay(1);
    
    SCL(0); 
    i2c_delay(1);
}

void i2c_stop(void)
{
    SDA(0);
    i2c_delay(1);
    
    SCL(1);
    i2c_delay(1);
    
    SDA(1);
    i2c_delay(1);
}


int i2c_ack(void)
{
    int pin_val;
      
    SCL(0);
    i2c_delay(1);
    
    SDA(1);
    i2c_delay(1);

	GET_SDA();//add
	
    SCL(1);
    i2c_delay(1);
    
    pin_val = GET_SDA();
    i2c_delay(1);
    
    SCL(0);
    i2c_delay(1);
   
    return pin_val;
}


void i2c_write(unsigned char data)
{
    int i = 0;
    
    for(i=0; i<8; i++) {
        SCL(0);
        i2c_delay(1);
        
        if(data & 0x80) SDA(1);
        else SDA(0);
        data = data<<1; 
        i2c_delay(1);
        
        SCL(1);
        i2c_delay(1);
    }
    SCL(0);
    i2c_delay(1);
}

unsigned char i2c_read(void)
{
    int i = 0;
    unsigned char data = 0;
    
    SCL(0);
    i2c_delay(1);
    SDA(1);
    GET_SDA();//add
	i2c_delay(1);
	
    for(i=0; i<8; i++) {
        SCL(1);
        i2c_delay(1);
        
        data = data<<1;
        if(GET_SDA()) data |= 0x01;
  
        SCL(0);
        i2c_delay(1);
    }
    
    SCL(1);//必须再给eeprom的ack提供一个时钟周期
    i2c_delay(1);
    SCL(0);
    i2c_delay(1);
    
    return data;
}

void eeprom_write_protect(char x)
{
	if(x)
		GPIO3->DATAOUT |=  (0x01<<7);
	else 
		GPIO3->DATAOUT &= ~(0x01<<7);
}

void eeprom_write(unsigned char addr, unsigned char data)
{
   eeprom_write_protect(0);

   i2c_start();
   
   i2c_write(0xA0);
   while(i2c_ack());
   
   i2c_write(addr>>8);//待确定
   while(i2c_ack());
   i2c_write(addr);
   while(i2c_ack());

   i2c_write(data);
   while(i2c_ack());
   
   i2c_stop();

   eeprom_write_protect(1);
}

unsigned char eeprom_read(unsigned char addr)
{
    unsigned char data = 0;
	
    eeprom_write_protect(0);
	
    i2c_start();
    
    i2c_write(0xA0);
    while(i2c_ack());
  
	i2c_write(addr>>8);//待确定
	while(i2c_ack());
	i2c_write(addr);
	while(i2c_ack());

    i2c_stop();
    
    i2c_delay(10);
    
    i2c_start();
    
    i2c_write(0xA1);
   	while(i2c_ack());

    data = i2c_read();
    
    i2c_stop();
	
	eeprom_write_protect(1);

	return data;
}

#endif








































#ifdef REG_I2C
volatile unsigned int flag = 1;

void i2c0_irq(void)
{
	unsigned int status = 0;
	//_100ask_printf("i2c0_irq.\n\r");
	
	
 	//Clear all enabled interrupt status except receive ready and transmit ready interrupt status 
	status = I2C0->IRQSTS;
	I2C0->IRQSTS = (status & (0x01<<3 | 0x01<<4));

	if(status & (0x01<<3))//接收数据
    {
   		//printf("irq3.\n\r");

		/* Clear receive ready interrupt status */	
		I2C0->IRQSTS |= (0x01<<3);

		 if(rCount == numOfBytes)
         {	
         	  /* Disable the receive ready interrupt */
              I2C0->IRQEN_CLR |= (0x01<<3);
              /* Generate a STOP */
              I2C0->CON |= (0x01<<1);  
         } 	 
		 else
		 {
			  /* Receive data from data receive register */
     		  //dataFromSlave[rCount++] = (unsigned char)I2C0->DATA;
     		  dataFromSlave[0] = I2C0->DATA;
			  rCount++;
		 }
	}

	if (status & (0x01<<4))//开始发送数据
    {
    	//printf("irq4.\n\r");
        /* Put data to data transmit register of i2c */
        I2C0->DATA = dataToSlave[tCount++];

        /* Clear Transmit interrupt status */
		I2C0->IRQSTS |= (0x01<<4);		 
						
         if(tCount == numOfBytes)
         {
              /* Disable the transmit ready interrupt */
              I2C0->IRQEN_CLR |= (0x01<<4);
         }

    }
        
    if (status & (0x01<<8))//总线空闲
    {
    	//printf("irq8.\n\r");
      	 /* Disable transmit data ready and receive data read interupt */
        I2C0->IRQEN_CLR |= (0x01<<4) | (0x01<<3) | (0x01<<8);

		flag = 0;
    }
   
    if(status & (0x01<<1))//没有响应
    {
		//printf("irq1.\n\r");
		I2C0->IRQEN_CLR |= (0x01<<4) | (0x01<<3) | (0x01<<8) | (0x01<<1);
        
         /* Generate a STOP */
         I2C0->CON |= (0x01<<1); 

         flag = 0;
    }
	
	//i2c_int_clear();
}



void eeprom_write_protect(char x)
{
	if(x)
		GPIO3->DATAOUT |=  (0x01<<7);
	else 
		GPIO3->DATAOUT &= ~(0x01<<7);
}

static unsigned int i2c_master_bus_busy(void)
{
	if(I2C0->IRQSTS_RAW & (0x01<<12))	
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


unsigned char eeprom_read(unsigned char addr)
{
	unsigned char data = 0;
	
	eeprom_write_protect(0);

    dataToSlave[0] = addr>>8;
    dataToSlave[1] = (addr & 0xFF);

    tCount = 0;
    rCount = 0;

    /* Data Count specifies the number of bytes to be transmitted */
    I2C0->CNT = 0x02;

	numOfBytes = I2C0->CNT;
	
	/* Clear status of all interrupts */
	//I2C0->IRQEN_SET =  0x6FFF;
	//I2C0->IRQSTS	=  0x6FFF;
	
	//I2C0->IRQEN_SET |=  0x6FFF;
	I2C0->IRQSTS	|=  0x7FFF;
	I2C0->IRQEN_CLR |=  0x6FFF;

	
	/* Configure I2C controller in Master Transmitter mode */
	I2C0->CON |= (0x01<<9 | 0x01<<10 | 0x01<<15); //MST=1  TRX=1  
	
	/* Transmit interrupt is enabled */
	I2C0->IRQEN_SET |= (0x01<<4);
	
	/* Generate Start Condition over I2C bus */
	I2C0->CON |= (0x01<<0);
	//while((I2C0->IRQSTS_RAW & (0x01<<12)));
	while(i2c_master_bus_busy() == 0);
	
	while(tCount != numOfBytes);//等待传输完成
	
	
	/* Wait untill I2C registers are ready to access */
	while(!(I2C0->IRQSTS_RAW & (0x01<<2)));


//----------------------------------------------------------------//
	//delay_ms(100);
	/* Data Count specifies the number of bytes to be received */
	I2C0->CNT = 0x01;
	
	numOfBytes = I2C0->CNT;
	
	//I2C0->IRQEN_SET =  0x6FFF;
	//I2C0->IRQSTS	=  0x6FFF;
	I2C0->IRQSTS	|=  0x7FFF;
	I2C0->IRQEN_CLR |=  0x6FFF;

		
	/* Configure I2C controller in Master Receiver mode */
	I2C0->CON |=  (0x01<<10 | (0x01<<15));	
	I2C0->CON &= ~(0x01<<9);
	
	/* Receive and Stop Condition Interrupts are enabled */
	I2C0->IRQEN_SET |= (0x01<<3 | 0x01<<8);
	
	/* Generate Start Condition over I2C bus */
	I2C0->CON |= (0x01<<0);

	//while((I2C0->IRQSTS_RAW & (0x01<<12)));
	while(i2c_master_bus_busy() == 0);


	while(rCount != numOfBytes);//等待传输完成



	/*for (i = 0; i < 10; i++ )
    {
         data[i] = dataFromSlave[i];
    }*/
	data = dataFromSlave[0];
	//debug_i2c("data");
	eeprom_write_protect(1);

	return data;
}


void eeprom_write(unsigned char addr, unsigned char data)
{	
	eeprom_write_protect(0);

    dataToSlave[0] = addr>>8;
    dataToSlave[1] = (addr & 0xFF);
	dataToSlave[2] = data;

    tCount = 0;

    /* Data Count specifies the number of bytes to be transmitted */
    I2C0->CNT = 0x03;
	numOfBytes = I2C0->CNT;
	/* Clear status of all interrupts */
	//I2C0->IRQEN_SET |=  0x7FFF;
	I2C0->IRQSTS	|=  0x7FFF;
	I2C0->IRQEN_CLR |=  0x7FFF;

	/* Configure I2C controller in Master Transmitter mode */
	I2C0->CON |= (0x01<<9 | 0x01<<10 | 0x01<<15); //MST=1  TRX=1  
	
	/* Transmit interrupt is enabled */
	I2C0->IRQEN_SET |= (0x01<<4);
	
	/* Generate Start Condition over I2C bus */
	I2C0->CON |= (0x01<<0);
	//while((I2C0->IRQSTS_RAW & (0x01<<12)));
	

	while(i2c_master_bus_busy() == 0);

	while(tCount != numOfBytes);//等待传输完成
	
	/* Generate a STOP */
	I2C0->CON |= (0x01<<1); 

	/* Wait untill I2C registers are ready to access */
	//while(!(I2C0->IRQSTS_RAW & (0x01<<2)));


//---------------------------------------------------------//


	eeprom_write_protect(1);

}


static void i2c_gpio_init(void)
{
	PRCM_CM_WKUP_I2C0_CLKCTRL |= (0x02<<0); //CP574
	PRCM_CM_WKUP_CLKSTCTRL    |= (0x01<<14);//CP569
	PRCM_CM_PER_L4LS_CLKSTCTRL|= (0x01<<27);

	PRCM_CM_PER_GPIO3_CLKCTRL  |= (0x02<<0);//to GPIO3_7->WP
	
	//gpio3_5->I2C0_SDA;gpio3_6->I2C0_SCL;GPIO3_7->WP

	CTRL_CONF_I2C0_SDA &= ~(0x07<<0 | 0x01<<16 | 0x01<<19);//CTRL_CONF_I2C0_SDA &= ~(0x07<<0)
	CTRL_CONF_I2C0_SCL &= ~(0x07<<0 | 0x01<<16 | 0x01<<19);
	//CTRL_CONF_EMU0
	GPIO3->OE      &= ~(0x01<<7);
	GPIO3->DATAOUT |=  (0x01<<7);
}


void i2c_init(void)
{
	i2c_gpio_init();

	register_irq(IRQ_I2C0, i2c0_irq);
	
	interrupt_init(IRQ_I2C0);

	
	I2C0->CON  &= ~(0x01<<15);//Controller in reset

	I2C0->SYSC &= ~(0x01<<0);//Auto Idle mechanism is disabled

	I2C0->PSC  = 3;//the module divided by (PSC + 1) -> 48M/(3+1)=12M

	I2C0->SCLL = 63;//tLOW = (SCLL + 7) * ICLK time period
	I2C0->SCLH = 65;//tHIGH = (SCLH + 5) * ICLK time period

	I2C0->SA = 0x50;//Slave address.//0x50?????

	I2C0->CON  |=  (0x01<<15);//Module enabled	
}



void debug_i2c(char *str)
{
	_100ask_printf("-------------------------%s---------------------------\r\n",str);
	//_100ask_printf("PRCM_CM_DPLL_CLKSEL_TIMER2_CLK= 0x%x\r\n",PRCM_CM_DPLL_CLKSEL_TIMER2_CLK);  
	//_100ask_printf("PRCM_CM_PER_TIMER2_CLKCTRL    = 0x%x\r\n",PRCM_CM_PER_TIMER2_CLKCTRL    );  
	//_100ask_printf("PRCM_CM_PER_L4LS_CLKSTCTRL    = 0x%x\r\n",PRCM_CM_PER_L4LS_CLKSTCTRL    ); 
    
    //_100ask_printf("CTRL_CONF_I2C0_SDA= 0x%x\r\n",CTRL_CONF_I2C0_SDA);
    //_100ask_printf("CTRL_CONF_I2C0_SCL= 0x%x\r\n",CTRL_CONF_I2C0_SCL);
    
	_100ask_printf("I2C0->REVNB_HI    = 0x%x\r\n",I2C0->REVNB_HI    );
	_100ask_printf("I2C0->REVNB_LO    = 0x%x\r\n",I2C0->REVNB_LO    );
	_100ask_printf("I2C0->REVNB_HI    = 0x%x\r\n",I2C0->REVNB_HI    );
	_100ask_printf("I2C0->SYSC        = 0x%x\r\n",I2C0->SYSC        );
	_100ask_printf("I2C0->IRQSTS_RAW  = 0x%x\r\n",I2C0->IRQSTS_RAW  );
	_100ask_printf("I2C0->IRQSTS      = 0x%x\r\n",I2C0->IRQSTS      );
	_100ask_printf("I2C0->IRQEN_SET   = 0x%x\r\n",I2C0->IRQEN_SET   );
	_100ask_printf("I2C0->IRQEN_CLR   = 0x%x\r\n",I2C0->IRQEN_CLR   );
	_100ask_printf("I2C0->WE          = 0x%x\r\n",I2C0->WE          );
	_100ask_printf("I2C0->DMARXEN_SET = 0x%x\r\n",I2C0->DMARXEN_SET );
	_100ask_printf("I2C0->DMATXEN_SET = 0x%x\r\n",I2C0->DMATXEN_SET );
	_100ask_printf("I2C0->DMARXEN_CLR = 0x%x\r\n",I2C0->DMARXEN_CLR );
	_100ask_printf("I2C0->DMATXEN_CLR = 0x%x\r\n",I2C0->DMATXEN_CLR );
	_100ask_printf("I2C0->DMARXWAKE_EN= 0x%x\r\n",I2C0->DMARXWAKE_EN);
	_100ask_printf("I2C0->DMATXWAKE_EN= 0x%x\r\n",I2C0->DMATXWAKE_EN);
	_100ask_printf("I2C0->SYSS        = 0x%x\r\n",I2C0->SYSS        );
	_100ask_printf("I2C0->BUF         = 0x%x\r\n",I2C0->BUF         );
	_100ask_printf("I2C0->CNT         = 0x%x\r\n",I2C0->CNT         );
	_100ask_printf("I2C0->DATA        = 0x%x\r\n",I2C0->DATA        );
	_100ask_printf("I2C0->CON         = 0x%x\r\n",I2C0->CON         );
	_100ask_printf("I2C0->OA          = 0x%x\r\n",I2C0->OA          );
	_100ask_printf("I2C0->SA          = 0x%x\r\n",I2C0->SA          );
	_100ask_printf("I2C0->PSC         = 0x%x\r\n",I2C0->PSC         );
	_100ask_printf("I2C0->SCLL        = 0x%x\r\n",I2C0->SCLL        );
	_100ask_printf("I2C0->SCLH        = 0x%x\r\n",I2C0->SCLH        );
	_100ask_printf("I2C0->SYSTEST     = 0x%x\r\n",I2C0->SYSTEST     );
	_100ask_printf("I2C0->BUFSTAT     = 0x%x\r\n",I2C0->BUFSTAT     );
	_100ask_printf("I2C0->OA1         = 0x%x\r\n",I2C0->OA1         );
	_100ask_printf("I2C0->OA2         = 0x%x\r\n",I2C0->OA2         );
	_100ask_printf("I2C0->OA3         = 0x%x\r\n",I2C0->OA3         );
	_100ask_printf("I2C0->ACTOA       = 0x%x\r\n",I2C0->ACTOA       );
	_100ask_printf("I2C0->SBLOCK      = 0x%x\r\n",I2C0->SBLOCK      ); 

	_100ask_printf("******************************************************\r\n");
}


#endif

