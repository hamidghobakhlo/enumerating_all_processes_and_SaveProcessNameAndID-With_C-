#include <windows.h>
#include <psapi.h>
#include <fstream>
#include <iostream>
#include <string>
#include <direct.h>

using namespace std;

void PrintProcessNameAndID(DWORD processID, ofstream& csvFile)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }

#ifdef UNICODE
        wstring ws(szProcessName);
        string processName(ws.begin(), ws.end());
#else
        string processName(szProcessName);
#endif

        csvFile << processName << "," << processID << std::endl;

        CloseHandle(hProcess);
    }
}

bool CreateDirectoryIfNotExists(const char* dirPath)
{
    DWORD fileAttr = GetFileAttributesA(dirPath);

    if (fileAttr == INVALID_FILE_ATTRIBUTES) {
        if (_mkdir(dirPath) == 0) {
            printf("Directory created: %s\n", dirPath);
            return true;
        }
        else {
            printf("Failed to create directory: %s\n", dirPath);
            return false;
        }
    }

    return (fileAttr & FILE_ATTRIBUTE_DIRECTORY);
}

int main(void)
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    char dirPath[MAX_PATH];
    printf("Enter the directory path to save the CSV file (e.g., C:\\path\\to\\folder): ");
    fgets(dirPath, sizeof(dirPath), stdin);
    dirPath[strcspn(dirPath, "\n")] = 0;

    if (!CreateDirectoryIfNotExists(dirPath)) {
        printf("The specified directory could not be created or accessed.\n");
        return 1;
    }

    char filePath[MAX_PATH];
    snprintf(filePath, sizeof(filePath), "%s\\process_list.csv", dirPath);

    std::ofstream csvFile(filePath);

    if (!csvFile.is_open()) {
        printf("Failed to create file at the specified path.\n");
        return 1;
    }

    csvFile << "ProcessName,PID\n";

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return 1;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            PrintProcessNameAndID(aProcesses[i], csvFile);
        }
    }

    csvFile.close();

    printf("Process list saved successfully to: %s\n", filePath);
    return 0;
}
