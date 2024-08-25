#include "pico/cyw43_arch.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pico_main.h"
#include "smb2.h"
#include "libsmb2.h"

void main_task(__unused void *params)
{
    if (cyw43_arch_init())
    {
        printf("Failed to initialise Pico W\n");
        return;
    }

    cyw43_arch_enable_sta_mode();
    
    printf("Connecting to WiFi...\n");

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("Failed to connect.\n");
        return;
    }

    ip4_addr_t *address = &(cyw43_state.netif[0].ip_addr);
    printf("Connected to %s as %d.%d.%d.%d as host %s\n", WIFI_SSID, ip4_addr1_16(address), ip4_addr2_16(address), ip4_addr3_16(address), ip4_addr4_16(address), cyw43_state.netif[0].hostname);

    smb2_ls_sync(SMB2_URL);
    vTaskDelete(NULL);
}


void pico_init_main()
{
    TaskHandle_t task;

    stdio_init_all();

    xTaskCreate(main_task, "MainThread", configMINIMAL_STACK_SIZE, NULL, 1, &task);
    vTaskStartScheduler();
}