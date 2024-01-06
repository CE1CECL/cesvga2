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

#ifndef __CESVGA2SURFACE_H__
#define __CESVGA2SURFACE_H__

#include <IOKit/IOUserClient.h>
#include <IOKit/graphics/IOAccelSurfaceConnect.h>
#include "VendorTransferBuffer.h"

class CEsvga2Surface: public IOUserClient
{
	OSDeclareDefaultStructors(CEsvga2Surface);

private:
	/*
	 * Base
	 */
	task_t m_owning_task;
	class CEsvga2Accel* m_provider;
	int m_log_level;

	/*
	 * Flags
	 */
	unsigned bHaveID:1;				// covers everything under "ID stuff"
	unsigned bHaveMasterSurface:1;
	unsigned bVideoMode:1;
	unsigned bDirectBlit:1;
	unsigned bHaveScreenObject:1;
	unsigned bSkipWriteLockOnce:1;
	unsigned bGLMode:1;

	/*
	 * Locking stuff
	 */
	enum {
		ceSurfaceLockRead = 0U,
		ceSurfaceLockWrite = 1U,
		ceSurfaceLockContext = 2U
	};
	uint8_t volatile bIsLocked;

	/*
	 * ID stuff
	 */
	uint32_t m_wID;
	SVGA3dSurfaceFormat m_surfaceFormat;
	uint32_t m_bytes_per_pixel;
	uint32_t m_pixel_format;

	/*
	 * Backing stuff
	 */
	struct {
		uint8_t* self;
		vm_offset_t offset;
		vm_size_t size;
		IOMemoryMap* map[2];
		VendorTransferBuffer vtb;
	} m_backing;

	/*
	 * Client backing stuff
	 */
	struct {
		mach_vm_address_t addr;
		vm_size_t rowbytes;
		vm_size_t size;
	} m_client_backing;

	/*
	 * Shape stuff
	 */
	OSData* m_last_shape;
	IOAccelDeviceRegion const* m_last_region;
	uint32_t m_framebufferIndex;

	/*
	 * Scale stuff
	 */
	IOAccelSurfaceScaling m_scale;

	/*
	 * Fullscreen stuff
	 */
	IOAccelSurfaceReadData m_screenInfo;

	/*
	 * Video stuff
	 */
	struct {
		uint32_t stream_id;
		uint32_t cecl_pixel_format;
		SVGAOverlayUnit	unit;
	} m_video;

	/*
	 * GL stuff
	 */

	struct {
		int original_mode_bits;
		IOAccelSize rt_size;	// render target size
		int volatile attach_count;
		uint32_t color_sid;
		uint32_t depth_sid;
		int ds_format;
		uint8_t volatile rt_dirty;
	} m_gl;

	/*
	 * Private support methods
	 */
	IOReturn set_shape_backing_length_ext(eIOAccelSurfaceShapeBits options,
										  uintptr_t framebufferIndex,
										  mach_vm_address_t backing,
										  size_t rowbytes,
										  size_t backingLength,
										  IOAccelDeviceRegion const* rgn,
										  size_t rgnSize);
	bool haveFrontBuffer() const;
	bool isBackingValid() const;
	int classifyBacking() const;
	bool hasSourceGrown() const;
	bool isSourceValid() const;
	bool isClientBackingValid() const;
	bool isIdentityScale() const;
	void Init();
	void Cleanup();
	void clearLastRegion();
	void calculateSurfaceInformation(IOAccelSurfaceInformation* info);
	void calculateScaleParameters(bool bFromGFB = false);
	void clipRegionToBuffer(IOAccelDeviceRegion* region,
							int deltaX,
							int deltaY);

	/*
	 * Private support methods - backing
	 */
	bool wrapClientBacking();
	bool allocGMRBacking();
	bool allocBacking();
	bool mapBacking(task_t for_task, uint32_t index);
	void releaseBacking();
	void releaseBackingMap(uint32_t index);
	IOReturn obtainKernelPtrs(IOVirtualAddress* base, vm_size_t* limit_from_base, IOMemoryMap** holder);

	/*
	 * Private support methods - 3D
	 */
	void Start3D();
	void Cleanup3D();
	IOReturn detectBlitBug();
	IOReturn DMAOutDirect(bool withFence);
	IOReturn DMAOutWithCopy(bool withFence);
	IOReturn DMAOutStretchWithCopy(bool withFence);
	IOReturn doPresent();

	/*
	 * Private support methods - Screen Object
	 */
	IOReturn ScreenObjectOutDirect(bool withFence);
	IOReturn ScreenObjectOutVia3D(bool withFence);

	/*
	 * Private support methods - GFB
	 */
	IOReturn GFBOutDirect();

	/*
	 * Private support methods - Video
	 */
	void clear_yuv_to_black(void* buffer, vm_size_t size);
	IOReturn setup_trick_buffer();
	bool setVideoDest();
	bool setVideoRegs();
	void videoReshape();

