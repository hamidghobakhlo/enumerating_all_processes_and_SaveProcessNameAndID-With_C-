# Process List Collector

This C++ program collects a list of running processes on a Windows system and saves their names and process IDs (PIDs) in a CSV file.

---

## Features

- **Process Information Retrieval:** Extracts process names and their respective PIDs.
- **CSV File Output:** Saves the collected data in a structured CSV file format.
- **Custom Directory Support:** Allows the user to specify the directory where the CSV file will be saved.
- **Automatic Directory Creation:** Creates the directory if it doesn't exist.
- **Error Handling:** Reports errors for inaccessible directories or files.

---

## How It Works

1. The program prompts the user to enter a directory path for saving the CSV file.
2. If the directory does not exist, it attempts to create it.
3. The program retrieves the list of running processes using Windows APIs.
4. It writes the process names and their PIDs to a CSV file named `process_list.csv` in the specified directory.
5. Upon successful execution, it notifies the user of the file's location.

---

## Code Structure

### Key Functions

#### `PrintProcessNameAndID(DWORD processID, ofstream& csvFile)`
- Retrieves the name of the process for the given PID and writes it to the CSV file.

#### `CreateDirectoryIfNotExists(const char* dirPath)`
- Checks if the specified directory exists. If not, it creates the directory.

### Main Program (`main`)
1. Prompts the user for a directory path.
2. Validates or creates the directory.
3. Generates a list of running processes and saves the details in `process_list.csv`.

---

## Example Usage

### Input
![Process List Screenshot](images/screenshot.png)
### Output File Content (`process_list.csv`)
```csv
ProcessName,PID
explorer.exe,1234
notepad.exe,5678
...
