/**
 ****************************************************************************************************
 * @file        led.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-25
 * @brief       LED驱动代码
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

#include "./BSP/LED/led.h"

/**
 * @brief       初始化LED
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    /* 使能时钟 */
    LED0_GPIO_CLK_ENABLE();                             /* LED0时钟使能 */
    LED1_GPIO_CLK_ENABLE();                             /* LED1时钟使能 */
    
    /* 配置LED0引脚 */
    gpio_init_struct.Pin = LED0_GPIO_PIN;               /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;        /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;              /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);   /* 初始化LED0引脚 */
    
    /* 配置LED1引脚 */
    gpio_init_struct.Pin = LED1_GPIO_PIN;               /* LED1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;        /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;              /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* 高速 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);   /* 初始化LED1引脚 */
    
    /* 默认关闭所有LED */
    LED0(1);
    LED1(1);
}
