#include <portmacro.h>
#include <task_switch.h>
#include <task.h>

//------------------------------------------------------
// Возвращает индекс текущей задачу
//------------------------------------------------------
uint8_t get_index(int priority)
{

    static int last_index[4] = {0, 0, 0, 0};
    int i;


    for(i = last_index[priority]; i < sTask_Status.task_num; i++)
    {
        if(task[i].task_element.Current_priority == priority)
        {
            last_index[priority] = i + 1;
            return i;
        }
    }


    last_index[priority] = 0;

    return -1; //not finde
}

//------------------------------------------------------
// Возвращает следующую задачу
//------------------------------------------------------
uint8_t sTask_Switch(void)
{
    static uint8_t c = 0;
    c ^= BIT0;
    return c;


    static int i     = 0,
               j     = 0;

    static int current_pr = 1; //!!!!!!!!!!!!!

    while(1)
    {

        for( ; i < sTask_Status.task_num; )
        {

            if(task[i].task_element.Current_priority == 0)
            {
                return i++;
            }
            ++i;
        }

        i = 0;

        for( ; j <= current_pr; )
        {


            if(get_index(j) != -1)
            {
                return j++;
                break;
            }
            ++j;

            if( j == current_pr)
                current_pr++;
            if(current_pr >= sTask_Status.task_num)
                current_pr = 0;
        }

        j = 0;

    }

}