	/*
	 * Private support methods - GL
	 */
	void InitGL();
	void CleanupGL();
	IOReturn flushGLSurface();
	IOReturn copyGLSurfaceToBacking();

public:
	/*
	 * Methods overridden from superclass
	 */
	IOExternalMethod* getTargetAndMethodForIndex(IOService** targetP, UInt32 index);
	IOReturn clientClose();
#if 1
	IOReturn clientMemoryForType(UInt32 type, IOOptionBits* options, IOMemoryDescriptor** memory);
#endif
	IOReturn externalMethod(uint32_t selector,
							IOExternalMethodArguments* arguments,
							IOExternalMethodDispatch* dispatch = 0,
							OSObject* target = 0,
							void* reference = 0);
	IOReturn message(UInt32 type, IOService* provider, void* argument = 0);
	bool start(IOService* provider);
	bool initWithTask(task_t owningTask, void* securityToken, UInt32 type);
	static CEsvga2Surface* withTask(task_t owningTask, void* securityToken, uint32_t type);

	/*
	 * Interface for CEsvga22DContext
	 */
	IOReturn context_set_surface(uint32_t cecl_pixel_format, uint32_t apple_pixel_format);
	IOReturn context_scale_surface(IOOptionBits options, uint32_t width, uint32_t height);
	IOReturn context_lock_memory(task_t context_owning_task,
								 mach_vm_address_t* address,
								 mach_vm_size_t* rowBytes);
	IOReturn context_unlock_memory(uint32_t* swapFlags);
	IOReturn copy_framebuffer_region_to_self(uint32_t framebufferIndex,
											 int destX,
											 int destY,
											 IOAccelDeviceRegion const* region,
											 size_t regionSize);
	IOReturn copy_self_region_to_framebuffer(uint32_t framebufferIndex,
											 int destX,
											 int destY,
											 IOAccelDeviceRegion const* region,
											 size_t regionSize);
	IOReturn copy_surface_region_to_self(class CEsvga2Surface* source_surface,
										 int destX,
										 int destY,
										 IOAccelDeviceRegion const* region,
										 size_t regionSize);
	IOReturn surface_video_off();
	IOReturn surface_flush_video(uint32_t* swapFlags);

	/*
	 * Interface for CEsvga2GLContext
	 */
	int getOriginalModeBits() const { return m_gl.original_mode_bits; }
	int getSurfaceFormat() const { return m_surfaceFormat; }
	uint8_t getBytesPerPixel() const { return m_bytes_per_pixel; }
	void getBoundsForGL(uint32_t* inner_width, uint32_t* inner_height, uint32_t* outer_width, uint32_t* outer_height) const;
	bool getSurfacesForGL(uint32_t* color_sid, uint32_t* depth_sid) const;
	IOReturn attachGL(int cmb);
	IOReturn resizeGL();
	IOReturn detachGL();
	void touchRenderTarget();

	/*
	 * IOAccelSurfaceConnect
	 */
	IOReturn surface_read_lock_options(eIOAccelSurfaceLockBits options, IOAccelSurfaceInformation* info, size_t* infoSize);
	IOReturn surface_read_unlock_options(eIOAccelSurfaceLockBits options);
	IOReturn get_state(eIOAccelSurfaceStateBits* state);	// not called
	IOReturn surface_write_lock_options(eIOAccelSurfaceLockBits options, IOAccelSurfaceInformation* info, size_t* infoSize);
	IOReturn surface_write_unlock_options(eIOAccelSurfaceLockBits options);
	IOReturn surface_read(IOAccelSurfaceReadData const* parameters, size_t parametersSize);
	IOReturn set_shape_backing(eIOAccelSurfaceShapeBits options,
							   uintptr_t framebufferIndex,
							   IOVirtualAddress backing,
							   size_t rowbytes,
							   IOAccelDeviceRegion const* rgn,
							   size_t rgnSize);	// not called
	IOReturn set_id_mode(uintptr_t wID, eIOAccelSurfaceModeBits modebits);
	IOReturn set_scale(eIOAccelSurfaceScaleBits options,
					   IOAccelSurfaceScaling const* scaling,
					   size_t scalingSize);
	IOReturn set_shape(eIOAccelSurfaceShapeBits options,
					   uintptr_t framebufferIndex,
					   IOAccelDeviceRegion const* rgn,
					   size_t rgnSize);
	IOReturn surface_flush(uintptr_t framebufferMask, IOOptionBits options);
	IOReturn surface_query_lock();
	IOReturn surface_read_lock(IOAccelSurfaceInformation* info, size_t* infoSize);
	IOReturn surface_read_unlock();
	IOReturn surface_write_lock(IOAccelSurfaceInformation* info, size_t* infoSize);
	IOReturn surface_write_unlock();
	IOReturn surface_control(uintptr_t selector, uintptr_t arg, uint32_t* result);
	IOReturn set_shape_backing_length(eIOAccelSurfaceShapeBits options,
									  uintptr_t framebufferIndex,
									  IOVirtualAddress backing,
									  size_t rowbytes,
									  size_t backingLength,
									  IOAccelDeviceRegion const* rgn /* , size_t rgnSize */);
};

#endif /* __CESVGA2SURFACE_H__ */
