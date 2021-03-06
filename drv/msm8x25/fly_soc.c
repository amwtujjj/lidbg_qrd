/* Copyright (c) 2012, swlee
 *
 */


#include "lidbg.h"

#include "fly_soc.h"
#ifdef _LIGDBG_SHARE__
LIDBG_SHARE_DEFINE;
void *global_lidbg_devp;

#endif

//int fastboot_get_status(void);
//void fastboot_pwroff(void);

struct platform_device fly_soc_device =
{
    .name			= "fly_socs",
    .id 			= 0,
};



static int fly_soc_probe(struct platform_device *pdev)
{
    lidbg("fly_soc_probe\n");
    return 0;

}
static int fly_soc_remove(struct platform_device *pdev)
{
    lidbg("fly_soc_remove\n");
    return 0;

}
static int fly_soc_suspend(struct platform_device *pdev, pm_message_t state)
{
    lidbg("fly_soc_suspend\n");
    return 0;

}

static int fly_soc_resume(struct platform_device *pdev)
{
    lidbg("fly_soc_resume\n");
    return 0;

}

static struct platform_driver fly_soc_driver =
{
    .probe = fly_soc_probe,
    .remove = fly_soc_remove,
    .suspend =  fly_soc_suspend,
    .resume =  fly_soc_resume,
    .driver = {
        .name = "fly_socs",
        .owner = THIS_MODULE,
    },
};




bool SOC_IO_ISR_Add(u32 irq, u32  interrupt_type, pinterrupt_isr func, void *dev)
{
    bool ret = 0;
    struct io_int_config io_int_config1;

    io_int_config1.ext_int_num = MSM_GPIO_TO_INT(irq);
    io_int_config1.irqflags = interrupt_type;
    io_int_config1.pisr = func;
    io_int_config1.dev = dev;

    lidbg("ext_int_num:%d \n", irq);

    ret =  share_soc_io_irq(&io_int_config1);

    return ret;
}

bool SOC_IO_ISR_Enable(u32 irq)
{
    share_soc_irq_enable(MSM_GPIO_TO_INT(irq));

    return 1;

}


bool SOC_IO_ISR_Disable(u32 irq)
{
    share_soc_irq_disable(MSM_GPIO_TO_INT(irq));

    return 1;
}
bool SOC_IO_ISR_Del (u32 irq)
{

    free_irq(MSM_GPIO_TO_INT(irq), NULL);
    return 1;
}


bool SOC_IO_Config(u32 index, bool direction, u32 pull, u32 drive_strength)
{
    return share_soc_io_config( index,  direction, pull, drive_strength, 1);


}

void SOC_IO_Output_Ext(u32 group, u32 index, bool status, u32 pull, u32 drive_strength)
{
    share_soc_io_config( index,  GPIO_CFG_OUTPUT, pull, drive_strength, 1);
    share_soc_io_output( index,  status);

}



void SOC_IO_Output(u32 group, u32 index, bool status)
{
    share_soc_io_config( index,  GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA, 0);
    share_soc_io_output( index,  status);
}

bool SOC_IO_Input(u32 group, u32 index, u32 pull)
{
    share_soc_io_config( index,  GPIO_CFG_INPUT, pull/*GPIO_CFG_NO_PULL*/, GPIO_CFG_16MA, 0);
    return share_soc_io_input(index);
}



bool SOC_ADC_Get (u32 channel , u32 *value)
{

    *value = 0xffffffff;

    *value = share_soc_ad_read(channel);

    if(*value == 0xffffffff)
        return 0;

    return 1;
}


void SOC_Key_Report(u32 key_value, u32 type)
{
    share_lidbg_key_report(key_value, type);

}

// 7bit i2c sub_addr
int SOC_I2C_Send(int bus_id, char chip_addr, char *buf, unsigned int size)
{
    return  share_i2c_api_do_send( bus_id,  chip_addr,  0,  buf,  size);


}
int SOC_I2C_Rec(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size)
{
    return  share_i2c_api_do_recv( bus_id,  chip_addr,  sub_addr, buf,  size);


}



int SOC_I2C_Rec_2B_SubAddr(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size)

{
    return  share_i2c_api_do_recv_sub_addr_2bytes( bus_id,  chip_addr,  sub_addr, buf,  size);


}

int SOC_I2C_Rec_3B_SubAddr(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size)

{
    return  share_i2c_api_do_recv_sub_addr_3bytes( bus_id,  chip_addr,  sub_addr, buf,  size);


}

int SOC_I2C_Rec_Simple(int bus_id, char chip_addr, char *buf, unsigned int size)
{
    return  share_i2c_api_do_recv_no_sub_addr( bus_id,  chip_addr,  0, buf,  size);


}



int i2c_api_do_recv_SAF7741(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size);
int i2c_api_do_send_TEF7000(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size);
int i2c_api_do_recv_TEF7000(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size);

int SOC_I2C_Rec_SAF7741(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size)
{
    return  share_i2c_api_do_recv_SAF7741( bus_id,  chip_addr, sub_addr, buf,  size);


}

int SOC_I2C_Send_TEF7000(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size)
{
    return  share_i2c_api_do_send_TEF7000( bus_id,  chip_addr, sub_addr, buf,  size);


}

int SOC_I2C_Rec_TEF7000(int bus_id, char chip_addr, unsigned int sub_addr, char *buf, unsigned int size)
{
    return  share_i2c_api_do_recv_TEF7000( bus_id,  chip_addr, sub_addr, buf,  size);


}




void SOC_PWM_Set(int pwm_id, int duty_ns, int period_ns)
{

    share_soc_pwm_set(pwm_id, duty_ns, period_ns);

}




