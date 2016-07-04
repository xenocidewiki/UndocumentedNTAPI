#include "Functions.hpp"

NTDLL::NTDLL() 
{
}

NTDLL::~NTDLL()
{
}

bool NTDLL::NTSUCCESS(NTSTATUS successStatus)
{
	if (!NT_SUCCESS(successStatus)) {
		std::cout << "NT_SUCCESS failed";
		free(buffer);
		return FALSE;
	}
	else
		return TRUE;
}

bool NTDLL::bufferAlloc(size_t SIZE)
{
	buffer = malloc(SIZE);
	if (!buffer) {
		std::cout << "Buffer allocation failed";
		free(buffer);
		return FALSE;
	}
	else
		return TRUE;
}

int NTDLL::GetProcessList() 
{
	if (!bufferAlloc(bufferSize))
		return 0;
		
	pSystemInfo = (PSYSTEM_PINFO)buffer;
	status = NtQuerySystemInformation(SystemProcessInformation, pSystemInfo, bufferSize, NULL);

	if (!NTSUCCESS(status))
		return 0;

	std::cout << "Process List - by xenocidewiki" << std::endl << std::endl;

	do {
		printf("Process name: %ws | pID: %d\n", pSystemInfo->ImageName.Buffer, pSystemInfo->ProcessId);
		pSystemInfo = (PSYSTEM_PINFO)((BYTE*)pSystemInfo + pSystemInfo->NextEntryOffset);
	} while (pSystemInfo->NextEntryOffset);

	free(buffer);
	getchar();
	return 0;
}

int NTDLL::EnumerateDrivers()
{
	if (!bufferAlloc(bufferSize))
		return 0;

	pProcessModules = (PRTL_PROCESS_MODULES)buffer;
	status = NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)(11), pProcessModules, bufferSize, NULL);
	
	if (!NTSUCCESS(status))
		return 0;

	std::cout << "Driver List - by xenocidewiki" << std::endl << std::endl;

	for (ULONG i = 0; i < pProcessModules->NumberOfModules; i++) {
		printf("%d:\t%s\n", i, pProcessModules->Modules[i].FullPathName + pProcessModules->Modules[i].OffsetToFileName);
	}

	free(buffer);
	getchar();
	return 0;
}

void NTDLL::init() 
{
	int input;

	std::cout << "Welcome to NTDLL memes - by xenocidewiki\nPlease pick one of the following:\n1. Get Process List\n2. Get Driver List" << std::endl;
	std::cin >> input;

	switch (input) {
	case 1:
		GetProcessList();
		break;
	case 2:
		EnumerateDrivers();
		break;
	default:
		std::cout << "No choice availble with that number, please restart and try again";
		break;
	}
	getchar();
}