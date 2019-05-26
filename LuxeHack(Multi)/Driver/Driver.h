#pragma once
#include "Utilit.h"
#include <string>
#include <winternl.h>
#include "Define.h"
#include "ShellCode.h"

typedef void (NTAPI* RtlInitUnicodeStringFn)(PUNICODE_STRING, PCWSTR);
typedef NTSTATUS(NTAPI* NtLoadDriverFn)(IN PUNICODE_STRING);
typedef NTSTATUS(NTAPI* NtUnloadDriverFn)(IN PUNICODE_STRING);

class cDriver
{
public:
	cDriver();
	~cDriver();
	static cDriver& Singleton();

	NTSTATUS Loaded();
	NTSTATUS Reload(std::wstring path);
	NTSTATUS Unload();

	std::wstring GetDriverPath();
	BOOLEAN  DropDriver();
	VOID     DeleteDriver();
	NTSTATUS JackR(DWORD pid, uint64_t base, uint64_t size, PVOID buffer);
	NTSTATUS JackW(DWORD pid, uint64_t base, uint64_t size, PVOID buffer);
	NTSTATUS UnlinkHandleTable(DWORD pid);
	NTSTATUS UnlinkProcessTable(DWORD pid);
	DWORD64  GetMainModuleById(DWORD pid);

	inline bool     IsLoaded()  const { return hDriver != INVALID_HANDLE_VALUE; }
	inline NTSTATUS GetStatus() const { return loadStatus; }
private:
	LSTATUS  PrepareDriverRegEntry(const std::wstring& svcName, const std::wstring& path);
	NTSTATUS LoadDriver(const std::wstring& svcName, const std::wstring& path);
	NTSTATUS UnloadDriver(const std::wstring& svcName);
private:
	cDriver(const cDriver&) = delete;
	cDriver& operator = (const cDriver&) = delete;

	HANDLE   hDriver = INVALID_HANDLE_VALUE;
	NTSTATUS loadStatus = STATUS_NOT_FOUND;

	RtlInitUnicodeStringFn pRtlInitUnicodeString = nullptr;
	NtLoadDriverFn pNtLoadDriver = nullptr;
	NtUnloadDriverFn pNtUnloadDriver = nullptr;

};

inline cDriver& Driver() {
	return cDriver::Singleton();
}



