
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
 * Created by: Rolf Nooteboom on 2024-04-09
 *
 * Sample project to demostrate the BLE capabilities with the OTX-18 module
 * 
 * For a description please see:
 * https://github.com/onethinx/BLE-example
 *
 ********************************************************************************/

#include "project.h"
#include "ble.h"

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
        /* In connected state, turn off disconnect indication and turn on 
        * blue LEDs. 
        */
        Cy_GPIO_Write(LED_R_PORT, LED_R_NUM, 0);
        Cy_GPIO_Write(LED_B_PORT, LED_B_NUM, 1);
    }
}

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
   
    for( ; ; ) {
        /* Allow BLE stack to process pending events */
        Cy_BLE_ProcessEvents();
        
        /* Send notification at button press */
		if (Cy_GPIO_Read(BUTTON_PORT, BUTTON_NUM))
		{
			if (++btcnt == 10) SendNotification();
		}
		else btcnt = 0;

        /* Check for data in UART RX buffer */
        while (Cy_SCB_UART_GetNumInRxFifo(UART_HW))
        {
            if (RXcnt < 240) buffer.data[RXcnt++] = Cy_SCB_UART_Get(UART_HW);
            RXtimeout = 1000;
        }
        /* Send notification with UART data after a small timeout */
        if (RXtimeout && RXtimeout-- == 1)
        {
            buffer.length = RXcnt;
            SendNotification();
            RXcnt = 0;
        }

        /* Update Leds once in a while */
        if ((++LEDdelay & 16383) == 1) UpdateLedState();
    }
}

