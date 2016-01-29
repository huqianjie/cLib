
#include "ringbuffer.h"

/**
  * @brief  ringbuffer��ʼ��
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
  * @brief  ��ȡringbufferδʹ�����ݵĻ�������С�ͻ�����ָ��
  * @param  arg1:ringbuffer  arg2:length
  * @retval ʧ�ܷ���NULL,�ɹ�����ringbufferδʹ�õĻ�������С�ͻ�����ָ��
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
  * @brief  ���ringbuffer��ǰslot��ʹ�û�������λ��
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
  * @brief  ��ringbuffer��ɾ�������ĵ�slot
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
  * @brief  ��ȡringbuffer��tail��д������ָ��
  * @param  arg1:ringbuffer
  * @retval ʧ�ܷ���NULL���ɹ�����ringbuffer��tail������
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
  * @brief  ��ringbuff��tail׷��length�����ݲ��������¸�slot
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







