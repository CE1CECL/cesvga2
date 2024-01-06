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

#ifndef __GLCOMMON_H__
#define __GLCOMMON_H__

#include "VendorTransferBuffer.h"

#if 1
struct GLKMemoryElement {
	uint32_t gart_ptr;		//    0
	uint32_t pitch;			//    4
	uint32_t f0;			//    8
	uint16_t f1[4];			// 0x0C
							// 0x14 end
};
#endif

#ifdef GL_INCL_SHARED
struct CEsvga2TextureBuffer
{
	VendorTransferBuffer xfer;
									// offset 0x10 - 0x28 all dwords
									// offset 0x20 initialized to 0xE34
	class IOMemoryMap* client_map;	// offset 0x28
	struct GLDSysObject* sys_obj;	// offset 0x2C
	mach_vm_address_t sys_obj_client_addr;
									// offset 0x30
	class CEsvga2Shared* creator;	// offset 0x38
	uint8_t sys_obj_type;			// offset 0x3C, copy of sys_obj->type, init to 12
	uint8_t num_faces;				// offset 0x3D, init to 1
	uint8_t num_mipmaps;			// offset 0x3E, init to 1
	uint8_t min_mipmap;				// offset 0x3F, init to 0
	uint32_t width;					// offset 0x40
	uint16_t height;				// offset 0x44
	uint16_t depth;					// offset 0x46
	uint32_t vram_pitch;			// offset 0x48
	uint32_t pitch;					// offset 0x4C
	uint32_t vram_bytes;			// offset 0x50
	uint32_t f1;					// offset 0x54
	uint16_t bytespp;				// offset 0x58
									// offset 0x5C, 0x60 next prev pointers of circular linked list
	CEsvga2TextureBuffer* next;		// offset 0x64
	CEsvga2TextureBuffer* prev;		// offset 0x68
									// Note - GLKMemoryElement at offset 0x6C (20 bytes)
	struct {						// Host Memory Element instead
		uint32_t surface_id;
		int surface_format;
		uint32_t yuv_shadow;
	};
	union {							// offset 0x80 Note: 0x80 - 0x98 a sub-structure
		CEsvga2TextureBuffer* linked_agp;	// for TEX_TYPE_AGPREF, TEX_TYPE_OOB
		struct {							// for TEX_TYPE_AGP
			mach_vm_address_t agp_offset_in_page;
			uint32_t mem_changed;			// offset 0x88
			mach_vm_offset_t agp_addr;		// offset 0x8C
			vm_size_t agp_size;				// offset 0x94
		};
		struct {							// for TEX_TYPE_SURFACE
			class CEsvga2Surface* linked_surface;
			class CEsvga2Surface* next_surface;	// offset 0x84
			uint32_t fb_idx_mask;			// offset 0x88
			uint32_t cgs_surface_id;		// offset 0x8C
		};
	};
	uint64_t vram_tile_pages;		// offset 0x98
	uint32_t vram_page_bytes;		// offset 0xA0
									// offset 0xA4 - 0xAC are dwords
									// ends   0xAC
};
#endif /* GL_INCL_SHARED */

#ifdef GL_INCL_PUBLIC
struct CEsvga2CommandBuffer
{
	VendorTransferBuffer xfer;
	uint32_t pad3[4];
	uint32_t submit_stamp;
	struct VendorCommandBufferHeader* kernel_ptr;
	size_t size;
};
#endif /* GL_INCL_PUBLIC */

#ifdef GL_INCL_PRIVATE

/*
 * Known:
 *   - data[4] is the size of the buffer (in dwords) starting
 *     right after the header.
 *   - data[5] is a flag word, bit 1 (mask 0x2) if on, tells
 *     the client to flush the surface attached to the context.
 *   - data[7] is really the first word of the pipeline
 *   - each pipeline command begins with a count of the number
 *     of dwords in that command.  A terminating token has a
 *     non-zero upper nibble (0x10000000 or 0x20000000).
 */
struct VendorCommandBufferHeader
{
	uint32_t data[4];
	uint32_t size_dwords;
	uint32_t flags;
	uint32_t stamp;
	uint32_t begin;
	uint32_t downstream[0];
};

struct VendorCommandDescriptor {
	uint32_t* next;		// residual downstream pointer, kernel
	uint32_t ds_ptr;	// residual downstream pointer, gart
	uint32_t ds_count_dwords;	// residual downstream count
	uint32_t* end_point;	// end point in CB of APP processor
};

static inline
bool isIdValid(uint32_t id)
{
	return static_cast<int>(id) >= 0;
}

static inline
uint32_t bit_select(uint32_t val, int shift, int num_bits)
{
	return (val >> shift) & ((1U << num_bits) - 1U);
}

#endif /* GL_INCL_PRIVATE */

#endif /* __GLCOMMON_H__ */
