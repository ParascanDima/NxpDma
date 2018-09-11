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
 *!< File Name 					: hal_dma.c
 *!< Author   	        		: Dumitru Parascan
 *!< Version	        		: V1.0
 *!< Date     		        	: Aug 30, 2018
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
 * | 1.0         | Create template                               | Aug 30, 2018 | Dumitru Parascan    | *
 *  --------------------------------------------------------------------------------------------  *
 *  END OF TABLE                                                                                  *
 **************************************************************************************************
 */


/*!< Include section --------------------------------------------------------------------------- */

#include "device_registers.h"
#undef bool
#include "hal_dma.h"

/*<! Definitions section ----------------------------------------------------------------------- */

#define  HAL_DMA_DISABLE_REGISTER(REG)     (hdma.REG->NOP = 1)
#define  HAL_DMA_IS_REGISTER_DISABLED(REG) (hdma.REG->NOP == 1)
#define  HAL_DMA_ENABLE_REGISTER(REG)      (hdma.REG->NOP = 0)


/*!< Type definitions section ------------------------------------------------------------------ */


/*!<
 *!< @brief Control register description.
 *!< */
typedef struct {

  __I uint8_t rezerved_2 : 1;                         /* Reserved                               */
  __IO uint8_t EDBG      : 1;                         /* Enable Debug                           */
  __IO uint8_t ERCA      : 1;                         /* Enable Round Robin Channel Arbitration */
  __I uint8_t rezerved_1 : 1;                         /* Reserved                               */
  __IO uint8_t HOE       : 1;                         /* Halt On Error                          */
  __IO uint8_t HALT      : 1;                         /* Halt DMA Operations                    */
  __IO uint8_t CLM       : 1;                         /* Continuous Link Mode                   */
  __IO uint8_t EMLM      : 1;                         /* Enable Minor Loop Mapping              */

  __I uint8_t zero_1;                                 /* Reserved                               */

  __IO uint8_t ECX       : 1;                         /* Error Cancel Transfer                  */
  __IO uint8_t CX        : 1;                         /* Cancel Transfer                        */
  __I uint8_t zero_0     : 6;                         /* Reserved                               */

  __I uint8_t eDMAVersion: 7;                         /* eDMA version number                    */
  __I uint8_t ACTIVE     : 1;                         /* DMA Active Status                      */

} HAL_DMA_CR_t;


/*!<
 *!< @brief Error Status Register description
 *!< */
typedef struct {

  __IO uint8_t DBE        : 1;                        /* Destination Bus Error                  */
  __IO uint8_t SBE        : 1;                        /* Source Bus Error                       */
  __IO uint8_t SGE        : 1;                        /* Scatter/Gather Configuration Error     */
  __IO uint8_t NCE        : 1;                        /* NBYTES/CITER Configuration Error       */
  __IO uint8_t DOE        : 1;                        /* Destination Offset Error               */
  __IO uint8_t DAE        : 1;                        /* Destination Address Error              */
  __IO uint8_t SOE        : 1;                        /* Source Offset Error                    */
  __IO uint8_t SAE        : 1;                        /* Source Address Error                   */
  __IO uint8_t ERRCHN     : 4;                        /* Canceled Channel Number                */
  __I uint8_t rezerved_2  : 2;                        /* Reserved                               */
  __IO uint8_t CPE        : 1;                        /* Channel Priority Error                 */
  __I uint8_t rezerved_1  : 1;                        /* Reserved                               */
  __IO uint8_t ECX        : 1;                        /* Transfer Canceled                      */
  __I uint16_t rezerved_0 : 14;                       /* Reserved                               */
  __IO uint8_t VLD        : 1;                        /* DMA any error status                   */

} HAL_DMA_ES_t;


/*!<
 *!< @brief Enable Request Register description
 *!< */
typedef struct {

  __IO uint16_t ERQn;                                 /* Enable DMA Requests on channel         */
  __I uint16_t reserved;                              /* Reserved                               */

} HAL_DMA_ERQ_t;


/*!<
 *!< @brief Enable Error Interrupt Register description
 *!< */
typedef struct {

  __IO uint16_t EEIn;                                 /* Enable Error Interrupt on channel      */
  __I uint16_t reserved;                              /* Reserved                               */

} HAL_DMA_EEI_t;


/*!<
 *!< @brief Clear Enable Error Interrupt Register description
 *!< */
