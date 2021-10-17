/** @file       demoprocess.h
 *  @brief      Demo Process CPP Template
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       03/10/2021
 */
#ifndef FILE_DEMOPROCESS_H
#define FILE_DEMOPROCESS_H

/** INCLUDES ******************************************************************/
#include "system.h"
/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/

struct demoParams_t
{
    uint32_t dummyValue;
};

struct demoConsts_t
{
    const uint32_t constDummyValue;
};

class DemoProcess : public Process
{
private:
public:
    DemoProcess(demoParams_t* _params, demoConsts_t* _consts, eProcessID_t _enum)
    {
        this->_parameters = _params;
        this->_constants  = _consts;
        this->_ID         = _enum;
        PROCESS_STATE_CHANGE(this, eProcessStateIdle);
    }
    ~DemoProcess()
    {
        delete this;
    }
    uint32_t start();
    uint32_t suspend();
    uint32_t resume();
    uint32_t terminate();

    static void* thread1Func(void* params);
    static void* thread2Func(void* params);
};

#define PROCESS_DEMO_CREATE(_name, _enum)                                                                                                                                                              \
    demoParams_t _name##Params = {                                                                                                                                                                     \
        .dummyValue = 0,                                                                                                                                                                               \
    };                                                                                                                                                                                                 \
    demoConsts_t _name##Consts = {                                                                                                                                                                     \
        .constDummyValue = 0,                                                                                                                                                                          \
    };                                                                                                                                                                                                 \
    DemoProcess _name(&_name##Params, &_name##Consts, _enum);

/** MACROS ********************************************************************/

#ifndef FILE_DEMOPROCESS_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

#undef INTERFACE // Should not let this roam free

#endif // FILE_DEMOPROCESS_H
