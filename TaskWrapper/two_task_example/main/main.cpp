//standard library includes
#include <stdio.h>
//in-house includes
#include "TaskWrapper.hpp"

void task_one_func();
void task_two_func(); 

/*TaskWrapper example with two tasks. 
* Tasks both print a count to the terminal.
* Task one running on core 0.
* Task two is running on core 1. 
* */
extern "C" void app_main()
{
    char task_info[200]={}; 

    //optional configurational argument for task two
    task_config_t task_two_conf = default_config;
    task_two_conf.core_id = 1; 


    TaskWrapper<> task_one(&task_one_func); //instantiate task one
    task_one.start_task(); //start task one

    TaskWrapper<> task_two(&task_two_func, task_two_conf); //instantiate task two
    task_two.start_task(); //start task two


    while(1)
    {
        vTaskDelay(10000/portTICK_PERIOD_MS); 
        //dump information about all tasks to terminal every 10 seconds
        vTaskList(task_info);
        ESP_LOGW("TaskInfo", "\n\rNAME       STATUS     PRIORITY  STACK  NUM CORE_ID\n\r %s", task_info);

    }

}

void task_one_func(){
    uint16_t count = 0; 
    while(1)
    {
        ESP_LOGI("TaskOne", "Count: %d", count);
        count++;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void task_two_func(){
    uint16_t count = 0; 
    while(1)
    {
        ESP_LOGI("TaskTwo", "Count: %d", count);
        count++;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

