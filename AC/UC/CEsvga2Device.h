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

#ifndef __CESVGA2DEVICE_H__
#define __CESVGA2DEVICE_H__

#include <IOKit/IOUserClient.h>

class CEsvga2Device: public IOUserClient
{
	OSDeclareDefaultStructors(CEsvga2Device);

private:
	task_t m_owning_task;
	class CEsvga2Accel* m_provider;	// offset 0x84
	int m_log_level;

	class CEsvga2Shared* m_shared;	// offset 0x7C
	class IOMemoryMap* m_channel_memory_map;

	void Cleanup();

public:
	/*
	 * Methods overridden from superclass
	 */
	IOExternalMethod* getTargetAndMethodForIndex(IOService** targetP, UInt32 index);
	IOReturn clientClose();
	IOReturn clientMemoryForType(UInt32 type, IOOptionBits* options, IOMemoryDescriptor** memory);
#if 1
	IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments* arguments, IOExternalMethodDispatch* dispatch = 0, OSObject* target = 0, void* reference = 0);
#endif
	bool start(IOService* provider);
	bool initWithTask(task_t owningTask, void* securityToken, UInt32 type);
	static CEsvga2Device* withTask(task_t owningTask, void* securityToken, uint32_t type);

	/*
	 * Interface for CEsvga2GLContext
	 */
	task_t getOwningTask() const { return m_owning_task; }
	class CEsvga2Shared* getShared() const { return m_shared; }

	/*
	 * Methods from IONVDevice
	 */
	IOReturn create_shared();
	IOReturn get_config(uint32_t*, uint32_t*, uint32_t*, uint32_t*, uint32_t*);
	IOReturn get_surface_info(uintptr_t, uint32_t*, uint32_t*, uint32_t*);
	IOReturn get_name(char*, size_t*);
	IOReturn wait_for_stamp(uintptr_t);
	IOReturn new_texture(struct VendorNewTextureDataStruc const*,
						 struct sIONewTextureReturnData*,
						 size_t,
						 size_t*);
	IOReturn delete_texture(uintptr_t);
	IOReturn page_off_texture(struct sIODevicePageoffTexture const*, size_t);
	IOReturn get_channel_memory(struct sIODeviceChannelMemoryData*, size_t*);

	/*
	 * NVDevice Methods
	 */
	IOReturn kernel_printf(char const*, size_t);
	IOReturn nv_rm_config_get(uint32_t const*, uint32_t*, size_t, size_t*);
	IOReturn nv_rm_config_get_ex(uint32_t const*, uint32_t*, size_t, size_t*);
	IOReturn nv_rm_control(uint32_t const*, uint32_t*, size_t, size_t*);
};

#endif /* __CESVGA2DEVICE_H__ */
