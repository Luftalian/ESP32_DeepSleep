#include <Arduino.h>

#include <SPICREATE.h>
#include "utils/example.h"

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 5 * 60      /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason()
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        esp_deep_sleep_start();
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Wakeup caused by touchpad");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Wakeup caused by ULP program");
        break;
    default:
        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
        break;
    }
}

boolean something_action_by_transaction()
{
    // ここにトランザクションを記述する
    return false;
}

uint32_t address = 0;
void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    delay(1000); // Take some time to open up the Serial Monitor

    // Increment boot number and print it every reboot
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    /*
    First we configure the wake up source
    We set our ESP32 to wake up every 5 seconds
    */
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");

    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, ESP_EXT1_WAKEUP_ANY_HIGH); // GPIO_NUM_?, ? = {0, 2, 4, 12-15, 25-27, 32-39}

    print_wakeup_reason(); // Setting the above two esp_sleep_enable_x former makes ESP32's move right when ESP32 will sleep in this function in case that wake_up_reason is ESP_SLEEP_WAKEUP_TIMER.

}

void loop()
{
    if (something_action_by_transaction())
    {
        Serial.println("Going to sleep now");
        Serial.flush();

        esp_deep_sleep_start();
    }
}