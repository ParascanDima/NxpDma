/********************************************* Login **********************************************
 *!< File Name 					: dma.h
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		: V1.0
 *!< Date     		        	: Aug 29, 2018
 *!< @brief		        		:
 *!<                            : (see note at the end of the file)
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
 * | 1.0         | Create template                               | Aug 29, 2018 | Dumitru Parascan    | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Define to prevent recursive inclusion ----------------------------------------------------- */
#ifndef DMA_H_
#define DMA_H_


/*!< C++ banding section start ----------------------------------------------------------------- */
#ifdef __cplusplus
    extern "C" {
#endif


/*!< Include section --------------------------------------------------------------------------- */
#include "Modules.h"
#include "Dma_Cfg.h"
#include "Dma_irq.h"

#ifdef USE_DMA
/*!< Type definitions section ------------------------------------------------------------------ */



/*!< Definitions section ----------------------------------------------------------------------- */




/*!< Exported variables section ---------------------------------------------------------------- */



/*!< Functions prototypes sections ------------------------------------------------------------- */


/****************************************************************************************
 *!< Function    	     	 : DMA_Init
 *!< @brief		   			 : This API must be called once during the initialization sequence. It shall perform the following operations:
 *!<                           - Initialize DMAMUX peripheral to a default state.
 *!<                           - Initialize DMA peripheral to a default state.
 *!< Parameters              :
 *!<                   Input : const DMA_ConfigType cfg
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_Init(const DMA_ConfigType* cfg);

/****************************************************************************************
 *!< Function    	     : DMA_Config
 *!< @brief		    	 : This function changes the state of a DMA channel. The following actions are allowed:
 *!<      - Enable: Initialize a given DMA channel. Once executed, the DMA channel is ready to be configured
 *!<        for any type of transfer scheme.
 *!<      Operations done:
 *!<      - Enable channel interrupt, set its priority and assign the callback to the interrupt.
 *!<      - Map source peripheral to DMA channel.
 *!<	  - Update: updates the configuration of a DMA channel.
 *!<      - Disable: Disable a DMA channel and release every resource allocated for it.
 *!<      Operations done:
 *!<      - Disable channel interrupt.
 *!<      - Reset to default the DMA channel.
 *!<      - disable the DMAMUX link for the DMA channel.
 *!< Parameters              :
 *!<                   Input : const DMA_Channel_ConfigType *cfg - Pointer to array of channels configuration structures
 *!<                   		 : uint8_t channelsCount - number of used channels
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_Config(const DMA_Channel_ConfigType *cfg, uint8_t channelsCount);


/****************************************************************************************
 *!< Function    	         : DMA_StartChannel
 *!< @brief		             : This function enables a DMA channel. Once enabled, the DMA channel can receive requests from peripherals.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - handle of the DMA channel to be started
 *!<                   Output: None
 *!< Return                  : DMA_ChannelHdl_t
 *!< Critical section YES/NO : NO
 */
DMA_ChannelHdl_t DMA_StartChannel(DMA_ChannelHdl_t Handle);


/****************************************************************************************
 *!< Function    	     	 : DMA_StopChannel
 *!< @brief		    		 : This function disables a DMA channel. Once disabled, no peripheral request is accepted by the DMA channel anymore.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel to stop.
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_StopChannel(DMA_ChannelHdl_t Handle);


/****************************************************************************************
 *!< Function    	        : DMA_SetupMultiBlockTransfer
 *!< @brief		     		: This function configures a DMA channel for a multi-block transfer.
 *!<      The function considers contiguous memory blocks, each block being transferred upon a single DMA request.
 *!<      Each block is split in a sequence of DMA read/write operations, each read/write operation moves TransferSize bytes of data.
 *!<      Once the last block of data has been transferred, the DMA channel is disabled automatically.
 *!<
 *!<      NOTE: For transfers to/from peripherals, make sure the transfer size is equal to the data buffer size of the peripheral used, otherwise only truncated chunks of data may be transferred (e.g. for a communication IP with an 8-bit data register the transfer size should be 1B, whereas for a 32-bit data register, the transfer size should be 4B).
 *!<      The rationale of this constraint is that, on the peripheral side, the address offset is set to zero, allowing to read/write data from/to the peripheral in a single source read/destination write operation.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel to setup.
 *!<			     		 : DMA_TransferType_t TransferType - Transfer type (M->M, P->M, M->P, P->P)
 *!<			    		 : uint32_t SrcAddr - A source register address or a source memory address.
 *!<			   			 : uint32_t DestAddr - A destination register address or a destination memory address.
			     	 	 	 : DMA_TransferSize_t TransferSize - The number of bytes to be transferred on every DMA write/read. Source/Dest share the same write/read size.
			     	 	 	 : uint32_t BlockSize - The total number of bytes inside a block.
			     	 	 	 : uint32_t BlockCount - The total number of data blocks (one block is transferred upon a DMA request).
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_SetupMultiBlockTransfer(DMA_ChannelHdl_t Handle,
				  DMA_TransferType_t TransferType,
				  uint32_t SrcAddr,
				  uint32_t DestAddr,
				  DMA_TransferSize_t TransferSize,
				  uint32_t BlockSize,
				  uint32_t BlockCount,
				  DMA_RequestSource_t RequestSource,
				  bool stopOnFinish);


/****************************************************************************************
 *!< Function    	     : DMA_SetupScatterGatherTransfer
 *!< @brief		     : This function configures the scatter-gather feature of DMA.
 *!< 			     : When the major loop finished the new TCD structure copied to registers.
 *!< Parameters              :
 *!<                   Input : uint32_t transferControl -
 *!<                   	     : DMA_TransferType_t TransferType - Transfer type (M->M, P->M, M->P, P->P)
 *!<                   	     : uint32_t SrcAddr - A source register address or a source memory address.
 *!<                   	     : uint32_t DestAddr - A destination register address or a destination memory address.
 *!<                   	     : DMA_TransferSize_t TransferSize - The number of bytes to be transferred on every DMA write/read. Source/Dest share the same write/read size.
 *!<                   	     : uint32_t BlockSize - The total number of bytes inside a block.
 *!<                   	     : uint32_t BlockCount - The total number of data blocks (one block is transferred upon a DMA request).
 *!<                   	     : bool stopOnFinish -
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_SetupScatterGatherTransfer(DMA_ChannelHdl_t Handle,
				    uint32_t transferControl,
				    DMA_TransferType_t TransferType,
				    uint32_t SrcAddr,
				    uint32_t DestAddr,
				    DMA_TransferSize_t TransferSize,
				    uint32_t BlockSize,
				    uint32_t BlockCount,
				    DMA_RequestSource_t RequestSource,
				    bool stopOnFinish);



/****************************************************************************************
 *!< Function    	    	 : DMA_GetCurrebtBlockIteration
 *!< @brief		    		 : This function returns the number of remaining blocks to be transferred.
 *!<      The value is updated after a block transfer has completed.
 *!<      In PingPong transfer the value will roll back to the beginning value once completed the last block.
 *!<      This function just returns the value of the CITER register in the channel's TCD area.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel.
 *!<                   Output: None
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t DMA_GetCurrentBlockIteration(DMA_ChannelHdl_t Handle);


/****************************************************************************************
 *!< Function    	     : DMA_ConfigTransferControl
 *!< @brief		     : This function configures the TCD structure. The parameter can be either pointer to TCD register
 *!< 			     : or TCD like memory structure
 *!< Parameters              :
 *!<                   Input : uint32_t transferCtrlPtr
 *!<                   Output:
 *!< Return                  : Std_ReturnType
 *!< Critical section YES/NO : YESNO
 */
Std_ReturnType DMA_ConfigTransferControl(uint32_t transferCtrlPtr, DMA_Channel_ConfigType *cfg);



/****************************************************************************************
 *!< Function    	    	 : DMA_Shutdown
 *!< @brief		    		 : This function shall disable all DMA channels and interrupt sources.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_Shutdown(void);



/****************************************************************************************
 *!< Function    	     : DMA_InstallCallback
 *!< @brief		     : Install callback on specified event.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle -
 *!<                         : DMA_EVENT_t event -
 *!<                         : void (*func)(void*) -
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_InstallCallback(uint32_t transferControl, DMA_EVENT_t event, void (*func)(void*), void* parameter);


/****************************************************************************************
 *!< Function    	     : DMA_InstallCallback
 *!< @brief		     : Install callback on specified event.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle -
 *!<                         : DMA_EVENT_t event -
 *!<                         : void (*func)(void*) -
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_InstallChannelLinkage(uint32_t transferControlOrChn, DMA_ChannelHdl_t HandleLinked);


/****************************************************************************************
 *!< Function    	     : DMA_InstallCallback
 *!< @brief		     : Install callback on specified event.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle -
 *!<                         : DMA_EVENT_t event -
 *!<                         : void (*func)(void*) -
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_InstallChannelOnFinishLinkage(uint32_t transferControlOrChn, DMA_ChannelHdl_t HandleLinked);



/****************************************************************************************
 *!< Function    	     : DMA_GetState
 *!< @brief		     : Get DMA driver state
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : DMA_State_t
 *!< Critical section YES/NO : NO
 */
DMA_State_t DMA_GetState(void);


/*!< C++ banding section finish ---------------------------------------------------------------- */
#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* USE_DMA */
#endif /* DMA_H_ */


/************************************** END OF FILE **********************************************/
