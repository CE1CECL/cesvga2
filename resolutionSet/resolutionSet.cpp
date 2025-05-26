/*

    CEsvga2 - ChrisEric1 Super Video Graphics Array 2
    Copyright (C) 2023-2025, Christopher Eric Lentocha

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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <IOKit/IOKitLib.h>

struct Provider {
	io_service_t service;
	int clientIndex;
	int methodIndex;
};

static inline io_service_t tryFindService(char const* serviceName) {
	return IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching(serviceName));
};

static kern_return_t getProvider(struct Provider* pProvider) {
	int gfx, count;
	io_service_t svc;

	if (!pProvider) {
		return 1;
	};
	for (gfx = 0, count = 0; count < 60; ++count) {
		svc = tryFindService("CEsvga2");
		if (!svc) {
			svc = tryFindService("CECLGfx");
			if (!svc) {
				sleep(1);
				continue;
			};
			gfx = 1;
		};
		pProvider->service = svc;
		pProvider->clientIndex = gfx ? 0 : 2;
		pProvider->methodIndex = gfx ? 0 : 3;
		return 0;
	};
	return 1;
};

int main(int argc, char *argv[]) {
	printf("\n    CEsvga2 - ChrisEric1 Super Video Graphics Array 2\n    Copyright (C) 2023-2025, Christopher Eric Lentocha\n\n    This program is free software: you can redistribute it and/or modify\n    it under the terms of the GNU Affero General Public License as published\n    by the Free Software Foundation, either version 3 of the License, or\n    (at your option) any later version.\n\n    This program is distributed in the hope that it will be useful,\n    but WITHOUT ANY WARRANTY; without even the implied warranty of\n    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n    GNU Affero General Public License for more details.\n\n    You should have received a copy of the GNU Affero General Public License\n    along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n");
	if (argc != 3) {
		printf(" Usage: \n\t %s 1024 768 \n\t\t Where %s is the app name that was executed \n\t\t Where 1024 is the custom width to set to \n\t\t Where 768 is the custom height to set to \n", argv[0], argv[0]);
		return 1;
	};
	struct Provider provider;
	kern_return_t krt;
	io_connect_t connect;
	size_t outputStructCount;
	typedef struct _ResolutionInfoOSXType {
		unsigned flags;
		unsigned w;
		unsigned h;
	} ResolutionInfoOSXType;
	ResolutionInfoOSXType inputStruct, outputStruct;
	printf("Requested W * H -> %u x %u\n", atoi(argv[1]), atoi(argv[2]));
	krt = getProvider(&provider);
	if (krt != 0) {
		printf("Unable to find the service\n");
		return 1;
	};
	krt = IOServiceOpen(provider.service, mach_task_self(), provider.clientIndex, &connect);
	IOObjectRelease(provider.service);
	if (krt != 0) {
		printf("Unable to open the service, error %#x\n", krt);
		return 1;
	};
	outputStructCount = sizeof outputStruct;
	inputStruct.flags = 1;
	inputStruct.w = atoi(argv[1]);
	inputStruct.h = atoi(argv[2]);
	krt = IOConnectCallStructMethod((mach_port_t)(uintptr_t)connect, provider.methodIndex, &inputStruct, sizeof inputStruct, &outputStruct, &outputStructCount);
	// krt = IOConnectMethodStructureIStructureO(connect, provider.methodIndex, sizeof inputStruct, &outputStructCount, &inputStruct, &outputStruct);
	IOServiceClose(connect);
	if (krt != 0) {
		printf("Unable to issue the ioctl, error %#x\n", krt);
		return 1;
	};
	printf("Now Set W * H -> %u x %u\n", outputStruct.w, outputStruct.h);
	return 0;
}
