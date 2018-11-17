/********************************************* Login **********************************************
 *!< File Name 					: dma.c
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		: V1.0
 *!< Date     		        	: Aug 29, 2018
 *!< @brief		        		:
 *!<                           	: (see note at the end of the file)
 *!< Modifiable YES/NO		    : YES
 *!< Critical explanation		: No
 **************************************************************************************************
 */

/**************************************************************************************************
 *  --------------------------------------------------------------------------------------------  *
 * |                                  Version control table                                     | *
 *  --------------------------------------------------------------------------------------------  *
 * | Version     | Comments                                      | Date       | Author          | *
 *  --------------------------------------------------------------------------------------------  *
 * | 1.0         | Create template                               | Aug 29, 2018 | Dumitru Parascan   | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Include section --------------------------------------------------------------------------- */

#include "dma.h"
#include "hal_dma.h"
#ifdef USE_DMA

/*<! Definitions section ----------------------------------------------------------------------- */


/*!< Type definitions section ------------------------------------------------------------------ */


/*!< Exported variables section ---------------------------------------------------------------- */


/*!< Static variable section ------------------------------------------------------------------- */

static DMA_State_t dmaState = enIdle;

/*!< Static functions prototypes sections ------------------------------------------------------ */


/*!< Static functions definition sections ------------------------------------------------------ */


/*!< Function definitions ---------------------------------------------------------------------- */

/****************************************************************************************
 *!< Function    	    	 : DMA_Init
 *!< @brief		    		 : This API must be called once during the initialization sequence. It shall perform the following operations:
 *!<                         : - Initialize DMAMUX peripheral to a default state.
 *!<                         : - Initialize DMA peripheral to a default state.
 *!< Parameters              :
 *!<                   Input : DMA_ConfigType cfg
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_Init(const DMA_ConfigType* cfg)
{
	HAL_DMA_SetChannelsArbitration((uint8_t)cfg->arbitrationAlgorithm);
	HAL_DMA_SetHaltOnError(cfg->bEnableHaltOnError);
	HAL_DMA_EnableDebug(cfg->bEnableDebug);
}

/****************************************************************************************
 *!< Function    	    	 : DMA_Config
 *!< @brief		     		 : This function changes the state of a DMA channel. The following actions are allowed:
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
 *!<                   Input : DMA_Channel_ConfigType *cfg - Pointer to array of channels configuration structures
 *!<                   		 : uint8_t channelsCount - number of used channels
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_Config(const DMA_Channel_ConfigType *cfg, uint8_t channelsCount)
{
  uint8_t index;
  uint32_t transferControl;

  INT_SYS_EnableIRQ(DMA0_IRQn);
  for (index = 0; index < channelsCount; index++)
    {
      HAL_DMA_InitChannelMUX(cfg[index].channelNumber, cfg[index].requestSource, enNormalMode);

      transferControl = HAL_DMA_GetTransferControl(cfg[index].channelNumber);

      if (cfg->transferType != enDMA_TRANSFER_PERIPH2PERIPH)
	{
	  HAL_DMA_EnableOffsetsPerRequest(enEnable);
	}

      /*!<
       *!< @brief Set channel priority if Fixed Priority arbitration is used.
       *!< */
      if(HAL_DMA_GetArbitrationAlgorith() == enDMA_ARBITRATION_FIXED_PRIORITY)
	{
	  HAL_DMA_SetChannelPriority(cfg[index].channelNumber, cfg[index].priority);
	}

	if (DMA_ConfigTransferControl(transferControl, (DMA_Channel_ConfigType *)&cfg[index]) == E_OK) {
	  DMA_AddConfiguredChannel(cfg[index]);
	}
    }
}


/****************************************************************************************
 *!< Function    	     	 : DMA_StartChannel
 *!< @brief		     		 : This function enables a DMA channel. Once enabled, the DMA channel can receive requests from peripherals.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - handle of the DMA channel to be started
 *!<                   Output: None
 *!< Return                  : DMA_ChannelHdl_t
 *!< Critical section YES/NO : NO
 */
DMA_ChannelHdl_t DMA_StartChannel(DMA_ChannelHdl_t Handle)
{
    INT_SYS_EnableIRQ(Handle);
	HAL_DMA_EnableRequest(Handle);
	return Handle;
}


