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

#ifndef __VENDORTRANSFERBUFFER_H__
#define __VENDORTRANSFERBUFFER_H__

struct VendorTransferBuffer {
	uint32_t pad1;			//   0
	uint32_t gart_ptr;		//   4
	class IOMemoryDescriptor* md;
							//   8
	uint16_t offset12;		// offset 0xC - initialized to 4 in CEsvga2TextureBuffer
	uint16_t counter14;		// offset 0xE
							// 0x10 end
	uint32_t gmr_id;
	uint32_t fence;

	void init(void);
	IOReturn prepare(class CEsvga2Accel* provider);
	void sync(class CEsvga2Accel* provider);
	void complete(class CEsvga2Accel* provider);
	void discard(void);
};

#endif /* __VENDORTRANSFERBUFFER_H__ */
