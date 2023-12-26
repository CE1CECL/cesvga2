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

#include "CEsvga2Client.h"
#include "CEsvga2.h"
#include "VLog.h"

#define super IOUserClient
OSDefineMetaClassAndStructors(CEsvga2Client, IOUserClient);

#if LOGGING_LEVEL >= 1
#define LogPrintf(log_level, ...) do { if (log_level <= logLevelFB) VLog("IOFBClient: ", ##__VA_ARGS__); } while (false)
#else
#define LogPrintf(log_level, ...)
#endif

static IOExternalMethod const iofbFuncsCache[1] =
{
	{0, reinterpret_cast<IOMethod>(&CEsvga2::CustomMode), kIOUCStructIStructO, sizeof(CustomModeData), sizeof(CustomModeData)}
};

IOExternalMethod* CEsvga2Client::getTargetAndMethodForIndex(IOService** targetP, UInt32 index)
{
	LogPrintf(2, "%s: index=%u.\n", __FUNCTION__, static_cast<unsigned>(index));
	if (!targetP)
		return 0;
	if (index != 0 && index != 3) {
		LogPrintf(1, "%s: Invalid index %u.\n",
				  __FUNCTION__, static_cast<unsigned>(index));
		return 0;
	}
	*targetP = getProvider();
	return const_cast<IOExternalMethod*>(&iofbFuncsCache[0]);
}

IOReturn CEsvga2Client::clientClose()
{
	LogPrintf(2, "%s()\n", __FUNCTION__);
	if (!terminate())
		LogPrintf(1, "%s: terminate failed.\n", __FUNCTION__);
	return kIOReturnSuccess;
}

bool CEsvga2Client::initWithTask(task_t owningTask, void* securityToken, UInt32 type)
{
	if (!super::initWithTask(owningTask, securityToken, type) ||
		clientHasPrivilege(securityToken, kIOClientPrivilegeAdministrator) != kIOReturnSuccess)
		return false;
	return true;
}
