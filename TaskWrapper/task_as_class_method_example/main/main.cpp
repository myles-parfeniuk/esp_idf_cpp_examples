#include <stdio.h>
#include "TaskWrapper.hpp"
#include "Object.hpp"

/*TaskWrapper example in which a task is instantiated within a class.
* The class implementation can be seen in Object.hpp & Object.cpp
* The objects generate some print statements to the terminal in their
* respective tasks. 
* */
extern "C" void app_main()
{

    //instantiate objects of class that contains function
    Object fred("fred");
    Object ted("ted");

    //start their respective tasks (this also could have been done in their constructors)
    fred.task.start_task();
    ted.task.start_task();

    while(1)
    {
        vTaskDelay(10000/portTICK_PERIOD_MS); //delay for 10 seconds 
    }


}
