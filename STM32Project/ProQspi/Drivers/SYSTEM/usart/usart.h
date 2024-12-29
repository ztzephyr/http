/**
 ****************************************************************************************************
 * @file        usart.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-25
 * @brief       串口初始化代码(一般是串口1)，支持printf
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

#ifndef _USART_H
#define _USART_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

/* 引脚和串口定义 */
#define USART_TX_GPIO_PORT          GPIOA
#define USART_TX_GPIO_PIN           GPIO_PIN_9
#define USART_TX_GPIO_AF            GPIO_AF7_USART1
#define USART_TX_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* 发送引脚时钟使能 */

#define USART_RX_GPIO_PORT          GPIOA
#define USART_RX_GPIO_PIN           GPIO_PIN_10
#define USART_RX_GPIO_AF            GPIO_AF7_USART1
#define USART_RX_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* 接收引脚时钟使能 */

#define USART_UX                    USART1
#define USART_UX_IRQn               USART1_IRQn
#define USART_UX_IRQHandler         USART1_IRQHandler
#define USART_UX_CLK_ENABLE()       do{ __HAL_RCC_USART1_CLK_ENABLE(); }while(0)    /* USART1 时钟使能 */

/* 串口接收相关定义 */
#define USART_REC_LEN               200                                             /* 定义最大接收200字节数据 */
#define USART_EN_RX                 1                                               /* 使能串口接收 */
#define RXBUFFERSIZE                1                                               /* 缓存大小 */

/* 导出相关变量 */
extern UART_HandleTypeDef g_uart1_handle;                                           /* UART句柄 */
extern uint8_t  g_usart_rx_buf[USART_REC_LEN];                                      /* 串口缓冲区 */
extern uint16_t g_usart_rx_sta;                                                     /* 串口接收状态 */
extern uint8_t g_rx_buffer[RXBUFFERSIZE];                                           /* HAL库USART接收Buffer */

/* 函数声明 */
void usart_init(uint32_t baudrate);                                                 /* 初始化串口 */

#endif
