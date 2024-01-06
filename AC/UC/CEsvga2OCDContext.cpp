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
#include "Vlog.h"
#include "UCGLDCommonTypes.h"
#include "UCMethods.h"
#include "CEsvga2Accel.h"
#include "CEsvga2OCDContext.h"

#define CLASS CEsvga2OCDContext
#define super IOUserClient
OSDefineMetaClassAndStructors(CEsvga2OCDContext, IOUserClient);

#if LOGGING_LEVEL >= 1
#define OCDLog(log_level, ...) do { if (log_level <= m_log_level) VLog("IOOCD: ", ##__VA_ARGS__); } while (false)
#else
#define OCDLog(log_level, ...)
#endif

static
IOExternalMethod const iofbFuncsCache[kIOCEOCDNumMethods] =
{
// IONVOCDContext
	{0, reinterpret_cast<IOMethod>(&CLASS::finish), kIOUCScalarIScalarO, 0, 0},
	{0, reinterpret_cast<IOMethod>(&CLASS::wait_for_stamp), kIOUCScalarIScalarO, 1, 0},
// NVOCDContext
	{0, reinterpret_cast<IOMethod>(&CLASS::check_error_notifier), kIOUCScalarIStructO, 0, 16U},
	{0, reinterpret_cast<IOMethod>(&CLASS::mark_texture_for_ocd_use), kIOUCScalarIScalarO, 1, 0},
	{0, reinterpret_cast<IOMethod>(&CLASS::FreeEvent), kIOUCScalarIScalarO, 0, 0},
	{0, reinterpret_cast<IOMethod>(&CLASS::GetHandleIndex), kIOUCScalarIScalarO, 0, 2},
};

#pragma mark -
#pragma mark IOUserClient Methods
#pragma mark -

IOExternalMethod* CLASS::getTargetAndMethodForIndex(IOService** targetP, UInt32 index)
{
	if (index >= kIOCEOCDNumMethods)
		OCDLog(1, "%s(target_out, %u)\n", __FUNCTION__, static_cast<unsigned>(index));
	if (!targetP || index >= kIOCEOCDNumMethods)
		return 0;
#if 1
	if (index >= kIOCEOCDNumMethods) {
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
	OCDLog(2, "%s\n", __FUNCTION__);
	if (!terminate(0))
		IOLog("%s: terminate failed\n", __FUNCTION__);
	m_owning_task = 0;
	m_provider = 0;
	return kIOReturnSuccess;
}

IOReturn CLASS::clientMemoryForType(UInt32 type, IOOptionBits* options, IOMemoryDescriptor** memory)
{
	OCDLog(1, "%s(%u, options_out, memory_out)\n", __FUNCTION__, static_cast<unsigned>(type));
	return super::clientMemoryForType(type, options, memory);
}

IOReturn CLASS::connectClient(IOUserClient* client)
{
	OCDLog(1, "%s(%p), name == %s\n", __FUNCTION__, client, client ? client->getName() : "NULL");
	return super::connectClient(client);
}

IOReturn CLASS::registerNotificationPort(mach_port_t port, UInt32 type, UInt32 refCon)
{
	OCDLog(1, "%s(%p, %u, %u)\n", __FUNCTION__, port, static_cast<unsigned>(type), static_cast<unsigned>(refCon));
	return super::registerNotificationPort(port, type, refCon);
}

bool CLASS::start(IOService* provider)
{
	m_provider = OSDynamicCast(CEsvga2Accel, provider);
	if (!m_provider)
		return false;
	m_log_level = imax(m_provider->getLogLevelGLD(), m_provider->getLogLevelAC());
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
#pragma mark IONVOCDContext Methods
#pragma mark -

__attribute__((visibility("hidden")))
IOReturn CLASS::finish()
{
	OCDLog(2, "%s()\n", __FUNCTION__);
	return kIOReturnUnsupported;
}

__attribute__((visibility("hidden")))
IOReturn CLASS::wait_for_stamp(uintptr_t c1)
{
	OCDLog(2, "%s(%lu)\n", __FUNCTION__, c1);
	return kIOReturnUnsupported;
}

#pragma mark -
#pragma mark NVOCDContext Methods
#pragma mark -

__attribute__((visibility("hidden")))
IOReturn CLASS::check_error_notifier(struct NvNotificationRec volatile* struct_out, size_t* struct_out_size)
{
	OCDLog(2, "%s(struct_out, %lu)\n", __FUNCTION__, *struct_out_size);
	if (*struct_out_size < sizeof *struct_out)
		return kIOReturnBadArgument;
	return kIOReturnUnsupported;
}

__attribute__((visibility("hidden")))
IOReturn CLASS::mark_texture_for_ocd_use(uintptr_t c1)
{
	OCDLog(2, "%s(%lu)\n", __FUNCTION__, c1);
	return kIOReturnUnsupported;
}

__attribute__((visibility("hidden")))
IOReturn CLASS::FreeEvent()
{
	OCDLog(2, "%s()\n", __FUNCTION__);
	return kIOReturnUnsupported;
}

__attribute__((visibility("hidden")))
IOReturn CLASS::GetHandleIndex(uint32_t*, uint32_t*)
{
	OCDLog(2, "%s(out1, out2)\n", __FUNCTION__);
	return kIOReturnUnsupported;
}
