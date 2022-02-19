/** @file       dev_gpio.cpp
 *  @brief      Gpio Device for ESP32
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       26/10/2021
 */
#define FILE_DEV_GPIO_C

/** INCLUDES ******************************************************************/
#include "dev_gpio.h"

using namespace std;
/** CONSTANTS *****************************************************************/
const char* tagDevice = "DEVICE->GPIO: ";
/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/
#define PARAMS_CONSTS_INIT()                                                                                                                                                                           \
    gpio_params_t*      params = (gpio_params_t*)this->_parameters;                                                                                                                                    \
    const gpio_const_t* consts = (gpio_const_t*)this->_constants;
/** VARIABLES *****************************************************************/

/** LOCAL FUNCTION DECLARATIONS ***********************************************/

int32_t Gpio::init()
{
    PARAMS_CONSTS_INIT()
    UNUSED(params);
    if (this->getState() == eDeviceStateInitiliazed)
    {
        cout << tagDevice << "Device is Already Initialized!" << endl;
        return EXIT_SUCCESS;
    }
    else
    {
        esp_err_t error = gpio_config(&consts->config);

        if (error != PLATFORM_SUCCESS)
        {
            cout << tagDevice << "Couldn't Initialized!" << endl;
            return error;
        }
        else
        {
            this->setState(eDeviceStateInitiliazed);
            set((void*)&consts->initialOutput);
            cout << tagDevice << "Initialized Succesfully!" << endl;
            return EXIT_SUCCESS;
        }
    }
}

int32_t Gpio::deinit()
{
    PARAMS_CONSTS_INIT()

    UNUSED(params);

    esp_err_t error = gpio_reset_pin(gpio_num_t(consts->pinNo));
    if (error != PLATFORM_SUCCESS)
    {
        cout << tagDevice << "Couldn't Deinitialized!" << endl;
        return error;
    }
    else
    {
        this->setState(eDeviceStateDeinitialized);
        cout << tagDevice << "Deinitialized Succesfully!" << endl;
        return EXIT_SUCCESS;
    }
}

uint32_t Gpio::get()
{
    PARAMS_CONSTS_INIT()
    UNUSED(params);
    if (this->_state != eDeviceStateInitiliazed)
    {
        cout << tagDevice << "Device not initialized" << endl;
        return EXIT_FAIL;
    }
    else
    {
        return (uint32_t)gpio_get_level(gpio_num_t(consts->pinNo));
    }
}

int32_t Gpio::set(void* data)
{
    PARAMS_CONSTS_INIT()
    esp_err_t error;

    UNUSED(params);

    if (this->_state == eDeviceStateInitiliazed)
    {
        if (consts->config.mode == GPIO_MODE_OUTPUT) // OUTPUT
        {
            if (consts->activeState == ACTIVE_HIGH)
            {
                error = gpio_set_level(gpio_num_t(consts->pinNo), *(uint32_t*)data);
                cout << tagDevice << "Set data: " << *(uint32_t*)data << "Error No: " << error << endl;
            }
            else
            {
                gpio_set_level(gpio_num_t(consts->pinNo), !*(uint32_t*)data);
                cout << tagDevice << "Set data: " << *(uint32_t*)data << endl;
            }

            return EXIT_SUCCESS;
        }
        else // INPUT
        {
            return EXIT_FAIL;
        }
    }
    else
    {
        cout << tagDevice << "Device not initialized" << endl;
        return EXIT_FAIL;
    }
}
/** INTERFACE FUNCTION DEFINITIONS ********************************************/

/** LOCAL FUNCTION DEFINITIONS ************************************************/
