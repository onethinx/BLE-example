/*******************************************************************************
* File Name: P0_7.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P0_7_ALIASES_H) /* Pins P0_7_ALIASES_H */
#define CY_PINS_P0_7_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P0_7_0			(P0_7__0__PC)
#define P0_7_0_INTR	((uint16)((uint16)0x0001u << P0_7__0__SHIFT))

#define P0_7_INTR_ALL	 ((uint16)(P0_7_0_INTR))

#endif /* End Pins P0_7_ALIASES_H */


/* [] END OF FILE */
