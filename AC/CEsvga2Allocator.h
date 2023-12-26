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

#ifndef __CESVGA2ALLOCATOR_H__
#define __CESVGA2ALLOCATOR_H__

#include <libkern/c++/OSObject.h>
#include <libkern/OSTypes.h>
#include <IOKit/IOReturn.h>

class CEsvga2Allocator : public OSObject
{
	OSDeclareDefaultStructors(CEsvga2Allocator);

private:
	typedef uint32_t pool_size_t;

	uint8_t* poolStart;		// First byte in the pool
	pool_size_t poolBlocks;

	int minBits;			// Minimum block size is 1 << minBits (expect 12 = log_2(PAGE_SIZE))
	int numSizes;			// sizes go up by powers of two (expect 13, max block == 2^24 bytes == SVGA_FB_MAX_TRACEABLE_SIZE)
	pool_size_t freeList[13];	// free lists
	uint8_t* map;			// bit map
	pool_size_t freeBytes;

	static bool memAll(void const *p, size_t bytes);
	bool testAll(size_t firstBit, size_t pastBit);
	void clearAll(size_t firstBit, size_t pastBit);
	IOReturn clearCheck(size_t firstBit, size_t pastBit);
	static bool memAny(void const *p, size_t bytes);
	bool testAny(size_t firstBit, size_t pastBit);
	void makeFree(pool_size_t firstFree, int bitsFree, bool zap);
	void toFree(pool_size_t firstBlock, pool_size_t pastBlock, bool zap);
	IOReturn BuddyMalloc(int bits, void **newStore);
	IOReturn BuddyAllocSize(void const *sss, int *numBits);
	void ReleaseMap();

public:
	/*
	 * Methods overridden from superclass
	 */
	bool init();
	void free();
	static CEsvga2Allocator* factory();

	/*
	 * Allocator's Methods
	 */
	IOReturn Init(void* startAddress, size_t bytes);
	IOReturn Rebase(void* newStartAddress);
	IOReturn Release(size_t startOffsetBytes, size_t endOffsetBytes);
	IOReturn Malloc(size_t bytes, void** newStore);
	IOReturn Realloc(void* ptrv, size_t size, void** newPtr);
	IOReturn Free(void* storage2);
	IOReturn Available(size_t* bytesFree);
	IOReturn Check(size_t* counts);
};

#endif /* __CESVGA2ALLOCATOR_H__ */
