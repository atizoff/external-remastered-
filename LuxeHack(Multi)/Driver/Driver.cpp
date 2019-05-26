#include "Driver.h"
#include "..\Protect\XorStr.h"

std::wstring DriverName = XorStringW(L"frost_64.sys");
std::wstring OutputPath = XorStringW(L"\\SoftwareDistribution\\Download\\");
std::wstring ServiceName = XorStringW(L"SYKUO");
std::wstring DeviceFile = XorStringW(L"\\\\.\\") + ServiceName;

cDriver::cDriver()
{
	IUtilit::SetPriviledge(XorStringW(L"SeDebugPrivilege"));
	IUtilit::SetPriviledge(XorStringW(L"SeLoadDriverPrivilege"));
	HMODULE ntdll = GetModuleHandleW(XorStringW(L"ntdll.dll"));
	pNtLoadDriver = (NtLoadDriverFn)GetProcAddress(ntdll, XorString("NtLoadDriver"));
	pNtUnloadDriver = (NtUnloadDriverFn)GetProcAddress(ntdll, XorString("NtUnloadDriver"));
	pRtlInitUnicodeString = (RtlInitUnicodeStringFn)GetProcAddress(ntdll, XorString("RtlInitUnicodeString"));
}
std::wstring cDriver::GetDriverPath()
{
	std::wstring path;
	if (path.empty())
	{
		WCHAR WinSysDir[256];
		GetWindowsDirectoryW(WinSysDir, 256);
		path = (std::wstring(WinSysDir) + OutputPath + DriverName);
	}
	return path;
}
BOOLEAN cDriver::DropDriver()
{
	HANDLE hFile;
	BOOLEAN bStatus = FALSE;
	DWORD NumberOfBytesWritten = 0;
	std::wstring path;
	WCHAR WinSysDir[256];
	GetWindowsDirectoryW(WinSysDir, 256);
	path = GetDriverPath();
	hFile = CreateFileW(path.c_str(), GENERIC_ALL, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_EXISTS)
		return true;

	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	bStatus = WriteFile(hFile, ShellCode, sizeof(ShellCode), &NumberOfBytesWritten, nullptr);
	CloseHandle(hFile);
	if (!bStatus)
		return false;

	return true;
}
VOID cDriver::DeleteDriver()
{
	DeleteFileW(GetDriverPath().c_str());
}
NTSTATUS cDriver::JackR(DWORD pid, uint64_t base, uint64_t size, PVOID buffer)
{
	DWORD bytes = 0;
	COPY_JACK pJack = { 0 };
	pJack.pJackId = pid;
	pJack.pJackAddress = base;
	pJack.pJackBuffer = (ULONGLONG)buffer;
	pJack.iJackSize = size;

	if (hDriver == INVALID_HANDLE_VALUE)
		return STATUS_DEVICE_DOES_NOT_EXIST;

	if (!DeviceIoControl(hDriver, IOCTL_JACK_R, &pJack, sizeof(pJack), nullptr, 0, &bytes, NULL))
		return LastNtStatus();
	return STATUS_SUCCESS;
}
NTSTATUS cDriver::JackW(DWORD pid, uint64_t base, uint64_t size, PVOID buffer)
{
	DWORD bytes = 0;
	COPY_JACK pJack = { 0 };
	pJack.pJackId = pid;
	pJack.pJackAddress = base;
	pJack.pJackBuffer = (ULONGLONG)buffer;
	pJack.iJackSize = size;

	if (hDriver == INVALID_HANDLE_VALUE)
		return STATUS_DEVICE_DOES_NOT_EXIST;

	if (!DeviceIoControl(hDriver, IOCTL_JACK_W, &pJack, sizeof(pJack), nullptr, 0, &bytes, NULL))
		return LastNtStatus();
	return STATUS_SUCCESS;
}
NTSTATUS cDriver::UnlinkHandleTable(DWORD pid)
{
	if (hDriver == INVALID_HANDLE_VALUE)
		return STATUS_DEVICE_DOES_NOT_EXIST;

	DWORD bytes = 0;
	JACK_UNLINK hideTable = { 0 };
	hideTable.pJackId = pid;

	if (!DeviceIoControl(hDriver, IOCTL_JACK_U, &hideTable, sizeof(hideTable), nullptr, 0, &bytes, NULL))
		return LastNtStatus();
	return STATUS_SUCCESS;
}
NTSTATUS cDriver::UnlinkProcessTable(DWORD pid)
{
	if (hDriver == INVALID_HANDLE_VALUE)
		return STATUS_DEVICE_DOES_NOT_EXIST;

	DWORD bytes = 0;
	JACK_UNLINK_PROCESS hideTable = { 0 };
	hideTable.pJackId = pid;

	if (!DeviceIoControl(hDriver, IOCTL_JACK_P, &hideTable, sizeof(hideTable), nullptr, 0, &bytes, NULL))
		return LastNtStatus();
	return STATUS_SUCCESS;
}
DWORD64 cDriver::GetMainModuleById(DWORD pid)
{
	DWORD64 Buffer;
	if (hDriver == INVALID_HANDLE_VALUE)
		return STATUS_DEVICE_DOES_NOT_EXIST;

	if (DeviceIoControl(hDriver, IOCTL_GET_M, &pid, sizeof(pid), &Buffer, sizeof(Buffer), 0, 0))
		return Buffer;
	else
		return false;
}
NTSTATUS cDriver::Loaded()
{
	if (hDriver != INVALID_HANDLE_VALUE)
		return STATUS_SUCCESS;

	hDriver = CreateFileW(DeviceFile.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDriver != INVALID_HANDLE_VALUE)
		return loadStatus = STATUS_SUCCESS;

	return Reload(GetDriverPath());
}
NTSTATUS cDriver::Reload(std::wstring path)
{
	NTSTATUS status = STATUS_SUCCESS;

	Unload();
	status = loadStatus = LoadDriver(ServiceName.c_str(), path);
	if (!NT_SUCCESS(status))
	{
		return LastNtStatus(status);
	}

	hDriver = CreateFileW(DeviceFile.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (hDriver == INVALID_HANDLE_VALUE)
	{
		status = LastNtStatus();
		return status;
	}
	return status;
}
NTSTATUS cDriver::LoadDriver(const std::wstring & svcName, const std::wstring & path)
{
	UNICODE_STRING Ustr;

	if (!path.empty() && PrepareDriverRegEntry(svcName, path) != 0)
		return LastNtStatus();

	std::wstring regPath = XorStringW(L"\\registry\\machine\\SYSTEM\\CurrentControlSet\\Services\\") + svcName;
	pRtlInitUnicodeString(&Ustr, regPath.c_str());

	return pNtLoadDriver(&Ustr);
}
NTSTATUS cDriver::UnloadDriver(const std::wstring & svcName)
{
	UNICODE_STRING Ustr = { 0 };

	std::wstring regPath = XorStringW(L"\\registry\\machine\\SYSTEM\\CurrentControlSet\\Services\\") + svcName;
	pRtlInitUnicodeString(&Ustr, regPath.c_str());

	NTSTATUS status = pNtUnloadDriver(&Ustr);
	RegDeleteTreeW(HKEY_LOCAL_MACHINE, (XorStringW(L"SYSTEM\\CurrentControlSet\\Services\\") + svcName).c_str());
	return status;
}
LSTATUS  cDriver::PrepareDriverRegEntry(const std::wstring & svcName, const std::wstring & path)
{
	HKEY key1,
		key2;
	DWORD dwType = 1;
	LSTATUS status = 0;
	WCHAR wszLocalPath[MAX_PATH] = { 0 };

	swprintf_s(wszLocalPath, MAX_PATH, XorStringW(L"\\??\\%s"), path.c_str());

	status = RegOpenKeyW(HKEY_LOCAL_MACHINE, XorStringW(L"system\\CurrentControlSet\\Services"), &key1);
	if (status)
		return status;

	status = RegCreateKeyW(key1, svcName.c_str(), &key2);
	if (status)
	{
		RegCloseKey(key1);
		return status;
	}

	status = RegSetValueExW(key2, XorStringW(L"ImagePath"), 0, REG_SZ, reinterpret_cast<const BYTE*>(wszLocalPath), static_cast<DWORD>(sizeof(WCHAR) * (wcslen(wszLocalPath) + 1)));

	if (status)
	{
		RegCloseKey(key2);
		RegCloseKey(key1);
		return status;
	}

	status = RegSetValueExW(key2, XorStringW(L"Type"), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&dwType), sizeof(dwType));
	if (status)
	{
		RegCloseKey(key2);
		RegCloseKey(key1);
		return status;
	}

	RegCloseKey(key2);
	RegCloseKey(key1);

	return status;
}
NTSTATUS cDriver::Unload()
{
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDriver);
		hDriver = INVALID_HANDLE_VALUE;
	}
	return UnloadDriver(ServiceName);
}
cDriver::~cDriver()
{
	Unload();
}
cDriver& cDriver::Singleton()
{
	static cDriver pObject;
	return pObject;
}