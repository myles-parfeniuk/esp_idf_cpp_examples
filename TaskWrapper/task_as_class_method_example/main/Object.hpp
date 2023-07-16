#pragma once
#include "TaskWrapper.hpp"
#include "esp_log.h"

class Object
{
    public:
    Object(const char * name); //constructor 
    TaskWrapper<Object> task; //task wrapper
    
    private:
    void task_function(); //task function
    const char *name; //name for print statements
    static const constexpr char* TAG = "Object"; //class name for print statements

};