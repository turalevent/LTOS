//
// LTOS_oneshot.h
//
// Author: Levent TURA
//
// Last revision date: 14/11/2009
//

#ifndef __LTOS_ONESHOT_H
#define __LTOS_ONESHOT_H

#include "LTOS_config.h"

typedef void (*os_callback_t)(uint32_t);

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif


// Oneshot struct
struct oneshot {
#ifdef LTOS_MAGIC
    uint32_t magic;
#endif
	tick_t 	 endTick;
#ifdef LTOS_GARBAGE_COLL_TOUT
	tick_t	 killTm;
#endif
    uint32_t arg;
    uint8_t  isEnabled;
    uint8_t  isOverflowed;
    os_callback_t callback;
    void     *nosp;
};
typedef struct oneshot oneshot_t;

enum ltos_error {
	LTOS_ERR_NONE,			// Success
	LTOS_ERR_MAGIC_CRASH,	// MAGIC number crashed. There is memory management error!
	LTOS_ERR_INVALID_PTR,	// NULL or invalid oneshot pointer
	LTOS_ERR_BUSY			// LTOS is busy to do new request.
};
typedef enum ltos_error ltosError_t;

/**
  * @brief  Run LTOS forever
  * @param	None
  * @retval result:
  * 		1- LTOS_ERR_MAGIC_CRASH
  */
ltosError_t LTOS_run(void);

/**
  * @brief  Allocate new Oneshot
  * @param	None
  * @retval Oneshot pointer if allocated else NULL
  */
oneshot_t *LTOS_oneshotAlloc(void);

/**
  * @brief  Attach Oneshot into Round-robin chain.
  * @param	*os : pointer of the oneshot will be attached
  * 		fp 	: function pointer will be called when timeout elapsed
  * 		arg	: argument will be passed to function
  * 		tout: timeout in terms of tick resolution
  * @retval result:
  * 		0- LTOS_ERR_NONE
  * 		1- LTOS_ERR_MAGIC_CRASH
  * 		2- LTOS_ERR_INVALID_PTR
  */
ltosError_t LTOS_oneshotAttach(oneshot_t *os, os_callback_t fp, uint32_t arg, tick_t tout);

/**
  * @brief  Attach Oneshot to todo list
  * @param	None
  * @retval result:
  * 		0- LTOS_ERR_NONE
  * 		1- LTOS_ERR_MAGIC_CRASH
  * 		2- LTOS_ERR_INVALID_PTR,
  * 		3- LTOS_ERR_BUSY
  */
ltosError_t LTOS_oneshotFree(oneshot_t *os);

#endif 
