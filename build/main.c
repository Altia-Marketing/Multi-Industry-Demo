/* Copyright (c) 2021-2022 Altia Acquisition Corporation dba Altia, Inc.
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Altia, Inc. The intellectual and technical concepts
 * contained herein are proprietary to Altia, Inc. and may be covered by
 * U.S. and Foreign Patents, patents in process, and are protected by trade
 * secret or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written permission is
 * obtained from Altia, Inc.
 *
 * ALTIA, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * ALTIA, INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Altia API */
#include "altia.h"


/*****************************************************************************/
/* Global variable definitions                                               */
/*****************************************************************************/


/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


/*****************************************************************************/
/* External function declarations                                            */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

void driver_glError(const char * s, ...)
{
}

void driver_InitHW()
{
}

int main(void)
{
    /* Start Altia */
    if (altiaConnect(NULL) < 0)
    {
        printf("Failed to start Altia\r\n");
    }
    else
    {
        /* IMPORTANT:  Cache the output for performance reasons */
        altiaCacheOutput(1);

        /* Select events to receive from altiaPending() */
        altiaSelectEvent(API_TEXT("*"));

        /* Executive Loop */
        for (;;)
        {
            int event_count = altiaPending();
            if (event_count > 0)
            {
                AltiaEventType event_value;
                AltiaCharType * event_name;

                altiaNextEvent((AltiaCharType **)(&event_name), &event_value);

                /* Do something here with new events from the GUI */
#ifdef ALTIAUNICODEAPI
                /* printf("%S = %f\r\n", event_name, (double)event_value); */
#else
                /* printf("%s = %f\r\n", event_name, (double)event_value); */
#endif
            }
            else if (event_count < 0)
            {
                /* Error condition */
                printf("Lost connnection to Altia\r\n");
                break;
            }

            /* Give up the CPU for other tasks -- no effect if the operating
            ** system does not support tasking with pre-emption.
            */
            //altiaSleep(17);
        }

        altiaDisconnect();
    }
}
