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

#ifndef __CESVGA2DVDCONTEXT_H__
#define __CESVGA2DVDCONTEXT_H__

#include <IOKit/IOUserClient.h>

class CEsvga2DVDContext: public IOUserClient
{
	OSDeclareDefaultStructors(CEsvga2DVDContext);

private:
	task_t m_owning_task;
	class CEsvga2Accel* m_provider;
	int m_log_level;

public:
	/*
	 * Methods overridden from superclass
	 */
	IOExternalMethod* getTargetAndMethodForIndex(IOService** targetP, UInt32 index);
	IOReturn clientClose();
	IOReturn clientMemoryForType(UInt32 type, IOOptionBits* options, IOMemoryDescriptor** memory);
	IOReturn connectClient(IOUserClient* client);
	bool start(IOService* provider);
	bool initWithTask(task_t owningTask, void* securityToken, UInt32 type);
	static CEsvga2DVDContext* withTask(task_t owningTask, void* securityToken, uint32_t type);

	/*
	 * TBD: Methods from IONVDVDContext
	 */

	/*
	 * TBD: Methods from NVDVDContext
	 */
};

#endif /* __CESVGA2DVDCONTEXT_H__ */
