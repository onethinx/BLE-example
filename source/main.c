
/********************************************************************************
 *    ___             _   _     _			
 *   / _ \ _ __   ___| |_| |__ (_)_ __ __  __
 *  | | | | '_ \ / _ \ __| '_ \| | '_ \\ \/ /
 *  | |_| | | | |  __/ |_| | | | | | | |>  < 
 *   \___/|_| |_|\___|\__|_| |_|_|_| |_/_/\_\
 *
 ********************************************************************************
 *
 * Copyright (c) 2019-2022 Onethinx BV <info@onethinx.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************
 *
 * Created by: Rolf Nooteboom on 2020-10-09
 *
 * Sample project to demostrate the integration of a PSoC Creator project
 * into Visual Studio Code
 * 
 * For a description please see:
 * https://github.com/onethinx/Onethinx_Creator
 *
 ********************************************************************************/

#include "project.h"
#include "ble.h"
#include "OnethinxCore01.h"
#include "LoRaWAN_keys.h"

/* Go to ../OnethinxCore/LoRaWAN_keys.h and fill in the fields of the TTN_OTAAkeys structure */

coreConfiguration_t	coreConfig = {
	.Join =
	{
		.KeysPtr = 			&TTN_OTAAkeys,
		.DataRate =			DR_AUTO,
		.Power =			PWR_MAX,
		.MAXTries = 		100,
		.SubBand_1st =     	EU_SUB_BANDS_DEFAULT,
		.SubBand_2nd =     	EU_SUB_BANDS_DEFAULT
	},
	.TX =
	{
		.Confirmed = 		false,
		.DataRate = 		DR_0,
		.Power = 			PWR_MAX,
		.FPort = 			1
	},
	.RX =
	{
		.Boost = 			true
	},
	.System =
	{
		.Idle =
		{
			.Mode = 		M0_DeepSleep,
			.BleEcoON =		false,
			.DebugON =		true,
		}
	}
};

sleepConfig_t sleepConfig =
{
	.sleepMode = modeDeepSleep,
	.BleEcoON = false,
	.DebugON = true,
	.sleepCores = coresBoth,
	.wakeUpPin = wakeUpPinHigh(true),
	.wakeUpTime = wakeUpDelay(0, 0, 0, 20), // day, hour, minute, second
};

/*******************************************************************************
* File Name: host_main.c
*
* Version 1.0
*
* Description:
*  Simple BLE example project that demonstrates how to configure and use 
*  Cypress's BLE component APIs and application layer callback. Device 
*  Information service is used as an example to demonstrate configuring 
*  BLE service characteristics in the BLE component.
*
* Hardware Dependency:
*  CY8CKIT-062 PSoC6 BLE Pioneer Kit
*
******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation.
******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/

     

/*******************************************************************************
* Function Name: UpdateLedState
********************************************************************************
*
* Summary:
*   Handles indications on Advertising and Disconnection LEDs.
*
* NOTE: To set breakpoints, please disable compiler inline optimizations
* using -fno-inline or -O0
*******************************************************************************/
void UpdateLedState(void)
{
    if(Cy_BLE_GetAdvertisementState() == CY_BLE_ADV_STATE_ADVERTISING)
    {
        /* In advertising state, turn off disconnect indication LED */
        Cy_GPIO_Write(LED_R_PORT, LED_R_NUM, 0);

        /* Blink advertising indication LED */
        Cy_GPIO_Inv(LED_B_PORT, LED_B_NUM);
    }
    else if(Cy_BLE_GetNumOfActiveConn() == 0u)
    {
        /* If in disconnected state, turn on disconnect indication LED and turn
        * off Advertising LED.
        */
        Cy_GPIO_Write(LED_R_PORT, LED_R_NUM, 1);
        Cy_GPIO_Write(LED_B_PORT, LED_B_NUM, 0);
    }
    else 
    {
        /* In connected state, turn off disconnect indication and advertising 
        * indication LEDs. 
        */
        Cy_GPIO_Write(LED_R_PORT, LED_R_NUM, 0);
        Cy_GPIO_Write(LED_B_PORT, LED_B_NUM, 0);
    }
}

