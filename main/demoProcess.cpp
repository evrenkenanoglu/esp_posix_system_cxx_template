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
#define THREAD_2_SLEEP_DURATION_IN_SEC 4
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

    ///** FreeRtos Queue Initialize **///
    systemQueueList[eThread1] = xQueueCreate(5, sizeof(Message_t));
    systemQueueList[eThread2] = xQueueCreate(5, sizeof(Message_t));

    ///** Posix Thread Creation **///
    pthread_t thread1, thread2;
    int       error;
    if ((error = pthread_create(&thread1, NULL, &DemoProcess::thread1Func, this)))
        cout << "Thread 1 creation failed ErrNo: " << error << endl;
    else
        this->threadList.push_back(&thread1);
    if ((error = pthread_create(&thread2, NULL, &DemoProcess::thread2Func, this)))
        cout << "Thread 2 creation failed ErrNo: " << error << endl;
    else
        this->threadList.push_back(&thread2);

    PROCESS_STATE_CHANGE(this, eProcessStateRunning);
    cout << "Process Changed State: " << eProcessStateRunning << endl;
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
    Message_t        receivedMessage; //= { 0, 0, 0,};
    const TickType_t tickToWait = pdMS_TO_TICKS(0);

    const auto sleepTime = chrono::seconds{THREAD_1_SLEEP_DURATION_IN_SEC};

    for (;;)
    {
        pthread_mutex_lock(&mutex1);
        cout << endl;
        cout << "<<" << processTag << ">>" << message1 << " Running" << endl;
        // cout << "ID: " << this_thread::get_id() << endl;
        // cout << "CoreID: " << xPortGetCoreID() << endl;
        // cout << "Counter Value: " << ++params->dummyValue << endl;
        // cout << endl;

        if (uxQueueMessagesWaiting(systemQueueList[eThread1]) != 0)
        {
            cout << "Queue is not empt" << endl;
        }

        xStatus = xQueueReceive(systemQueueList[eThread1], &receivedMessage, tickToWait);

        if (xStatus != pdPASS)
        {
            cout << "Couldn't received anything from queue" << endl;
        }
        else
        {
            cout << "Message Received from Process: " << receivedMessage.senderProcess << "| Thread: " << receivedMessage.senderThread << endl;
            cout << "Received message: " << *(uint32_t*)receivedMessage.data << endl;

            if (receivedMessage.senderProcess == eProcessDemo2)
            {
                cout << "Process2 Found!" << endl;
                if (receivedMessage.senderThread == eThread2)
                {
                    cout << "Thread2 Found!" << endl;
                }
                else
                {
                    cout << "Thread2 Not Found!" << endl;
                }
            }
            // printf("Received message: %d \n", receivedValue);
        }

        cout << endl;
        this_thread::sleep_for(sleepTime);
        pthread_mutex_unlock(&mutex1);
    }
}

void* DemoProcess::thread2Func(void* parameters)
{
    const char*         message1 = "Thread 2";
    DemoProcess*        process  = (DemoProcess*)parameters;
    demoParams_t*       params   = (demoParams_t*)process->_parameters;
    const demoConsts_t* consts   = (demoConsts_t*)process->_constants;

    BaseType_t       xStatus;
    Message_t*       receivedMessage; //= { 0, 0, 0,};
    Message_t        message;
    const TickType_t tickToWait = pdMS_TO_TICKS(0);

    const auto sleepTime = chrono::seconds{THREAD_2_SLEEP_DURATION_IN_SEC};

    for (;;)
    {
        pthread_mutex_lock(&mutex1);
        cout << endl;
        cout << "<<" << processTag << ">> " << message1 << " Running" << endl;
        // cout << "ID: " << this_thread::get_id() << endl;
        // cout << "CoreID: " << xPortGetCoreID() << endl;
        // cout << "Counter Value: " << ++params->dummyValue << endl;
        // cout << endl;

        static uint8_t state = 0;
        uint32_t       value;
        if (state == 0)
        {
            value                 = 16000;
            message.senderProcess = eProcessID_t(process->_ID);
            message.senderThread  = eThread2;
            message.data          = &value;
        }
        else
        {
            value                 = 32000;
            message.senderProcess = eProcessID_t(process->_ID);
            message.senderThread  = eThread2;
            message.data          = &value;
        }
        state = !state;

        xStatus = uxQueueSpacesAvailable(systemQueueList[eThread1]);
        cout << "Available Space in Queue of Thread1: " << xStatus << endl;
        if (xStatus == 0)
        {
            // cout << "No available space in Queue of Task1" << endl;;
        }
        else
        {
            xStatus = xQueueSend(systemQueueList[eThread1], &message, tickToWait);
            if (xStatus != pdPASS)
            {
                cout << "Message Couldn't Send!" << endl;
                ;
            }
            else
            {
                cout << "Message Send Succesfull" << endl;
                ;
            }
        }
        cout << endl;
        this_thread::sleep_for(sleepTime);
        pthread_mutex_unlock(&mutex1);
    }
}
/** LOCAL FUNCTION DEFINITIONS ************************************************/
