/**
 ****************************************************************************************************
 * @file        key.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-25
 * @brief       按键驱动代码
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

#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"

/* 引脚定义 */
#define KEY0_GPIO_PORT          GPIOA
#define KEY0_GPIO_PIN           GPIO_PIN_15
#define KEY0_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define WKUP_GPIO_PORT          GPIOA
#define WKUP_GPIO_PIN           GPIO_PIN_0
#define WKUP_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

/* IO操作 */
#define KEY0                    HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)
#define WK_UP                   HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN)

/* 按键按下定义 */
#define KEY0_PRES               1    /* KEY0按下 */
#define WKUP_PRES               2    /* KEY_UP按下(即WK_UP) */

/* 函数声明 */
void key_init(void);                 /* 按键初始化函数 */
uint8_t key_scan(uint8_t mode);      /* 按键扫描函数 */

#endif
