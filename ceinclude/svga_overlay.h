/*

    CEsvga2 - ChrisEric1 Super Video Graphics Array 2
    Copyright (C) 2023-2024, Christopher Eric Lentocha

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

/*
 * svga_overlay.h --
 *
 *    Definitions for video-overlay support.
 */

#ifndef _SVGA_OVERLAY_H_
#define _SVGA_OVERLAY_H_

#include "svga_reg.h"

/*
 * Video formats we support
 */

#define CECL_FOURCC_YV12 0x32315659 // 'Y' 'V' '1' '2'
#define CECL_FOURCC_YUY2 0x32595559 // 'Y' 'U' 'Y' '2'
#define CECL_FOURCC_UYVY 0x59565955 // 'U' 'Y' 'V' 'Y'

typedef enum {
   SVGA_OVERLAY_FORMAT_INVALID = 0,
   SVGA_OVERLAY_FORMAT_YV12 = CECL_FOURCC_YV12,
   SVGA_OVERLAY_FORMAT_YUY2 = CECL_FOURCC_YUY2,
   SVGA_OVERLAY_FORMAT_UYVY = CECL_FOURCC_UYVY,
} SVGAOverlayFormat;

#define SVGA_VIDEO_COLORKEY_MASK             0x00ffffff

#define SVGA_ESCAPE_CECL_VIDEO             0x00020000

#define SVGA_ESCAPE_CECL_VIDEO_SET_REGS    0x00020001
        /* FIFO escape layout:
         * Type, Stream Id, (Register Id, Value) pairs */

#define SVGA_ESCAPE_CECL_VIDEO_FLUSH       0x00020002
        /* FIFO escape layout:
         * Type, Stream Id */

typedef
struct SVGAEscapeVideoSetRegs {
   struct {
      uint32 cmdType;
      uint32 streamId;
   } header;

   // May include zero or more items.
   struct {
      uint32 registerId;
      uint32 value;
   } items[1];
} SVGAEscapeVideoSetRegs;

typedef
struct SVGAEscapeVideoFlush {
   uint32 cmdType;
   uint32 streamId;
} SVGAEscapeVideoFlush;


/*
 * Struct definitions for the video overlay commands built on
 * SVGAFifoCmdEscape.
 */
typedef
struct {
   uint32 command;
   uint32 overlay;
} SVGAFifoEscapeCmdVideoBase;

typedef
struct {
   SVGAFifoEscapeCmdVideoBase videoCmd;
} SVGAFifoEscapeCmdVideoFlush;

typedef
struct {
   SVGAFifoEscapeCmdVideoBase videoCmd;
   struct {
      uint32 regId;
      uint32 value;
   } items[1];
} SVGAFifoEscapeCmdVideoSetRegs;

typedef
struct {
   SVGAFifoEscapeCmdVideoBase videoCmd;
   struct {
      uint32 regId;
      uint32 value;
   } items[SVGA_VIDEO_NUM_REGS];
} SVGAFifoEscapeCmdVideoSetAllRegs;


/*
 *----------------------------------------------------------------------
 *
 * CECLVideoGetAttributes --
 *
 *      Computes the size, pitches and offsets for YUV frames.
 *
 * Results:
 *      TRUE on success; otherwise FALSE on failure.
 *
 * Side effects:
 *      Pitches and offsets for the given YUV frame are put in 'pitches'
 *      and 'offsets' respectively. They are both optional though.
 *
 *----------------------------------------------------------------------
 */

static INLINE Bool
CECLVideoGetAttributes(const SVGAOverlayFormat format,    // IN
                         uint32 *width,                     // IN / OUT
                         uint32 *height,                    // IN / OUT
                         uint32 *size,                      // OUT
                         uint32 *pitches,                   // OUT (optional)
                         uint32 *offsets)                   // OUT (optional)
{
    int tmp;

    *width = (*width + 1) & ~1;

    if (offsets) {
        offsets[0] = 0;
    }

    switch (format) {
    case CECL_FOURCC_YV12:
       *height = (*height + 1) & ~1;
       *size = (*width + 3) & ~3;

       if (pitches) {
          pitches[0] = *size;
       }

       *size *= *height;

       if (offsets) {
          offsets[1] = *size;
       }

       tmp = ((*width >> 1) + 3) & ~3;

       if (pitches) {
          pitches[1] = pitches[2] = tmp;
       }

       tmp *= (*height >> 1);
       *size += tmp;

       if (offsets) {
          offsets[2] = *size;
       }

       *size += tmp;
       break;

    case CECL_FOURCC_YUY2:
    case CECL_FOURCC_UYVY:
       *size = *width * 2;

       if (pitches) {
          pitches[0] = *size;
       }

       *size *= *height;
       break;

    default:
       return FALSE;
    }

    return TRUE;
}

#endif // _SVGA_OVERLAY_H_
