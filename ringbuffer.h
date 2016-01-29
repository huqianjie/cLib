
#ifndef __RING_BUFFER__H__
#define __RING_BUFFER__H__

#include <stdio.h>

#define RING_SLOTS          3
#define RING_DATA_SIZE      8192

#define RING_PARAM_PASS(x)  (void)x

typedef struct _bufent_t {
    char                buffer[RING_DATA_SIZE]; // 数据缓存区
    char               *bufferPtr;              // 数据缓存区指针
    int                 left;                   // 剩余的空间
    struct _bufent_t   *next;                   // 下个节点
} BUFENT_T;

typedef struct _ringbuffer_t {
    BUFENT_T            slots[RING_SLOTS];
    BUFENT_T           *head;                   // 从头部读数据
    BUFENT_T           *tail;                   // 从尾部写数据
    int                 used;                   // 被使用的slot个数
} RINGBUFFER_T;

/**
  * @brief  ringbuffer初始化
  * @param  arg1:ringbuffer
  * @retval void
  */
void ringbuffer_init(RINGBUFFER_T *ringbuffer);

/**
  * @brief  ringbuffer当前大小
  * @param  arg1:ringbuffer
  * @retval 返回当前大小
  */
static inline int ringbuffer_size(RINGBUFFER_T *ringbuffer)
{
    return ringbuffer->used;
}

/**
  * @brief  ringbuffer容量
  * @param  arg1:ringbuffer
  * @retval 返回ringbuffer容量
  */
static inline int ringbuffer_capacity(RINGBUFFER_T *ringbuffer)
{
    RING_PARAM_PASS(ringbuffer);
    return RING_SLOTS;
}

/**
  * @brief  ringbuffer是否为空
  * @param  arg1:ringbuffer
  * @retval 1为空，0为非空
  */
static inline int ringbuffer_is_empty(RINGBUFFER_T *ringbuffer)
{
    if (ringbuffer->used == 0)
    {
        return 1;
    }

    return 0;
}

/**
  * @brief  ringbuffer是否已满
  * @param  arg1:ringbuffer
  * @retval 1为已满，0为未满
  */
static inline int  ringbuffer_is_full(RINGBUFFER_T *ringbuffer)
{
    if (ringbuffer->used == RING_SLOTS)
    {
        return 1;
    }

    return 0;
}

/**
  * @brief  获取ringbuffer未使用数据的缓存区大小和缓存区指针
  * @param  arg1:ringbuffer  arg2:length
  * @retval 失败返回NULL,成功返回ringbuffer未使用的缓存区大小和缓存区指针
  */
char *ringbuffer_read_next(RINGBUFFER_T *ringbuffer, int *length);

/**
  * @brief  标记ringbuffer当前slot已使用缓存区的位置
  * @param  arg1:ringbuffer  arg2:length
  * @retval void
  */
void ringbuffer_read_skip(RINGBUFFER_T *ringbuffer, int length);

/**
  * @brief  从ringbuffer中删除已消耗的slot
  * @param  arg1:ringbuffer
  * @retval void
  */
void ringbuffer_read_pop(RINGBUFFER_T *ringbuffer);

/**
  * @brief  获取ringbuffer的tail的写缓存区指针
  * @param  arg1:ringbuffer
  * @retval 失败返回NULL，成功返回ringbuffer的tail缓存区
  */
char *ringbuffer_write_ptr(RINGBUFFER_T *ringBuffer);

/**
  * @brief  在ringbuff的tail追加length个数据并且移至下个slot
  * @param  arg1:ringbuffer  arg2:length
  * @retval void
  */
void ringbuffer_write_append(RINGBUFFER_T *ringBuffer, int length);

#endif
