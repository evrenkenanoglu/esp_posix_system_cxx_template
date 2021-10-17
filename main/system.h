/** @file       system.h
 *  @brief      System Wide Components
 *  @copyright  (c) 2021-Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       01/08/2021
 */
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

/** INCLUDES ******************************************************************/

///** Standard Library Includes **///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///** FreeRTOS Includes **///
#include "freertos/FreeRTOS.h"
#include "freertos/list.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/timers.h"

///** POSIX Includes **///
#include "esp_pthread.h"
#include <pthread.h>

///** CPP Standard Includes **//
#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

//** Process Architecture Includes **//
#include "porting.h"
#include "process.h"

///** uController Includes **///
#include "esp_log.h"

/** CONSTANTS *****************************************************************/
#define EXIT_SUCCESS       0
#define EXIT_FAILURE       1

#define QUEUE_SIZE         32 // Default Queue List Size

#define SYS_ENABLE         0
#define SYS_DISABLE        1

#define DEBUG_PRINT_ENABLE SYS_ENABLE

/** TYPEDEFS ******************************************************************/

typedef enum
{
    //**Demo App **//
    eThread1 = 0,
    eThread2,
    eThread3,
    //**Demo App2 **//
    eThreadMax,
} eThreadID_t;

typedef enum
{
    eProcessDemo1 = 1,
    eProcessDemo2,
    eProcessMax,
} eProcessID_t;

typedef struct
{
    eProcessID_t senderProcess; ///> Sender Process ID
    eThreadID_t  senderThread;  ///> Sender Task ID
    void*        data;          ///> Data pointer
} Message_t;

/** MACROS ********************************************************************/

#ifndef FILE_SYSTEM_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

#define GLOBAL_QUEUE_LIST_CREATE(_size) static QueueHandle_t systemQueueList[_size];

static QueueHandle_t systemQueueList[eThreadMax]; ///< Inter-Tasks Communications

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

#undef INTERFACE // Should not let this roam free

#endif // FILE_SYSTEM_H