/****************************************************************************************
 *!< Function    	     	 : DMA_StopChannel
 *!< @brief		     		 : This function disables a DMA channel. Once disabled, no peripheral request is accepted by the DMA channel anymore.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel to stop.
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_StopChannel(DMA_ChannelHdl_t Handle)
{
  DMA_RemoveConfiguredChannel(Handle);
  HAL_DMA_DisableRequestAfterFinish(Handle);
  INT_SYS_DisableIRQ(Handle);
}


/****************************************************************************************
 *!< Function    	     : DMA_SetupMultiBlockTransfer
 *!< @brief		     : This function configures a DMA channel for a multi-block transfer.
 *!<      The function considers contiguous memory blocks, each block being transferred upon a single DMA request.
 *!<      Each block is split in a sequence of DMA read/write operations, each read/write operation moves TransferSize bytes of data.
 *!<      Once the last block of data has been transferred, the DMA channel is disabled automatically.
 *!<
 *!<      NOTE: For transfers to/from peripherals, make sure the transfer size is equal to the data buffer size of the peripheral used, otherwise only truncated chunks of data may be transferred (e.g. for a communication IP with an 8-bit data register the transfer size should be 1B, whereas for a 32-bit data register, the transfer size should be 4B).
 *!<      The rationale of this constraint is that, on the peripheral side, the address offset is set to zero, allowing to read/write data from/to the peripheral in a single source read/destination write operation.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel to setup.
 *!<			     : DMA_TransferType_t TransferType - Transfer type (M->M, P->M, M->P, P->P)
 *!<			     : uint32_t SrcAddr - A source register address or a source memory address.
 *!<			     : uint32_t DestAddr - A destination register address or a destination memory address.
			     : DMA_TransferSize_t TransferSize - The number of bytes to be transferred on every DMA write/read. Source/Dest share the same write/read size.
			     : uint32_t BlockSize - The total number of bytes inside a block.
			     : uint32_t BlockCount - The total number of data blocks (one block is transferred upon a DMA request).
			     : DMA_RequestSource_t RequestSource
			     : bool stopOnFinish
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
				  bool stopOnFinish)
{

	DMA_Channel_ConfigType cfg = {
	    .bUseAddrMask = FALSE,
	    .bUseLinkToChannelAfterFinish = FALSE,
	    .bUseLinkToChannelAfterRequest = FALSE,
	    .bStopOnFinish = stopOnFinish,
	    .bytesPerRequest = BlockSize,
	    .channelNumber = Handle,
	    .dstAddr = DestAddr,
	    .srcAddr = SrcAddr,
	    .offsetPerRequest = 0,
	    .transferType = TransferType,
	    .transferSize = TransferSize,
	    .totalSize = (uint16_t)BlockSize*BlockCount,
	    .requestSource = RequestSource,
	};

	DMA_Config(&cfg, 1);
}


/****************************************************************************************
 *!< Function    	     : DMA_SetupScatterGatherTransfer
 *!< @brief		     : This function configures the scatter-gather feature of DMA.
 *!< 			     : When the major loop finished the new TCD structure copied to registers.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel to setup.
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
				    bool stopOnFinish)
{
  uint32_t transferCtrlReg = HAL_DMA_GetTransferControl(Handle);

  DMA_Channel_ConfigType cfg = {
      .bUseAddrMask = FALSE,
      .bUseLinkToChannelAfterFinish = FALSE,
      .bUseLinkToChannelAfterRequest = FALSE,
      .bStopOnFinish = TRUE,
      .bytesPerRequest = BlockSize,
      .dstAddr = DestAddr,
      .srcAddr = SrcAddr,
      .offsetPerRequest = 0,
      .transferType = TransferType,
      .transferSize = TransferSize,
      .totalSize = (uint16_t)BlockSize*BlockCount,
      .requestSource = RequestSource,
  };

  DMA_ConfigTransferControl(transferControl, &cfg);
  HAL_DMA_SetDstAddrAdjustment(transferCtrlReg, transferControl);
  HAL_DMA_EnableScatterGather(transferCtrlReg, TRUE);
}



/****************************************************************************************
 *!< Function    	     : DMA_GetCurrebtBlockIteration
 *!< @brief		     : This function returns the number of remaining blocks to be transferred.
 *!<      The value is updated after a block transfer has completed.
 *!<      In PingPong transfer the value will roll back to the beginning value once completed the last block.
 *!<      This function just returns the value of the CITER register in the channel's TCD area.
 *!< Parameters              :
 *!<                   Input : DMA_ChannelHdl_t Handle - Handle of the DMA channel.
 *!<                   Output: None
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t DMA_GetCurrentBlockIteration(DMA_ChannelHdl_t Handle)
{
	return HAL_DMA_GetBlockIteration(Handle);
}


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
Std_ReturnType DMA_ConfigTransferControl(uint32_t transferCtrlPtr, DMA_Channel_ConfigType *cfg)
{

  uint8_t accessToMLOFF = FALSE;
  uint16_t minorLoopCount = 1;
  Std_ReturnType response = E_OK;

  HAL_DMA_ClearTransferControlDescriptor(transferCtrlPtr);

  /*!<
   *!< @brief Configure the source and destination offset after request.
   *!< */
  switch (cfg->transferType) {

    case enDMA_TRANSFER_PERIPH2MEM:
      /*!<
       *!< @brief Only destination offset is enabled.
       *!< */
      if(cfg->offsetPerRequest != 0)
	{
	  HAL_DMA_SetDstRequestOffset(transferCtrlPtr, enEnable);
	  accessToMLOFF = TRUE;
	}

      cfg->srcTransferOffset = 0;
      cfg->dstTransferOffset = (uint16_t)cfg->transferSize;
      break;

    case enDMA_TRANSFER_MEM2PERIPH:
      /*!<
       *!< @brief Only source offset is enabled.
       *!< */
      if(cfg->offsetPerRequest != 0)
	{
	  HAL_DMA_SetSrcRequestOffset(transferCtrlPtr, enEnable);
	  accessToMLOFF = TRUE;
	}

      cfg->srcTransferOffset = (uint16_t)cfg->transferSize;
      cfg->dstTransferOffset = 0;
      break;

    case enDMA_TRANSFER_MEM2MEM:
      /*!<
       *!< @brief Both destination and source offset enabled.
       *!< */
      if(cfg->offsetPerRequest != 0)
	{
	  HAL_DMA_SetSrcRequestOffset(transferCtrlPtr, enEnable);
	  HAL_DMA_SetDstRequestOffset(transferCtrlPtr, enEnable);
	  accessToMLOFF = TRUE;
	}

      cfg->srcTransferOffset = (uint16_t)cfg->transferSize;
      cfg->dstTransferOffset = (uint16_t)cfg->transferSize;
      break;

    default:

      cfg->srcTransferOffset = 0;
      cfg->dstTransferOffset = 0;
      break;
  }
  /*!<
   *!< @brief If transfer type is valid the offset should be set.
   *!< */
  if (accessToMLOFF)
    {
      HAL_DMA_UseOffsetPerRequest(transferCtrlPtr, cfg->offsetPerRequest);
    }

  HAL_DMA_SetRequestBlockSize(transferCtrlPtr, cfg->bytesPerRequest);

  /*!<
   *!< @brief Configure the initial source and destination addresses.
   *!< */
  HAL_DMA_SetSrcAddr(transferCtrlPtr, cfg->srcAddr);
  HAL_DMA_SetDstAddr(transferCtrlPtr, cfg->dstAddr);

  /*!<
   *!< @brief Configure the source read/destination write size
   *!< */
  HAL_DMA_SetSrcTransferSize(transferCtrlPtr, cfg->transferSize);
  HAL_DMA_SetDstTransferSize(transferCtrlPtr, cfg->transferSize);

  /*!<
   *!< @brief Configure the offset after each source read/destination write operation.
   *!< */
  HAL_DMA_SetSrcTransferOffset(transferCtrlPtr, cfg->srcTransferOffset);
  HAL_DMA_SetDstTransferOffset(transferCtrlPtr, cfg->dstTransferOffset);

  /*!<
   *!< @brief Configure the cyclic buffer transmission of 2^n bytes (n - value of mask).
   *!< */
  if (cfg->bUseAddrMask)
    {
      HAL_DMA_SetSrcAddrMask(transferCtrlPtr, cfg->srcAddrMask);
      HAL_DMA_SetDstAddrMask(transferCtrlPtr, cfg->dstAddrMask);
    }
  else
    {
      /*!<
       *!< @brief Disable modulo feature.
       *!< */
      HAL_DMA_SetSrcAddrMask(transferCtrlPtr, 0x00);
      HAL_DMA_SetDstAddrMask(transferCtrlPtr, 0x00);
    }

  if (cfg->transferType != enDMA_TRANSFER_PERIPH2PERIPH &&
      cfg->transferType !=enDMA_TRANSFER_PERIPH2MEM)
    {
      /*!<
       *!< @brief Set the source address to starts with after finishing buffer transmission.
       *!< */
      if (cfg->bUseOtherSrcAddrOnFinish)
	{
	  HAL_DMA_SetSrcAddrAdjustment(transferCtrlPtr, cfg->srcAddrAdjustment);
	}
      else
	{
	  HAL_DMA_SetSrcAddrAdjustment(transferCtrlPtr, -(cfg->totalSize));
	}
    }
  if (cfg->transferType != enDMA_TRANSFER_PERIPH2PERIPH &&
      cfg->transferType !=enDMA_TRANSFER_MEM2PERIPH)
    {
      /*!<
       *!< @brief Set the destination address to starts with after finishing buffer transmission.
       *!< 		The Scatter/Gather processing should be considered (not implemented)
       *!< */
      if (cfg->bUseOtherDstAddrOnFinish)
	{
	  HAL_DMA_SetDstAddrAdjustment(transferCtrlPtr, cfg->dstAddrOnFinish);
	}
      else
	{
	  HAL_DMA_SetDstAddrAdjustment(transferCtrlPtr, -(cfg->totalSize));
	}
    }

  /*!<
   *!< @brief Set the link channel after minor loop termination.
   *!< */
  HAL_DMA_ChannelsLinkOnRequestFinish(transferCtrlPtr, cfg->bUseLinkToChannelAfterRequest);
  if (cfg->bUseLinkToChannelAfterRequest)
    {
      HAL_DMA_SetLinkedChannelOnRequestFinish(transferCtrlPtr, cfg->afterRequestLinkedChannel);
    }

  /*!<
   *!< @brief Compute the request counts for buffer transmission.
   *!< */
  if(cfg->totalSize % cfg->bytesPerRequest != 0)
    {
      minorLoopCount = (cfg->totalSize/cfg->bytesPerRequest)+1;
    }
  else
    {
      minorLoopCount = (cfg->totalSize/cfg->bytesPerRequest);
    }
  HAL_DMA_SetRequestCountToFinish(transferCtrlPtr, minorLoopCount);

  /*!<
   *!< @brief Set the link channel after major loop termination.
   *!< */
  HAL_DMA_ChannelsLinkOnRequestFinish(transferCtrlPtr, cfg->bUseLinkToChannelAfterFinish);
  if (cfg->bUseLinkToChannelAfterFinish)
    {
      HAL_DMA_SetLinkedChannelOnRequestFinish(transferCtrlPtr, cfg->afterFinishLinkedChannel);
    }

  /*!<
   *!< @brief Enable/disable Half transfer interrupt.
   *!< */
  if (cfg->onHalfCallback != NULL)
    {
      HAL_DMA_HalfMajorLoopInterrupt(transferCtrlPtr, TRUE);
    }

  /*!<
   *!< @brief Enable/disable Complete transfer interrupt.
   *!< */
  if (cfg->onFinishCallback != NULL)
    {
      HAL_DMA_CompleteMajorLoopInterrupt(transferCtrlPtr, TRUE);
    }

  /*!<
   *!< @brief Enable/disable Error interrupt.
   *!< */
  if (cfg->onErrorCallback != NULL)
    {
      HAL_DMA_EnableErrorInterrupt(transferCtrlPtr, TRUE);
    }

  if (cfg->bStopOnFinish)
    {
      HAL_DMA_DisableRequestAfterFinish(transferCtrlPtr);
    }

  return response;
}



