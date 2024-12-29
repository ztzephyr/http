/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-25
 * @brief       QSPI实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 M100Z-M7最小系统板STM32H750版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./USMART/usmart.h"
#include "./BSP/MPU/mpu.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/QSPI/qspi.h"
#include "./BSP/NORFLASH/norflash.h"
#include "./BSP/NORFLASH/norflash_ex.h"

/* 要写入到FLASH的字符串数组 */
const uint8_t g_text_buf[] = {"M100ZM7 STM32H7 QSPI TEST"};

/* 待写入NOR Flash数据的长度 */
#define TEXT_SIZE sizeof(g_text_buf)

int main(void)
{
    uint8_t key;
    uint16_t i = 0;
    uint8_t datatemp[TEXT_SIZE];
    uint32_t flashsize;
    uint16_t id = 0;
    
    sys_cache_enable();                 /* 打开L1-Cache */
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(240, 2, 2, 4); /* 配置系统时钟, 480Mhz */
    delay_init(480);                    /* 初始化延时功能 */
    usart_init(115200);                 /* 初始化串口 */
    usmart_dev.init(240);               /* 初始化USMART */
    mpu_memory_protection();            /* 保护相关存储区域 */
    led_init();                         /* 初始化LED */
    lcd_init();                         /* 初始化LCD */
    key_init();                         /* 初始化按键 */
    
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "QSPI TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "WK_UP:Write  KEY0:Read", RED);
    
    id = norflash_ex_read_id();                                                     /* 读取FLASH ID */
    
    while ((id == 0) || (id == 0xFFFF))                                             /* 检测不到FLASH芯片 */
    {
        lcd_show_string(30, 130, 200, 16, 16, "FLASH Check Failed!", RED);
        delay_ms(500);
        lcd_show_string(30, 130, 200, 16, 16, "Please Check!      ", RED);
        delay_ms(500);
        LED0_TOGGLE();
    }
    
    lcd_show_string(30, 130, 200, 16, 16, "QSPI FLASH Ready!", BLUE);
    flashsize = 16 * 1024 * 1024;                                                   /* FLASH 大小为16M字节 */
    
    while (1)
    {
        key = key_scan(0);
        
        if (key == WKUP_PRES)                                                       /* WK_UP按下,写入数据 */
        {
            lcd_fill(0, 150, 239, 319, WHITE);
            lcd_show_string(30, 150, 200, 16, 16, "Start Write FLASH....", BLUE);
            sprintf((char *)datatemp, "%s%d", (char *)g_text_buf, i);
            norflash_ex_write((uint8_t *)datatemp, flashsize - 100, TEXT_SIZE);     /* 从倒数第100个地址处开始,写入SIZE长度的数据 */
            lcd_show_string(30, 150, 200, 16, 16, "FLASH Write Finished!", BLUE);
        }
        
        if (key == KEY0_PRES)                                                       /* KEY0按下,读取字符串并显示 */
        {
            lcd_show_string(30, 150, 200, 16, 16, "Start Read FLASH... . ", BLUE);
            norflash_ex_read(datatemp, flashsize - 100, TEXT_SIZE);                 /* 从倒数第100个地址处开始,读出SIZE个字节 */
            lcd_show_string(30, 150, 200, 16, 16, "The Data Readed Is:   ", BLUE);
            lcd_show_string(30, 170, 200, 16, 16, (char *)datatemp, BLUE);
        }
        
        i++;
        
        if (i == 20)
        {
            LED0_TOGGLE();
            i = 0;
        }
        
        delay_ms(10);
    }
}
