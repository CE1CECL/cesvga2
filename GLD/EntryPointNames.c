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

#include "EntryPointNames.h"

#pragma GCC visibility push(hidden)

char const* const entry_point_names[NUM_ENTRIES] =
{
/*
 * From OS 10.6
 */
"gldGetVersion",
"gldGetRendererInfo",
"gldChoosePixelFormat",
"gldDestroyPixelFormat",
"gldCreateShared",
"gldDestroyShared",
"gldCreateContext",
"gldReclaimContext",
"gldDestroyContext",
"gldAttachDrawable",
"gldInitDispatch",
"gldUpdateDispatch",
"gldGetString",
"gldGetError",
"gldSetInteger",
"gldGetInteger",
"gldFlush",
"gldFinish",
"gldTestObject",
"gldFlushObject",
"gldFinishObject",
"gldWaitObject",
"gldCreateTexture",
"gldIsTextureResident",
"gldModifyTexture",
"gldLoadTexture",
"gldUnbindTexture",
"gldReclaimTexture",
"gldDestroyTexture",
"gldCreateTextureLevel",		// Discontinued OS 10.6.3
"gldGetTextureLevelInfo",
"gldGetTextureLevelImage",
"gldModifyTextureLevel",		// Discontinued OS 10.6.3
"gldDestroyTextureLevel",		// Discontinued OS 10.6.3
"gldCreateBuffer",
"gldLoadBuffer",
"gldFlushBuffer",
"gldPageoffBuffer",
"gldUnbindBuffer",
"gldReclaimBuffer",
"gldDestroyBuffer",
"gldGetMemoryPlugin",
"gldSetMemoryPlugin",
"gldTestMemoryPlugin",
"gldFlushMemoryPlugin",
"gldDestroyMemoryPlugin",
"gldCreateFramebuffer",
"gldUnbindFramebuffer",
"gldReclaimFramebuffer",
"gldDestroyFramebuffer",
"gldCreatePipelineProgram",
"gldGetPipelineProgramInfo",
"gldModifyPipelineProgram",
"gldUnbindPipelineProgram",
"gldDestroyPipelineProgram",
"gldCreateProgram",
"gldDestroyProgram",
"gldCreateVertexArray",
"gldModifyVertexArray",
"gldFlushVertexArray",
"gldUnbindVertexArray",
"gldReclaimVertexArray",
"gldDestroyVertexArray",
"gldCreateFence",
"gldDestroyFence",
"gldCreateQuery",
"gldGetQueryInfo",
"gldDestroyQuery",
"gldObjectPurgeable",
"gldObjectUnpurgeable",
"gldCreateComputeContext",
"gldDestroyComputeContext",
"gldLoadHostBuffer",
"gldSyncBufferObject",
"gldSyncTexture",
/*
 * Added OS 10.6.3
 */
"gldGenerateTexMipmaps",
"gldCopyTexSubImage",
"gldModifyTexSubImage",
"gldBufferSubData",
"gldModifyQuery",
"gldDiscardFramebuffer",
/*
 * From OS 10.5.8
 */
"gldGetTextureLevel",
"gldDeleteTextureLevel",
"gldDeleteTexture",
"gldAllocVertexBuffer",
"gldCompleteVertexBuffer",
"gldFreeVertexBuffer",
"gldGetMemoryPluginData",
"gldSetMemoryPluginData",
"gldFinishMemoryPluginData",
"gldTestMemoryPluginData",
"gldDestroyMemoryPluginData"
};

#pragma GCC visibility pop
