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

#include <IOKit/IOKitLib.h>
#include "BlitHelper.h"
#include "UCMethods.h"

IOReturn useAccelUpdates(io_connect_t context, int state)
{
	uint64_t input;

	input = state ? 1 : 0;
	return IOConnectCallMethod(context,
							   kIOCE2DUseAccelUpdates,
							   &input, 1,
							   0, 0,
							   0, 0,
							   0, 0);
}

IOReturn RectCopy(io_connect_t context, void const* copyRects, size_t copyRectsSize)
{
	return IOConnectCallMethod(context,
							   kIOCE2DRectCopy,
							   0, 0,
							   copyRects, copyRectsSize,
							   0, 0,
							   0, 0);
}

IOReturn RectFill(io_connect_t context, uintptr_t color, void const* rects, size_t rectsSize)
{
	uint64_t input;

	input = color;
	return IOConnectCallMethod(context,
							   kIOCE2DRectFill,
							   &input, 1,
							   rects, rectsSize,
							   0, 0,
							   0, 0);
}

IOReturn UpdateFramebuffer(io_connect_t context, UInt32 const* rect)
{
	return IOConnectCallMethod(context,
							   kIOCE2DUpdateFramebuffer,
							   0, 0,
							   rect, 4U * sizeof(UInt32),
							   0, 0,
							   0, 0);
}

IOReturn CopyRegion(io_connect_t context, uintptr_t source_surface_id, intptr_t destX, intptr_t destY, void const* region, size_t regionSize)
{
	uint64_t input[3];

	input[0] = source_surface_id;
	input[1] = (uint64_t) destX;
	input[2] = (uint64_t) destY;
	return IOConnectCallMethod(context,
							   kIOCE2DCopyRegion,
							   &input[0], 3,
							   region, regionSize,
							   0, 0,
							   0, 0);
}
