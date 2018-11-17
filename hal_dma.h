/********************************************* Login **********************************************
 *!< File Name 					    : hal_dma.h
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		  : V1.0
 *!< Date     		        	: Aug 30, 2018
 *!< @brief		        		  :
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
 * | 1.0         | Create template                               | Aug 30, 2018 | Dumitru Parascan    | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Define to prevent recursive inclusion ----------------------------------------------------- */
#ifndef HAL_DMA_H_
#define HAL_DMA_H_


/*!< C++ banding section start ----------------------------------------------------------------- */
#ifdef __cplusplus
    extern "C" {
#endif


/*!< Include section --------------------------------------------------------------------------- */

#include "hal_dmaif.h"

#ifdef USE_DMA
/*!< Definitions section ----------------------------------------------------------------------- */

#define DMA_CHANNEL_0           0U
#define DMA_CHANNEL_1           1U
#define DMA_CHANNEL_2           2U
#define DMA_CHANNEL_3           3U
#define DMA_CHANNEL_4           4U
#define DMA_CHANNEL_5           5U
#define DMA_CHANNEL_6           6U
#define DMA_CHANNEL_7           7U
#define DMA_CHANNEL_8           8U
#define DMA_CHANNEL_9           9U
#define DMA_CHANNEL_10          10U
#define DMA_CHANNEL_11          11U
#define DMA_CHANNEL_12          12U
#define DMA_CHANNEL_13          13U
#define DMA_CHANNEL_14          14U
#define DMA_CHANNEL_15          15U

#define DMA_CHANNEL_INEXISTENT  99U



/*!< Type definitions section ------------------------------------------------------------------ */

/*!<
 *!< @brief Definition of DMA channels
 *!< */
typedef enum {

  enDMA_ChannelFlag_0  = (1<<DMA_CHANNEL_0),         /* Channel 0                              */
  enDMA_ChannelFlag_1  = (1<<DMA_CHANNEL_1),         /* Channel 1                              */
  enDMA_ChannelFlag_2  = (1<<DMA_CHANNEL_2),         /* Channel 2                              */
  enDMA_ChannelFlag_3  = (1<<DMA_CHANNEL_3),         /* Channel 3                              */
  enDMA_ChannelFlag_4  = (1<<DMA_CHANNEL_4),         /* Channel 4                              */
  enDMA_ChannelFlag_5  = (1<<DMA_CHANNEL_5),         /* Channel 5                              */
  enDMA_ChannelFlag_6  = (1<<DMA_CHANNEL_6),         /* Channel 6                              */
  enDMA_ChannelFlag_7  = (1<<DMA_CHANNEL_7),         /* Channel 7                              */
  enDMA_ChannelFlag_8  = (1<<DMA_CHANNEL_8),         /* Channel 8                              */
  enDMA_ChannelFlag_9  = (1<<DMA_CHANNEL_9),         /* Channel 9                              */
  enDMA_ChannelFlag_10 = (1<<DMA_CHANNEL_10),        /* Channel 10                             */
  enDMA_ChannelFlag_11 = (1<<DMA_CHANNEL_11),        /* Channel 11                             */
  enDMA_ChannelFlag_12 = (1<<DMA_CHANNEL_12),        /* Channel 12                             */
  enDMA_ChannelFlag_13 = (1<<DMA_CHANNEL_13),        /* Channel 13                             */
  enDMA_ChannelFlag_14 = (1<<DMA_CHANNEL_14),        /* Channel 14                             */
  enDMA_ChannelFlag_15 = (1<<DMA_CHANNEL_15),        /* Channel 15                             */

} DMA_ChannelFlag_t;


/*!<
 *!< @brief Definition of DMA errors
 *!< */
typedef enum {

  enDestinationBusError = (1<<0),                    /*  */
  enSourseBusError = (1<<1),                         /*  */
  enScatterGatherCfgError = (1<<2),                  /*  */
  enCITERError = (1<<3),                             /*  */
  enDestinationOffsetError = (1<<4),                 /*  */
  enDestinationAddrError = (1<<5),                   /*  */
  enSourceOffsetError = (1<<6),                      /*  */
  enSourseAddrError = (1<<7),                        /*  */
  enChannelPriorityError = (1<<14),                   /*  */
  enTransferCanceledError = (1<<16),                  /*  */

} DMA_Error_t;



/*!< Exported variables section ---------------------------------------------------------------- */



/*!< Functions prototypes sections ------------------------------------------------------------- */


/****************************************************************************************
 *!< Function    	    	 : HAL_DMA_GetEngineState
 *!< @brief		    		 : Shows either DMA engine active or not
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetEngineState(void);


/****************************************************************************************
 *!< Function    	         : HAL_DMA_GetChannelState
 *!< @brief		             : Shows either DMA channel active or not
 *!< Parameters              :
 *!<                   Input : uint8_t channel - specify which channel state is required
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetChannelState(uint8_t channel);


/****************************************************************************************
 *!< Function    	    	 : HAL_DMA_ReportErrors
 *!< @brief		    		 : Indicates if some DMA errors appear
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : YESNO
 */
uint8_t HAL_DMA_ReportErrors(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ReportErrors
 *!< @brief		    		 : Indicates if some DMA errors appear.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint16_t
 *!< Critical section YES/NO : no
 */
uint16_t HAL_DMA_GetTotalSize(uint32_t transferCtrlPtr);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetArbitrationAlgorith
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : DMA_Arbitration_Algorithm_t
 *!< Critical section YES/NO : no
 */
DMA_Arbitration_Algorithm_t HAL_DMA_GetArbitrationAlgorith(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ClearErrorFlag
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ClearErrorFlag(uint8_t channelNumber);


/****************************************************************************************
 *!< Function    	     : HAL_DMA_IsChannelActive
 *!< @brief		     : Shows either channel active or not.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t HAL_DMA_GetTransferControl(uint8_t channelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_UseOffsetPerRequest
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint32_t transferCtrlPtr
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_UseOffsetPerRequest(uint32_t transferCtrlPtr, int32_t transferOffset);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcTransferOffset
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcTransferOffset(uint32_t transferCtrlPtr, int16_t transferOffset);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcTransferOffset
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstTransferOffset(uint32_t transferCtrlPtr, int16_t transferOffset);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ClearInterruptFlag
 *!< @brief		    		 : Clear interrupt flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channel
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ClearInterruptFlag(uint8_t channelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetInterruptedChannel
 *!< @brief		    		 : Shows on which channel interrupt request is active.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t - represents the interrupted channel number.
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetInterruptedChannel(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_CancelTransfers
 *!< @brief		    		 : Cancel the remaining data transfer.
 *!< 						 : Stop the executing channel and force the minor loop to finish.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_CancelTransfers(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_CancelTransferWithError
 *!< @brief		    		 : Cancel the remaining data transfer.
 *!< 						 : Stop the executing channel and force the minor loop to finish
 *!< 						 : and treats the cancel as an error condition.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_CancelTransferWithError(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_HaltOperations
 *!< @brief		    		 : Stall the start of any new channels.
 *!< 						 : Executing channels are allowed to complete.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_HaltOperations(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ResumeOperations
 *!< @brief		    		 : Enables the operations halted by setting the HALT bit in CR register.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ResumeOperations(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableRequest
 *!< @brief		    		 : Enables request on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableRequest(uint8_t channelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableRequest
 *!< @brief		    		 : Disables request on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableRequestImmediately(uint8_t channelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableAllRequests
 *!< @brief		    		 : Disables all requests.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableAllRequests(void);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableRequestAfterFinish
 *!< @brief		    		 : Enables request on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableRequestAfterFinish(uint32_t transferCtrlPtr);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableMemMappedRegisters
 *!< @brief		    		 : Set 1 to NOP bit of CEEI, SEEI, CERQ, SERQ, CDNE, SSRT, CERR, CINT registers.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableMemMappedRegisters(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ClearAllErrorInterrupts
 *!< @brief		    		 : Disables all error interrupts.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableAllErrorInterrupts(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetChannelReportedError
 *!< @brief		    		 : Shows which channel catched error
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetChannelReportedError(void);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ErrorInterrupt
 *!< @brief		    		 : Enables error interrupt on one channel
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableErrorInterrupt(uint8_t channelNumber, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetChannelPriority
 *!< @brief		    		 : Set channel priority (is ignored if ERCA bit (CR register) is 0)
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   		 : uint8_t priority
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetChannelPriority(uint8_t channelNumber, uint8_t priority);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_IsChannelActive
 *!< @brief		    		 : Shows either channel active or not.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_IsChannelActive(uint8_t channelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcAddrOnFinish
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, int32_t adj
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcAddrAdjustment(uint32_t transferCtrlPtr, int32_t adj);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstAddrOnFinish
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, int32_t adj
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstAddrAdjustment(uint32_t transferCtrlPtr, int32_t adj);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetChannelsArbitration
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t arbitrationType
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetChannelsArbitration(uint8_t arbitrationType);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetHaltOnError
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t bHOE
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetHaltOnError(uint8_t bHOE);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableDebug
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t bDBG
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableDebug(uint8_t bDBG);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetSrcAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t HAL_DMA_GetSrcAddr(uint8_t channelNumber);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint32_t srcAddr
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcAddr(uint32_t transferCtrlPtr, uint32_t srcAddr);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint32_t dstAddr
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstAddr(uint32_t transferCtrlPtr, uint32_t dstAddr);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetDstAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t HAL_DMA_GetDstAddr(uint32_t transferCtrlPtr);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcAddrMask
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint8_t mask
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcAddrMask(uint32_t transferCtrlPtr, uint8_t mask);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstAddrMask
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint8_t mask
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstAddrMask(uint32_t transferCtrlPtr, uint8_t mask);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcTransferSize
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_TransferSize_t size
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcTransferSize(uint32_t transferCtrlPtr, DMA_TransferSize_t size);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstTransferSize
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_TransferSize_t size
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstTransferSize(uint32_t transferCtrlPtr, DMA_TransferSize_t size);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcRequestOffset
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcRequestOffset(uint32_t transferCtrlPtr, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstRequestOffset
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstRequestOffset(uint32_t transferCtrlPtr, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableOffsetsPerRequest
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableOffsetsPerRequest(DMA_Decision_t decision);


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetRequestBlockSize
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint32_t size
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetRequestBlockSize(uint32_t transferCtrlPtr, uint32_t size);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableChannelsLinkOnMinorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ChannelsLinkOnRequestFinish(uint32_t transferCtrlPtr, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetLinkedChannelOnRequestFinish
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint8_t linkedChannelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetLinkedChannelOnRequestFinish(uint32_t transferCtrlPtr, uint8_t linkedChannelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableChannelsLinkOnMinorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetRequestCountToFinish(uint32_t transferCtrlPtr, uint16_t minorLoops);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetBlockIteration
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint16_t
 *!< Critical section YES/NO : NO
 */
uint16_t HAL_DMA_GetBlockIteration(uint32_t transferCtrlPtr);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetBandwidthControl
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_BWC_t bandwidth
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetBandwidthControl(uint32_t transferCtrlPtr, DMA_BWC_t bandwidth);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableChannelsLinkOnMajorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ChannelsLinkOnMajorLoop(uint32_t transferCtrlPtr, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetLinkedChannelOnMajorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetLinkedChannelOnMajorLoop(uint32_t transferCtrlPtr, uint8_t linkedChannelNumber);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_HalfMajorLoopInterrupt
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_HalfMajorLoopInterrupt(uint32_t transferCtrlPtr, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_CompleteMajorLoopInterrupt
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_CompleteMajorLoopInterrupt(uint32_t transferCtrlPtr, DMA_Decision_t decision);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_HalfMajorLoopInterrupt
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_TriggerSwRequest(uint32_t transferCtrlPtr);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_InitChannelMUX
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_RequestSource_t source, DMA_ChannelOperation_t mode
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_InitChannelMUX(uint8_t channelNumber, DMA_RequestSource_t source, DMA_ChannelOperation_t mode);



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ClearTransferControlDescriptor
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint32_t transferCtrlPtr
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ClearTransferControlDescriptor(uint32_t transferCtrlPtr);


/****************************************************************************************
 *!< Function    	     : HAL_DMA_EnableScatterGather
 *!< @brief		     : Function set the CSR[ESG] bit in TCD
 *!< Parameters              :
 *!<                   Input : uint32_t transferCtrlPtr -
 *!<                   	     : BOOL enable -
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableScatterGather(uint32_t transferCtrlPtr, BOOL enable);


/****************************************************************************************
 *!< Function    	     : HAL_DMA_ClearDoneFlag
 *!< @brief		     : Function set the CSR[ESG] bit in TCD
 *!< Parameters              :
 *!<                   Input : uint32_t transferCtrlPtr -
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ClearDoneFlag(uint32_t transferCtrlPtr);


/****************************************************************************************
 *!< Function    	     : HAL_DMA_GetChnNrByTcd
 *!< @brief		     :
 *!< Parameters              :
 *!<                   Input : uint32_t transferCtrlPtr -
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
uint32_t HAL_DMA_GetChnNrByTcd(uint32_t transferCtrlPtr);



/*!< C++ banding section finish ---------------------------------------------------------------- */
#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* USE_DMA */
#endif /* HAL_DMA_H_ */


/************************************** END OF FILE **********************************************/
