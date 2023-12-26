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
 * svga_escape.h --
 *
 *    Definitions for our own (vendor-specific) SVGA Escape commands.
 */

#ifndef _SVGA_ESCAPE_H_
#define _SVGA_ESCAPE_H_


/*
 * Namespace IDs for the escape command
 */

#define SVGA_ESCAPE_NSID_CECL 0x00000000
#define SVGA_ESCAPE_NSID_DEVEL  0xFFFFFFFF


/*
 * Within SVGA_ESCAPE_NSID_CECL, we multiplex commands according to
 * the first DWORD of escape data (after the nsID and size). As a
 * guideline we're using the high word and low word as a major and
 * minor command number, respectively.
 *
 * Major command number allocation:
 *
 *   0000: Reserved
 *   0001: SVGA_ESCAPE_CECL_LOG (svga_binary_logger.h)
 *   0002: SVGA_ESCAPE_CECL_VIDEO (svga_overlay.h)
 *   0003: SVGA_ESCAPE_CECL_HINT (svga_escape.h)
 */

#define SVGA_ESCAPE_CECL_MAJOR_MASK  0xFFFF0000


/*
 * SVGA Hint commands.
 *
 * These escapes let the SVGA driver provide optional information to
 * he host about the state of the guest or guest applications. The
 * host can use these hints to make user interface or performance
 * decisions.
 *
 * Notes:
 *
 *   - SVGA_ESCAPE_CECL_HINT_FULLSCREEN is deprecated for guests
 *     that use the SVGA Screen Object extension. Instead of sending
 *     this escape, use the SVGA_SCREEN_FULLSCREEN_HINT flag on your
 *     Screen Object.
 */

#define SVGA_ESCAPE_CECL_HINT               0x00030000
#define SVGA_ESCAPE_CECL_HINT_FULLSCREEN    0x00030001  // Deprecated

typedef
struct {
   uint32 command;
   uint32 fullscreen;
   struct {
      int32 x, y;
   } monitorPosition;
} SVGAEscapeHintFullscreen;

#endif /* _SVGA_ESCAPE_H_ */
