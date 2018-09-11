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
		.arbitrationAlgorithm = enDMA_ARBITRATION_ROUND_ROBIN,
		.bEnableDebug = FALSE,
		.bEnableHaltOnError = TRUE
};

static uint8_t TCD0_Source[] = {"Hello World"};

DMA_Channel_ConfigType DMA_ChannelsConfig[DMA_USED_CHANNELS] = {
		{
			.channelNumber = 0,
			.srcAddr = (uint32_t)TCD0_Source,
			.dstAddr = (uint32_t)&TCD0_Dest,
			.bUseLinkToChannelAfterRequest = FALSE,
			.bUseLinkToChannelAfterFinish = FALSE,
			.bEnableOnHalfInterrupt = FALSE,
			.bEnableOnFinishInterrupt = FALSE,
			.bEnableOnErrorInterrupt = FALSE,
			.bUseAddrMask = FALSE,
			.bUseOtherSrcAddrOnFinish = FALSE,
			.bUseOtherDstAddrOnFinish = FALSE,
			.srcTransferOffset = 1,
			.dstTransferOffset = 0,
			.transferSize = 0,
			.bytesPerRequest = 1,
			.transferType = enDMA_TRANSFER_MEM2MEM,
			.offsetPerRequest = 0,
			.totalSize = 11,
		}
};

/*!< Static variable section ------------------------------------------------------------------- */


/*!< Static functions prototypes sections ------------------------------------------------------ */


/*!< Static functions definition sections ------------------------------------------------------ */


/*!< Function definitions ---------------------------------------------------------------------- */




/************************************** END OF FILE **********************************************/
