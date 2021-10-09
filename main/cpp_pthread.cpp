#include "demoProcess.h"
#include "system.h"

using namespace std;
PROCESS_DEMO_CREATE(demo1, eProcessDemo1)

#define THREAD_SLEEP_DURATION_IN_SEC 3

const auto sleepTime = chrono::seconds{THREAD_SLEEP_DURATION_IN_SEC};

const char* thread1Tag = "Thread1";
const char* thread2Tag = "Thread2";
const char* thread3Tag = "Thread3";

esp_pthread_cfg_t create_config(const char* name, int core_id, int stack, int prio)
{
    auto cfg        = esp_pthread_get_default_config();
    cfg.thread_name = name;
    cfg.pin_to_core = core_id;
    cfg.stack_size  = stack;
    cfg.prio        = prio;
    return cfg;
}

void thread1Func(const char* arg)
{
    for (;;)
    {
        cout << "Thread 1 !!!" << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        cout << "CoreID: " << xPortGetCoreID() << endl;
        cout << arg << endl;
        this_thread::sleep_for(sleepTime);
    }
}

void thread2Func()
{

    for (;;)
    {
        cout << "Thread 2 !!!" << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        cout << "CoreID: " << xPortGetCoreID() << endl;
        this_thread::sleep_for(sleepTime);

    }
}

void thread3Func()
{
    for (;;)
    {
        cout << "Thread 3 !!!" << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        cout << "CoreID: " << xPortGetCoreID() << endl;
        this_thread::sleep_for(sleepTime);

    }
}
extern "C" void app_main(void)
{

    const char* passArg      = "Passing Argument";
    auto        threadConfig = esp_pthread_get_default_config();

    esp_pthread_set_cfg(&threadConfig);
    thread any_core(thread1Func, passArg);

    auto threadConfig2 = create_config(thread2Tag, 0, 3 * 1024, 5);
    esp_pthread_set_cfg(&threadConfig2);
    thread thread2(thread2Func);

    auto threadConfig3 = create_config(thread3Tag, 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&threadConfig3);
    thread thread3(thread3Func);

    // any_core.join();
    // thread2.join();
    processStart(&demo1);
    int i = 0;
    thread2.join();
    thread3.joinable();

    this_thread::sleep_for(sleepTime);

    
    while (1)
    {
        printf("[%d] Hello world!\n", i);
        cout << "New Line " << endl;
        i++;

        this_thread::sleep_for(sleepTime);
    }
}
