
#include "uart.h"

void Test_Uart()
{
    uint8_t arr[] = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65};

    UART1_Init();
    UART1_SendBytes(arr, 10);
}