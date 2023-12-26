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

#ifndef __CESVGA2GA_H__
#define __CESVGA2GA_H__

#include <IOKit/IOCFPlugIn.h>

#ifdef __cplusplus

class CEsvga2GA
{
public:
	HRESULT QueryInterface(REFIID iid, LPVOID *ppv);
	ULONG AddRef();
	ULONG Release();
	IOReturn Probe(CFDictionaryRef propertyTable, io_service_t service, SInt32* order);
	IOReturn Start(CFDictionaryRef propertyTable, io_service_t service);
	IOReturn Stop();
	IOReturn Reset(IOOptionBits options);
	IOReturn CopyCapabilities(FourCharCode select, CFTypeRef* capabilities);
	IOReturn Flush(IOOptionBits options);
	IOReturn Synchronize(UInt32 options, UInt32 x, UInt32 y, UInt32 w, UInt32 h);
	IOReturn GetBeamPosition(IOOptionBits options, SInt32 * position);
	IOReturn AllocateSurface(IOOptionBits options, IOBlitSurface* surface, void* cgsSurfaceID);
	IOReturn FreeSurface(IOOptionBits options, IOBlitSurface* surface);
	IOReturn LockSurface(IOOptionBits options, IOBlitSurface* surface, vm_address_t* address);
	IOReturn UnlockSurface(IOOptionBits options, IOBlitSurface* surface, IOOptionBits* swapFlags);
	IOReturn SwapSurface(IOOptionBits options, IOBlitSurface* surface, IOOptionBits* swapFlags);
	IOReturn SetDestination(IOOptionBits options, IOBlitSurface* surface);
	IOReturn GetBlitter(IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitterPtr* blitter);
	IOReturn WaitComplete(IOOptionBits options);

	IOReturn Blitter(IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitOperation* operation, void* source);
};

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * IOGraphicsAccelerator
 */
static IOReturn ceReset(void* myInstance, IOOptionBits options);
static IOReturn ceGetCapabilities(void* myInstance, FourCharCode select, CFTypeRef* capabilities);
static IOReturn ceFlush(void* myInstance, IOOptionBits options);
static IOReturn ceSynchronize(void* myInstance, UInt32 options, UInt32 x, UInt32 y, UInt32 w, UInt32 h);
static IOReturn ceGetBeamPosition(void* myInstance, IOOptionBits options, SInt32* position);
static IOReturn ceAllocateSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface, void* cgsSurfaceID);
static IOReturn ceFreeSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface);
static IOReturn ceLockSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface, vm_address_t* address);
static IOReturn ceUnlockSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface, IOOptionBits* swapFlags);
static IOReturn ceSwapSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface, IOOptionBits* swapFlags);
static IOReturn ceSetDestination(void* myInstance, IOOptionBits options, IOBlitSurface* surface);
static IOReturn ceGetBlitter(void* myInstance, IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitterPtr* blitter);
static IOReturn ceWaitComplete(void* myInstance, IOOptionBits options);
static IOReturn ceWaitSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface);
static IOReturn ceSetSurface(void* myInstance, IOOptionBits options, IOBlitSurface* surface);
/*
 * Blitters
 */
static IOReturn ceCopy(void* myInstance, IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitOperation* operation, void* source);
static IOReturn ceFill(void* myInstance, IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitOperation* operation, void* source);
static IOReturn ceCopyRegion(void* myInstance, IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitOperation* operation, void* source);
static IOReturn ceMemCopy(void* myInstance, IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitOperation* operation, void* source);
static IOReturn ceMemCopyRegion(void* myInstance, IOOptionBits options, IOBlitType type, IOBlitSourceType sourceType, IOBlitOperation* operation, void* source);

#ifdef __cplusplus
}
#endif

#endif /* __CESVGA2GA_H__ */
