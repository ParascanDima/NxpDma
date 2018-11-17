/********************************************* Login **********************************************
 *!< File Name 					: DMA_Cfg.h
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
 * | 1.0         | Create template                               | Sep 7, 2018 | Dumitru Parascan | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Define to prevent recursive inclusion ----------------------------------------------------- */
#ifndef DMA_CFG_H_
#define DMA_CFG_H_


/*!< C++ banding section start ----------------------------------------------------------------- */
#ifdef __cplusplus
    extern "C" {
#endif


/*!< Include section --------------------------------------------------------------------------- */

#include "hal_dmaif.h"
#ifdef USE_DMA
/*!< Type definitions section ------------------------------------------------------------------ */




/*!< Definitions section ----------------------------------------------------------------------- */

#define DMA_INITIALY_USED_CHANNELS 0


/*!< Exported variables section ---------------------------------------------------------------- */

extern DMA_ConfigType DMA_ConfigDevice;
extern DMA_Channel_ConfigType DMA_ChannelsConfig[DMA_TOTAL_CHANNELS];


/*!< Functions prototypes sections ------------------------------------------------------------- */


/****************************************************************************************
 *!< Function    	     : DMA_IsConfigMapped
 *!< @brief		     : Check if configurations were mapped
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t DMA_IsConfigMapped(void);



/****************************************************************************************
 *!< Function    	     : DMA_ConfigMap
 *!< @brief		     : Is used to map the configurations
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_ConfigMap(void);



/****************************************************************************************
 *!< Function    	     : DMA_GetNumberOfConfiguredChannels
 *!< @brief		     : Get the number of configured DMA channels
 *!< Parameters              :
 *!<                   Input :
 *!<                   Output:
 *!< Return                  : Number of configured DMA channels
 *!< Critical section YES/NO : NO
 */
uint8_t DMA_GetNumberOfConfiguredChannels(void);


/****************************************************************************************
 *!< Function    	     : DMA_AddConfiguredChannel
 *!< @brief		     : Indicates that one channel is configured
 *!< Parameters              :
 *!<                   Input : -
 *!<                   Output: -
 *!< Return                  : -
 *!< Critical section YES/NO : NO
 */
void DMA_AddConfiguredChannel(DMA_Channel_ConfigType channelCfg);


/****************************************************************************************
 *!< Function    	     : DMA_RemoveConfiguredChannel
 *!< @brief		     : Indicates that one channel is configured
 *!< Parameters              :
 *!<                   Input : -
 *!<                   Output: -
 *!< Return                  : -
 *!< Critical section YES/NO : NO
 */
void DMA_RemoveConfiguredChannel(uint8_t channel);



/****************************************************************************************
 *!< Function    	     : DMA_isChannelConfigured
 *!< @brief		     : Check if "channel" is configured
 *!< Parameters              :
 *!<                   Input : uint8_t channel - should be verified if configured
 *!<                   Output: -
 *!< Return                  : -
 *!< Critical section YES/NO : NO
 */
bool DMA_isChannelConfigured(uint8_t channel);


/*!< C++ banding section finish ---------------------------------------------------------------- */
#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* USE_DMA */
#endif /* DMA_CFG_H_ */


/************************************** END OF FILE **********************************************/
