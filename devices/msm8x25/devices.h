

#ifndef _DEV_SOC__
#define _DEV_SOC__


#define DEBUG_LED
#define DEBUG_UMOUNT_USB

void lidbg_device_main(int argc, char **argv);



struct platform_devices_resource
{

    unsigned int led_gpio;

};


enum
{
    PLATFORM_SKU7,
    PLATFORM_SKU5,
    PLATFORM_FLY,
};

//up always online


//#define SOC_VIN_DETECT
//#define DEBUG_POWER_KEY
//#define DEBUG_POWER_UP


#ifdef BOARD_V1
#define GPIO_USB_ID (34)
#define GPIO_LED_FLY (33)


//LCD_IDLE,  PANNE_PEN , PWM
#define LCD_ON  do{       SOC_IO_Output(0, GPIO_LCD1, 1);\
    					    SOC_IO_Output(0, GPIO_LCD2, 1);\
    					    SOC_IO_Output(0, GPIO_LCD3, 1);\
				}while(0)
#define LCD_OFF  do{       SOC_IO_Output(0, GPIO_LCD1, 0);\
    					    SOC_IO_Output(0, GPIO_LCD2, 0);\
    					    SOC_IO_Output(0, GPIO_LCD3, 0);\
				}while(0)

#define USB_HUB_ENABLE  do{SOC_IO_Config(GPIO_USB_HUB,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_HUB, 1); }while(0)
#define USB_HUB_DISABLE do{SOC_IO_Config(GPIO_USB_HUB,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_HUB, 0); }while(0)

#define USB_SWITCH_DISCONNECT   do{SOC_IO_Config(GPIO_USB_SWITCH,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_SWITCH, 1); }while(0)
#define USB_SWITCH_CONNECT  do{SOC_IO_Config(GPIO_USB_SWITCH,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_SWITCH, 0); }while(0)


#endif




#ifdef BOARD_V2
#define GPIO_USB_ID (81)
#define GPIO_LED_FLY (82)

//LCD_IDLE,  PANNE_PEN , PWM
#define LCD_ON  do{       SOC_IO_Output(0, GPIO_LCD1, 1);\
    					    SOC_IO_Output(0, GPIO_LCD3, 0);\
				}while(0)
#define LCD_OFF  do{       SOC_IO_Output(0, GPIO_LCD1, 0);\
    					    SOC_IO_Output(0, GPIO_LCD3, 1);\
				}while(0)

#define USB_HUB_ENABLE  do{SOC_IO_Config(GPIO_USB_HUB,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_HUB, 0); }while(0)
#define USB_HUB_DISABLE do{SOC_IO_Config(GPIO_USB_HUB,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_HUB, 1); }while(0)

#define USB_SWITCH_DISCONNECT   do{SOC_IO_Config(GPIO_USB_SWITCH,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_SWITCH, 0); }while(0)
#define USB_SWITCH_CONNECT  do{SOC_IO_Config(GPIO_USB_SWITCH,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_USB_SWITCH, 1); }while(0)

#endif



#ifdef FLY_DEBUG
#define DEBUG_AD_KEY
#define DEBUG_BUTTON


#define DVD_RESET_HIGH  do{SOC_IO_Output(0, GPIO_DVD_RESET, 1); }while(0)
#define DVD_RESET_LOW   do{SOC_IO_Output(0, GPIO_DVD_RESET, 0); }while(0)
#define DVD_RESET  do{    DVD_RESET_LOW; \
    							msleep(100); \
    							DVD_RESET_HIGH;\
    							}while(0)


#define BL_SET(x) SOC_BL_Set(x)





#else
//#define LCD_ON
//#define LCD_OFF
#define DVD_RESET_HIGH
#define DVD_RESET_LOW
#define DVD_RESET
#define BL_SET(x)


#endif


//led
#define LED_ON  do{/*SOC_IO_Config(devices_resource.led_gpio,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);*/SOC_IO_Output(0, devices_resource.led_gpio, 0); }while(0)
#define LED_OFF  do{/*SOC_IO_Config(devices_resource.led_gpio,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);*/SOC_IO_Output(0, devices_resource.led_gpio, 1); }while(0)

#define GPIO_LED_SKU7 (108)

#define GPIO_NULL GPIO_LED_FLY

