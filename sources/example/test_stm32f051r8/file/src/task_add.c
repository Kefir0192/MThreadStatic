#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "task_add.h"
#include <task.h>
#include <mutex.h>
#include <delay.h>


struct Mmutex MutexA;

uint32_t stack_a[64];
uint32_t stack_b[64];

uint32_t vA = 5, vB;

void Thread_A(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);
        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_8;

        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_8;

        eMutex_unlock(&MutexA);
    }
}

void Thread_B(void *pVoid)
{
    while(1) {
        eMutex_lock(&MutexA);

        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_9;

        Delay(0x10000);
        Delay(0x10000);
        Delay(0x10000);
        GPIOC->ODR ^= GPIO_ODR_9;

        eMutex_unlock(&MutexA);
    }
}

/// Массив структур для каждой задачи
struct task_add task[] = {
    {Thread_A, &vA, &stack_a[63]},
    {Thread_B, &vB, &stack_b[63]},
};
