#ifndef NTDLLMEMES_FUNCTIONS_H
#define NTDLLMEMES_FUNCTIONS_H

#include "structures.hpp"

class NTDLL {
	public:
		NTDLL();
		~NTDLL();

		int GetProcessList();
		int EnumerateDrivers();
		void init();

	private:
		int NTSUCCESS(NTSTATUS successStatus);
		int bufferAlloc(size_t SIZE);

		const int bufferSize		= 1024 * 1024;

		PVOID				buffer;
		NTSTATUS			status;
		PSYSTEM_PINFO			pSystemInfo;
		PRTL_PROCESS_MODULES		pProcessModules;
};

#endif
