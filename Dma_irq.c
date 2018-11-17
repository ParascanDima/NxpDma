/********************************************* Login **********************************************
 *!< File Name 					: Dma_irq.c
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		: V1.0
 *!< Date     		        	: Sep 13, 2018
 *!< @brief		        		: 
 *!<                           	: (see note at the end of the file)
 *!< Modifiable YES/NO		    : 
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
#ifdef USE_DMA
/*<! Definitions section ----------------------------------------------------------------------- */

#define IS_EMPTY(x)  (x == 0)

/*!< Type definitions section ------------------------------------------------------------------ */


/*!< Exported variables section ---------------------------------------------------------------- */


/*!< Static variable section ------------------------------------------------------------------- */



/*!< Static functions prototypes sections ------------------------------------------------------ */


/*!< Static functions definition sections ------------------------------------------------------ */

void DMA_InterruptHandler(uint8_t channel)
{
	uint16_t remainsBlockSize;
	uint32_t transferControl = HAL_DMA_GetTransferControl(channel);
	uint32_t totalSize = HAL_DMA_GetTotalSize(transferControl);

	HAL_DMA_ClearInterruptFlag(channel);

	remainsBlockSize = HAL_DMA_GetBlockIteration(transferControl);

	DMA_RemoveConfiguredChannel(DMA_ChannelsConfig[channel].channelNumber);
	HAL_DMA_ClearDoneFlag(transferControl);

	if (remainsBlockSize == totalSize || IS_EMPTY(remainsBlockSize) )
	{
		if(DMA_ChannelsConfig[channel].onFinishCallbackParameter == NULL)
		{
			DMA_ChannelsConfig[channel].onFinishCallback((void*)&DMA_ChannelsConfig[channel].channelNumber);
		}
		else
		{
			DMA_ChannelsConfig[channel].onFinishCallback(DMA_ChannelsConfig[channel].onFinishCallbackParameter);
		}
	}
	else
	{
		if (remainsBlockSize == (totalSize>>1) ) {
			if(DMA_ChannelsConfig[channel].onHalfCallbackParameter == NULL)
			{
				DMA_ChannelsConfig[channel].onHalfCallback((void*)&DMA_ChannelsConfig[channel].channelNumber);
			}
			else
			{
				DMA_ChannelsConfig[channel].onHalfCallback(DMA_ChannelsConfig[channel].onHalfCallbackParameter);
			}
		}
	}
}

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
	DMA_InterruptHandler(0);
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
	DMA_InterruptHandler(1);
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
	DMA_InterruptHandler(2);
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
	DMA_InterruptHandler(3);
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
	DMA_InterruptHandler(4);
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
	DMA_InterruptHandler(5);
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
	DMA_InterruptHandler(6);
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
	DMA_InterruptHandler(7);
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
	DMA_InterruptHandler(8);
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
	DMA_InterruptHandler(9);
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
	DMA_InterruptHandler(10);
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
	DMA_InterruptHandler(11);
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
	DMA_InterruptHandler(12);
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
	DMA_InterruptHandler(13);
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
	DMA_InterruptHandler(14);
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
	DMA_InterruptHandler(15);
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

#endif /* USE_DMA */
/************************************** END OF FILE **********************************************/
