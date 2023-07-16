#include "Object.hpp"

Object::Object(const char* name) : 
task(std::bind(&Object::task_function, this)), name(name)
{
    
}


void Object::task_function()
{
    while(1)
    {
        ESP_LOGI(TAG, "My name is %s, I am an object, and this is my task.", name);
        vTaskDelay(1000/portTICK_PERIOD_MS); //delay for 1 seconds
    }
    
}