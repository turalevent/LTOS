//
// LTOS_oneshot.c
//
// Author: Levent TURA
//
//

#include "main.h"
#include "stdlib.h"
#include "LTOS_config.h"

static oneshot_t 	*fosp = NULL,
					*dosp = NULL;	// oneshot will be deleted..

void oneshotFree(oneshot_t *os);
void oneshotInit(oneshot_t *os);


/**
  * @brief  Init Oneshot module
  * @param	None
  * @retval None
  */
void oneshotInit(oneshot_t *os)
{
	tick_t time_now;

    oneshot_t *osp = NULL;

    time_now = LTOS_getTick();

#ifdef LTOS_MAGIC
    os->magic = LTOS_MAGIC;
#endif
	os->callback = NULL;
	os->arg = 0;
#ifdef LTOS_GARBAGE_COLL_TOUT
	os->killTm		= time_now + LTOS_GARBAGE_COLL_TOUT;
#endif
	os->isEnabled = false;
	os->isOverflowed = false;
	os->nosp = NULL;
    
    if(os != fosp) {                // if this onceall is not first oneshot..
    	osp = fosp;
		while(1) {
            if(osp->nosp !=  NULL) {
                osp = osp->nosp;
            } else {
				break;
			}
        }
        osp->nosp = os;
    }
}

/**
  * @brief  Free Oneshot
  * @param	os : oneshot pointer will be free
  * @retval None
  */
void oneshotFree(oneshot_t *os)
{
    oneshot_t   *osp = NULL;

	osp = fosp;
    if(osp == os) {
        fosp = os->nosp;
    } else {
        while(1) {						// link current os's next os pointer to previous os's next pointer
            if(osp->nosp == os) {
                osp->nosp = os->nosp;
                break;
            } else {
            	osp = osp->nosp;		// skip to next os
            }
        }
    }
    free(os);
}

/**
  * @brief  Run LTOS forever
  * @param	None
  * @retval result:
  * 		1- LTOS_ERR_MAGIC_CRASH
  */
ltosError_t LTOS_run(void)
{
    oneshot_t *os = NULL,
    		  *nos= NULL;

	tick_t tickNow = 0x00;

	ltosError_t err = LTOS_ERR_NONE;

	os = fosp;

	while(err == LTOS_ERR_NONE) {
#ifdef LTOS_MAGIC
        if(os->magic != LTOS_MAGIC) {
            err = LTOS_ERR_MAGIC_CRASH;  // there is memory crash, stop execution..
        }
#endif
		tickNow = LTOS_getTick();
		if(!os->isEnabled) {
			// Find next oneshot
            if(os->nosp == NULL) {
            	nos = fosp;
            } else {
        		nos = os->nosp;
            }
            // Garbage collection
#ifdef LTOS_GARBAGE_COLL_TOUT
        	if(os->killTm <= tickNow) {
        		oneshotFree(os);
        	}
#endif
        	// Jump to next oneshot
        	os = nos;
			continue;
		}
		// Execute callback if its time elapsed
		if(tickNow >= os->endTick) {
			os->isOverflowed= true;
			os->isEnabled 	= false;
            os->callback(os->arg);
		}
		// Find next oneshot
        if(os->nosp !=  NULL) 	{ os = os->nosp; }
        else 					{ os = fosp;     }
        // Free oneshot if requested by user
        if(dosp) {
        	oneshotFree(dosp);
        	dosp = NULL;
        }
	}
    
    return err;
}

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
ltosError_t LTOS_oneshotAttach(oneshot_t *os, os_callback_t fp, uint32_t arg, tick_t tout)
{
	tick_t time_now = 0x00;

	if((os == NULL) || (fp == NULL)) {
		return LTOS_ERR_INVALID_PTR;
	}
#ifdef LTOS_MAGIC
    if(os->magic != LTOS_MAGIC) {
        return LTOS_ERR_MAGIC_CRASH;
    }
#endif

    time_now 		= LTOS_getTick();
	os->endTick 	= time_now + tout;
#ifdef LTOS_GARBAGE_COLL_TOUT
	os->killTm		= time_now + LTOS_GARBAGE_COLL_TOUT;
#endif
	os->callback 	= fp;
	os->arg 		= arg;
	os->isEnabled 	= true;
   	os->isOverflowed= false;

	return LTOS_ERR_NONE;
}

/**
  * @brief  Allocate new Oneshot
  * @param	None
  * @retval Oneshot pointer if allocated else NULL
  */
oneshot_t *LTOS_oneshotAlloc(void)
{
    oneshot_t *os = NULL;

    os = malloc(sizeof(oneshot_t));
    if(!os) {                               // no free space on heap for oneshot allocation!
        return NULL;
    }

    if( fosp == NULL ) {                    // if this oneshot is first oneshot, save this address..
        fosp = os;
    }
    oneshotInit(os);

    return os;
}

/**
  * @brief  Attach Oneshot to todo list
  * @param	None
  * @retval result:
  * 		0- LTOS_ERR_NONE
  * 		1- LTOS_ERR_MAGIC_CRASH
  * 		2- LTOS_ERR_INVALID_PTR,
  * 		3- LTOS_ERR_BUSY
  */
ltosError_t LTOS_oneshotFree(oneshot_t *os)
{
    if(!os) {
        return LTOS_ERR_INVALID_PTR;
    }
	if(dosp) {
		return LTOS_ERR_BUSY;
	}

	dosp = os;

    return LTOS_ERR_NONE;
}
