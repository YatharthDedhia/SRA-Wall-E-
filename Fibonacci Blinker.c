       /*  BLINKIN LEDS IN FIBONACCI SEQUENCE

        EXPECTED OUTPUT:
        0 = 00000000 = 0x00
        1 = 00000001 = 0x01
        1 = 00000001 = 0x01
        2 = 00000011 = 0x03
        3 = 00000111 = 0x07
        5 = 00011111 = 0x1F
        8 = 11111111 = 0xFF
    */
    // Header Files
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
            //Initializing variables for Fibonacci numbers
            int fib_no,t2,t3;
            int i = 0;
            fib_no = 0;
            t2  = 1;

            //Fibonacci loop
            while(i<7) //7 because outputting for 8 LEDS
            {
                //Initializing variables for LED Blink
                uint8_t LED_OFF = 0x00;
                uint8_t LED_1 = 0x01;
                uint8_t LED_ON = 0x01;

                //IF and ELSE IF Ladder For 1st two OUTPUTS
                if(fib_no ==0 )
                {
                    //Display 00000000
                    ESP_ERROR_CHECK(set_bar_graph(LED_OFF));
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }

                else if(fib_no ==1)
                {
                    //Display 00000001
                    ESP_ERROR_CHECK(set_bar_graph(LED_1));
                    vTaskDelay(1000 / portTICK_RATE_MS);

                    //Display 00000000
                    ESP_ERROR_CHECK(set_bar_graph(LED_OFF));
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }
                
                //ELSE for any other value of fib_no
                else
                {
                    //FOR loop to get the LED blinking
                    for(int j=1; j<=fib_no-1;j++)
                    {
                        LED_ON = LED_ON | LED_1<<(fib_no-j);

                      //Loop functioning
                      //fib_no = 2
                      //LED_ON = 0x01 | 0x01<<1 = 00000001|00000010 = 00000011 =0x03
            
                      //LED_ON = 0x01
                      //fib_no = 3
                      //LED_ON = 0x01 | 0x01<<1 = 00000001|00000010 = 00000011 =0x03
                      //LED_ON = 0x03 | 0x01<<2 = 00000011|00000100 = 00000111 =0x07

                      //LED_ON = 0x01
                      //fib_no = 5
                      //LED_ON = 0x01 | 0x01<<1 = 00000001|00000010 = 00000011 =0x03
                      //LED_ON = 0x03 | 0x01<<2 = 00000011|00000100 = 00000111 =0x07
                      //LED_ON = 0x07 | 0x01<<3 = 00000111|00001000 = 00001111 =0x0F
                      //LED_ON = 0x0F | 0x01<<4 = 00001111|00010000 = 00011111 =0x1F

                      //LED_ON = 0x01
                      //fib_no = 8
                      //LED_ON = 0x01 | 0x01<<1 = 00000001|00000010 = 00000011 =0x03
                      //LED_ON = 0x03 | 0x01<<2 = 00000011|00000100 = 00000111 =0x07
                      //LED_ON = 0x07 | 0x01<<3 = 00000111|00001000 = 00001111 =0x0F
                      //LED_ON = 0x0F | 0x01<<4 = 00001111|00010000 = 00011111 =0x1F
                      //LED_ON = 0x1F | 0x01<<5 = 00011111|00100000 = 00111111 =0x3F
                      //LED_ON = 0x03 | 0x01<<6 = 00000011|01000000 = 01111111 =0x7F
                      //LED_ON = 0x07 | 0x01<<7 = 00000111|10000000 = 11111111 =0xFF
                    }

                    //Display LED_ON (No of LEDs to turn ON)
                    ESP_ERROR_CHECK(set_bar_graph(LED_ON));
                    vTaskDelay(1000 / portTICK_RATE_MS);

                    ESP_ERROR_CHECK(set_bar_graph(LED_OFF));
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }
                //Resetting LED_ON to 0x00 (00000001)
                LED_ON = 0x01;

                //To get the next fibonacci number (fib_no)
                t3 = fib_no+t2;
                fib_no = t2;
                t2 = t3;
                i++;
            }
        }  
    } 