uint32_t count = 1000;

/*******************************************************************************
* Function Name: _write
********************************************************************************
* Summary: 
* NewLib C library is used to retarget printf to _write. printf is redirected to 
* this function when GCC compiler is used to print data to terminal using UART. 
*
* \param file
* This variable is not used.
* \param *ptr
* Pointer to the data which will be transfered through UART.
* \param len
* Length of the data to be transfered through UART.
*
* \return
* returns the number of characters transferred using UART.
* \ref int
*******************************************************************************/
int _write(int file __attribute__((unused)), char *ptr, int len)
{
    return Cy_SCB_UART_PutArray(UART_HW, ptr, len);
}



/*******************************************************************************
* Function Name: DisUpdateFirmWareRevision
********************************************************************************
*
* Summary:
*   Updates the Firmware Revision characteristic with BLE Stack version.
*
*******************************************************************************/
static void DisUpdateFirmWareRevision(void)
{
    cy_stc_ble_stack_lib_version_t stackVersion;
    uint8_t fwRev[9u] = "0.0.0.000";
    
    if(Cy_BLE_GetStackLibraryVersion(&stackVersion) == CY_BLE_SUCCESS)
    {
        /* Transform numbers to ASCII string */
        fwRev[0u] = stackVersion.majorVersion + '0'; 
        fwRev[2u] = stackVersion.minorVersion + '0';
        fwRev[4u] = stackVersion.patch + '0';
        fwRev[6u] = (stackVersion.buildNumber / 100u) + '0';
        stackVersion.buildNumber %= 100u; 
        fwRev[7u] = (stackVersion.buildNumber / 10u) + '0';
        fwRev[8u] = (stackVersion.buildNumber % 10u) + '0';
    }
    
    Cy_BLE_DISS_SetCharacteristicValue(CY_BLE_DIS_FIRMWARE_REV, sizeof(fwRev), fwRev);
}


/*******************************************************************************
* Function Name: HostMain
********************************************************************************
*
* Summary:
*   Main function for the project.
*
* Theory:
*   The function starts BLE.
*   This function processes all BLE events and also implements the low power 
*   functionality.
*
*******************************************************************************/

uint32_t btcnt = 0;
uint32_t RXtimeout = 0;
uint32_t LEDdelay = 0;
uint8_t RXcnt = 0;

BLEbuffer buffer = {{'O', 'T', 'X'}, 3};

int main(void)
{
	/* enable global interrupts */
	__enable_irq();

    /* Start UART (115200 baud, RX on P9_0, TX on P9_1) */
	UART_Start();

	/* Initialize BLE */
    Ble_Init();

	// start the notifications timer
	//Timer_Start()
    // enable the Blue LED
    Cy_GPIO_Write(LED_B_PORT, LED_B_NUM, 1);
   
    for( ; ; ) {
        /* Cy_Ble_ProcessEvents() allows BLE stack to process pending events */
        Cy_BLE_ProcessEvents();
        
		if (Cy_GPIO_Read(BUTTON_PORT, BUTTON_NUM))
		{
			if (++btcnt == 10) SendNotification();
		}
		else btcnt = 0;
        while (Cy_SCB_UART_GetNumInRxFifo(UART_HW))
        {
            if (RXcnt < 240) buffer.data[RXcnt++] = Cy_SCB_UART_Get(UART_HW);
            RXtimeout = 1000;
        }
        if (RXtimeout && RXtimeout-- == 1)
        {
            buffer.length = RXcnt;
            SendNotification();
            RXcnt = 0;
        }
        if ((++LEDdelay & 16383) == 1) UpdateLedState();
    }
}

