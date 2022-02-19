/** @file       device.h
 *  @brief      Device abstract layer
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       26/10/2021
 */
#ifndef FILE_DEVICE_H
#define FILE_DEVICE_H

/** INCLUDES ******************************************************************/
#include "system.h"
/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/
typedef enum
{
    eDeviceStateIdle = 0,
    eDeviceStateInitiliazed,
    eDeviceStateDeinitialized,
} eDeviceState_t;

/** MACROS ********************************************************************/

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_INIT_FUNC(_name)    int32_t _name()

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_DEINIT_FUNC(_name)  int32_t _name()

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_GET_FUNC(_name)     uint32_t _name()

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_SET_FUNC(_name)     int32_t _name(void* data)

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_OPEN_FUNC(_name)    int32_t _name()

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_SEND_FUNC(_name)    int32_t _name(const void* txb, uint16_t length)

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_RECEIVE_FUNC(_name) int32_t _name(void* rxb, uint16_t length)

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_CLOSE_FUNC(_name)   int32_t _name()

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_ERASE_FUNC(_name)   int32_t _name(uint32_t address, uint32_t size)

/** @brief      DEVICE init function prototype
 *  @param      _name   Name of the function
 *  @details    DEVICE Pointer to tsDEVICE structure that holds the DEVICE information
 */
#define DEVICE_WRITE_FUNC(_name)   int32_t _name(void* data)

/**
 * @brief Device Abstract Class
 * @param
 * @param _parameters description
 * @param _constants description
 * @param _state description
 */
class Device
{
protected:
    void*          _parameters;
    void*          _constants;
    eDeviceState_t _state;

public:
    virtual ~Device() {}
    virtual DEVICE_INIT_FUNC(init)     = 0;
    virtual DEVICE_DEINIT_FUNC(deinit) = 0;
    virtual DEVICE_GET_FUNC(get)       = 0;
    virtual DEVICE_SET_FUNC(set)       = 0;
    eDeviceState_t getState(void)
    {
        return this->_state;
    }
    void setState(eDeviceState_t state)
    {
        this->_state = state;
    }
};

#ifndef FILE_DEVICE_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

// /** @brief      Start a Device
//  *  @param[in]  Device Object pointer to target object
//  *  @retval     EXIT_FAIL
//  *  @retval     EXIT_SUCCESS
//  */
// INTERFACE uint32_t deviceInit(Device* device);

// /** @brief      Suspend a Device
//  *  @param[in]  Device Object pointer to target object
//  *  @retval     EXIT_FAIL
//  *  @retval     EXIT_SUCCESS
//  */
// INTERFACE uint32_t deviceDeinit(Device* device);

#undef INTERFACE // Should not let this roam free

#endif // FILE_DEVICE_H
