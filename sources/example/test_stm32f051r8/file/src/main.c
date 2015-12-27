#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "task_add.h"
#include <task.h>
#include <mutex.h>
#include <delay.h>


//------------------------------------------------------
//  Инициализация скорости работы МК
//------------------------------------------------------
void Oscillator_int(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
}


//------------------------------------------------------
//  Инициализация
//------------------------------------------------------
void Init_Hardware(void)
{
    Oscillator_int();
    Port_Init();
    __enable_irq();
}

int main(void)
{
    //  Инициализация
    Init_Hardware();

    eMutex_Create(&MutexA);

    eTask_Init(task, 2);

    eStart_Schedule();

    while(1) {

    }
}
