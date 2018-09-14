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
 *!< File Name 					: DMA_Cfg.c
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		: V1.0
 *!< Date     		        	: Sep 7, 2018
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
 * | 1.0         | Create template                               | Sep 7, 2018 | Dumitru Parascan    | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Include section --------------------------------------------------------------------------- */

#include "Dma_Cfg.h"

/*<! Definitions section ----------------------------------------------------------------------- */


/*!< Type definitions section ------------------------------------------------------------------ */


/*!< Exported variables section ---------------------------------------------------------------- */

DMA_ConfigType DMA_ConfigData = {
		.arbitrationAlgorithm = enDMA_ARBITRATION_FIXED_PRIORITY,
		.bEnableDebug = FALSE,
		.bEnableHaltOnError = FALSE
};

static int8_t DmaCfgMap[16] =
    {
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1
    };

DMA_Channel_ConfigType DMA_ChannelsConfig[DMA_USED_CHANNELS] = {

};

/*!< Static variable section ------------------------------------------------------------------- */


/*!< Static functions prototypes sections ------------------------------------------------------ */


/*!< Static functions definition sections ------------------------------------------------------ */


/*!< Function definitions ---------------------------------------------------------------------- */


/****************************************************************************************
 *!< Function    	     : DMA_IsConfigMapped
 *!< @brief		     : Check if configurations were mapped
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t DMA_IsConfigMapped(void)
{
  uint8_t index;
  uint8_t result = 0;

  for (index = 0; index < 16; index++)
    {
      if (DmaCfgMap[index] >= 0)
	{
	  result = 1;
	  break;
	}
    }

  return result;
}



/****************************************************************************************
 *!< Function    	     : DMA_ConfigMapping
 *!< @brief		     : Is used to map the configurations
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_ConfigMap(void)
{
  uint8_t index;

  for (index = 0; index < DMA_USED_CHANNELS; index++)
    {
      DmaCfgMap[DMA_ChannelsConfig[index].channelNumber] = index;
    }

}



/****************************************************************************************
 *!< Function    	     : DMA_GetChannelConfigIndex
 *!< @brief		     : Get the index of channel in configuration array
 *!< Parameters              :
 *!<                   Input : uint8_t channel
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t DMA_GetChannelConfigIndex(uint8_t channel)
{
  return DmaCfgMap[channel];
}


/************************************** END OF FILE **********************************************/
