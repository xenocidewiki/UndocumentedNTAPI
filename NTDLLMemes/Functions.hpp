#ifndef NTDLLMEMES_FUNCTIONS_H
#define NTDLLMEMES_FUNCTIONS_H
#include "structures.hpp"

class NTDLL {
	public:
		NTDLL();
		~NTDLL();

		NTSTATUS GetProcessList();
		NTSTATUS EnumerateDrivers();
		void init();

	private:
		bool NTSUCCESS(NTSTATUS successStatus);
		bool bufferAlloc(size_t SIZE);

		const int bufferSize		= 1024 * 1024;

		PVOID					buffer;
		NTSTATUS					status;
		PSYSTEM_PINFO			pSystemInfo;
		PRTL_PROCESS_MODULES		pProcessModules;
};

#endif