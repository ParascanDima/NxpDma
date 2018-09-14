/************************** (C) 2018 BSS-ONE ******************************************************
 *  @verbatim
 *   Copyright (C) 2018 BSS-ONE
 *   All Rights Reserved.
 *
 *   The reproduction, transmission or use of this document or its contents is not permitted
 *   without express written authority.
 *   Offenders will be liable for damages. All rights, including rights created
 *   by patent grant or registration of a utility model or design, are reserved.
 * @endverbatim
 **************************************************************************************************
 */

/********************************************* Login **********************************************
 *!< File Name 				: Dma_irq.c
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		: V1.0
 *!< Date     		        	: Sep 13, 2018
 *!< @brief		        	: 
 *!<                           		: (see note at the end of the file)
 *!< Modifiable YES/NO		    	: 
 *!< Critical explanation		: 
 **************************************************************************************************
 */

/**************************************************************************************************
 *  --------------------------------------------------------------------------------------------  *
 * |                                  Version control table                                     | *
 *  --------------------------------------------------------------------------------------------  *
 * | Version     | Comments                                      | Date       | Author          | *
 *  --------------------------------------------------------------------------------------------  *
 * | 1.0         | Create template                               | Sep 13, 2018 | Dumitru Parascan    | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Include section --------------------------------------------------------------------------- */

#include "stdint.h"
#include "Dma_irq.h"
#include "hal_dma.h"
#include "Dma_Cfg.h"

/*<! Definitions section ----------------------------------------------------------------------- */

#define IS_EMPTY(x)  (x == 0)

/*!< Type definitions section ------------------------------------------------------------------ */


/*!< Exported variables section ---------------------------------------------------------------- */


/*!< Static variable section ------------------------------------------------------------------- */



/*!< Static functions prototypes sections ------------------------------------------------------ */


/*!< Static functions definition sections ------------------------------------------------------ */


/*!< Function definitions ---------------------------------------------------------------------- */

/****************************************************************************************
 *!< Function    	     : DMA0_IRQHandler
 *!< @brief		     : DMA channel 0 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA0_IRQHandler(void)
{
  uint8_t channel_0_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_0);

  channel_0_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_0);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_0);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_0) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_0_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_0_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA1_IRQHandler
 *!< @brief		     : DMA channel 1 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA1_IRQHandler(void)
{
  uint8_t channel_1_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_1);

  channel_1_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_1);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_1);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_1) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_1_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_1_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA2_IRQHandler
 *!< @brief		     : DMA channel 2 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA2_IRQHandler(void)
{
  uint8_t channel_2_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_2);

  channel_2_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_2);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_2);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_2) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_2_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_2_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA3_IRQHandler
 *!< @brief		     : DMA channel 3 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA3_IRQHandler(void)
{
  uint8_t channel_3_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_3);

  channel_3_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_3);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_3);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_3) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_3_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_3_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA4_IRQHandler
 *!< @brief		     : DMA channel 4 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA4_IRQHandler(void)
{
  uint8_t channel_4_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_4);

  channel_4_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_4);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_4);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_4) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_4_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_4_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA5_IRQHandler
 *!< @brief		     : DMA channel 5 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA5_IRQHandler(void)
{
  uint8_t channel_5_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_5);

  channel_5_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_5);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_5);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_5) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_5_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_5_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA6_IRQHandler
 *!< @brief		     : DMA channel 6 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA6_IRQHandler(void)
{
  uint8_t channel_6_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_6);

  channel_6_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_6);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_6);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_6) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_6_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_6_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA7_IRQHandler
 *!< @brief		     : DMA channel 7 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA7_IRQHandler(void)
{
  uint8_t channel_7_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_7);

  channel_7_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_7);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_7);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_7) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_7_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_7_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA8_IRQHandler
 *!< @brief		     : DMA channel 8 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA8_IRQHandler(void)
{
  uint8_t channel_8_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_8);

  channel_8_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_8);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_8);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_8) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_8_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_8_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA9_IRQHandler
 *!< @brief		     : DMA channel 9 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA9_IRQHandler(void)
{
  uint8_t channel_9_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_9);

  channel_9_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_9);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_9);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_9) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_9_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_9_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA10_IRQHandler
 *!< @brief		     : DMA channel 10 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA10_IRQHandler(void)
{
  uint8_t channel_10_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_10);

  channel_10_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_10);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_10);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_10) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_10_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_10_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA11_IRQHandler
 *!< @brief		     : DMA channel 11 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA11_IRQHandler(void)
{
  uint8_t channel_11_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_11);

  channel_11_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_11);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_11);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_11) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_11_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_11_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA12_IRQHandler
 *!< @brief		     : DMA channel 12 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA12_IRQHandler(void)
{
  uint8_t channel_12_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_12);

  channel_12_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_12);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_12);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_12) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_12_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_12_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA13_IRQHandler
 *!< @brief		     : DMA channel 13 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA13_IRQHandler(void)
{
  uint8_t channel_13_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_13);

  channel_13_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_13);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_13);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_13) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_13_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_13_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA14_IRQHandler
 *!< @brief		     : DMA channel 14 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA14_IRQHandler(void)
{
  uint8_t channel_14_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_14);

  channel_14_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_14);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_14);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_14) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_14_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_14_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA15_IRQHandler
 *!< @brief		     : DMA channel 15 transfer complete handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA15_IRQHandler(void)
{
  uint8_t channel_15_Index;
  uint16_t remainsBlockSize;

  HAL_DMA_ClearInterruptFlag(DMA_CHANNEL_15);

  channel_15_Index = DMA_GetChannelConfigIndex(DMA_CHANNEL_15);
  remainsBlockSize = HAL_DMA_GetBlockIteration(DMA_CHANNEL_15);

  if (remainsBlockSize == HAL_DMA_GetTotalSize(DMA_CHANNEL_15) || IS_EMPTY(remainsBlockSize))
    {
      DMA_ChannelsConfig[channel_15_Index].onFinishCallback();
    }
  else
    {
      DMA_ChannelsConfig[channel_15_Index].onHalfCallback();
    }
}



/****************************************************************************************
 *!< Function    	     : DMA_Error_IRQHandler
 *!< @brief		     : DMA error interrupt channels 0-15 handler
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : YES
 */
void DMA_Error_IRQHandler(void)
{

}


/************************************** END OF FILE **********************************************/
