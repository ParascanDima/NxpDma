/********************************************* Login **********************************************
 *!< File Name 						    : hal_dmaif.h
 *!< Author   	        			: Dumitru Parascan
 *!< Version	        			  : V1.0
 *!< Date     		        		: Aug 30, 2018
 *!< @brief		        			  :
 *!<                          : (see note at the end of the file)
 *!< Modifiable YES/NO		    :
 *!< Critical explanation			:
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
#ifndef HAL_DMAIF_H_
#define HAL_DMAIF_H_


/*!< C++ banding section start ----------------------------------------------------------------- */
#ifdef __cplusplus
    extern "C" {
#endif


/*!< Include section --------------------------------------------------------------------------- */
#include "Modules.h"
#include <Std_Types.h>

#ifdef USE_DMA

/*!< Type definitions section ------------------------------------------------------------------ */

/*!<
 *!< @brief Configuration bit value.
 *!< */
typedef enum {

  enDisable = 0,
  enEnable,

} DMA_Decision_t;


/*!<
 *!< @brief DMA state machine definition
 *!< */
typedef enum {

  enIdle = 0,                             /*  */
  enReady = 1,
  enActive = 2,
  enError = 3,

} DMA_State_t;


/*!<
 *!< @brief DMA Bandwidth control
 *!< */
typedef enum {

  enNoDmaStalls = 0,                             /*  */
  enDmaStallFor4Cycles = 2,
  enDmaStallFor8Cycles = 3,

} DMA_BWC_t;


/*!<
 *!< @brief Size of each DMA access from/to memory or peripheral register.
 *!< */
typedef enum DMA_TransferSize_e
{
  enDMA_TRANSFER_SIZE_1B = 0x1U,                    /* read/write accesses are done 8 bit at a time */
  enDMA_TRANSFER_SIZE_2B = 0x2U,                    /* read/write accesses are done 16 bit at a time */
  enDMA_TRANSFER_SIZE_4B = 0x4U,                    /* read/write accesses are done 32 bit at a time */
  enDMA_TRANSFER_SIZE_16B = 0x16U,                   /* read/write accesses are done in bursts of 16 bytes at a time */
  enDMA_TRANSFER_SIZE_32B = 0x32U,                   /* read/write accesses are done in bursts of 32 bytes at a time */

} DMA_TransferSize_t;


/*!<!
 *!< @brief Structure for the DMA hardware request
 *!<
 *!< Defines the structure for the DMA hardware request collections. The user can configure the
 *!< hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 *!< of the hardware request varies according  to the to SoC.
 *!< */

typedef enum {
    enDMA_REQ_DISABLED = 0U,
    enDMA_REQ_LPUART0_RX = 2U,
    enDMA_REQ_LPUART0_TX = 3U,
    enDMA_REQ_LPUART1_RX = 4U,
    enDMA_REQ_LPUART1_TX = 5U,
    enDMA_REQ_FLEXIO_SHIFTER0 = 10U,
    enDMA_REQ_FLEXIO_SHIFTER1 = 11U,
    enDMA_REQ_FLEXIO_SHIFTER2 = 12U,
    enDMA_REQ_FLEXIO_SHIFTER3 = 13U,
    enDMA_REQ_LPSPI0_RX = 14U,
    enDMA_REQ_LPSPI0_TX = 15U,
    enDMA_REQ_LPSPI1_RX = 16U,
    enDMA_REQ_LPSPI1_TX = 17U,
    enDMA_REQ_FTM1_CHANNEL_0 = 20U,
    enDMA_REQ_FTM1_CHANNEL_1 = 21U,
    enDMA_REQ_FTM1_CHANNEL_2 = 22U,
    enDMA_REQ_FTM1_CHANNEL_3 = 23U,
    enDMA_REQ_FTM1_CHANNEL_4 = 24U,
    enDMA_REQ_FTM1_CHANNEL_5 = 25U,
    enDMA_REQ_FTM1_CHANNEL_6 = 26U,
    enDMA_REQ_FTM1_CHANNEL_7 = 27U,
    enDMA_REQ_FTM2_CHANNEL_0 = 28U,
    enDMA_REQ_FTM2_CHANNEL_1 = 29U,
    enDMA_REQ_FTM2_CHANNEL_2 = 30U,
    enDMA_REQ_FTM2_CHANNEL_3 = 31U,
    enDMA_REQ_FTM2_CHANNEL_4 = 32U,
    enDMA_REQ_FTM2_CHANNEL_5 = 33U,
    enDMA_REQ_FTM2_CHANNEL_6 = 34U,
    enDMA_REQ_FTM2_CHANNEL_7 = 35U,
    enDMA_REQ_FTM0_OR_CH0_CH7 = 36U,
    enDMA_REQ_FTM3_OR_CH0_CH7 = 37U,
    enDMA_REQ_ADC0 = 42U,
    enDMA_REQ_ADC1 = 43U,
    enDMA_REQ_LPI2C0_RX = 44U,
    enDMA_REQ_LPI2C0_TX = 45U,
    enDMA_REQ_PDB0 = 46U,
    enDMA_REQ_PDB1 = 47U,
    enDMA_REQ_CMP0 = 48U,
    enDMA_REQ_PORTA = 49U,
    enDMA_REQ_PORTB = 50U,
    enDMA_REQ_PORTC = 51U,
    enDMA_REQ_PORTD = 52U,
    enDMA_REQ_PORTE = 53U,
    enDMA_REQ_FLEXCAN0 = 54U,
    enDMA_REQ_FLEXCAN1 = 55U,
    enDMA_REQ_LPTMR0 = 59U,
    enDMA_REQ_DMAMUX_ALWAYS_ENABLED0 = 62U,
    enDMA_REQ_DMAMUX_ALWAYS_ENABLED1 = 63U
} DMA_RequestSource_t;


/*!<
 *!< @brief DMA channel operation mode
 *!< */
typedef enum {

  enDisabledMode = 0,                             /*  */
  enNormalMode = 1,
  enPeriodicTriggered = 2,

} DMA_ChannelOperation_t;

/*!<
 *!< @brief Type of memory transfer.
 *!< */
typedef enum DMA_TransferType_e
{
  enDMA_TRANSFER_PERIPH2MEM = 0u,                   /* Transfer from peripheral to memory */
  enDMA_TRANSFER_MEM2PERIPH = 1u,                   /* Transfer from memory to peripheral */
  enDMA_TRANSFER_MEM2MEM = 2u,                      /* Transfer from memory to memory */
  enDMA_TRANSFER_PERIPH2PERIPH = 3u,                /* Transfer from peripheral to peripheral */

} DMA_TransferType_t;


/*!< @brief eDMA channel arbitration algorithm used for selection among channels.
 *!<Implements : edma_arbitration_algorithm_t_Class
 *!< */
typedef enum {
    enDMA_ARBITRATION_FIXED_PRIORITY = 0U,  /* Fixed Priority */
    enDMA_ARBITRATION_ROUND_ROBIN           /* Round-Robin arbitration */
} DMA_Arbitration_Algorithm_t;


/*!<
 *!< @brief Definition of channel handler type (channel number)
 *!< */
typedef uint8_t DMA_ChannelHdl_t;



/*! @brief eDMA modulo configuration
 */
typedef enum {
    enDMA_MODULO_OFF = 0U,
    enDMA_MODULO_2B,
    enDMA_MODULO_4B,
    enDMA_MODULO_8B,
    enDMA_MODULO_16B,
    enDMA_MODULO_32B,
    enDMA_MODULO_64B,
    enDMA_MODULO_128B,
    enDMA_MODULO_256B,
    enDMA_MODULO_512B,
    enDMA_MODULO_1KB,
    enDMA_MODULO_2KB,
    enDMA_MODULO_4KB,
    enDMA_MODULO_8KB,
    enDMA_MODULO_16KB,
    enDMA_MODULO_32KB,
    enDMA_MODULO_64KB,
    enDMA_MODULO_128KB,
    enDMA_MODULO_256KB,
    enDMA_MODULO_512KB,
    enDMA_MODULO_1MB,
    enDMA_MODULO_2MB,
    enDMA_MODULO_4MB,
    enDMA_MODULO_8MB,
    enDMA_MODULO_16MB,
    enDMA_MODULO_32MB,
    enDMA_MODULO_64MB,
    enDMA_MODULO_128MB,
    enDMA_MODULO_256MB,
    enDMA_MODULO_512MB,
    enDMA_MODULO_1GB,
    enDMA_MODULO_2GB
} DMA_Modulo_t;



/*!<
 *!< @brief User DMA device configuration
 *!< */
typedef struct DMA_UserCfg_type{

	DMA_Arbitration_Algorithm_t arbitrationAlgorithm;/*  */
	BOOL bEnableHaltOnError;
	BOOL bEnableDebug;

} DMA_ConfigType;


/*!<
 *!< @brief On half interrupt callback type
 *!< */
typedef void (*onHalf_t)(void *);

/*!<
 *!< @brief On finish interrupt callback type
 *!< */
typedef void (*onFinish_t)(void *);

/*!<
 *!< @brief On error interrupt callback type
 *!< */
typedef void (*onError_t)(void *);

/*!<
 *!< @brief User DMA channel configuration
 *!< */
typedef struct DMA_Channel_UserCfg_type{

	uint32_t            srcAddr;

	uint32_t            dstAddr;

	uint32_t            srcAddrAdjustment;

	uint32_t            dstAddrOnFinish;

	uint32_t            bytesPerRequest;

	BOOL                bUseLinkToChannelAfterRequest;

	BOOL                bUseLinkToChannelAfterFinish;

	onHalf_t            onHalfCallback;

	void*               onHalfCallbackParameter;

	onFinish_t          onFinishCallback;

	void*               onFinishCallbackParameter;

	onError_t           onErrorCallback;

	void*               onErrorCallbackParameter;

	BOOL                bUseAddrMask;

	BOOL                bUseOtherSrcAddrOnFinish;

	BOOL                bUseOtherDstAddrOnFinish;

	BOOL                bStopOnFinish;

	int16_t             srcTransferOffset;

	int16_t             dstTransferOffset;

	int16_t             totalSize;

	DMA_TransferSize_t  transferSize;

	DMA_TransferType_t  transferType;

	uint8_t             offsetPerRequest;

	uint8_t             priority;

	uint8_t             srcAddrMask;

	uint8_t             dstAddrMask;

	DMA_RequestSource_t requestSource;

	uint8_t             channelNumber;

	uint8_t             afterRequestLinkedChannel;

	uint8_t             afterFinishLinkedChannel;

} DMA_Channel_ConfigType;


/*!<
 *!< @brief DMA event type
 *!< */
typedef enum {

  enDMA_On_Finish = 0,                             /*  */
  enDMA_On_Half,
  enDMA_On_Error,

} DMA_EVENT_t;



/*!< Definitions section ----------------------------------------------------------------------- */

#define DMA_TOTAL_CHANNELS 16


/*!< Exported variables section ---------------------------------------------------------------- */



/*!< Functions prototypes sections ------------------------------------------------------------- */



/*!< C++ banding section finish ---------------------------------------------------------------- */
#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* USE_DMA */
#endif /* HAL_DMAIF_H_ */


/************************************** END OF FILE **********************************************/
