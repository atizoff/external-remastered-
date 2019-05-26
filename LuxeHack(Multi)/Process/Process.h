#pragma once
#include "Driver\Driver.h"
#include <tlhelp32.h>
#include <map>

DWORD getProcId(const char* ProcName) 
{
	PROCESSENTRY32   pe32;
	HANDLE         hSnapshot = NULL;
	DWORD dwProcId = 0;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hSnapshot, &pe32))
	{
		do {
			if (strcmp(pe32.szExeFile, ProcName) == 0)
			{
				dwProcId = pe32.th32ProcessID;
				break;
			}

		} while (Process32Next(hSnapshot, &pe32));
	}
	if (hSnapshot != INVALID_HANDLE_VALUE)
		CloseHandle(hSnapshot);
	return dwProcId;
}

DWORD IdProcess;
void SetProcessId(DWORD ProcId)
{
	IdProcess = ProcId;
}

bool find(const char* name)
{
	IdProcess = getProcId(name);
	return  (IdProcess != 0);
}

template <class cData>
cData Read(DWORD dwAddress)
{
	cData cRead;
	Driver().JackR(IdProcess, (uint64_t)dwAddress, sizeof(cData), &cRead);
	return cRead;
}

template <class cData>
VOID Write(DWORD dwAddress, cData write)
{
	Driver().JackW(IdProcess, (uint64_t)dwAddress, sizeof(cData), &write);
}

template <class cData>
cData ReadMem(SIZE_T dwAddress, DWORD bufSize)
{
	cData cRead;
	Driver().ReadMem(IdProcess, (uint64_t)dwAddress, bufSize, &cRead);
	return cRead;
}

template <class cData>
void WriteMem(DWORD dwAddress, cData write)
{
	Driver().WriteMem(IdProcess, (uint64_t)dwAddress, sizeof(cData), &write);
}

bool ReadMemory(DWORD lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize)
{
	if (!NT_SUCCESS(Driver().JackR(IdProcess, (uint64_t)lpBaseAddress, (uint64_t)nSize, (LPVOID)lpBuffer)))
		return false;

	return true;
}

bool WriteMemory(DWORD lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize)
{
	if (!NT_SUCCESS(Driver().JackW(IdProcess, (uint64_t)lpBaseAddress, (uint64_t)nSize, (LPVOID)lpBuffer)))
		return false;

	return true;
}

const char* ReadStringMemory(DWORD dwAddress)
{
	char buffer[1000];
	Driver().JackR(IdProcess, (uint64_t)dwAddress, sizeof(buffer), &buffer);
	return buffer;
}

const char* ReadStringMemoryPtr(DWORD dwAddress)
{
	if (DWORD v0 = Read<DWORD>(dwAddress)) return ReadStringMemory(v0);
	return NULL;
}

BOOL read(DWORD_PTR dwAddress, LPVOID lpBuffer, DWORD dwSize)
{
	return (Driver().JackR(IdProcess, dwAddress, dwSize, lpBuffer) == TRUE);
}


