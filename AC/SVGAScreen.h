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

#ifndef __SVGASCREEN_H__
#define __SVGASCREEN_H__

#include <libkern/OSTypes.h>
#include "svga_apple_header.h"
#include "svga_reg.h"
#include "svga_apple_footer.h"

class SVGADevice;

class SVGAScreen
{
private:
	SVGADevice* m_svga;

public:
	bool Init(SVGADevice*);

	bool DefineScreen(SVGAScreenObject const* screen);
	bool DestroyScreen(UInt32 screenId);
	bool DefineGMRFB(SVGAGuestPtr ptr,
					 UInt32 bytesPerLine,
					 SVGAGMRImageFormat format);
	bool BlitFromGMRFB(SVGASignedPoint const* srcOrigin,
					   SVGASignedRect const* destRect,
					   UInt32 destScreen);
	bool BlitToGMRFB(SVGASignedPoint const* destOrigin,
					 SVGASignedRect const* srcRect,
					 UInt32 srcScreen);
	bool AnnotateFill(SVGAColorBGRX color);
	bool AnnotateCopy(SVGASignedPoint const* srcOrigin,
					  UInt32 srcScreen);
};

#endif /* __SVGASCREEN_H__ */
