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

#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

class VertexArray
{
	uint8_t* kernel_ptr;
	size_t size_bytes;
	size_t offset_in_gmr;
	size_t next_avail;
	uint32_t sid;
	uint32_t gmr_id;
	uint32_t fence;

public:
	void init(void);
	void purge(class CEsvga2Accel* provider);
	IOReturn alloc(class CEsvga2Accel* provider, size_t num_bytes, uint8_t** ptr);
	IOReturn upload(class CEsvga2Accel* provider, uint8_t const* ptr, size_t num_bytes, uint32_t* sid);
};

#endif /* __VERTEXARRAY_H__ */