typedef struct {

  __IO uint8_t CEEI     : 4;                          /* Clear Enable Error Interrupt           */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t CAEE     : 1;                          /* Clear All Enable Error Interrupts      */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_CEEI_t;


/*!<
 *!< @brief Set Enable Error Interrupt Register description
 *!< */
typedef struct {

  __IO uint8_t SEEI     : 4;                          /* Set Enable Error Interrupt             */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t SAEE     : 1;                          /* Sets All Enable Error Interrupts       */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_SEEI_t;


/*!<
 *!< @brief Clear Enable Request Register description
 *!< */
typedef struct {

  __IO uint8_t CERQ     : 4;                          /* Clear Enable Request                   */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t CAER     : 1;                          /* Clear All Enable Requests              */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_CERQ_t;


/*!<
 *!< @brief Set Enable Request Register description
 *!< */
typedef struct {

  __IO uint8_t SERQ     : 4;                          /* Set Enable Request                     */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t SAER     : 1;                          /* Set All Enable Requests                */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_SERQ_t;


/*!<
 *!< @brief Clear DONE Status Bit Register description
 *!< */
typedef struct {

  __IO uint8_t CDNE     : 4;                          /* Clear DONE Bit                         */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t CADN     : 1;                          /* Clears All DONE Bits                   */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_CDNE_t;


/*!<
 *!< @brief Set START Bit Register description
 *!< */
typedef struct {

  __IO uint8_t SSRT     : 4;                          /* Set START Bit                          */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t SAST     : 1;                          /* Set All START Bits                     */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_SSRT_t;


/*!<
 *!< @brief Clear Error Register description
 *!< */
typedef struct {

  __IO uint8_t CERR     : 4;                          /* Clear Error Indicator                  */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t CAEI     : 1;                          /* Clear All Error Indicators             */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_CERR_t;


/*!<
 *!< @brief Clear Interrupt Request Register description
 *!< */
typedef struct {

  __IO uint8_t CINT     : 4;                          /* Clear Interrupt Request                */
  __I uint16_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t CAIR     : 1;                          /* Clear All Interrupt Requests           */
  __IO uint8_t NOP      : 1;                          /* No Op enable                           */

} HAL_DMA_CINT_t;


/*!<
 *!< @brief Interrupt Request Register description
 *!< */
typedef struct {

  __IO uint16_t INTn;                                 /* Interrupt Request on channel           */
  __I uint16_t reserved;                              /* Reserved                               */

} HAL_DMA_INT_t;


/*!<
 *!< @brief Error Register description
 *!< */
typedef struct {

  __IO uint16_t ERRn;                                 /* Error in channel                       */
  __I uint16_t reserved;                              /* Reserved                               */

} HAL_DMA_ERR_t;


/*!<
 *!< @brief Hardware Request Status Register description
 *!< */
typedef struct {

  __I uint16_t HRSn;                                  /* Hardware Request Status for channel    */
  __I uint16_t reserved;                              /* Reserved                               */

} HAL_DMA_HRS_t;


/*!<
 *!< @brief Enable Asynchronous Request in Stop Register description
 *!< */
typedef struct {

  __I uint16_t EARSn;                                 /* Enable asynchronous DMA request in stop mode for channel    */
  __I uint16_t reserved;                              /* Reserved                               */

} HAL_DMA_EARS_t;

/*!<
 *!< @brief Clear Error Register description
 *!< */
typedef struct {

  __IO uint8_t CHPRI    : 4;                          /* Channel n Arbitration Priority         */
  __I  uint8_t reserved : 2;                          /* Reserved                               */
  __IO uint8_t DPA      : 1;                          /* Disable Preempt Ability                */
  __IO uint8_t ECP      : 1;                          /* Enable Channel Preemption              */

} HAL_DMA_DCHPRIn_t;



/*!<
 *!< @brief TCD_Source Address type
 *!< */
typedef uint32_t HAL_DMA_TCDn_SADDR_t;


/*!<
 *!< @brief TCD Signed Source Address Offset
 *!< */
typedef int16_t HAL_DMA_TCDn_SOFF_t;


/*!<
 *!< @brief TCD Transfer Attributes
 *!< */
typedef struct {

  __IO uint8_t DSIZE : 3;                             /* Destination data transfer size         */
  __IO uint8_t DMOD  : 5;                             /* Destination Address Modulo             */
  __IO uint8_t SSIZE : 3;                             /* Source data transfer size              */
  __IO uint8_t SMOD  : 5;                             /* Source Address Modulo                  */

} HAL_DMA_TCDn_ATTR_t;


/*!<
 *!< @brief TCD Signed Minor Loop Offset (Minor Loop Mapping Disabled)
 *!< */
typedef uint32_t HAL_DMA_TCDn_NBYTES_MLNO_t;

/*!<
 *!< @brief TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Disabled) description
 *!< */
typedef struct {

  __IO uint32_t NBYTES : 30;                          /* Minor Byte Transfer Count               */
  __IO uint8_t DMLOE   : 1;                           /* Destination Minor Loop Offset Enable    */
  __IO uint8_t SMLOE   : 1;                           /* Source Minor Loop Offset Enable         */

} HAL_DMA_TCDn_NBYTES_MLOFFNO_t;


/*!<
 *!< @brief TCD Signed Minor Loop Offset (Minor Loop Mapping Enabled and Offset Enabled) description
 *!< */
typedef struct {

  __IO uint16_t NBYTES : 10;                          /* Minor Byte Transfer Count               */
  __IO uint32_t MLOFF  : 20;                          /* Minor Byte Transfer Count               */
  __IO uint8_t DMLOE   : 1;                           /* Destination Minor Loop Offset Enable    */
  __IO uint8_t SMLOE   : 1;                           /* Source Minor Loop Offset Enable         */

} HAL_DMA_TCDn_NBYTES_MLOFFYES_t;


/*!<
 *!< @brief TCD Signed Minor Loop Offset description
 *!< */
typedef union {

  HAL_DMA_TCDn_NBYTES_MLNO_t MLNO;                    /* NBYTES register if EMLM = 0             */
  HAL_DMA_TCDn_NBYTES_MLOFFNO_t MLOFFNO;              /* NBYTES register if EMLM = 1 and DMLOE and SMLOE = 0 */
  HAL_DMA_TCDn_NBYTES_MLOFFYES_t MLOFFYES;            /* NBYTES register if EMLM = 1 and DMLOE or SMLOE = 1 */

} HAL_DMA_TCDn_NBYTES_t;


/*!<
 *!< @brief TCD Last Source Address Adjustment
 *!< */
typedef int32_t HAL_DMA_TCDn_SLAST_t;


/*!<
 *!< @brief TCD Destination Address
 *!< */
typedef uint32_t HAL_DMA_TCDn_DADDR_t;


/*!<
 *!< @brief TCD Signed Destination Address Offset
 *!< */
typedef int16_t HAL_DMA_TCDn_DOFF_t;



/*!<
 *!< @brief TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled)
 *!< */
typedef struct {

  __IO uint16_t CITER  : 15;                         /* Current Major Iteration Count           */
  __IO uint8_t ELINK   : 1;                          /* Enable channel-to-channel linking on minor-loop complete */

} HAL_DMA_TCDn_CITER_LINKNO_t;


/*!<
 *!< @brief TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled)
 *!< */
typedef struct {

  __IO uint16_t CITER   : 9;                         /* Current Major Iteration Count           */
  __IO uint8_t LINKCHN  : 4;			             /* Minor Loop Link Channel Number          */
  __I  uint8_t reserved : 2;                         /* Reserved                                */
  __IO uint8_t ELINK    : 1;                         /* Enable channel-to-channel linking on minor-loop complete */

} HAL_DMA_TCDn_CITER_LINKYES_t;


/*!<
 *!< @brief TCD Current Minor Loop Link, Major Loop Count description
 *!< */
typedef union {

  HAL_DMA_TCDn_CITER_LINKNO_t LINKNO;                /* CITER register if ELINK = 0             */
  HAL_DMA_TCDn_CITER_LINKYES_t LINKYES;              /* CITER register if ELINK = 1             */

} HAL_DMA_TCDn_CITER_t;


/*!<
 *!< @brief TCD Last Destination Address Adjustment/Scatter Gather Address
 *!< */
typedef int32_t HAL_DMA_TCDn_DLASTSGA_t;


/*!<
 *!< @brief TCD Control and Status description
 *!< */
typedef struct {

  __IO uint8_t START        : 1;                     /* Channel Start                           */
  __IO uint8_t INTMAJOR     : 1;                     /* Enable an interrupt when major iteration count completes */
  __IO uint8_t INTHALF      : 1;                     /* Enable an interrupt when major counter is half complete */
  __IO uint8_t DREQ         : 1;                     /* Disable Request                         */
  __IO uint8_t ESG          : 1;                     /* Enable Scatter/Gather Processing        */
  __IO uint8_t MAJORELINK   : 1;                     /* Enable channel-to-channel linking on major loop complete */
  __I  uint8_t ACTIVE       : 1;                     /* Channel Active Flag                     */
  __IO uint8_t DONE         : 1;                     /* Channel Done Flag                       */
  __IO uint8_t MAJORLINKCH  : 4;                     /* Major Loop Link Channel Number          */
  __I  uint8_t reserved     : 2;                     /* Reserved (returns zero while reading)   */
  __IO uint8_t BWC          : 2;                     /* Bandwidth Control                       */

} HAL_DMA_TCDn_CSR_t;


/*!<
 *!< @brief TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled)
 *!< */
typedef struct {

  __IO uint16_t BITER  : 15;                         /* Starting Major Iteration Count          */
  __IO uint8_t ELINK   : 1;                          /* Enable channel-to-channel linking on minor-loop complete */

} HAL_DMA_TCDn_BITER_ELINKNO_t;


/*!<
 *!< @brief TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled)
 *!< */
typedef struct {

  __IO uint16_t BITER   : 9;                         /* Starting major iteration count          */
  __IO uint8_t LINKCHN  : 4;			             /* Link Channel Number                     */
  __I  uint8_t reserved : 2;                         /* Reserved (returns zero while reading)   */
  __IO uint8_t ELINK    : 1;                         /* Enable channel-to-channel linking on minor-loop complete */

} HAL_DMA_TCDn_BITER_ELINKYES_t;


/*!<
 *!< @brief TCD Beginning Minor Loop Link, Major Loop Count description
 *!< */
typedef union {

  HAL_DMA_TCDn_BITER_ELINKNO_t ELINKNO;              /* BITER register if ELINK = 0             */
  HAL_DMA_TCDn_BITER_ELINKYES_t ELINKYES;            /* BITER register if ELINK = 1             */

} HAL_DMA_TCDn_BITER_t;


/*!<
 *!< @brief DMA Transfer Control Descriptor
 *!< */
typedef struct {

  HAL_DMA_TCDn_SADDR_t    SADDR;                     /* SADDR register                          */
  HAL_DMA_TCDn_SOFF_t     SOFF;                      /* SOFF register                           */
  HAL_DMA_TCDn_ATTR_t     ATTR;                      /* ATTR register                           */
  HAL_DMA_TCDn_NBYTES_t   NBYTES;                    /* NBYTES register                         */
  HAL_DMA_TCDn_SLAST_t    SLAST;                     /* SLAST register                          */
  HAL_DMA_TCDn_DADDR_t    DADDR;                     /* DADDR register                          */
  HAL_DMA_TCDn_DOFF_t     DOFF;                      /* DOFF register                           */
  HAL_DMA_TCDn_CITER_t    CITER;                     /* CITER register                          */
  HAL_DMA_TCDn_DLASTSGA_t DLASTSGA;                  /* DLASTSGA register                       */
  HAL_DMA_TCDn_CSR_t      CSR;                       /* CSR register                            */
  HAL_DMA_TCDn_BITER_t    BITER;                     /* BITER register                          */

} HAL_DMA_TCD_t;


/*!<
 *!< @brief DMAMUX CHCFG register definition
 *!< */
typedef struct {

   __IO uint8_t SOURCE : 6;                          /* DMA Channel Source (Slot)               */
   __IO uint8_t TRIG : 1;                            /* DMA Channel Trigger Enable              */
   __IO uint8_t ENBL : 1;                            /* DMA Channel Enable                      */

} HAL_DMAMUX_CHCFG_t;


/*!<
 *!< @brief HAL DMA description
 *!< */
typedef struct {

  HAL_DMA_CR_t* CR;                                  /* CR register                             */
  HAL_DMA_ES_t* ES;                                  /* ES register                             */
  HAL_DMA_ERQ_t* ERQ;                                /* ERQ register                            */
  HAL_DMA_EEI_t* EEI;                                /* EEI register                            */
  HAL_DMA_CEEI_t* CEEI;                              /* CEEI register                           */
  HAL_DMA_SEEI_t* SEEI;                              /* SEEI register                           */
  HAL_DMA_CERQ_t* CERQ;                              /* CERQ register                           */
  HAL_DMA_SERQ_t* SERQ;                              /* SERQ register                           */
  HAL_DMA_CDNE_t* CDNE;                              /* CDNE register                           */
  HAL_DMA_SSRT_t* SSRT;                              /* SSRT register                           */
  HAL_DMA_CERR_t* CERR;                              /* CERR register                           */
  HAL_DMA_CINT_t* CINT;                              /* CINT register                           */
  HAL_DMA_INT_t* INT;                                /* INT register                            */
  HAL_DMA_ERR_t* ERR;                                /* ERR register                            */
  HAL_DMA_HRS_t* HRS;                                /* HRS register                            */
  HAL_DMA_EARS_t* EARS;                              /* EARS register                           */
  HAL_DMA_DCHPRIn_t* DCHPRI[DMA_DCHPRI_COUNT];       /* DCHPRI registers                        */
  HAL_DMA_TCD_t* TCD[DMA_TCD_COUNT];                 /* TCD registers                           */
  HAL_DMAMUX_CHCFG_t* CHCFG[DMAMUX_CHCFG_COUNT];     /* CHCFG register                          */

} HAL_DMA_t;


/*!< Exported variables section ---------------------------------------------------------------- */


/*!< Static variable section ------------------------------------------------------------------- */


static const HAL_DMA_t hdma = {
		.CR = (HAL_DMA_CR_t*)&DMA->CR,
		.ES = (HAL_DMA_ES_t*)&DMA->ES,
		.ERQ = (HAL_DMA_ERQ_t*)&DMA->ERQ,
		.EEI = (HAL_DMA_EEI_t*)&DMA->EEI,
		.CEEI = (HAL_DMA_CEEI_t*)&DMA->CEEI,
		.SEEI = (HAL_DMA_SEEI_t*)&DMA->SEEI,
		.CERQ = (HAL_DMA_CERQ_t*)&DMA->CERQ,
		.SERQ = (HAL_DMA_SERQ_t*)&DMA->SERQ,
		.CDNE = (HAL_DMA_CDNE_t*)&DMA->CDNE,
		.SSRT = (HAL_DMA_SSRT_t*)&DMA->SSRT,
		.CERR = (HAL_DMA_CERR_t*)&DMA->CERR,
		.CINT = (HAL_DMA_CINT_t*)&DMA->CINT,
		.INT = (HAL_DMA_INT_t*)&DMA->INT,
		.ERR = (HAL_DMA_ERR_t*)&DMA->ERR,
		.HRS = (HAL_DMA_HRS_t*)&DMA->HRS,
		.EARS = (HAL_DMA_EARS_t*)&DMA->EARS,
		.DCHPRI[3] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[0],
		.DCHPRI[2] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[1],
		.DCHPRI[1] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[2],
		.DCHPRI[0] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[3],
		.DCHPRI[7] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[4],
		.DCHPRI[6] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[5],
		.DCHPRI[5] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[6],
		.DCHPRI[4] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[7],
		.DCHPRI[11] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[8],
		.DCHPRI[10] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[9],
		.DCHPRI[9] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[10],
		.DCHPRI[8] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[11],
		.DCHPRI[15] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[12],
		.DCHPRI[14] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[13],
		.DCHPRI[13] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[14],
		.DCHPRI[12] = (HAL_DMA_DCHPRIn_t*)&DMA->DCHPRI[15],
		.TCD[0] = (HAL_DMA_TCD_t*)&DMA->TCD[0],
		.TCD[1] = (HAL_DMA_TCD_t*)&DMA->TCD[1],
		.TCD[2] = (HAL_DMA_TCD_t*)&DMA->TCD[2],
		.TCD[3] = (HAL_DMA_TCD_t*)&DMA->TCD[3],
		.TCD[4] = (HAL_DMA_TCD_t*)&DMA->TCD[4],
		.TCD[5] = (HAL_DMA_TCD_t*)&DMA->TCD[5],
		.TCD[6] = (HAL_DMA_TCD_t*)&DMA->TCD[6],
		.TCD[7] = (HAL_DMA_TCD_t*)&DMA->TCD[7],
		.TCD[8] = (HAL_DMA_TCD_t*)&DMA->TCD[8],
		.TCD[9] = (HAL_DMA_TCD_t*)&DMA->TCD[9],
		.TCD[10] = (HAL_DMA_TCD_t*)&DMA->TCD[10],
		.TCD[11] = (HAL_DMA_TCD_t*)&DMA->TCD[11],
		.TCD[12] = (HAL_DMA_TCD_t*)&DMA->TCD[12],
		.TCD[13] = (HAL_DMA_TCD_t*)&DMA->TCD[13],
		.TCD[14] = (HAL_DMA_TCD_t*)&DMA->TCD[14],
		.TCD[15] = (HAL_DMA_TCD_t*)&DMA->TCD[15],
		.CHCFG[0]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[0],
		.CHCFG[1]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[1],
		.CHCFG[2]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[2],
		.CHCFG[3]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[3],
		.CHCFG[4]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[4],
		.CHCFG[5]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[5],
		.CHCFG[6]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[6],
		.CHCFG[7]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[7],
		.CHCFG[8]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[8],
		.CHCFG[9]  = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[9],
		.CHCFG[10] = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[10],
		.CHCFG[11] = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[11],
		.CHCFG[12] = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[12],
		.CHCFG[13] = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[13],
		.CHCFG[14] = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[14],
		.CHCFG[15] = (HAL_DMAMUX_CHCFG_t*)&DMAMUX->CHCFG[15],
};

/*!< Static functions prototypes sections ------------------------------------------------------ */


/*!< Static functions definition sections ------------------------------------------------------ */


/*!< Function definitions ---------------------------------------------------------------------- */


/****************************************************************************************
 *!< Function    	         : HAL_DMA_GetChannelState
 *!< @brief		    	     : Shows either DMA channel active or not.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber - specify which channel state is required.
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetChannelState(uint8_t channelNumber)
{
	return hdma.TCD[channelNumber]->CSR.ACTIVE;
}


/****************************************************************************************
 *!< Function    	 		 : HAL_DMA_GetEngineState
 *!< @brief		    		 : Shows either DMA engine active or not.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetEngineState(void)
{
	return hdma.CR->ACTIVE;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ReportErrors
 *!< @brief		    		 : Indicates if some DMA errors appear.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : no
 */
uint8_t HAL_DMA_ReportErrors(void)
{
	return hdma.ES->VLD;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetArbitrationAlgorith
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : DMA_Arbitration_Algorithm_t
 *!< Critical section YES/NO : no
 */
DMA_Arbitration_Algorithm_t HAL_DMA_GetArbitrationAlgorith(void)
{
	return (DMA_Arbitration_Algorithm_t)hdma.CR->ERCA;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ClearErrorFlag
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ClearErrorFlag(uint8_t channelNumber)
{
	/* Write 1 to clear bit */
	hdma.ERR->ERRn = (1<<channelNumber);
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_UseOffsetPerRequest
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_UseOffsetPerRequest(uint8_t channelNumber, int32_t transferOffset)
{
	/* Write 1 to clear bit */
	hdma.TCD[channelNumber]->NBYTES.MLOFFYES.MLOFF = transferOffset;
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcTransferOffset
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcTransferOffset(uint8_t channelNumber, int16_t transferOffset)
{
	/* Write 1 to clear bit */
	hdma.TCD[channelNumber]->SOFF = transferOffset;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcTransferOffset
 *!< @brief		    		 : Clear error flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstTransferOffset(uint8_t channelNumber, int16_t transferOffset)
{
	/* Write 1 to clear bit */
	hdma.TCD[channelNumber]->DOFF = transferOffset;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ClearInterruptFlag
 *!< @brief		    		 : Clear interrupt flag on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channel
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ClearInterruptFlag(uint8_t channelNumber)
{
	/* Write 1 to clear bit */
	hdma.INT->INTn = (1<<channelNumber);
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetInterruptedChannel
 *!< @brief		    		 : Shows on which channel interrupt request is active.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t - represents the interrupted channel number.
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetInterruptedChannel(void)
{
	uint8_t channelNumber = DMA_CHANNEL_INEXISTENT;

	switch (hdma.INT->INTn) {
		case enDMA_ChannelFlag_0:
			channelNumber = DMA_CHANNEL_0;
			break;
		case enDMA_ChannelFlag_1:
			channelNumber = DMA_CHANNEL_1;
			break;
		case enDMA_ChannelFlag_2:
			channelNumber = DMA_CHANNEL_2;
			break;
		case enDMA_ChannelFlag_3:
			channelNumber = DMA_CHANNEL_3;
			break;
		case enDMA_ChannelFlag_4:
			channelNumber = DMA_CHANNEL_4;
			break;
		case enDMA_ChannelFlag_5:
			channelNumber = DMA_CHANNEL_5;
			break;
		case enDMA_ChannelFlag_6:
			channelNumber = DMA_CHANNEL_6;
			break;
		case enDMA_ChannelFlag_7:
			channelNumber = DMA_CHANNEL_7;
			break;
		case enDMA_ChannelFlag_8:
			channelNumber = DMA_CHANNEL_8;
			break;
		case enDMA_ChannelFlag_9:
			channelNumber = DMA_CHANNEL_9;
			break;
		case enDMA_ChannelFlag_10:
			channelNumber = DMA_CHANNEL_10;
			break;
		case enDMA_ChannelFlag_11:
			channelNumber = DMA_CHANNEL_11;
			break;
		case enDMA_ChannelFlag_12:
			channelNumber = DMA_CHANNEL_12;
			break;
		case enDMA_ChannelFlag_13:
			channelNumber = DMA_CHANNEL_13;
			break;
		case enDMA_ChannelFlag_14:
			channelNumber = DMA_CHANNEL_14;
			break;
		case enDMA_ChannelFlag_15:
			channelNumber = DMA_CHANNEL_15;
			break;
		default:
			break;
	}

	return channelNumber;
}


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
void HAL_DMA_CancelTransfers(void)
{
	/* Will be cleared by itself after the transfer */
	hdma.CR->CX = 1;
}


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
void HAL_DMA_CancelTransferWithError(void)
{
	/* Cancel the channel transfer with  */
	hdma.CR->ECX = 1;
}


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
void HAL_DMA_HaltOperations(void)
{
	/*  Channel execution resumes when this bit is cleared. */
	hdma.CR->HALT = 1;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ResumeOperations
 *!< @brief		    		 : Enables the operations halted by setting the HALT bit in CR register.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ResumeOperations(void)
{
	/*  Channel execution resumes. */
	hdma.CR->HALT = 0;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableRequest
 *!< @brief		    		 : Enables request on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableRequest(uint8_t channelNumber)
{
	/* Enable requests on channel (16 bit: 1 bit - 1 channel) */
	hdma.ERQ->ERQn |= (1 << channelNumber);
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableRequest
 *!< @brief		    		 : Enables request on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableRequestImmediately(uint8_t channelNumber)
{
	/* Disable requests on channel immediately */
	hdma.ERQ->ERQn &= ~(1 << channelNumber);
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableAllRequests
 *!< @brief		    		 : Disables all requests.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableAllRequests(void)
{
	HAL_DMA_ENABLE_REGISTER(CERQ);
	/* Disable requests on channel immediately */
	hdma.CERQ->CAER = 1;

	HAL_DMA_DISABLE_REGISTER(CERQ);
}




/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableRequestAfterFinish
 *!< @brief		    		 : Enables request on channel.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableRequestAfterFinish(uint8_t channelNumber)
{
	/* Disable requests on channel when major iteration count reaches zero */
	hdma.TCD[channelNumber]->CSR.DREQ = 1;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableMemMappedRegisters
 *!< @brief		    		 : Set 1 to NOP bit of CEEI, SEEI, CERQ, SERQ, CDNE, SSRT, CERR, CINT registers.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableMemMappedRegisters(void)
{
	HAL_DMA_DISABLE_REGISTER(CEEI);
	HAL_DMA_DISABLE_REGISTER(SEEI);
	HAL_DMA_DISABLE_REGISTER(CERQ);
	HAL_DMA_DISABLE_REGISTER(SERQ);
	HAL_DMA_DISABLE_REGISTER(CDNE);
	HAL_DMA_DISABLE_REGISTER(SSRT);
	HAL_DMA_DISABLE_REGISTER(CERR);
	HAL_DMA_DISABLE_REGISTER(CINT);
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableAllErrorInterrupts
 *!< @brief		    		 : Disables all error interrupts.
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_DisableAllErrorInterrupts(void)
{
	HAL_DMA_ENABLE_REGISTER(CEEI);

	hdma.CEEI->CAEE = 1;

	HAL_DMA_DISABLE_REGISTER(CEEI);
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetChannelReportedError
 *!< @brief		    		 : Shows which channel catched error
 *!< Parameters              :
 *!<                   Input : void
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_GetChannelReportedError(void)
{
	return hdma.ES->ERRCHN;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_ErrorInterrupt
 *!< @brief		    		 : Enables error interrupt on one channel
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableErrorInterrupt(uint8_t channelNumber, DMA_Decision_t decision)
{
	if (decision == enEnable)
	{
		hdma.EEI->EEIn |= (1 << channelNumber);
	}
	else
	{
		hdma.EEI->EEIn &= ~(1 << channelNumber);
	}
}



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
void HAL_DMA_SetChannelPriority(uint8_t channelNumber, uint8_t priority)
{
	hdma.DCHPRI[channelNumber]->CHPRI = (priority & 0x0F);
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_IsChannelActive
 *!< @brief		    		 : Shows either channel active or not.
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint8_t
 *!< Critical section YES/NO : NO
 */
uint8_t HAL_DMA_IsChannelActive(uint8_t channelNumber)
{
	return hdma.TCD[channelNumber]->CSR.ACTIVE;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcAddrOnFinish
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, int32_t adj
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcAddrAdjustment(uint8_t channelNumber, int32_t adj)
{
	hdma.TCD[channelNumber]->SLAST = adj;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstAddrAdjustment
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, int32_t adj
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstAddrAdjustment(uint8_t channelNumber, int32_t adj)
{
	hdma.TCD[channelNumber]->DLASTSGA = adj;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetChannelsArbitration
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t arbitrationType
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetChannelsArbitration(uint8_t arbitrationType)
{
	hdma.CR->ERCA = arbitrationType;
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetHaltOnError
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t bHOE
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetHaltOnError(uint8_t bHOE)
{
	hdma.CR->HOE = bHOE;
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableDebug
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t bDBG
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_EnableDebug(uint8_t bDBG)
{
	hdma.CR->EDBG = bDBG;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetSrcAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t HAL_DMA_GetSrcAddr(uint8_t channelNumber)
{
	return hdma.TCD[channelNumber]->SADDR;
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint32_t srcAddr
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcAddr(uint8_t channelNumber, uint32_t srcAddr)
{
	hdma.TCD[channelNumber]->SADDR = srcAddr;
}


/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint32_t dstAddr
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstAddr(uint8_t channelNumber, uint32_t dstAddr)
{
	hdma.TCD[channelNumber]->DADDR = dstAddr;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetDstAddr
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint32_t
 *!< Critical section YES/NO : NO
 */
uint32_t HAL_DMA_GetDstAddr(uint8_t channelNumber)
{
	return hdma.TCD[channelNumber]->DADDR;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcAddrMask
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint8_t mask
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcAddrMask(uint8_t channelNumber, uint8_t mask)
{
	hdma.TCD[channelNumber]->ATTR.SMOD = mask;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstAddrMask
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint8_t mask
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstAddrMask(uint8_t channelNumber, uint8_t mask)
{
	hdma.TCD[channelNumber]->ATTR.DMOD = mask;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcTransferSize
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_TransferSize_t size
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcTransferSize(uint8_t channelNumber, DMA_TransferSize_t size)
{
	hdma.TCD[channelNumber]->ATTR.SSIZE = size;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstTransferSize
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_TransferSize_t size
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstTransferSize(uint8_t channelNumber, DMA_TransferSize_t size)
{
	hdma.TCD[channelNumber]->ATTR.DSIZE = size;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetSrcRequestOffset
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetSrcRequestOffset(uint8_t channelNumber, DMA_Decision_t decision)
{
	hdma.TCD[channelNumber]->NBYTES.MLOFFNO.SMLOE = decision;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetDstRequestOffset
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetDstRequestOffset(uint8_t channelNumber, DMA_Decision_t decision)
{
	hdma.TCD[channelNumber]->NBYTES.MLOFFNO.DMLOE = decision;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetRequestBlockSize
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint32_t size
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetRequestBlockSize(uint8_t channelNumber, uint32_t size)
{
	HAL_DMA_TCD_t* tcd = hdma.TCD[channelNumber];

	if (hdma.CR->EMLM == enDisable)
	{
		tcd->NBYTES.MLNO = size;
	}
	else
	{
		if ((tcd->NBYTES.MLOFFNO.DMLOE ^ tcd->NBYTES.MLOFFNO.SMLOE) ||
				(tcd->NBYTES.MLOFFNO.DMLOE || tcd->NBYTES.MLOFFNO.SMLOE) )
		{
			tcd->NBYTES.MLOFFNO.NBYTES = size;
		}
		else
		{
			tcd->NBYTES.MLOFFYES.NBYTES = (uint16_t)size;
		}
	}

}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableChannelsLinkOnMinorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ChannelsLinkOnRequestFinish(uint8_t channelNumber, DMA_Decision_t decision)
{
	if (decision == enDisable){
		HAL_DMA_TCD_t* tcd = hdma.TCD[channelNumber];

		if(tcd->CITER.LINKYES.ELINK || tcd->BITER.ELINKYES.ELINK)
		{
			tcd->CITER.LINKYES.LINKCHN = 0;
			tcd->BITER.ELINKYES.LINKCHN = 0;
		}

		tcd->CITER.LINKNO.ELINK = enDisable;
		tcd->BITER.ELINKNO.ELINK = enDisable;
	}
	else
	{
		hdma.TCD[channelNumber]->CITER.LINKNO.ELINK = enEnable;
		hdma.TCD[channelNumber]->BITER.ELINKNO.ELINK = enEnable;
	}
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetEnableDstMinorLoopOffset
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, uint8_t linkedChannelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetLinkedChannelOnRequestFinish(uint8_t channelNumber, uint8_t linkedChannelNumber)
{
	HAL_DMA_ChannelsLinkOnRequestFinish(channelNumber, enEnable);

	hdma.TCD[channelNumber]->CITER.LINKYES.LINKCHN = linkedChannelNumber;
	hdma.TCD[channelNumber]->BITER.ELINKYES.LINKCHN = linkedChannelNumber;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_EnableChannelsLinkOnMinorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetRequestCountToFinish(uint8_t channelNumber, uint16_t minorLoops)
{
	hdma.TCD[channelNumber]->CITER.LINKNO.CITER = minorLoops;
	hdma.TCD[channelNumber]->BITER.ELINKNO.BITER = minorLoops;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_GetBlockIteration
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : uint16_t
 *!< Critical section YES/NO : NO
 */
uint16_t HAL_DMA_GetBlockIteration(uint8_t channelNumber)
{
	return hdma.TCD[channelNumber]->CITER.LINKNO.CITER;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetBandwidthControl
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_BWC_t bandwidth
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetBandwidthControl(uint8_t channelNumber, DMA_BWC_t bandwidth)
{
	hdma.TCD[channelNumber]->CSR.BWC = bandwidth;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_DisableChannelsLinkOnMajorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_ChannelsLinkOnMajorLoop(uint8_t channelNumber, DMA_Decision_t decision)
{
	hdma.TCD[channelNumber]->CSR.MAJORELINK = decision;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_SetLinkedChannelOnMajorLoop
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t isEnable
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_SetLinkedChannelOnMajorLoop(uint8_t channelNumber, uint8_t linkedChannelNumber)
{
	HAL_DMA_ChannelsLinkOnMajorLoop(channelNumber, enEnable);

	hdma.TCD[channelNumber]->CSR.MAJORLINKCH = linkedChannelNumber;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_HalfMajorLoopInterrupt
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_HalfMajorLoopInterrupt(uint8_t channelNumber, DMA_Decision_t decision)
{
	hdma.TCD[channelNumber]->CSR.INTHALF = decision;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_CompleteMajorLoopInterrupt
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_Decision_t decision
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_CompleteMajorLoopInterrupt(uint8_t channelNumber, DMA_Decision_t decision)
{
	hdma.TCD[channelNumber]->CSR.INTMAJOR = decision;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_HalfMajorLoopInterrupt
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_TriggerSwRequest(uint8_t channelNumber)
{
	/* The eDMA hardware automatically clears this flag after the channel begins execution. */
	hdma.TCD[channelNumber]->CSR.START = enEnable;
}



/****************************************************************************************
 *!< Function    	     	 : HAL_DMA_InitChannelMUX
 *!< @brief		    		 : comment
 *!< Parameters              :
 *!<                   Input : uint8_t channelNumber, DMA_RequestSource_t source, DMA_ChannelOperation_t mode
 *!<                   Output:
 *!< Return                  : void
 *!< Critical section YES/NO : NO
 */
void HAL_DMA_InitChannelMUX(uint8_t channelNumber, DMA_RequestSource_t source, DMA_ChannelOperation_t mode)
{
	bool validConfig = true;

	if (mode == enPeriodicTriggered)
	{
		if (channelNumber >= 4)
		{
			hdma.CHCFG[channelNumber]->ENBL = enDisable;
			validConfig = false;
		}
		else
		{
			hdma.CHCFG[channelNumber]->TRIG = enEnable;
		}
	}

	if(validConfig)
	{
		hdma.CHCFG[channelNumber]->ENBL = enEnable;
		hdma.CHCFG[channelNumber]->SOURCE = (uint8_t)source;
	}

}



/************************************** END OF FILE **********************************************/
