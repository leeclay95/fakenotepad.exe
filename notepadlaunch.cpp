#include <windows.h>
#include <iostream>

int main()
{
    // Structure to receive process startup info
    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    // Structure to receive process information
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // Command line to execute
    // Note: CreateProcessA requires a mutable buffer for the command line
    char cmd[] = "notepad.exe";

    // Create the process
    BOOL success = CreateProcessA(
        nullptr,   // lpApplicationName: use command line only
        cmd,       // lpCommandLine: our mutable command string
        nullptr,   // lpProcessAttributes: default security
        nullptr,   // lpThreadAttributes: default security
        FALSE,     // bInheritHandles: no handle inheritance
        0,         // dwCreationFlags: default options
        nullptr,   // lpEnvironment: use parent environment
        nullptr,   // lpCurrentDirectory: use parent working dir
        &si,       // pointer to STARTUPINFO
        &pi        // pointer to PROCESS_INFORMATION
    );

    if (!success)
    {
        std::cerr << "CreateProcess failed (" << GetLastError() << ")\n";
        return 1;
    }

    std::cout << "Launched Notepad (PID = " << pi.dwProcessId << ")\n";

    // Optionally, wait for the process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
