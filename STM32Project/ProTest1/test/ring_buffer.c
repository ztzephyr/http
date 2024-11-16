#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 10          // 缓冲区的最大数据组数
#define DATA_SIZE 160           // 每组数据的字节数

typedef struct {
    uint8_t Data[BUFFER_SIZE][DATA_SIZE]; // 存储实际数据的二维数组
    uint32_t WriteIndex;                  // 写指针，指向写入位置
    uint32_t ReadIndex;                   // 读指针，指向读取位置
    uint32_t ItemCount;                   // 当前存储的数据组数
} RingBuffer;

// 初始化环形缓冲区
void RingBuffer_Init(RingBuffer *pBuf) {
    pBuf->WriteIndex = 0;
    pBuf->ReadIndex = 0;
    pBuf->ItemCount = 0;
}

// 检查缓冲区是否为空
bool RingBuffer_IsEmpty(RingBuffer *pBuf) {
    return pBuf->ItemCount == 0;
}

// 添加数据到缓冲区
void RingBuffer_AddData(RingBuffer *pBuf, const uint8_t *Data) {
    if (pBuf->ItemCount == BUFFER_SIZE) {
        // 如果缓冲区已满，则丢弃最早的数据，前移读指针
        pBuf->ReadIndex = (pBuf->ReadIndex + 1) % BUFFER_SIZE;
    } else {
        pBuf->ItemCount++; // 增加数据组数，仅当缓冲区未满时
    }

    // 将数据复制到当前写指针位置
    memcpy(pBuf->Data[pBuf->WriteIndex], Data, DATA_SIZE);

    // 更新写指针位置
    pBuf->WriteIndex = (pBuf->WriteIndex + 1) % BUFFER_SIZE;
}

// 从缓冲区读取数据
bool RingBuffer_ReadData(RingBuffer *pBuf, uint8_t *dataOut) {
    if (RingBuffer_IsEmpty(pBuf)) {
        return false; // 缓冲区为空，无法读取数据
    }

    // 从当前读指针位置复制数据
    memcpy(dataOut, pBuf->Data[pBuf->ReadIndex], DATA_SIZE);

    // 更新读指针位置
    pBuf->ReadIndex = (pBuf->ReadIndex + 1) % BUFFER_SIZE;
    pBuf->ItemCount--;

    return true; // 成功读取数据
}


volatile uint8_t spiReceiveBuffer[DATA_SIZE]; // SPI 数据接收缓冲区
volatile uint32_t spiReceivedBytes = 0;       // 当前接收的字节计数

// SPI 接收中断处理函数
void SPI_IRQHandler(void) {
    uint8_t receivedByte = SPI_ReadData(); // 假设有 SPI 数据读取函数
    spiReceiveBuffer[spiReceivedBytes++] = receivedByte;

    // 检查是否收到了 160 字节
    if (spiReceivedBytes == DATA_SIZE) {
        RingBuffer_AddData(&gRingBuffer, spiReceiveBuffer);
        spiReceivedBytes = 0; // 重置字节计数器
    }
}