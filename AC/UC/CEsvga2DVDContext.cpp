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

#include <IOKit/IOLib.h>
#include "VLog.h"
#include "CEsvga2Accel.h"
#include "CEsvga2DVDContext.h"
#include "UCMethods.h"

#define CLASS CEsvga2DVDContext
#define super IOUserClient
OSDefineMetaClassAndStructors(CEsvga2DVDContext, IOUserClient);

#if LOGGING_LEVEL >= 1
#define DVDLog(log_level, ...) do { if (log_level <= m_log_level) VLog("IODVD: ", ##__VA_ARGS__); } while (false)
#else
#define DVDLog(log_level, ...)
#endif

static
IOExternalMethod const iofbFuncsCache[kIOCEDVDNumMethods] =
{
// TBD: IONVDVDContext
// TBD: NVDVDContext
};

#pragma mark -
#pragma mark IOUserClient Methods
#pragma mark -

IOExternalMethod* CLASS::getTargetAndMethodForIndex(IOService** targetP, UInt32 index)
{
	DVDLog(1, "%s(target_out, %u)\n", __FUNCTION__, static_cast<unsigned>(index));
	if (!targetP || index >= kIOCEDVDNumMethods)
		return 0;
#if 1
	if (index >= kIOCEDVDNumMethods) {
		if (m_provider)
			*targetP = m_provider;
		else
			return 0;
	} else
		*targetP = this;
#else
	*targetP = this;
#endif
	return const_cast<IOExternalMethod*>(&iofbFuncsCache[index]);
}

IOReturn CLASS::clientClose()
{
	DVDLog(2, "%s\n", __FUNCTION__);
	if (!terminate(0))
		IOLog("%s: terminate failed\n", __FUNCTION__);
	m_owning_task = 0;
	m_provider = 0;
	return kIOReturnSuccess;
}

IOReturn CLASS::clientMemoryForType(UInt32 type, IOOptionBits* options, IOMemoryDescriptor** memory)
{
	DVDLog(1, "%s(%u, options_out, memory_out)\n", __FUNCTION__, static_cast<unsigned>(type));
	return super::clientMemoryForType(type, options, memory);
}

IOReturn CLASS::connectClient(IOUserClient* client)
{
	DVDLog(1, "%s(%p), name == %s\n", __FUNCTION__, client, client ? client->getName() : "NULL");
	return super::connectClient(client);
}

bool CLASS::start(IOService* provider)
{
	m_provider = OSDynamicCast(CEsvga2Accel, provider);
	if (!m_provider)
		return false;
	m_log_level = m_provider->getLogLevelAC();
	return super::start(provider);
}

bool CLASS::initWithTask(task_t owningTask, void* securityToken, UInt32 type)
{
	m_log_level = LOGGING_LEVEL;
	if (!super::initWithTask(owningTask, securityToken, type))
		return false;
	m_owning_task = owningTask;
	return true;
}

__attribute__((visibility("hidden")))
CLASS* CLASS::withTask(task_t owningTask, void* securityToken, uint32_t type)
{
	CLASS* inst;

	inst = new CLASS;

	if (inst && !inst->initWithTask(owningTask, securityToken, type))
	{
		inst->release();
		inst = 0;
	}

	return (inst);
}

#pragma mark -
#pragma mark IONVDVDContext Methods
#pragma mark -

#pragma mark -
#pragma mark NVDVDContext Methods
#pragma mark -
