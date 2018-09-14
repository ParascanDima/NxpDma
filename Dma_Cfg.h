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

/*!< Type definitions section ------------------------------------------------------------------ */




/*!< Definitions section ----------------------------------------------------------------------- */

#define DMA_USED_CHANNELS 0


/*!< Exported variables section ---------------------------------------------------------------- */

extern DMA_ConfigType DMA_ConfigData;
extern DMA_Channel_ConfigType DMA_ChannelsConfig[DMA_USED_CHANNELS];


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
 *!< Function    	     : DMA_GetChannelConfigIndex
 *!< @brief		     : Get the index of channel in configuration array
 *!< Parameters              :
 *!<                   Input : uint8_t channel
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t DMA_GetChannelConfigIndex(uint8_t channel);


/*!< C++ banding section finish ---------------------------------------------------------------- */
#ifdef __cplusplus
	}
#endif /* __cplusplus */


#endif /* DMA_CFG_H_ */


/************************************** END OF FILE **********************************************/
