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

#ifndef __GLDCODE_H__
#define __GLDCODE_H__

#ifdef __cplusplus
extern "C" {
#endif

kern_return_t glrPopulateDevice(io_connect_t connect, display_info_t* dinfo);
uint32_t glrGLIBitsGE(uint32_t num);
uint32_t glrGLIColorsGE(uint32_t num);
void glrWaitSharedObject(gld_shared_t* shared, gld_sys_object_t* obj);
void glrInitializeHardwareShared(gld_shared_t* shared, void* channel_memory);
void glrDestroyZeroTexture(gld_shared_t* shared, gld_texture_t* texture);
void glrDestroyHardwareShared(gld_shared_t* shared);
void glrFlushSysObject(gld_context_t* context, gld_sys_object_t* obj, int arg2);
void load_libs();
void unload_libs();
void SubmitPacketsToken(gld_context_t*, int);
void glrReleaseVendShrPipeProg(gld_shared_t* shared, void* arg1);
void glrReleaseVendCtxPipeProg(void* arg0, void* arg1);
void glrDeleteCachedProgram(gld_pipeline_program_t* pp, vend_ctx_pipe_prog* ctxp);
void glrDeleteSysPipelineProgram(gld_shared_t* shared, gld_pipeline_program_t* pp);
void glrModifySysPipelineProgram(gld_shared_t* shared, gld_pipeline_program_t* pp);
GLDReturn glrValidatePixelFormat(PixelFormat* pixel_format);
void glrKillClient(kern_return_t kr);
uint32_t xlateColorMode(uint32_t colorMode);
void glrSetWindowModeBits(uint32_t* wmb, PixelFormat* pixel_format);
void glrInitializeHardwareState(gld_context_t* context, PixelFormat* pixel_format);
void glrSetConfigData(gld_context_t* context, void* arg3, PixelFormat* pixel_format);
uint32_t glrGLIAlphaGE(int alpha_bits);
char const* glrGetString(display_info_t* dinfo, int string_code);
void glrFlushMemory(int, uint8_t const* base, uint32_t num_bytes);
void glrReleaseDrawable(gld_context_t* context);
int glrSanitizeWindowModeBits(uint32_t);
void glrDrawableChanged(gld_context_t* context);
int glrGetKernelTextureAGPRef(gld_shared_t* shared,
							  gld_texture_t* texture,
							  void const* pixels1,
							  void const* pixels2,
							  uint32_t texture_size);
void glrWriteAllHardwareState(gld_context_t* context);

void cb_chkpt(gld_context_t*, int);

/*
 * Dispatch functions
 */
void glrAccum(gld_context_t*, uint32_t, float);
void glrClear(gld_context_t*, uint32_t);
int glrReadPixels(gld_context_t*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, void*, uint32_t, void*);
void glrDrawPixels(gld_context_t*);
void glrCopyPixels(gld_context_t*);
void glrRenderBitmap(gld_context_t*);
void glrRenderPoints(gld_context_t*, void*, uint32_t);
void glrRenderLines(gld_context_t*, void*, uint32_t);
void glrRenderLineStrip(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderLineLoop(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderPolygon(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderTriangles(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderTriangleFan(gld_context_t*, void*, uint32_t, uint32_t, uint32_t);
void glrRenderTriangleStrip(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderQuads(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderQuadStrip(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderPointsPtr(gld_context_t*, void*, uint32_t);
void glrRenderLinesPtr(gld_context_t*, void*, uint32_t, uint32_t);
void glrRenderPolygonPtr(gld_context_t*, void*, uint32_t, uint32_t);
void glrBeginPrimitiveBuffer(gld_context_t*, uint32_t, void*);
void glrEndPrimitiveBuffer(gld_context_t*, void*, void*, uint32_t);
void glrHookFinish(gld_context_t*);
void glrHookFlush(gld_context_t*);
void glrHookSwap(gld_context_t*);
void glrSetFence(gld_context_t*, void*);
int glrNoopRenderVertexArray(gld_context_t*);

#ifdef __cplusplus
}
#endif

#endif /* __GLDCODE_H__ */
