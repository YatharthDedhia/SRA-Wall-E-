/* A program to blink lights in order of: 
All OFF, 1 ON, 2 ON , 3 ON, and so on......

00000000  0x00
00000001  0x01
00000011  0x03
00000111  0x07
00001111  0x0F
00011111  0x1F
00111111  0x3F
01111111  0x7F
11111111  0xFF

*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sra_board.h"

void app_main()
{

	ESP_ERROR_CHECK(enable_bar_graph());
	// enable_bar_graph() turns on the gpio pins, if it succeeds it returns ESP_OK else it returns ESP_FAIL
	// If the argument of ESP_ERROR_CHECK() is not equal ESP_OK, then an error message is printed on the console, and abort() is called.
    while(1)
    {
        //blinks all the 8 leds 3 times
        for (int i = 0; i < 3; i++)
        {
            ESP_ERROR_CHECK(set_bar_graph(0xFF));
            //0xFF = 1111 1111(all leds are on)
            // setting values of all 8 leds to 1
            vTaskDelay(1000 / portTICK_RATE_MS);
            //delay of 1s
            ESP_ERROR_CHECK(set_bar_graph(0x00));
            //0x00 = 0000 0000(all leds are off)
            // setting values of all 8 leds to 0
            vTaskDelay(1000 / portTICK_RATE_MS);
            //delay of 1s
        }
    

//Actual Program starts
        //initiating
        uint8_t t1,t2,t3;

        t1 = 0x00; //All OFF: 00000000
        t2 = 0x01; //1 ON :   00000001
        
        //itertion
        int j=0;
        while(j<10)
        {
            ESP_ERROR_CHECK(set_bar_graph(t1));
            vTaskDelay(500 / portTICK_RATE_MS);
            t3 = (t2<<1) | t2; //uses bitwise OR operator
            t1 = t2;
            t2 = t3;
            j++;
        }

        //3s delay indicating end of program
        vTaskDelay(3000 / portTICK_RATE_MS); 
    }
}
