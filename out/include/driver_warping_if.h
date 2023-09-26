/* Copyright (c) 2023 Altia Acquisition Corporation dba Altia, Inc.
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


/** FILE: driver_warping_if.h ***************************************************
 **
 ** This file contains defines and function declarations for warping
 ** functions.
 **
 ***************************************************************************/
#ifndef DRIVER_WARPING_IF_INCLUDED
#define DRIVER_WARPING_IF_INCLUDED

#include <stdint.h>
#include <EGL/egl.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


#if (1 == DRIVER_WARPING_ENABLED)



/*! This function is called by target driver to initialize the warping
 *! interfaces module.
 *\param dindex - Index of the display.  Not the display ID.
 *\param width - width of the display in pixels
 *\param height - height of the display in pixels
 *\returns 0 on success.
 */
extern int32_t driver_warping_init(uint32_t dindex, uint32_t width, uint32_t height);


/*! This function is called by target driver to de-initialize the warping
 *! module.
 *\param dindex - Index of the display.  Not the display ID.
 *\returns 0 on success
 */
extern int32_t driver_warping_shutdown(uint32_t dindex);


/*! This function is called by target driver to render the pre-warp layer
 *! buffer with warping applied to the on-screen framebuffer.
 *\param dindex - Index of the display.  Not the display ID.
 *\param image - Pointer to the 32bit ARGB image data for the current frame
 *\param size - Size of the data pointed to by image in bytes
 *\returns 0 on success
 */
extern int32_t driver_do_warping(const uint32_t dindex, uint8_t *image, const uint32_t size);


#if (0 == DRIVER_HW_WARPING)
/*! This function is called by target driver to set the mesh
 *! data used for warping. Source mesh data indicates the part of the
 *! layer texture that would be warped and rendered to the display.
 *! Target mesh data indicates to the points on the target display
 *! that the source data points would be rendered to.
 *\param dindex - Index of the display.  Not the display ID.
 *\param src_mesh: pointer to source mesh data
 *\param tgt_mesh: pointer to target mesh data
 *\param xCount: The number of horizontal cells in the meshes
 *\param yCount: The number of vertical cells in the meshes
 *\returns 0 on success
 */
extern int32_t driver_warp_set_mesh(
        uint32_t dindex,
        const float * src_mesh,
        const float * tgt_mesh,
        const uint32_t xCount,
        const uint32_t yCount);
#endif /* (0 == DRIVER_HW_WARPING) */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* (1 == DRIVER_WARPING_ENABLED) */

#endif /* !DRIVER_WARPING_IF_INCLUDED */
