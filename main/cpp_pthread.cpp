#include "demoProcess.h"
#include "system.h"

using namespace std;

#define THREAD_MAIN_SLEEP_DURATION_IN_SEC 5

PROCESS_DEMO_CREATE(demo1, eProcessDemo1)

extern "C" void app_main(void)
{
    processStart(&demo1);
    while (1)
    {
        static int i = 0;
        cout << "[" << i++ << "] <<MAIN THREAD RUNNING>>" << endl;
        this_thread::sleep_for(chrono::seconds{THREAD_MAIN_SLEEP_DURATION_IN_SEC});
    }
}
