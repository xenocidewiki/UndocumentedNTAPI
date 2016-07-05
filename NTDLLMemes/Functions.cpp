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
		delete[] buffer;
		return FALSE;
	}
	else
		return TRUE;
}

bool NTDLL::bufferAlloc(size_t SIZE)
{
	buffer = new PVOID[SIZE];
	if (!buffer) {
		std::cout << "Buffer allocation failed";
		delete[] buffer;
		return FALSE;
	}
	else
		return TRUE;
}

NTSTATUS NTDLL::GetProcessList() 
{
	if (!bufferAlloc(bufferSize))
		return STATUS_UNSUCCESSFUL;
		
	pSystemInfo = reinterpret_cast<PSYSTEM_PINFO>(buffer);
	status = NtQuerySystemInformation(SystemProcessInformation, pSystemInfo, bufferSize, NULL);

	if (!NTSUCCESS(status))
		return STATUS_UNSUCCESSFUL;

	std::cout << "Process List - by xenocidewiki" << std::endl << std::endl;

	do {
		printf("Process name: %ws\t | pID: %d\n", pSystemInfo->ImageName.Buffer, pSystemInfo->ProcessId);
		pSystemInfo = reinterpret_cast<PSYSTEM_PINFO>((reinterpret_cast<BYTE*>(pSystemInfo) + pSystemInfo->NextEntryOffset));
	} while (pSystemInfo->NextEntryOffset);

	delete[] buffer;
	std::cin.get();

	return STATUS_SUCCESS;
}

NTSTATUS NTDLL::EnumerateDrivers()
{
	if (!bufferAlloc(bufferSize))
		return STATUS_UNSUCCESSFUL;

	pProcessModules = reinterpret_cast<PRTL_PROCESS_MODULES>(buffer);
	status = NtQuerySystemInformation(SystemModuleInformation, pProcessModules, bufferSize, NULL); //NOTE: I manually edited winternl.h because I'm lazy. There are many other (better) ways of getting the SystemModuleInformation defined and working without having to modify things like winternl.h
	
	if (!NTSUCCESS(status))
		return STATUS_UNSUCCESSFUL;

	std::cout << "Driver List - by xenocidewiki" << std::endl << std::endl;

	for (ULONG i = 0; i < pProcessModules->NumberOfModules; i++) {
		printf("%d:\t%s\n", i, pProcessModules->Modules[i].FullPathName + pProcessModules->Modules[i].OffsetToFileName);
	}

	delete[] buffer;
	std::cin.get();

	return STATUS_SUCCESS;
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

	std::cin.get();
}