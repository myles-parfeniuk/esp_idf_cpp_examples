//standard library includes
#include <iostream> 

//in-house component includes
#include "DataControl.hpp"
#include "Button.hpp"

//esp-idf component includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/* ButtonDriver example with a two buttons.
* Every 10 presses of button one its call-back will be paused, suppressing terminal output.
* If a long press is detected on button two, button one's call-back will be un-paused
* When a call-back is paused it is not executed even if button activity is detected. 
*
* - Default gpio pins for button one and button two are 25 and 26, respectively. 
* - Button one is as assumed to be active low with external pull-up being used
* - Button two is assumed to be active high with external pull-down being used
*
* Modify the button_config_t struct initializations as necessary. 
**/
extern "C" void app_main()
{
    uint16_t button_one_cb_id = 0;  //id of a callback registered to button one
    uint16_t press_count = 0;  //amount of times button one has been pressed

    //instantiate and initialize button config structs

    Button::button_config_t button_one_conf =
    {
        .gpio_num = GPIO_NUM_25, //gpio number 25
        .active_lo = true, //active low
        .active_hi = false, //not active high
        .pull_en = false, //no internal pullups/pulldowns
        .long_press_evt_time = 300000, //300ms long-press event generation time
        .held_evt_time = 200000, //200ms held event generation time
    };

    Button::button_config_t button_two_conf =
    {
        .gpio_num = GPIO_NUM_26, //gpio number 25
        .active_lo = false, //not active low
        .active_hi = true, //active high
        .pull_en = false, //no internal pullups/pulldowns
        .long_press_evt_time = 300000, //300ms long-press event generation time
        .held_evt_time = 200000, //200ms held event generation time
    };

    //instantiate button objects
    Button button_one(button_one_conf);
    Button button_two(button_two_conf);

    //register call-backs
    button_one_cb_id = button_one.event.follow(
        //call-back executed when button activity is detected
        [&button_one, button_one_cb_id, &press_count](Button::ButtonEvent event)
        {
            //if button event is quick press or long press, ignore all other event types
            if((event == Button::ButtonEvent::quick_press) || (event == Button::ButtonEvent::long_press))
            {
                press_count++; 

                if(press_count < 10)
                  ESP_LOGI("ButtonOneCb", "Counted Presses: %d", press_count);
                else
                {
                  //if presses exceed 10, mute this call-back and reset counted presses
                  button_one.event.pause(button_one_cb_id);
                  ESP_LOGW("ButtonOneCb", "Counted Presses: %d, button one call-back paused", press_count); 
                  press_count = 0; 
                }
            }

        }
    );

    button_two.event.follow(
        [&button_one, button_one_cb_id](Button::ButtonEvent event)
        {
            //if long press is detected, ignore all other event types
            if(event == Button::ButtonEvent::long_press)
            {
                button_one.event.un_pause(button_one_cb_id);
                ESP_LOGI("ButtonTwoCb", "button one call-back un-paused");
            }
        }
    );

    
    
    while(1)
    {
        vTaskDelay(10000/portTICK_PERIOD_MS); //delay for 10 seconds
    }

}