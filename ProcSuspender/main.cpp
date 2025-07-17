/*
    This tool is useful for reversing, debugging, and other scenarios where you need to control process execution.
    Example use cases:
      * Suspending a process before it starts to inspect or modify its memory.
      * Injecting code or DLLs before the main thread runs.
      * Setting breakpoints or attaching a debugger before any code executes.
      * Analyzing process startup behavior in a controlled state.
      * Preventing anti-debug or anti-tamper routines from running immediately.
      * Pausing malware or suspicious binaries for safe analysis.
      * Automating process manipulation tasks that require suspension and resumption.
    
    <This is a basic tool, it doesn't have any fancy features.>
*/

#include <Windows.h>
#include <iostream>
#include <string>

/**
 * Terminates a process given its process ID.
 * @param targetPID The process ID of the target process.
 * @return true if the process was terminated successfully, false otherwise.
 */
bool terminateProcessById(DWORD targetPID) {
    HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, targetPID);
    if (!processHandle) {
        return false;
    }
    bool terminated = TerminateProcess(processHandle, 0);
    CloseHandle(processHandle);
    return terminated;
}

/**
 * Entry point for the process management utility.
 * Prompts the user for a process path and whether to terminate the process after resuming.
 * Creates the process in a suspended state, optionally terminates it, then resumes execution.
 * @return 0 on success, nonzero on failure.
 */
int main() {
    std::string processPath;
    std::string killAfterDone;

    std::cout << "Enter the path to the process: ";
    std::getline(std::cin, processPath);
    std::cout << "Kill Process After Done (y/n): ";
    std::getline(std::cin, killAfterDone);

    bool kill = (killAfterDone == "y" || killAfterDone == "Y" || killAfterDone == "yes" || killAfterDone == "Yes");

    STARTUPINFOA startupInfo = { sizeof(startupInfo) };
    PROCESS_INFORMATION processInfo;

    if (CreateProcessA(
            nullptr,
            &processPath[0],
            nullptr,
            nullptr,
            FALSE,
            CREATE_SUSPENDED,
            nullptr,
            nullptr,
            &startupInfo,
            &processInfo
        )) {
        std::cout
            << "Process created & suspended\n"
            << "Process ID: " << processInfo.dwProcessId << "\n"
            << "Thread ID: " << processInfo.dwThreadId << "\n"
            << "Process Name: " << processPath << "\n"
            << "Kill Process After Done: " << killAfterDone << "\n";

        std::getchar();

        if (kill) {
            terminateProcessById(processInfo.dwProcessId);
        }

        ResumeThread(processInfo.hThread);

        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
    } else {
        std::cout << "Failed to create process. Error code: " << GetLastError() << "\n";
    }

    return 0;
}
