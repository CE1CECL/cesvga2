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

#ifndef _CESVGA2CLIENT_H_
#define _CESVGA2CLIENT_H_

#include <IOKit/IOUserClient.h>

class CEsvga2Client: public IOUserClient
{
	OSDeclareDefaultStructors(CEsvga2Client);

public:
	IOExternalMethod* getTargetAndMethodForIndex(IOService** targetP, UInt32 index);
	IOReturn clientClose();
	bool initWithTask(task_t owningTask, void* securityToken, UInt32 type);
};

#endif /* _CESVGA2CLIENT_H_ */
