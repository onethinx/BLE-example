#pragma once

/***************************************
*       Constants
***************************************/


/***************************************
*       Function Prototypes
***************************************/
void HandleBleProcessing(void);
void Ble_Init(void);
void SendNotification(void);
void StackEventHandler(uint32 event, void* eventParam);

typedef struct 
{
    uint8_t data[243];
    uint8_t length;
} BLEbuffer;