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

#include <IOKit/IOMemoryDescriptor.h>
#include "VendorTransferBuffer.h"
#include "CEsvga2Accel.h"

#define CLASS VendorTransferBuffer

#define HIDDEN __attribute__((visibility("hidden")))

#pragma mark -
#pragma mark Global Functions
#pragma mark -

static inline
bool isIdValid(uint32_t id)
{
	return static_cast<int>(id) >= 0;
}

#pragma mark -
#pragma mark Public Methods
#pragma mark -

HIDDEN
void CLASS::init(void)
{
	gmr_id = SVGA_ID_INVALID;
}

HIDDEN
IOReturn CLASS::prepare(CEsvga2Accel* provider)
{
	IOReturn rc;

	if (!provider)
		return kIOReturnNotReady;
	if (isIdValid(gmr_id))
		return kIOReturnSuccess;
	if (!md)
		return kIOReturnNotReady;
	gmr_id = provider->AllocGMRID();
	if (!isIdValid(gmr_id)) {
#if 0
		IOLog("%s: Out of GMR IDs\n", __FUNCTION__);
#endif
		return kIOReturnNoResources;
	}
	rc = md->prepare();
	if (rc != kIOReturnSuccess)
		goto clean1;
	rc = provider->createGMR(gmr_id, md);
	if (rc != kIOReturnSuccess)
		goto clean2;
	return kIOReturnSuccess;

clean2:
	md->complete();
clean1:
	provider->FreeGMRID(gmr_id);
	gmr_id = SVGA_ID_INVALID;
	return rc;
}

HIDDEN
void CLASS::sync(CEsvga2Accel* provider)
{
	if (!provider || !fence)
		return;
	provider->SyncToFence(fence);
	fence = 0U;
}

HIDDEN
void CLASS::complete(CEsvga2Accel* provider)
{
	sync(provider);
	if (!provider || !isIdValid(gmr_id))
		return;
	provider->destroyGMR(gmr_id);
	if (md)
		md->complete();
	provider->FreeGMRID(gmr_id);
	gmr_id = SVGA_ID_INVALID;
}

HIDDEN
void CLASS::discard(void)
{
	if (!md)
		return;
	md->release();
	md = 0;
}
