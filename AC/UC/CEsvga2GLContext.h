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

#ifndef __CESVGA2GLCONTEXT_H__
#define __CESVGA2GLCONTEXT_H__

#include <IOKit/IOUserClient.h>

struct VendorCommandBufferHeader;
struct VendorGLStreamInfo;
struct CEsvga2TextureBuffer;
class IOMemoryDescriptor;

class CEsvga2GLContext: public IOUserClient
{
	OSDeclareDefaultStructors(CEsvga2GLContext);

private:
	task_t m_owning_task;					// offset 0x78
											// offset 0x7C - 0x80: unknown
	class CEsvga2Accel* m_provider;			// offset 0x80
											// offset 0x84 - 0x8C: unknown
	class CEsvga2Shared* m_shared;			// offset 0x8C
											// offset 0x90 - 0xA8: unknown 
	uint16_t m_drawbuf_params[2];			// offset 0xA8 - 0xAC
											// offset 0xAC - 0xB4: unknown
	IOMemoryDescriptor* m_fences;			// offset 0xB4
	size_t m_fences_len;					// offset 0xB8
	struct GLDFence* m_fences_ptr;			// offset 0xBC
											// offset 0xC0 - 0xC4: unknown
	class CEsvga2Surface* m_surface_client;	// offset 0xC4
	CEsvga2CommandBuffer m_command_buffer;	// offset 0xC8 - 0xFC
	class OSSet* m_gc;						// offset 0xFC
	CEsvga2CommandBuffer m_context_buffer0; // offset 0x100 - 0x134
	CEsvga2CommandBuffer m_context_buffer1; // offset 0x130 - 0x164
											// offset 0x160 - 0x194: unknown
	int m_stream_error;						// offset 0x194
											// offset 0x198 - 0x19C: unknown
	uint32_t m_mem_type;					// offset 0x19C
											// offset 0x1A0 - 0x1B0: unknown
	CEsvga2TextureBuffer* m_txs[21U];		// offset 0x1B0
											// textures 0 - 15 used for texture stages
											// texture 16 used for vertex buffer
											// textures 17 - 18 used for DrawFBO (color & depth)
											// textures 19 - 20 used for ReadFBO (color & depth)
	struct FBODescriptor* m_fbo[2];			// m_fbo[0] for DrawFBO [offset 0x204]
											// m_fbo[1] for ReadFBO [offset 0x208]
											// offset 0x20C - 0x228: VendorGLStreamInfo
											// offset 0x228 - 0x238: unknown
											// offset 0x238: mask from map_state
											// offset 0x23C: count of num bits in mask
											// offset 0x240 - 0x300: uint32[16][3] for tex data from map_state
											// offset 0x300 - 0x304: unknown
	uint32_t m_drawrect[4];					// offset 0x304 - 0x314

	/*
	 * CEsvga2 Specific
	 */
	int m_log_level;
	/*
	 * Intel Pipeline processor
	 */
	class CEsvga2IPP* m_ipp;

	/*
	 * Private Methods
	 */
	void Init();
	void Cleanup();
	static bool allocCommandBuffer(CEsvga2CommandBuffer*, size_t);
	static void initCommandBufferHeader(VendorCommandBufferHeader*, size_t);
	bool allocAllContextBuffers();
	static IOReturn get_status(uint32_t*);