/****************************************************************************************
 *!< Function    	    	 : DMA_Shutdown
 *!< @brief		    		 : This function shall disable all DMA channels and interrupt sources.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output: None
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void DMA_Shutdown(void)
{
	HAL_DMA_DisableAllRequests();
	HAL_DMA_DisableAllErrorInterrupts();
}


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
void DMA_InstallCallback(uint32_t transferControl, DMA_EVENT_t event, void (*func)(void*), void* callbackParameter)
{
  uint32_t chNumber;
  DMA_Channel_ConfigType *channel;

  if (transferControl < DMA_TOTAL_CHANNELS)
    {
      chNumber = transferControl;
      transferControl = HAL_DMA_GetTransferControl(chNumber);
    }
  else
    {
      chNumber = HAL_DMA_GetChnNrByTcd(transferControl);
      if (chNumber >= DMA_TOTAL_CHANNELS){
	  return;
      }
    }
  channel = &DMA_ChannelsConfig[chNumber];

  switch (event) {
    case enDMA_On_Finish:
      channel->onFinishCallback = func;
      channel->onFinishCallbackParameter = callbackParameter;
      HAL_DMA_CompleteMajorLoopInterrupt(transferControl, TRUE);
      break;

    case enDMA_On_Half:
      channel->onHalfCallback = func;
      channel->onHalfCallbackParameter = callbackParameter;
      HAL_DMA_HalfMajorLoopInterrupt(transferControl, TRUE);
      break;

    case enDMA_On_Error:
      channel->onErrorCallback = func;
      channel->onErrorCallbackParameter = callbackParameter;
      HAL_DMA_EnableErrorInterrupt(transferControl, TRUE);
      break;

    default:
      break;
  }
}


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
void DMA_InstallChannelLinkage(uint32_t transferControlOrChn, DMA_ChannelHdl_t HandleLinked)
{
  uint32_t chNumber;
  DMA_Channel_ConfigType *channel;

  if (transferControlOrChn < DMA_TOTAL_CHANNELS)
    {
      chNumber = transferControlOrChn;
      transferControlOrChn = HAL_DMA_GetTransferControl(chNumber);
    }
  else
    {
      chNumber = HAL_DMA_GetChnNrByTcd(transferControlOrChn);
      if (chNumber >= DMA_TOTAL_CHANNELS){
	  return;
      }
    }
  channel = &DMA_ChannelsConfig[chNumber];

  channel->bUseLinkToChannelAfterRequest = TRUE;
  channel->afterRequestLinkedChannel = HandleLinked;
  HAL_DMA_SetLinkedChannelOnRequestFinish(transferControlOrChn, HandleLinked);
}


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
void DMA_InstallChannelOnFinishLinkage(uint32_t transferControlOrChn, DMA_ChannelHdl_t HandleLinked)
{
  uint32_t chNumber;
  DMA_Channel_ConfigType *channel;

  if (transferControlOrChn < DMA_TOTAL_CHANNELS)
    {
      chNumber = transferControlOrChn;
      transferControlOrChn = HAL_DMA_GetTransferControl(chNumber);
    }
  else
    {
      chNumber = HAL_DMA_GetChnNrByTcd(transferControlOrChn);
      if (chNumber >= DMA_TOTAL_CHANNELS){
	  return;
      }
    }
  channel = &DMA_ChannelsConfig[chNumber];

  channel->bUseLinkToChannelAfterFinish = TRUE;
  channel->afterFinishLinkedChannel = HandleLinked;
  HAL_DMA_SetLinkedChannelOnMajorLoop(transferControlOrChn, HandleLinked);
}



/****************************************************************************************
 *!< Function    	    	 : DMA_GetState
 *!< @brief		 		     : Get DMA driver state
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : DMA_State_t
 *!< Critical section YES/NO : NO
 */
DMA_State_t DMA_GetState(void)
{

	if (dmaState == enActive || dmaState == enReady)
	{
		if (HAL_DMA_ReportErrors() == 0)
		{
			dmaState = (DMA_State_t)(HAL_DMA_GetEngineState()+1);
		}
		else
		{
			dmaState = enError;
		}
	}
	else
	{

	}

	return dmaState;
}

#endif /* USE_DMA */
/************************************** END OF FILE **********************************************/
