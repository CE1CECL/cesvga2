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

#include <IOKit/IOLib.h>
#include "SVGAScreen.h"
#include "SVGADevice.h"

#if LOGGING_LEVEL >= 1
#define SLog(fmt, ...) IOLog(fmt, ##__VA_ARGS__)
#else
#define SLog(fmt, ...)
#endif

#define CLASS SVGAScreen

bool CLASS::Init(SVGADevice* device)
{
	if (!device) {
		m_svga = 0;
		return false;
	}
	m_svga = device;
	if (!device->HasFIFOCap(SVGA_FIFO_CAP_SCREEN_OBJECT | SVGA_FIFO_CAP_SCREEN_OBJECT_2)) {
		SLog("%s: Physical device does not have Screen Object support.\n", __FUNCTION__);
		return false;
	}
	return true;
}

bool CLASS::DefineScreen(SVGAScreenObject const* screen)
{
	SVGAFifoCmdDefineScreen* cmd = static_cast<SVGAFifoCmdDefineScreen*>(m_svga->FIFOReserveCmd(SVGA_CMD_DEFINE_SCREEN, screen->structSize));
	if (!cmd)
		return false;
	memcpy(cmd, screen, screen->structSize);
	m_svga->FIFOCommitAll();
	return true;
}

bool CLASS::DestroyScreen(UInt32 screenId)
{
	SVGAFifoCmdDestroyScreen* cmd = static_cast<SVGAFifoCmdDestroyScreen*>(m_svga->FIFOReserveCmd(SVGA_CMD_DESTROY_SCREEN, sizeof *cmd));
	if (!cmd)
		return false;
	cmd->screenId = screenId;
	m_svga->FIFOCommitAll();
	return true;
}

bool CLASS::DefineGMRFB(SVGAGuestPtr ptr,
						UInt32 bytesPerLine,
						SVGAGMRImageFormat format)
{
	SVGAFifoCmdDefineGMRFB* cmd = static_cast<SVGAFifoCmdDefineGMRFB*>(m_svga->FIFOReserveCmd(SVGA_CMD_DEFINE_GMRFB, sizeof *cmd));
	if (!cmd)
		return false;
	cmd->ptr = ptr;
	cmd->bytesPerLine = bytesPerLine;
	cmd->format = format;
	m_svga->FIFOCommitAll();
	return true;
}

bool CLASS::BlitFromGMRFB(SVGASignedPoint const* srcOrigin,
						  SVGASignedRect const* destRect,
						  UInt32 destScreen)
{
	SVGAFifoCmdBlitGMRFBToScreen* cmd = static_cast<SVGAFifoCmdBlitGMRFBToScreen*>(m_svga->FIFOReserveCmd(SVGA_CMD_BLIT_GMRFB_TO_SCREEN, sizeof *cmd));
	if (!cmd)
		return false;
	cmd->srcOrigin = *srcOrigin;
	cmd->destRect = *destRect;
	cmd->destScreenId = destScreen;
	m_svga->FIFOCommitAll();
	return true;
}

bool CLASS::BlitToGMRFB(SVGASignedPoint const* destOrigin,
						SVGASignedRect const* srcRect,
						UInt32 srcScreen)
{
	SVGAFifoCmdBlitScreenToGMRFB* cmd = static_cast<SVGAFifoCmdBlitScreenToGMRFB*>(m_svga->FIFOReserveCmd(SVGA_CMD_BLIT_SCREEN_TO_GMRFB, sizeof *cmd));
	if (!cmd)
		return false;
	cmd->destOrigin = *destOrigin;
	cmd->srcRect = *srcRect;
	cmd->srcScreenId = srcScreen;
	m_svga->FIFOCommitAll();
	return true;
}

bool CLASS::AnnotateFill(SVGAColorBGRX color)
{
	SVGAFifoCmdAnnotationFill* cmd = static_cast<SVGAFifoCmdAnnotationFill*>(m_svga->FIFOReserveCmd(SVGA_CMD_ANNOTATION_FILL, sizeof *cmd));
	if (!cmd)
		return false;
	cmd->color = color;
	m_svga->FIFOCommitAll();
	return true;
}

bool CLASS::AnnotateCopy(SVGASignedPoint const* srcOrigin, UInt32 srcScreen)
{
	SVGAFifoCmdAnnotationCopy* cmd = static_cast<SVGAFifoCmdAnnotationCopy*>(m_svga->FIFOReserveCmd(SVGA_CMD_ANNOTATION_COPY, sizeof *cmd));
	if (!cmd)
		return false;
	cmd->srcOrigin = *srcOrigin;
	cmd->srcScreenId = srcScreen;
	m_svga->FIFOCommitAll();
	return true;
}
