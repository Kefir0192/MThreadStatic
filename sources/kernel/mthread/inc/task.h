#ifndef MTHREAD_CONFIG
#define MTHREAD_CONFIG


/// The count of elements in the array.
#define COUNT_ELEMENTS(array) (sizeof(array) / sizeof(array[0]))

/// Всего задач
#define COUNT_ELEMENTS_TASKS    2

/// Указатель на переменную в которую нужно сохранить текущие положение стека
extern uint32_t **pPointer_Save_Context_Stask;
/// Указатель на переменную которая ссылается на указатель стека для загрузки
extern uint32_t **pPointer_Load_Context_Stask;

/// Descriptor Task
typedef void *descriptorTask;

struct Task_Element {
    /// Текущий указатель стека
    uint32_t    *pStack_pointer;
    /// Установленный приоритет
    uint8_t     Setting_priority,
    /// Текущий приоритет
                Current_priority;
    /// Дескриптор задачи
    descriptorTask pTask_Descriptor;
};

/// Массив структур для каждой задачи
struct task_add {
    /// Указатель на функцию задачи
    void (*pTack)(void *pVoid);
    /// Аргумент потока
    void *pParameters;
    /// Указатель на вершину стека
    uint32_t *pStack;
    /// Статус индивидуальной задачи
    struct Task_Element task_element;
};

struct Task_Status {
    /// Индекс элемента массива структур текущей задачи
    uint32_t    Task_Current,
    /// Индекс элемента массива структур следующий задачи
                Task_Next;
    /// Всего задач
    uint8_t     task_num;
    /// Дескриптор текущий задачи
    descriptorTask pTask_Descriptor;
};

/// Массив структур для каждой задачи
extern struct task_add task[];
/// Статусная структура всех задач
extern struct Task_Status sTask_Status;

//------------------------------------------------------
// Создание новой задачи
// pTask_Element    Указатель на элемент задачи
// pTack            Указатель на функцию задачи type -> pFunction *
// pStack           Указатель на вершину стека  type -> uint32_t *
// Size_Stack       Размера стека в словах      type -> uint32_t
// pParameters      Аргумент потока             type -> void *
//------------------------------------------------------
void eTask_Create(struct Task_Element *pTask_Element, void (*pTack)(void *pVoid), uint32_t *pStack, uint32_t Size_Stack, void *pParameters, uint8_t priority);
// task_add         Указатель на массив структур для каждой задачи
// task_num         Всего задач
//------------------------------------------------------
void eTask_Init(struct task_add *ptask_add, uint8_t task_num);
// Выбирает задачу, затем вызывает переключение контекста
//------------------------------------------------------
void sTask_Schedule(void);
// Запустить шедулер
//------------------------------------------------------
void eStart_Schedule(void);



#endif // MTHREAD_CONFIG

