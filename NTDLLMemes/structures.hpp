#ifndef NTDLL_STRUCTURES_H
#define NTDLL_STRUCTURES_H

#include <iostream>
#include <windows.h>
#include <winternl.h>

#pragma comment (lib, "ntdll.lib") 

typedef struct _SYSTEM_PROCESS_INFO {

	ULONG                   NextEntryOffset;
	ULONG                   NumberOfThreads;
	LARGE_INTEGER           Reserved[3];
	LARGE_INTEGER           CreateTime;
	LARGE_INTEGER           UserTime;
	LARGE_INTEGER           KernelTime;
	UNICODE_STRING          ImageName;
	ULONG			BasePriority;
	HANDLE                  ProcessId;
	HANDLE                  InheritedFromProcessId;
	ULONG                   HandleCount;

} SYSTEM_PINFO, *PSYSTEM_PINFO;

typedef struct _SYSTEM_MOD {

	HANDLE			Section;
	PVOID			MappedBaseAddress;
	PVOID			ImageBaseAddress;
	ULONG			ImageSize;
	ULONG			Flags;
	USHORT			LoadOrderIndex;
	USHORT			InitOrderIndex;
	USHORT			LoadCount;
	USHORT			NameOffset;
	UCHAR			Name[256];

} SYSTEM_MOD, *PSYSTEM_MOD;

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	void *Section;
	void *MappedBase;
	void *ImageBase;
	unsigned int ImageSize;
	unsigned int Flags;
	unsigned __int16 LoadOrderIndex;
	unsigned __int16 InitOrderIndex;
	unsigned __int16 LoadCount;
	unsigned __int16 OffsetToFileName;
	char FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

#endif
