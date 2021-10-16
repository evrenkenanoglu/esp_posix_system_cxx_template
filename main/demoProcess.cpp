/** @file       demoprocess.c
 *  @brief      Demo Process CPP Template
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       03/10/2021
 */
#define FILE_DEMOPROCESS_C

/** INCLUDES ******************************************************************/
#include "demoProcess.h"

using namespace std;
const char* processTag = "Demo Process 1";
const char* tagTask1   = "Task1";
/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/
#define THREAD_1_SLEEP_DURATION_IN_SEC 2
#define THREAD_1_QUEUE_SIZE            5
/** VARIABLES *****************************************************************/

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
/** LOCAL FUNCTION DECLARATIONS ***********************************************/

/** INTERFACE FUNCTION DEFINITIONS ********************************************/

uint32_t DemoProcess::start()
{
    ESP_LOGI(processTag, " Process Started!");
    demoParams_t*       params = (demoParams_t*)this->_parameters;
    const demoConsts_t* consts = (demoConsts_t*)this->_constants;
    
    pthread_t thread1, thread2;
    int       error;
    if ((error = pthread_create(&thread1, NULL, &DemoProcess::thread1Func, this)))
        cout << "Thread 1 creation failed ErrNo: " << error << endl;
    else
        this->threadList.push_back(&thread1);
    if ((error = pthread_create(&thread2, NULL, &DemoProcess::thread2Func, (void*)this)))
        cout << "Thread 2 creation failed ErrNo: " << error << endl;
    else
        this->threadList.push_back(&thread2);

    return EXIT_SUCCESS;
}

uint32_t DemoProcess::suspend()
{
    return EXIT_SUCCESS;
}
uint32_t DemoProcess::resume()
{
    return EXIT_SUCCESS;
}
uint32_t DemoProcess::terminate()
{
    return EXIT_SUCCESS;
}

void* DemoProcess::thread1Func(void* parameters)
{
    const char*         message1 = "Thread 1";
    DemoProcess*        process  = (DemoProcess*)parameters;
    demoParams_t*       params   = (demoParams_t*)process->_parameters;
    const demoConsts_t* consts   = (demoConsts_t*)process->_constants;

    BaseType_t       xStatus;
    Message_t*       receivedMessage; //= { 0, 0, 0,};
    const TickType_t tickToWait = pdMS_TO_TICKS(0);

    const auto sleepTime = chrono::seconds{THREAD_1_SLEEP_DURATION_IN_SEC};

    for (;;)
    {
        pthread_mutex_lock(&mutex1);
        cout << endl;
        cout << "<<" << processTag << ">>" << message1 << " Running" << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        // cout << "CoreID: " << xPortGetCoreID() << endl;
        cout << "Counter Value: " << ++params->dummyValue << endl;
        cout << endl;
        this_thread::sleep_for(sleepTime);
        pthread_mutex_unlock(&mutex1);
    }
}

void* DemoProcess::thread2Func(void* parameters)
{
    const char*         message1 = "Thread 2";
    Process*            process  = (Process*)parameters;
    demoParams_t*       params   = (demoParams_t*)process->_parameters;
    const demoConsts_t* consts   = (demoConsts_t*)process->_constants;

    BaseType_t       xStatus;
    Message_t*       receivedMessage; //= { 0, 0, 0,};
    const TickType_t tickToWait = pdMS_TO_TICKS(0);

    const auto sleepTime = chrono::seconds{THREAD_1_SLEEP_DURATION_IN_SEC};

    for (;;)
    {
        pthread_mutex_lock(&mutex1);
        cout << endl;
        cout << "<<" << processTag << ">>" << message1 << " Running" << endl;
        cout << "ID: " << this_thread::get_id() << endl;
        // cout << "CoreID: " << xPortGetCoreID() << endl;
        cout << "Counter Value: " << ++params->dummyValue << endl;
        cout << endl;
        this_thread::sleep_for(sleepTime);
        pthread_mutex_unlock(&mutex1);
    }
}
/** LOCAL FUNCTION DEFINITIONS ************************************************/
