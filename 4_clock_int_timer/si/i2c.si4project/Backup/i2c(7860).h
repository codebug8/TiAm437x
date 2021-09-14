
#ifndef  __I2C_H__
#define  __I2C_H__

void i2c_start(void);
void i2c_stop(void);

//#define GPIO_I2C
#define REG_I2C

#ifdef GPIO_I2C
extern void i2c_init(void);
extern void eeprom_write(unsigned char addr, unsigned char data);
extern unsigned char eeprom_read(unsigned char addr);
#endif


#ifdef REG_I2C
volatile unsigned int tCount;
volatile unsigned int rCount;

volatile unsigned int numOfBytes;
volatile unsigned char dataToSlave[5];
volatile unsigned char dataFromSlave[5];

extern void i2c_init(void);
extern unsigned char eeprom_read(unsigned char addr);
extern void eeprom_write(unsigned char addr, unsigned char data);
extern void debug_i2c(char *str);

#endif


#endif



