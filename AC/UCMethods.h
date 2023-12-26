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

#ifndef __UCMETHODS_H__
#define __UCMETHODS_H__

enum eIOCEGLMethods {
	kIOCEGLSetSurface,
	kIOCEGLSetSwapRect,
	kIOCEGLSetSwapInterval,
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	kIOCEGLGetConfig,
#endif
	kIOCEGLGetSurfaceSize,
	kIOCEGLGetSurfaceInfo,
	kIOCEGLReadBuffer,
	kIOCEGLFinish,
	kIOCEGLWaitForStamp,
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	kIOCEGLNewTexture,
	kIOCEGLDeleteTexture,
#endif
	kIOCEGLBecomeGlobalShared,
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	kIOCEGLPageOffTexture,
#endif
	kIOCEGLPurgeTexture,
	kIOCEGLSetSurfaceVolatileState,
	kIOCEGLSetSurfaceGetConfigStatus,
	kIOCEGLReclaimResources,
	kIOCEGLGetDataBuffer,
	kIOCEGLSetStereo,
	kIOCEGLPurgeAccelerator,
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	kIOCEGLGetChannelMemory,
#else
	kIOCEGLSubmitCommandBuffer,
	kIOCEGLFilterControl,	// This method only appeared in OS 10.6.8
#endif

	kIOCEGLGetQueryBuffer,
	kIOCEGLGetNotifiers,
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	kIOCEGLNewHeapObject,
#endif
	kIOCEGLKernelPrintf,
	kIOCEGLNvRmConfigGet,
	kIOCEGLNvRmConfigGetEx,
	kIOCEGLNvClientRequest,
	kIOCEGLPageoffSurfaceTexture,
	kIOCEGLGetDataBufferWithOffset,
	kIOCEGLNvRmControl,
	kIOCEGLGetPowerState,
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1060
	kIOCEGLSetWatchdogTimer,
	kIOCEGLGetHandleIndex,
	kIOCEGLForceTextureLargePages,
#endif

	kIOCEGLNumMethods
};

enum eIOCE2DMethods {
	kIOCE2DSetSurface,
	kIOCE2DGetConfig,
	kIOCE2DGetSurfaceInfo1,
	kIOCE2DSwapSurface,
	kIOCE2DScaleSurface,
	kIOCE2DLockMemory,
	kIOCE2DUnlockMemory,
	kIOCE2DFinish,
	kIOCE2DDeclareImage,
	kIOCE2DCreateImage,
	kIOCE2DCreateTransfer,
	kIOCE2DDeleteImage,
	kIOCE2DWaitImage,
	kIOCE2DSetSurfacePagingOptions,
	kIOCE2DSetSurfaceVsyncOptions,
	kIOCE2DSetMacrovision,

	kIOCE2DReadConfigs,
	kIOCE2DReadConfigEx,
	kIOCE2DGetSurfaceInfo2,
	kIOCE2DKernelPrintf,

	kIOCE2DCopyRegion,
	kIOCE2DUseAccelUpdates,
	kIOCE2DRectCopy,
	kIOCE2DRectFill,
	kIOCE2DUpdateFramebuffer,

	kIOCE2DNumMethods
};

enum eIOCEDVDMethods {
	kIOCEDVDNumMethods
};

enum eIOCEDeviceMethods {
	kIOCEDeviceCreateShared,
	kIOCEDeviceGetConfig,
	kIOCEDeviceGetSurfaceInfo,
	kIOCEDeviceGetName,
	kIOCEDeviceWaitForStamp,
	kIOCEDeviceNewTexture,
	kIOCEDeviceDeleteTexture,
	kIOCEDevicePageOffTexture,
	kIOCEDeviceGetChannelMemory,

	kIOCEDeviceKernelPrintf,
	kIOCEDeviceNvRmConfigGet,
	kIOCEDeviceNvRmConfigGetEx,
	kIOCEDeviceNvRmControl,

	kIOCEDeviceNumMethods
};

enum eIOCEOCDMethods {
	kIOCEOCDFinish,
	kIOCEOCDWaitForStamp,

	kIOCEOCDCheckErrorNotifier,
	kIOCEOCDMarkTextureForOCDUse,
	kIOCEOCDFreeEvent,
	kIOCEOCDGetHandleIndex,

	kIOCEOCDNumMethods
};

#endif /* __UCMETHODS_H__ */
