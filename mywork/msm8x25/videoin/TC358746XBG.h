#ifndef __SOC_TC358746XBG__
#define __SOC_TC358746XBG__
#include "tw9912.h"
#include "i2c_io.h"

#define DISABLE 0
#define ENABLE 1

#define TC358746XBG_BLACK 1
#define TC358746XBG_BLUE 2
#define TC358746XBG_RED 3
#define TC358746XBG_PINK 4
#define TC358746XBG_GREEN 5
#define TC358746XBG_LIGHT_BLUE 6
#define TC358746XBG_YELLOW 7
#define TC358746XBG_WHITE 8

struct TC358_register_struct
{
    u16 add_reg;
    u32 add_val;
    u8 registet_width;
};
struct TC358_register_struct_read
{
    u16 add_reg;
    u8 registet_width;
};

//#ifdef DFLY_DEBUG
#define DEBUG_TC358
//#define tc358746_debug
//#endif

#ifdef BOARD_V2
#define TC358746XBG_RESET 33
#else//BOARD_V1
#define TC358746XBG_RESET 28
#endif
#define register_value_width_32 32
#define register_value_width_16 16
#define TC358746_I2C_ChipAdd 0x07
#if 0
#define tc358746_dbg(msg...)  do { printk( KERN_CRIT "TC358746: " msg); }while(0)
#else
#define tc358746_dbg(msg...)  do {}while(0)
#endif
#if 0
#define Video_RESX_UP do{i2c_io_config( 43,  GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_16MA,0);gpio_set_value(43, 1);}while(0)
#define Video_RESX_DOWN do{i2c_io_config( 43,  GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_16MA,0);gpio_set_value(43,0);}while(0)//tp0707 reset output, active low 
#else
#define Video_RESX_UP do{}while(0)
#define Video_RESX_DOWN do{}while(0)
#endif
#if 0
#define tc358_RESX_UP do{SOC_IO_Config(34,GPIO_CFG_OUTPUT,GPIO_CFG_PULL_UP,GPIO_CFG_12MA);SOC_IO_Output(0, 34, 1);}while(0)
#define tc358_RESX_DOWN do{SOC_IO_Config(34,GPIO_CFG_OUTPUT,GPIO_CFG_PULL_UP,GPIO_CFG_12MA);SOC_IO_Output(0, 34, 0);}while(0)//System reset input, active low 
#else
#if 1
#define tc358_RESX_UP do{i2c_io_config(TC358746XBG_RESET,GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_16MA,0);gpio_set_value(TC358746XBG_RESET, 0);}while(0)
#define tc358_RESX_DOWN do{i2c_io_config(TC358746XBG_RESET,GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_16MA,0);gpio_set_value(TC358746XBG_RESET, 1);}while(0)
#else
#define tc358_RESX_UP do{}while(0)
#define tc358_RESX_DOWN do{}while(0)
#endif

#endif
#if 0
#define RTC358_CS_UP do{SOC_IO_Config(33,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_12MA);SOC_IO_Output(0, 33, 1);}while(0)
#define RTC358_CS_DOWN	 do{SOC_IO_Config(33,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_12MA);SOC_IO_Output(0, 33, 0);}while(0)	 //Chip Select, active low
#else
#define RTC358_CS_UP do{}while(0)
#define RTC358_CS_DOWN	 do{}while(0)	 //Chip Select, active low
#endif

#define tc358_MSEL_UP do{}while(0)//	do{SOC_IO_Config(34,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_12MA);SOC_IO_Output(0, 34, 1);}while(0)// 1: Par_in -> CSI-2 TX
#define tc358_MSEL_DOWN do{}while(0)//do{SOC_IO_Config(34,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_12MA);SOC_IO_Output(0, 34, 0);}while(0)
void TC358_init(Vedio_Format);
void TC358_Hardware_Rest(void);

i2c_ack TC358_Register_Write(u16 *add, u32 *valu, u8 flag);
i2c_ack TC358_Register_Read(u16 add, char *buf, u8 flag);

void TC358_data_output_enable(u8 flag);
//void TC358_exit( void );
#endif
