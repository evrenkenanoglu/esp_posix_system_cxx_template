#include "demoProcess.h"
#include "system.h"

using namespace std;
PROCESS_DEMO_CREATE(demo1, eProcessDemo1)

#define THREAD_SLEEP_DURATION_IN_SEC      2
#define THREAD_MAIN_SLEEP_DURATION_IN_SEC 10

const auto sleepTime     = chrono::seconds{THREAD_SLEEP_DURATION_IN_SEC};
const auto sleepMainTime = chrono::seconds{THREAD_MAIN_SLEEP_DURATION_IN_SEC};

const char* thread1Tag = "Thread1";
const char* thread2Tag = "Thread2";
const char* thread3Tag = "Thread3";

pthread_mutex_t mutext1 = PTHREAD_MUTEX_INITIALIZER;

esp_pthread_cfg_t create_config(const char* name, int core_id, int stack, int prio)
{
    auto cfg        = esp_pthread_get_default_config();
    cfg.thread_name = name;
    cfg.pin_to_core = core_id;
    cfg.stack_size  = stack;
    cfg.prio        = prio;
    return cfg;
}

void* thread1Func(void* params)
{
    for (;;)
    {
        cout << endl;
        cout << (const char*)params << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        cout << "CoreID: " << xPortGetCoreID() << endl;
        this_thread::sleep_for(sleepTime);
    }
}

void* thread2Func(void* params)
{
    for (;;)
    {
        cout << endl;
        cout << (const char*)params << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        cout << "CoreID: " << xPortGetCoreID() << endl;
        this_thread::sleep_for(sleepTime);
    }
}

void thread3Func(void* params)
{
    for (;;)
    {
        cout << endl;
        cout << (const char*)params << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        cout << "CoreID: " << xPortGetCoreID() << endl;
        this_thread::sleep_for(sleepTime);
    }
}
extern "C" void app_main(void)
{
    processStart(&demo1);
    pthread_t   thread1, thread2;
    const char* message1 = "Thread 1";
    const char* message2 = "Thread 2";
    int         error;

    if ((error = pthread_create(&thread1, NULL, &thread1Func, (void*)message1)))
    {
        cout << "Thread 1 creation failed ErrNo: " << error << endl;
    }
    if ((error = pthread_create(&thread2, NULL, &thread2Func, (void*)message2)))
{
        cout << "Thread 2 creation failed ErrNo: " << error << endl;
    }

    while (1)
    {
        static int i = 0;
        cout << "[" << i++ << "] <<MAIN THREAD RUNNING>>" << endl;
        this_thread::sleep_for(sleepMainTime);
    }
}
