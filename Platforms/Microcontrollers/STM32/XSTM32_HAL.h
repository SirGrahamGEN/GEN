//------------------------------------------------------------------------------------------
//  XSTM32_HAL.H
//
/**
// \class
//
//  STM32_HAL includes
//
//  @author  Abraham J. Velez
//  @version 05/04/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _XSTM32_HAL_H_
#define _XSTM32_HAL_H_


//---- INCLUDES ----------------------------------------------------------------------------

#if defined(STM32F072xB)
#define HW_STM32F0XX
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#endif

#if defined(STM32F303xC) || defined(STM32F303xE)
#define HW_STM32F3XX
#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
#endif

#if defined(STM32F407xx)|| defined(STM32F411xE) || defined(STM32F446xx)
#define HW_STM32F4XX
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#endif

#if defined(STM32WB55xx) || defined (STM32WB5Mxx) || defined(STM32WB35xx)
#define HW_STM32WB55XX
#include "stm32wbxx.h"
#include "stm32wbxx_hal.h"
#endif



//---- DEFINES & ENUMS  --------------------------------------------------------------------

#ifndef TRUE
#define TRUE                  1
#endif

#ifndef FALSE
#define FALSE                 0
#endif



#ifdef __cplusplus
extern "C"
{
#endif
    
/* ------ Declarations copied from arm\src\lib\<dlib\heap>\dlmalloc.c ----*/
/* ------ MAKE SURE to copy correct/current content from dlmalloc.c ------*/

#define MALLINFO_FIELD_TYPE size_t

#define STRUCT_MALLINFO_DECLARED 1
struct mallinfo {
  MALLINFO_FIELD_TYPE arena;    /* non-mmapped space allocated from system */
  MALLINFO_FIELD_TYPE ordblks;  /* number of free chunks */
  MALLINFO_FIELD_TYPE smblks;   /* always 0 */
  MALLINFO_FIELD_TYPE hblks;    /* always 0 */
  MALLINFO_FIELD_TYPE hblkhd;   /* space in mmapped regions */
  MALLINFO_FIELD_TYPE usmblks;  /* maximum total allocated space */
  MALLINFO_FIELD_TYPE fsmblks;  /* always 0 */
  MALLINFO_FIELD_TYPE uordblks; /* total allocated space */
  MALLINFO_FIELD_TYPE fordblks; /* total free space */
  MALLINFO_FIELD_TYPE keepcost; /* releasable (via malloc_trim) space */
};
/* ------------------------------------------------------------------------*/

struct mallinfo __iar_dlmallinfo(void);
void __iar_dlmalloc_stats(void);

#ifdef __cplusplus
}
#endif

//---- CLASS -------------------------------------------------------------------------------


//---- INLINE FUNCTIONS --------------------------------------------------------------------


#endif
