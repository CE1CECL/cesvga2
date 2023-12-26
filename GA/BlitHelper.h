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

#ifndef __BLITHELPER_H__
#define __BLITHELPER_H__

#ifdef __cplusplus
extern "C" {
#endif

IOReturn useAccelUpdates(io_connect_t context, int state);
IOReturn RectCopy(io_connect_t context, void const* copyRects, size_t copyRectsSize);
IOReturn RectFill(io_connect_t context, uintptr_t color, void const* rects, size_t rectsSize);
IOReturn UpdateFramebuffer(io_connect_t context, UInt32 const* rect);
IOReturn CopyRegion(io_connect_t context, uintptr_t source_surface_id, intptr_t destX, intptr_t destY, void const* region, size_t regionSize);

#ifdef __cplusplus
}
#endif

#endif /* __BLITHELPER_H__ */
