# ProcSuspender

ProcSuspender is a utility that allows you to launch a Windows process in a suspended state. This is useful for debugging, memory inspection, or manipulating the process before it starts running.

## What It Does
- Starts any executable in a suspended state
- Lets you attach a debugger or inspect memory before the process begins execution
- Optionally terminates the process after resuming
- Useful for reverse engineering, malware analysis, and advanced debugging tasks

## How It Works
- When you run ProcSuspender, it will prompt you to enter the path to the executable you want to launch.
- It will also ask if you want to kill the process after you are done (enter 'y' or 'n').
- The tool creates the process in a suspended state and displays its process and thread IDs.
- You can attach a debugger or perform analysis while the process is suspended.
- Press Enter to continue. If you chose to kill the process, it will be terminated; otherwise, it will resume execution.

## Usage Example
```
Enter the path to the process: C:\Path\To\Target.exe
Kill Process After Done (y/n): y
Process created & suspended
Process ID: 1234
Thread ID: 5678
Process Name: C:\Path\To\Target.exe
Kill Process After Done: y
```

After launching, you can attach a debugger or perform other analysis before resuming or terminating the process.

---

For more tools and utilities, see the main [My Reversing Utils](../README.md) repository. 