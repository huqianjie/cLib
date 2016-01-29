
#include "ringbuffer.h"

/**
  * @brief  ringbuffer初始化
  * @param  arg1:ringbuffer
  * @retval void
  */
void ringbuffer_init(RINGBUFFER_T *ringbuffer)
{
    int index;

    ringbuffer->head = &ringbuffer->slots[0];
    ringbuffer->tail = &ringbuffer->slots[0];
    ringbuffer->used = 0;

    for (index=0; index<RING_SLOTS; index++)
    {
        ringbuffer->slots[index].next = &(ringbuffer->slots[(index + 1) % RING_SLOTS]);
    }
}

/**
  * @brief  获取ringbuffer未使用数据的缓存区大小和缓存区指针
  * @param  arg1:ringbuffer  arg2:length
  * @retval 失败返回NULL,成功返回ringbuffer未使用的缓存区大小和缓存区指针
  */
char *ringbuffer_read_next(RINGBUFFER_T *ringbuffer, int *length)
{
    if (ringbuffer->used == 0)
    {
        return NULL;
    }

    *length = ringbuffer->head->left;
    return ringbuffer->head->bufferPtr;
}

/**
  * @brief  标记ringbuffer当前slot已使用缓存区的位置
  * @param  arg1:ringbuffer  arg2:length
  * @retval void
  */
void ringbuffer_read_skip(RINGBUFFER_T *ringbuffer, int length)
{
    if (ringbuffer->used == 0)
    {
        return;
    }

    ringbuffer->head->bufferPtr += length;
    ringbuffer->head->left -= length;
}

/**
  * @brief  从ringbuffer中删除已消耗的slot
  * @param  arg1:ringbuffer
  * @retval void
  */
void ringbuffer_read_pop(RINGBUFFER_T *ringbuffer)
{
    if (ringbuffer->used == 0)
    {
        return;
    }

    ringbuffer->head = ringbuffer->head->next;
    ringbuffer->used--;
}

/**
  * @brief  获取ringbuffer的tail的写缓存区指针
  * @param  arg1:ringbuffer
  * @retval 失败返回NULL，成功返回ringbuffer的tail缓存区
  */
char *ringbuffer_write_ptr(RINGBUFFER_T *ringBuffer)
{
    if (ringBuffer->used >= RING_SLOTS)
    {
        return NULL;
    }

    return ringBuffer->tail->buffer;
}

/**
  * @brief  在ringbuff的tail追加length个数据并且移至下个slot
  * @param  arg1:ringbuffer  arg2:length
  * @retval void
  */
void ringbuffer_write_append(RINGBUFFER_T *ringBuffer, int length)
{
    if (ringBuffer->used >= RING_SLOTS)
    {
        return;
    }

    ringBuffer->used++;
    ringBuffer->tail->bufferPtr = ringBuffer->tail->buffer;
    ringBuffer->tail->left = length;
    ringBuffer->tail = ringBuffer->tail->next;
}







