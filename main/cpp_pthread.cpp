#include "demoProcess.h"
#include "dev_gpio.h"
#include "system.h"

using namespace std;

#define THREAD_MAIN_SLEEP_DURATION_IN_MS 1000

#define BUILTIN_LED                      2

// PROCESS_DEMO_CREATE(demo1, eProcessDemo1)
DEVICE_GPIO_CREATE(demoGpio, BUILTIN_LED, OUTPUT, INITIAL_LOW, ACTIVE_HIGH, GPIO_INTR_DISABLE, PULL_UP_DISABLE)

uint8_t high = 1;
uint8_t low  = 0;

extern "C" void app_main(void)
{
    // processStart(&demo1);
    while (1)
    {
        demoGpio.init();
        static int i = 0;
        cout << "[" << i++ << "] <<MAIN THREAD RUNNING>>" << endl;
        demoGpio.set(&high);
        cout << "DEMO GPIO OUTPUT -> " << demoGpio.get() << endl;

        this_thread::sleep_for(chrono::milliseconds{THREAD_MAIN_SLEEP_DURATION_IN_MS});

        demoGpio.set(&low);
        cout << "DEMO GPIO OUTPUT -> " << demoGpio.get() << endl;

        this_thread::sleep_for(chrono::milliseconds{THREAD_MAIN_SLEEP_DURATION_IN_MS});

        demoGpio.deinit();

        demoGpio.set(&high);
        this_thread::sleep_for(chrono::milliseconds{THREAD_MAIN_SLEEP_DURATION_IN_MS});

        demoGpio.init();
        demoGpio.set(&high);
        cout << "DEMO GPIO OUTPUT -> " << demoGpio.get() << endl;

        this_thread::sleep_for(chrono::milliseconds{THREAD_MAIN_SLEEP_DURATION_IN_MS});

        demoGpio.set(&low);
        cout << "DEMO GPIO OUTPUT -> " << demoGpio.get() << endl;

        this_thread::sleep_for(chrono::milliseconds{THREAD_MAIN_SLEEP_DURATION_IN_MS});

    }
}
