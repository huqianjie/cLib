
#ifndef __RING_BUFFER__H__
#define __RING_BUFFER__H__

#include <stdio.h>

#define RING_SLOTS          3
#define RING_DATA_SIZE      8192

#define RING_PARAM_PASS(x)  (void)x

typedef struct _bufent_t {
    char                buffer[RING_DATA_SIZE]; // ���ݻ�����
    char               *bufferPtr;              // ���ݻ�����ָ��
    int                 left;                   // ʣ��Ŀռ�
    struct _bufent_t   *next;                   // �¸��ڵ�
} BUFENT_T;

typedef struct _ringbuffer_t {
    BUFENT_T            slots[RING_SLOTS];
    BUFENT_T           *head;                   // ��ͷ��������
    BUFENT_T           *tail;                   // ��β��д����
    int                 used;                   // ��ʹ�õ�slot����
} RINGBUFFER_T;

/**
  * @brief  ringbuffer��ʼ��
  * @param  arg1:ringbuffer
  * @retval void
  */
void ringbuffer_init(RINGBUFFER_T *ringbuffer);

/**
  * @brief  ringbuffer��ǰ��С
  * @param  arg1:ringbuffer
  * @retval ���ص�ǰ��С
  */
static inline int ringbuffer_size(RINGBUFFER_T *ringbuffer)
{
    return ringbuffer->used;
}

/**
  * @brief  ringbuffer����
  * @param  arg1:ringbuffer
  * @retval ����ringbuffer����
  */
static inline int ringbuffer_capacity(RINGBUFFER_T *ringbuffer)
{
    RING_PARAM_PASS(ringbuffer);
    return RING_SLOTS;
}

/**
  * @brief  ringbuffer�Ƿ�Ϊ��
  * @param  arg1:ringbuffer
  * @retval 1Ϊ�գ�0Ϊ�ǿ�
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
  * @brief  ringbuffer�Ƿ�����
  * @param  arg1:ringbuffer
  * @retval 1Ϊ������0Ϊδ��
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
  * @brief  ��ȡringbufferδʹ�����ݵĻ�������С�ͻ�����ָ��
  * @param  arg1:ringbuffer  arg2:length
  * @retval ʧ�ܷ���NULL,�ɹ�����ringbufferδʹ�õĻ�������С�ͻ�����ָ��
  */
char *ringbuffer_read_next(RINGBUFFER_T *ringbuffer, int *length);

/**
  * @brief  ���ringbuffer��ǰslot��ʹ�û�������λ��
  * @param  arg1:ringbuffer  arg2:length
  * @retval void
  */
void ringbuffer_read_skip(RINGBUFFER_T *ringbuffer, int length);

/**
  * @brief  ��ringbuffer��ɾ�������ĵ�slot
  * @param  arg1:ringbuffer
  * @retval void
  */
void ringbuffer_read_pop(RINGBUFFER_T *ringbuffer);

/**
  * @brief  ��ȡringbuffer��tail��д������ָ��
  * @param  arg1:ringbuffer
  * @retval ʧ�ܷ���NULL���ɹ�����ringbuffer��tail������
  */
char *ringbuffer_write_ptr(RINGBUFFER_T *ringBuffer);

/**
  * @brief  ��ringbuff��tail׷��length�����ݲ��������¸�slot
  * @param  arg1:ringbuffer  arg2:length
  * @retval void
  */
void ringbuffer_write_append(RINGBUFFER_T *ringBuffer, int length);

#endif