//0~255
int SOC_BL_Set( u32 bl_level)
{
    share_soc_bl_set(bl_level);

    return 1;

}

void SOC_Write_Servicer(int cmd)
{

    share_k2u_write(cmd);
}


void SOC_Log_Dump(int cmd)
{

    //share_k2u_write(cmd);
}


void SOC_Capts_Insmod(int cmd)
{

    share_k2u_write(cmd);
}

#if 0
void SOC_LED_Trigger()
{
    static int led_status = 0;
    if(led_status == 0)
    {
        LED_OFF;
        led_status = 1;
    }
    else
    {
        LED_ON;
        led_status = 0;
    }
}
#endif



int SOC_PWR_GetStatus(void)
{

    //return  (((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_PWR_GetStatus)();

}

void SOC_PWR_ShutDown(void)
{

    //fastboot_pwroff();
    //(((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_PWR_ShutDown)();
}



int SOC_Display_Get_Res(u32 *screen_x, u32 *screen_y)
{
#if 0
    u32 x, y;
    int ret = soc_get_screen_res(&x, &y);
    if(ret)
    {
        if(x == 1024 || x == 800)
        {
            *screen_x = x;
            *screen_y = y;

        }
    }
    return ret;
#else
    return share_soc_get_screen_res(screen_x, screen_y);

#endif
}


void SOC_Mic_Enable( bool enable)
{



}

static void set_func_tbl(void)
{
    //io
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_Output = SOC_IO_Output;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_Input = SOC_IO_Input;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_Output_Ext = SOC_IO_Output_Ext;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_Config = SOC_IO_Config;
    //i2c
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_I2C_Send = SOC_I2C_Send;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_I2C_Rec = SOC_I2C_Rec;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_I2C_Rec_Simple = SOC_I2C_Rec_Simple;

    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_I2C_Rec_SAF7741 = SOC_I2C_Rec_SAF7741;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_I2C_Send_TEF7000 = SOC_I2C_Send_TEF7000;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_I2C_Rec_TEF7000 = SOC_I2C_Rec_TEF7000;

    //io-irq
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_ISR_Add = SOC_IO_ISR_Add;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_ISR_Enable = SOC_IO_ISR_Enable;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_ISR_Disable = SOC_IO_ISR_Disable;
    ((struct lidbg_dev *)global_lidbg_devp)->soc_func_tbl.pfnSOC_IO_ISR_Del = SOC_IO_ISR_Del;

    //ad
    ((struct lidbg_dev *)global_lidbg_devp) ->soc_func_tbl.pfnSOC_ADC_Get = SOC_ADC_Get;

    //key
    ((struct lidbg_dev *)global_lidbg_devp) ->soc_func_tbl.pfnSOC_Key_Report = SOC_Key_Report;

    //bl
    ((struct lidbg_dev *)global_lidbg_devp) ->soc_func_tbl.pfnSOC_BL_Set = SOC_BL_Set;

    //
    ((struct lidbg_dev *)global_lidbg_devp) ->soc_func_tbl.pfnSOC_Write_Servicer = SOC_Write_Servicer;
    //video



    //display/touch
    ((struct lidbg_dev *)global_lidbg_devp) ->soc_func_tbl.pfnSOC_Display_Get_Res = SOC_Display_Get_Res;


    //mic
    ((struct lidbg_dev *)global_lidbg_devp) ->soc_func_tbl.pfnSOC_Mic_Enable = SOC_Mic_Enable;
}


int fly_soc_init(void)
{
    lidbg("fly_soc_init\n");
    DUMP_FUN;

#ifdef _LIGDBG_SHARE__
    LIDBG_SHARE_GET;
    global_lidbg_devp = plidbg_share->lidbg_devp;

#endif



    set_func_tbl();

    platform_device_register(&fly_soc_device);
    platform_driver_register(&fly_soc_driver);


    //  fly_devices_init();
    return 0;
}

void fly_soc_deinit(void)
{
    lidbg("fly_soc_deinit\n");

}




module_init(fly_soc_init);
module_exit(fly_soc_deinit);


EXPORT_SYMBOL(SOC_IO_ISR_Add);
EXPORT_SYMBOL(SOC_IO_ISR_Enable);
EXPORT_SYMBOL(SOC_IO_ISR_Disable);
EXPORT_SYMBOL(SOC_IO_ISR_Del);
EXPORT_SYMBOL(SOC_IO_Output);
EXPORT_SYMBOL(SOC_IO_Output_Ext);
EXPORT_SYMBOL(SOC_IO_Input);
EXPORT_SYMBOL(SOC_IO_Config);


EXPORT_SYMBOL(SOC_ADC_Get);
EXPORT_SYMBOL(SOC_Key_Report);
EXPORT_SYMBOL(SOC_I2C_Send);
EXPORT_SYMBOL(SOC_I2C_Rec);
EXPORT_SYMBOL(SOC_I2C_Rec_Simple);
EXPORT_SYMBOL(SOC_I2C_Rec_2B_SubAddr);
EXPORT_SYMBOL(SOC_I2C_Rec_3B_SubAddr);
EXPORT_SYMBOL(SOC_BL_Set);
EXPORT_SYMBOL(SOC_PWR_ShutDown);
EXPORT_SYMBOL(SOC_PWR_GetStatus);



EXPORT_SYMBOL(SOC_I2C_Rec_SAF7741);
EXPORT_SYMBOL(SOC_I2C_Send_TEF7000);
EXPORT_SYMBOL(SOC_I2C_Rec_TEF7000);
EXPORT_SYMBOL(SOC_Write_Servicer);
EXPORT_SYMBOL(SOC_Log_Dump);
EXPORT_SYMBOL(SOC_Capts_Insmod);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Flyaudad Inc.");

