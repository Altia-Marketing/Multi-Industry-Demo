/* Copyright (c) 2006-2023 Altia Acquisition Corporation dba Altia, Inc.
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


/*
 * This file contains the callback definitions for the 
 * DrawingAreaObject. These must support c as well as c++.
 */
#ifndef DRAWAREACB_H
#define DRAWAREACB_H

#define ALT_REDRAW_CALLBACK     1
#define ALT_RESIZE_CALLBACK     2
#define ALT_CLOSE_CALLBACK      3
#define ALT_EVENT_CALLBACK      4
#define ALT_SHOW_CALLBACK       5
#define ALT_RUNMODE_CALLBACK    6
#define ALT_ACTIVATE_CALLBACK   7
#define ALT_MOVE_CALLBACK       8

typedef void (*AltiaDARedrawFunc)(
    int objId,
    void *win,
    void *dc,
    int  left,
    int  bottom,
    int  right,
    int  top,
    int  x,
    int  y,
    int  xoff,
    int  yoff,
    AltiaEx_Transform_type *trans);

typedef int (*AltiaDAResizeFunc)(
    int objId,
    int width,
    int height);

typedef int (*AltiaDACloseFunc)(
    int objId);

typedef int (*AltiaDARunModeFunc)(
    int mode);

typedef int (*AltiaDAActivateFunc)(
    void *win,
    int active);

#ifndef ALTIADACALLBACKFUNC
#define ALTIADACALLBACKFUNC
typedef int (*AltiaDACallBkFunc)(int objId);
#endif

typedef void (*AltiaDAEventFunc)(
    int objId,
    void *win,
    AltiaEx_InputEvent_type *event);

typedef void (*AltiaDAShowFunc)(
    int objId,
    int showFlag);

typedef void (*AltiaDAMoveFunc)(
    int objId,
    int x,
    int y);

/* If this function changes change the typedef below */
extern int altiaExRegCallback(
    int objId,
    int callbkType,
    AltiaDACallBkFunc func);

typedef int (*AltiaExRegCallbackFunc)(
    int objId,
    int callbkType,
    AltiaDACallBkFunc func);

/* If this function changes change the typedef below */
extern int altiaExGetInfo(
    int objId,
    void **win,
    int *x,
    int *y,
    int *width,
    int *height);

typedef int (*AltiaExGetInfoFunc)(
    int objId,
    void **win,
    int *x,
    int *y,
    int *width,
    int *height);

/* If this function changes change the typedef below */
extern int altiaExUpdate(
    int objId,
    int left,
    int bottom,
    int right,
    int top);

typedef int (*AltiaExUpdateFunc)(
    int objId,
    int left,
    int bottom,
    int right,
    int top);

extern int altiaExRouteValue(
    ALTIA_CHAR *eventName,
    AltiaEventType value);

typedef int (*AltiaExRouteValueFunc)(
    ALTIA_CHAR *eventName,
    AltiaEventType value);

extern int altiaExRouteText(
    ALTIA_CHAR *eventName,
    const ALTIA_CHAR *string );

typedef int (*AltiaExRouteTextFunc)(
    ALTIA_CHAR *eventName,
    const ALTIA_CHAR *string);

extern int altiaExRouteConnectionValue(
    int objId,
    ALTIA_CHAR *eventName,
    AltiaEventType value);

typedef int (*AltiaExRouteConnectionValueFunc)(
    int objId,
    ALTIA_CHAR *eventName,
    AltiaEventType value);

extern int altiaExRouteConnectionText(
    int objId,
    ALTIA_CHAR *eventName,
    const ALTIA_CHAR *string);

typedef int (*AltiaExRouteConnectionTextFunc)(
    int objId,
    ALTIA_CHAR *eventName,
    const ALTIA_CHAR *string);

#endif /* DRAWAREACB_H */
