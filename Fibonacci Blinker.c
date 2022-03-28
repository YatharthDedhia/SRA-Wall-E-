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
            
            int term_1,term_2,term_3;
            int i = 0;
            term_1 = 0;
            term_2  = 1;

            while(i<7)
            {
                uint8_t a0 = 0x00;
                uint8_t a1 = 0x01;
                uint8_t a2 = 0x01;

                if(term_1 ==0 )
                {
                    ESP_ERROR_CHECK(set_bar_graph(a0));
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }

                else if(term_1 ==1)
                {
                    ESP_ERROR_CHECK(set_bar_graph(a1));
                    vTaskDelay(1000 / portTICK_RATE_MS);

                    ESP_ERROR_CHECK(set_bar_graph(a0));
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }
            
                else
                {
                    for(int j=1; j<=term_1-1;j++)
                    {
                        a2 = a2 | a1<<(term_1-j);
                    }

                    ESP_ERROR_CHECK(set_bar_graph(a2));
                    vTaskDelay(1000 / portTICK_RATE_MS);

                    ESP_ERROR_CHECK(set_bar_graph(a0));
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }
                a2 = 0x01;
                term_3 = term_1+term_2;
                term_1 = term_2;
                term_2 = term_3;
                i++;
            }
        }  
    } 