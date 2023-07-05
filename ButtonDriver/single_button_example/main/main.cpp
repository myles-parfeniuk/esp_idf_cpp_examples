//standard library includes
#include <iostream> 

//in-house component includes
#include "DataControl.hpp"
#include "Button.hpp"

//esp-idf component includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/*ButtonDriver example with a single button. 
* Button has single registered call-back that prints to terminal when button activity is detected.
*
* - Default gpio is pin 25
* - Button is assumed to be active low with external pullup
*
* Modify the button_config_t struct initialization as necessary. */
extern "C" void app_main()
{
    //configuring a button that is active low, with external pullup
    Button::button_config_t button_conf =
    {
        .gpio_num = GPIO_NUM_25, //gpio number 25
        .active_lo = true, //active low
        .active_hi = false, //not active high
        .pull_en = false, //no internal pullups (external is being used)
        .long_press_evt_time = 300000, //300ms long-press event generation time
        .held_evt_time = 200000, //200ms held event generation time
    };

        Button my_button(button_conf); //instantiating button object 


        my_button.event.follow( //register lambda style call-back function with button
        //this call-back will be executed whenever user-input is detected on button
        [](Button::ButtonEvent new_event)
        {
            switch(new_event){
                case Button::ButtonEvent::quick_press:
                    ESP_LOGI("Main", "quick-press");
                break;

                case Button::ButtonEvent::long_press:
                    ESP_LOGI("Main", "long-press");
                break;

                case Button::ButtonEvent::held:
                    ESP_LOGI("Main", "held");
                break;

                case Button::ButtonEvent::released:
                    ESP_LOGI("Main", "released");
                break;
            }
        });

        while(1)
        {
            vTaskDelay(10000/portTICK_PERIOD_MS); 
        }


}