	/*
	 * Apple Pipeline processor
	 */
	void CleanupApp();
	uint32_t processCommandBuffer(struct VendorCommandDescriptor*);
	void discardCommandBuffer();
	static void removeTextureFromStream(CEsvga2TextureBuffer*);
	static void addTextureToStream(CEsvga2TextureBuffer*);
	void submit_midbuffer(VendorGLStreamInfo*);
	void get_texture(VendorGLStreamInfo*, CEsvga2TextureBuffer*, bool);
	static void dirtyTexture(CEsvga2TextureBuffer* tx, uint8_t face, uint8_t mipmap);
	static void get_tex_data(CEsvga2TextureBuffer* tx, uint32_t* tex_gart_address, uint32_t* tex_pitch, int kind);
	static void write_tex_data(uint32_t, uint32_t*, CEsvga2TextureBuffer*);
	void touchDrawFBO(void);
	IOReturn create_host_surface_for_texture(CEsvga2TextureBuffer*);
	IOReturn alloc_and_load_texture(CEsvga2TextureBuffer*);
	IOReturn tex_subimage_2d(CEsvga2TextureBuffer* tx,
							 struct GLDTexSubImage2DStruc const* desc);
	void setup_drawbuffer_registers(uint32_t*);

public:
	/*
	 * Command buffer process & discard methods [Apple]
	 */
	/*
	 * Tokens 0 - 11
	 */
	void process_token_Noop(VendorGLStreamInfo*);
	void process_token_TextureVolatile(VendorGLStreamInfo*);
	void process_token_TextureNonVolatile(VendorGLStreamInfo*);
	void process_token_SetSurfaceState(VendorGLStreamInfo*);
	void process_token_BindDrawFBO(VendorGLStreamInfo*);
	void process_token_BindReadFBO(VendorGLStreamInfo*);
	void process_token_UnbindDrawFBO(VendorGLStreamInfo*);
	void process_token_UnbindReadFBO(VendorGLStreamInfo*);
	void process_token_Start(VendorGLStreamInfo*);
	void process_token_End(VendorGLStreamInfo*);
	void process_token_UserEnd(VendorGLStreamInfo*);
	void process_token_Swap(VendorGLStreamInfo*);
	void process_token_Flush(VendorGLStreamInfo*);

	/*
	 * Tokens 32 - 64
	 */
	void discard_token_Texture(VendorGLStreamInfo*);
	void discard_token_NoTex(VendorGLStreamInfo*);
	void discard_token_VertexBuffer(VendorGLStreamInfo*);
	void discard_token_NoVertexBuffer(VendorGLStreamInfo*);
	void discard_token_DrawBuffer(VendorGLStreamInfo*);
	void discard_token_Noop(VendorGLStreamInfo*);
	void discard_token_TexSubImage2D(VendorGLStreamInfo*);
	void discard_token_CopyPixelsDst(VendorGLStreamInfo*);
	void discard_token_AsyncReadDrawBuffer(VendorGLStreamInfo*);
	void discard_token_BindHeap(VendorGLStreamInfo*);
	void discard_token_SetShaderHeapOffsets(VendorGLStreamInfo*);
	void process_token_Texture(VendorGLStreamInfo*);
	void process_token_NoTex(VendorGLStreamInfo*);
	void process_token_VertexBuffer(VendorGLStreamInfo*);
	void process_token_NoVertexBuffer(VendorGLStreamInfo*);
	void process_token_DrawBuffer(VendorGLStreamInfo*);
	void process_token_SetFence(VendorGLStreamInfo*);
	void process_token_TexSubImage2D(VendorGLStreamInfo*);
	void process_token_CopyPixelsDst(VendorGLStreamInfo*);
	void process_token_CopyPixelsSrc(VendorGLStreamInfo*);
	void process_token_CopyPixelsSrcFBO(VendorGLStreamInfo*);
	void process_token_DrawRect(VendorGLStreamInfo*);
	void process_token_AsyncReadDrawBuffer(VendorGLStreamInfo*);
	void process_token_BindHeap(VendorGLStreamInfo*);
	void process_token_SetShaderHeapOffsets(VendorGLStreamInfo*);

public:
	/*
	 * Methods overridden from superclass
	 */
	IOExternalMethod* getTargetAndMethodForIndex(IOService** targetP, UInt32 index);
	IOReturn clientClose();
	IOReturn clientMemoryForType(UInt32 type, IOOptionBits* options, IOMemoryDescriptor** memory);
	IOReturn connectClient(IOUserClient* client);
#if 0
	IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments* arguments, IOExternalMethodDispatch* dispatch = 0, OSObject* target = 0, void* reference = 0);
