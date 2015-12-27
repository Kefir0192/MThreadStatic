#include <portmacro.h>
#include <task.h>
#include <task_switch.h>

/// Указатель на переменную в которую нужно сохранить текущие положение стека
uint32_t **pPointer_Save_Context_Stask;
/// Указатель на переменную которая ссылается на указатель стека для загрузки
uint32_t **pPointer_Load_Context_Stask;

/// Статусная структура всех задач
struct Task_Status sTask_Status;

//------------------------------------------------------
// task_add         Указатель на массив структур для каждой задачи
// task_num         Всего задач
//------------------------------------------------------
void eTask_Init(struct task_add *ptask_add, uint8_t task_num)
{
    if(!ptask_add) return;

    for(uint8_t counter = 0; counter < task_num; counter++) {
        ptask_add[counter].task_element.pTask_Descriptor = (descriptorTask)ptask_add[counter].pTack;

        sTask_Status.task_num = task_num;

        // Текущий указатель на стек
        ptask_add[counter].task_element.pStack_pointer =
                port_Initialise_Stack(ptask_add[counter].pTack, ptask_add[counter].pStack, ptask_add[counter].pParameters);
    }
}

//------------------------------------------------------
// Выбирает задачу, затем вызывает переключение контекста
//------------------------------------------------------
void sTask_Schedule(void)
{
    // Сброс системного таймера
    port_Reset_SysTick();

    // Выбираем текущий поток
    sTask_Status.Task_Current = sTask_Status.Task_Next;
    // Выбираем задачу
    sTask_Status.Task_Next = sTask_Switch();

    // Указатель на переменную в которую нужно сохранить текущие положение стека
    pPointer_Save_Context_Stask = &task[sTask_Status.Task_Current].task_element.pStack_pointer;
    // Указатель на стек откуда нужно начать восстановление контекста
    pPointer_Load_Context_Stask = &task[sTask_Status.Task_Next].task_element.pStack_pointer;

    // Копируем дескриптор потока
    sTask_Status.pTask_Descriptor = task[sTask_Status.Task_Next].task_element.pTask_Descriptor;

    // Программное прерывание Schedule
    port_Inquiry_Interruption();
}

//------------------------------------------------------
// Запустить шедулер
//------------------------------------------------------
void eStart_Schedule(void)
{
    // Начальная инициализация
    sTask_Status.Task_Current = 0;
    sTask_Status.Task_Next = 0;

    // Выбираем задачу
    sTask_Status.Task_Next = sTask_Switch();
    // Текущая задача
    sTask_Status.Task_Current = sTask_Status.Task_Next;
    // Указатель на переменную в которую нужно сохранить текущие положение стека
    pPointer_Save_Context_Stask = &task[sTask_Status.Task_Current].task_element.pStack_pointer;
    // Указатель на стек откуда нужно начать восстановление контекста
    pPointer_Load_Context_Stask = &task[sTask_Status.Task_Next].task_element.pStack_pointer;
    // Копируем дескриптор потока
    sTask_Status.pTask_Descriptor = task[sTask_Status.Task_Next].task_element.pTask_Descriptor;

    // Запустить шедулер
    port_Start_Schedule(task[sTask_Status.Task_Current].task_element.pStack_pointer);
}
