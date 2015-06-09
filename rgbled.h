#ifndef __RGBLED_H__
#define __RGBLED_H__
#include <linux/types.h>
#include <linux/ioctl.h>
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define     RSTR    0x00
#define     GCR     0x01
#define     ISR     0x02
#define     CTR    0x30
#define     LCFG0   0x31
#define     LCFG1   0x32
#define     LCFG2   0x33
#define     PWM0    0x34
#define     PWM1    0x35
#define     PWM2    0x36
#define     LED0T0  0x37
#define     LED0T1  0x38
#define     LED0T2  0x39
#define     LED1T0  0x3A
#define     LED1T1  0x3B
#define     LED1T2  0x3C
#define     LED2T0  0x3D
#define     LED2T1  0x3E
#define     LED2T2  0x3F
#define     IADR    0x77

union lcfg{
    uint8_t value;
    struct{
        uint8_t    IMAX:2;
        uint8_t    BIT2_3:2;
        uint8_t    MD:1;
        uint8_t    FI:1;
        uint8_t    FO:1;
    }lcfg;
}__attribute__((packed));

union lctr{
    uint8_t value;
    struct{
        uint8_t    LED0:1;
        uint8_t    LED1:1;
        uint8_t    LED2:1;
    }lctr;
}__attribute__((packed));

union t1_t2{
    uint8_t   value;
    struct{
        uint8_t    T2:3;
        uint8_t    BIT3:1;
        uint8_t    T1:3;
    }t1_t2;
}__attribute__((packed));

union t3_t4{
    uint8_t value;
    struct{
        uint8_t    T4:3;
        uint8_t    BIT3:1;
        uint8_t    T3:3;
    }t3_t4;
}__attribute__((packed));

union t0{
    uint8_t   value;
    struct{
        uint8_t    REPEAT:4;
        uint8_t    T0:4;
    }t0;
}__attribute__((packed));


struct  ledcfg{
    union lcfg LCFG;
    union lctr LCTR;
    union t1_t2 T1_T2;
    union t3_t4 T3_T4;
    union t0   T0;
    uint8_t   r;
    uint8_t   g;
    uint8_t   b;
};

#define LED_IOC_MAGIC   'c'

#define RGB2LONG(r, g, b)   ((r << 16) | (g << 8) | b)
#define L2RED(l)            ((l >> 16) & 0xff)
#define L2GREEN(l)          ((l >> 8) & 0xff)
#define L2BLUE(l)           (l & 0xff)

#define LED_SET_RGB         _IOW(LED_IOC_MAGIC, 1, unsigned int)    //设置颜色值
#define LED_GET_RGB         _IOR(LED_IOC_MAGIC, 2, unsigned int)    //获取颜色值
#define LED_SET_FLICKER     _IOW(LED_IOC_MAGIC, 3, unsigned char)   //1打开闪烁,0关闭闪烁
#define LED_SET_BRIGHTNESS  _IOW(LED_IOC_MAGIC, 4, unsigned char)   //0:0mA 1:5mA 2:10mA 3:15mA  默认15mA
#define LED_GET_BRIGHTNESS  _IOR(LED_IOC_MAGIC, 5, unsigned char)   //获取最大亮度
#define LED_SET_FI          _IOW(LED_IOC_MAGIC, 6, unsigned char)   //1打开渐入, 0关闭渐进
#define LED_SET_FO          _IOW(LED_IOC_MAGIC, 7, unsigned char)   //1打开渐出
#define LED_SET_REPEAD      _IOW(LED_IOC_MAGIC, 8, unsigned char)   //设置呼吸重复次数 0用不停止
#define LED_SET_T0          _IOW(LED_IOC_MAGIC, 9, unsigned char)   //设置启动延时
#define LED_SET_T1          _IOW(LED_IOC_MAGIC, 10, unsigned char)  //设置渐进时间
#define LED_SET_T2          _IOW(LED_IOC_MAGIC, 11, unsigned char)  //最大亮度保持时间
#define LED_SET_T3          _IOW(LED_IOC_MAGIC, 12, unsigned char)  //设置渐出时间
#define LED_SET_T4          _IOW(LED_IOC_MAGIC, 13, unsigned char)  //设置灯灭保持时间
#define LED_SET_CFG         _IOW(LED_IOC_MAGIC, 14, struct ledcfg)  //直接写配置
#define LED_GET_CFG         _IOR(LED_IOC_MAGIC, 15, struct ledcfg)  //读取当前配置
#define LED_SET_WORK        _IOW(LED_IOC_MAGIC, 16, struct ledcfg)  //设置一个工作
#endif
