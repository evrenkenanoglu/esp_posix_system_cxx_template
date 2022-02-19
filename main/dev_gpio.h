/** @file       dev_gpio.h
 *  @brief      Gpio Device for ESP32
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       26/10/2021
 */
#ifndef FILE_DEV_GPIO_H
#define FILE_DEV_GPIO_H

/** INCLUDES ******************************************************************/
#include "driver/gpio.h"
#include "system.h"

/** MACROS ********************************************************************/

#define GPIO_PIN_SEL(_pinNo) ((1ULL << _pinNo))
#define PULL_UP_ENABLE       SYS_ENABLE  // Pull-down disable
#define PULL_UP_DISABLE      SYS_DISABLE // Pull-down enable
#define ACTIVE_HIGH          1
#define ACTIVE_LOW           0
#define OUTPUT               0
#define INPUT                1
#define INITIAL_HIGH         1
#define INITIAL_LOW          0

/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/

struct gpio_params_t
{
    uint32_t dummyValue;
};

struct gpio_const_t
{
    const gpio_config_t config;
    const uint8_t       activeState;
    const uint32_t      pinNo;
    const uint8_t       initialOutput;
};

class Gpio : public Device
{
private:
    /* data */
public:
    Gpio(gpio_params_t* _params, gpio_const_t* _consts)
    {
        this->_parameters = _params;
        this->_constants  = _consts;
        this->_state      = eDeviceStateIdle;
    }
    ~Gpio()
    {
        delete this;
    }
    int32_t  init();
    int32_t  deinit();
    uint32_t get();
    int32_t  set(void* data);

    ///** DEVICE SPECIFIC FUNCTIONS **///

    ///** DEVICE SPECIFIC FUNCTIONS END **///
};

/**
 *  @brief GENERIC GPIO CREATE MACRO
 *  @param _name            Name of GPIO Device
 *
 *  @param _pinNo           Pin Number of GPIO
 *
 *  @param _input           For INPUT   -> 1
 *                          For OUTPUT  -> 0
 *
 *  @param _initial         Initial HIGH or LOW
 *
 *
 *  @param _interruptType
 *                          GPIO_INTR_DISABLE = 0,     -> Disable GPIO interrupt
 *                          GPIO_INTR_POSEDGE = 1,     -> GPIO interrupt type : rising edge
 *                          GPIO_INTR_NEGEDGE = 2,     -> GPIO interrupt type : falling edge
 *                          GPIO_INTR_ANYEDGE = 3,     -> GPIO interrupt type : both rising and falling edge
 *                          GPIO_INTR_LOW_LEVEL = 4,   -> GPIO interrupt type : input low level trigger
 *                          GPIO_INTR_HIGH_LEVEL = 5,  -> GPIO interrupt type : input high level trigger
 *                          GPIO_INTR_MAX,
 *
 *  @param _active          ACTIVE_HIGH or ACTIVE_LOW (!This will for INPUT)
 *
 *  @param _pullUpEnable    PULL_UP_ENABLE Or PULL_UP_DISABLE For output this is ignored.
 *
 */
#define DEVICE_GPIO_CREATE(_name, _pinNo, _input, _initial, _active, _interruptType, _pullUpEnable)                                                                                                    \
    gpio_params_t _name##Params = {                                                                                                                                                                    \
        .dummyValue = 0,                                                                                                                                                                               \
    };                                                                                                                                                                                                 \
    gpio_const_t _name##Consts = {                                                                                                                                                                     \
        .config =                                                                                                                                                                                      \
            {                                                                                                                                                                                          \
                .pin_bit_mask = GPIO_PIN_SEL(_pinNo),                                                                                                                                                  \
                .mode         = (_input) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT,                                                                                                                         \
                .pull_up_en   = (_input) ? gpio_pullup_t(_pullUpEnable) : GPIO_PULLUP_DISABLE,                                                                                                         \
                .pull_down_en = (_input) ? gpio_pulldown_t(!_pullUpEnable) : GPIO_PULLDOWN_DISABLE,                                                                                                    \
                .intr_type    = gpio_int_type_t(_interruptType),                                                                                                                                       \
            },                                                                                                                                                                                         \
        .activeState   = _active,                                                                                                                                                                      \
        .pinNo         = _pinNo,                                                                                                                                                                       \
        .initialOutput = _initial,                                                                                                                                                                     \
    };                                                                                                                                                                                                 \
    Gpio _name(&_name##Params, &_name##Consts);

#ifndef FILE_DEV_GPIO_CPP
#define INTERFACE extern
#else
#define INTERFACE
#endif

/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

#undef INTERFACE // Should not let this roam free

#endif // FILE_DEV_GPIO_H
