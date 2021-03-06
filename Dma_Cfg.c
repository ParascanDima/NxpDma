/********************************************* Login **********************************************
 *!< File Name 				     	: DMA_Cfg.c
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        	  	: V1.0
 *!< Date     		        	: Sep 7, 2018
 *!< @brief		        	  	:
 *!<                        : (see note at the end of the file)
 *!< Modifiable YES/NO		  :
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
#ifdef USE_DMA
/*<! Definitions section ----------------------------------------------------------------------- */


/*!< Type definitions section ------------------------------------------------------------------ */


/*!< Exported variables section ---------------------------------------------------------------- */

DMA_ConfigType DMA_ConfigDevice = {
		.arbitrationAlgorithm = enDMA_ARBITRATION_ROUND_ROBIN,
		.bEnableDebug = FALSE,
		.bEnableHaltOnError = FALSE
};

static int8_t DmaCfgMap[DMA_TOTAL_CHANNELS] =
    {
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1
    };

DMA_Channel_ConfigType DMA_ChannelsConfig[DMA_TOTAL_CHANNELS];

static uint8_t dmaConfiguredChannels = 0;


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

  for (index = 0; index < dmaConfiguredChannels; index++)
    {
      DmaCfgMap[DMA_ChannelsConfig[index].channelNumber] = index;
    }

}


/****************************************************************************************
 *!< Function    	     : DMA_GetNumberOfConfiguredChannels
 *!< @brief		     : Get the number of configured DMA channels
 *!< Parameters              :
 *!<                   Input :
 *!<                   Output:
 *!< Return                  : Number of configured DMA channels
 *!< Critical section YES/NO : NO
 */
uint8_t DMA_GetNumberOfConfiguredChannels(void)
{
  return dmaConfiguredChannels;
}


/****************************************************************************************
 *!< Function    	     : DMA_AddConfiguredChannel
 *!< @brief		     : Indicates that one channel is configured
 *!< Parameters              :
 *!<                   Input : -
 *!<                   Output: -
 *!< Return                  : -
 *!< Critical section YES/NO : NO
 */
void DMA_AddConfiguredChannel(DMA_Channel_ConfigType channelCfg)
{
  DmaCfgMap[channelCfg.channelNumber] = channelCfg.channelNumber;
  DMA_ChannelsConfig[channelCfg.channelNumber] = channelCfg;
  dmaConfiguredChannels++;

}


/****************************************************************************************
 *!< Function    	     : DMA_AddConfiguredChannel
 *!< @brief		     : Indicates that one channel is no more configured
 *!< Parameters              :
 *!<                   Input : -
 *!<                   Output: -
 *!< Return                  : -
 *!< Critical section YES/NO : NO
 */
void DMA_RemoveConfiguredChannel(uint8_t channel)
{
  dmaConfiguredChannels--;
  DmaCfgMap[channel] = -1;
}


/****************************************************************************************
 *!< Function    	     : DMA_isChannelConfigured
 *!< @brief		     : Check if "channel" is configured
 *!< Parameters              :
 *!<                   Input : uint8_t channel - should be verified if configured
 *!<                   Output: -
 *!< Return                  : -
 *!< Critical section YES/NO : NO
 */
bool DMA_isChannelConfigured(uint8_t channel)
{
  return DmaCfgMap[channel] == -1 ? FALSE : TRUE;
}


#endif /* USE_DMA */
/************************************** END OF FILE **********************************************/