#endif
	bool start(IOService* provider);
	bool initWithTask(task_t owningTask, void* securityToken, UInt32 type);
	static CEsvga2GLContext* withTask(task_t owningTask, void* securityToken, uint32_t type);

	/*
	 * Methods corresponding to Apple's GeForce.kext GL Context User Client
	 */
	/*
	 * IONVGLContext
	 */
	IOReturn set_surface(uintptr_t, uintptr_t /* eIOGLContextModeBits */, uintptr_t, uintptr_t);
	IOReturn set_swap_rect(intptr_t, intptr_t, intptr_t, intptr_t);
	IOReturn set_swap_interval(intptr_t, intptr_t);
	IOReturn get_config(uint32_t*, uint32_t*, uint32_t*);
	IOReturn get_surface_size(uint32_t*, uint32_t*, uint32_t*, uint32_t*);
	IOReturn get_surface_info(uintptr_t, uint32_t*, uint32_t*, uint32_t*);
	IOReturn read_buffer(struct sIOGLContextReadBufferData const*, size_t);
	IOReturn finish();
	IOReturn wait_for_stamp(uintptr_t);
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	IOReturn new_texture(struct VendorNewTextureDataStruc const*,
						 struct sIONewTextureReturnData*,
						 size_t,
						 size_t*);
	IOReturn delete_texture(uintptr_t);
#endif
	IOReturn become_global_shared(uintptr_t);
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	IOReturn page_off_texture(struct sIODevicePageoffTexture const*, size_t);
#endif
	IOReturn purge_texture(uintptr_t);
	IOReturn set_surface_volatile_state(uintptr_t);
	IOReturn set_surface_get_config_status(struct sIOGLContextSetSurfaceData const*,
										   struct sIOGLContextGetConfigStatus*,
										   size_t,
										   size_t*);
	IOReturn reclaim_resources();
	IOReturn get_data_buffer(struct sIOGLContextGetDataBuffer*, size_t*);
	IOReturn set_stereo(uintptr_t, uintptr_t);
	IOReturn purge_accelerator(uintptr_t);
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	IOReturn get_channel_memory(struct sIODeviceChannelMemoryData*, size_t*);
#else
	IOReturn submit_command_buffer(uintptr_t do_get_data,
								   struct sIOGLGetCommandBuffer*,
								   size_t*);
	IOReturn filter_control(struct sIOGLFilterControl const*,		// OS 10.6.8 Only
							struct sIOGLFilterControl*,
							size_t,
							size_t*);
#endif

	/*
	 * NVGLContext
	 */
	IOReturn get_query_buffer(uintptr_t c1, struct sIOGLGetQueryBuffer*, size_t*);
	IOReturn get_notifiers(uint32_t*, uint32_t*);
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 1060
	IOReturn new_heap_object(struct sNVGLNewHeapObjectData const*,
							 struct sIONewTextureReturnData*,
							 size_t,
							 size_t*);
#endif
	IOReturn kernel_printf(char const*, size_t);
	IOReturn nv_rm_config_get(uint32_t const*, uint32_t*, size_t, size_t*);
	IOReturn nv_rm_config_get_ex(uint32_t const*, uint32_t*, size_t, size_t*);
	IOReturn nv_client_request(void const*, void*, size_t, size_t*);
	IOReturn pageoff_surface_texture(struct sNVGLContextPageoffSurfaceTextureData const*, size_t);
	IOReturn get_data_buffer_with_offset(struct sIOGLContextGetDataBuffer*, size_t*);
	IOReturn nv_rm_control(uint32_t const*, uint32_t*, size_t, size_t*);
	IOReturn get_power_state(uint32_t*, uint32_t*);
#if __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1060
	IOReturn set_watchdog_timer(uintptr_t);
	IOReturn GetHandleIndex(uint32_t*, uint32_t*);
	IOReturn ForceTextureLargePages(uintptr_t);
#endif
};

#endif /* __CESVGA2GLCONTEXT_H__ */