#define GPIO_DVD_RESET  (109)

#define GPIO_LCD1  (31)
#define GPIO_LCD2  (96)
//becauseof i can't catch the msg ,so i do with it on the way below;
#ifdef FLY_DEBUG
	#define GPIO_LCD3  (97)
#else
	#define GPIO_LCD3  (82) 
#endif

#define GPIO_PWR_EN (23)
#define GPIO_USB_HUB  (35)
#define GPIO_USB_SWITCH  (15)

//pwr_key
#define PWR_SLEEP_PORT   (MCU_IIC_REQ_I)
#define PWR_SLEEP_INDEX  (MCU_IIC_REQ_I)
#define PWR_SLEEP_TEST_TIME_DELAY   (20*1000)
#define PWR_SLEEP_PORT_POLLING_TIME   (1000)

//ad
#define AD_KEY_PORT   (0xff)
#define AD_KEY_READ_POLLING_TIME   (100)
#define USB_REC_POLLING_TIME (300)



#define BUTTON_LEFT_1 (76)//k4
#define BUTTON_LEFT_2 (58)//k3

#define BUTTON_RIGHT_1 (44)//k1
#define BUTTON_RIGHT_2 (49)//k2

#define  MCU_IIC_REQ_ISR  (30)


#define BL_MAX (255)


#if 0//def FLY_DEBUG
//sku7: find <4> i2c_devices:0xe, 0x18, 0x1c, 0x2c
#define PLATFORM_GET do{ \
						u8 i2c_devices_found[32],i; \
						memset(i2c_devices_found,0,32);\
						i2c_devices_probe(1,i2c_devices_found);\
						platform_id = PLATFORM_FLY;\
						for(i=0;i<32;i++)\
						{\
							if(i2c_devices_found[i] == 0xe)\
							{\
								platform_id = PLATFORM_SKU7;\
								break;\
							}\
						}\
					}while(0)


#else
#define PLATFORM_GET do{platform_id=PLATFORM_FLY;}while(0)
#endif


#define PWR_EN_ON   do{SOC_IO_Config(GPIO_PWR_EN,GPIO_CFG_OUTPUT,GPIO_CFG_PULL_UP,GPIO_CFG_16MA);SOC_IO_Output(0, GPIO_PWR_EN, 1); }while(0)
#define PWR_EN_OFF  do{SOC_IO_Config(GPIO_PWR_EN,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_8MA);SOC_IO_Output(0, GPIO_PWR_EN, 0); }while(0)


#define USB_ID_HIGH_DEV do{\
								SOC_IO_Config(GPIO_USB_ID,GPIO_CFG_INPUT,GPIO_CFG_PULL_UP,GPIO_CFG_8MA);\
								SOC_IO_Input(0,GPIO_USB_ID,GPIO_CFG_PULL_UP);\
							}while(0)
#define USB_ID_LOW_HOST do{  \
								SOC_IO_Config(GPIO_USB_ID,GPIO_CFG_OUTPUT,GPIO_CFG_NO_PULL,GPIO_CFG_16MA);\
								SOC_IO_Output(0, GPIO_USB_ID, 0);\
							}while(0)





#define USB_HUB_RST do{USB_HUB_DISABLE;msleep(500);USB_HUB_ENABLE;}while(0);




#define  MCU_IIC_REQ_I (30)
#define  MCU_SUSPEND_FLAG (29)

//lidbg("tell lpc power off ok!#\n");
#define TELL_LPC_PWR_OFF
							
//lidbg("tell lpc power on ok!#\n");
#define TELL_LPC_PWR_ON do{\
								SOC_IO_Input(0,MCU_IIC_REQ_I,GPIO_CFG_PULL_UP);\
							}while(0)


#define USB_WORK_ENABLE do{\
				lidbg("USB_WORK_ENABLE\n");\
    			USB_ID_LOW_HOST;\
    			USB_SWITCH_CONNECT;\
    			USB_HUB_RST;\
			}while(0)				
							


#define USB_WORK_DISENABLE  do{\
			lidbg("USB_WORK_DISENABLE\n");\
			USB_HUB_DISABLE;\
			msleep(100);\
			USB_SWITCH_DISCONNECT;\
			USB_ID_LOW_HOST;\
	}while(0)







#endif
