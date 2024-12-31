#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using namespace std;

// Function to list files and directories in the current directory
void listFiles(const string& path) {
    cout << "Contents of directory: " << path << endl;
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (fs::is_directory(entry) ? "[DIR] " : "[FILE] ") << entry.path().filename() << endl;
    }
}

// Function to create a new directory
void createDirectory(const string& path) {
    if (fs::create_directory(path)) {
        cout << "Directory created: " << path << endl;
    } else {
        cout << "Failed to create directory: " << path << endl;
    }
}

// Function to copy a file
void copyFile(const string& source, const string& destination) {
    try {
        fs::copy(source, destination);
        cout << "File copied from " << source << " to " << destination << endl;
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Function to move a file
void moveFile(const string& source, const string& destination) {
    try {
        fs::rename(source, destination);
        cout << "File moved from " << source << " to " << destination << endl;
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Function to read and display file content
void readFile(const string& path) {
    ifstream file(path);
    if (file.is_open()) {
        string line;
        cout << "Contents of file: " << path << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Failed to open file: " << path << endl;
    }
}

// Main function
int main() {
    string currentDir = fs::current_path().string();
    int choice;
    string input, input2;

    while (true) {
        cout << "\nBasic File Manager - Current Directory: " << currentDir << endl;
        cout << "1. List files and directories\n";
        cout << "2. Change directory\n";
        cout << "3. Create directory\n";
        cout << "4. Read file\n";
        cout << "5. Copy file\n";
        cout << "6. Move file\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listFiles(currentDir);
                break;

            case 2:
                cout << "Enter directory to navigate to: ";
                cin >> input;
                if (fs::exists(input) && fs::is_directory(input)) {
                    currentDir = input;
                    fs::current_path(input);
                    cout << "Changed directory to: " << currentDir << endl;
                } else {
                    cout << "Directory does not exist." << endl;
                }
                break;

            case 3:
                cout << "Enter directory name to create: ";
                cin >> input;
                createDirectory(currentDir + "/" + input);
                break;

            case 4:
                cout << "Enter file name to read: ";
                cin >> input;
                readFile(currentDir + "/" + input);
                break;

            case 5:
                cout << "Enter source file name: ";
                cin >> input;
                cout << "Enter destination file name: ";
                cin >> input2;
                copyFile(currentDir + "/" + input, currentDir + "/" + input2);
                break;

            case 6:
                cout << "Enter source file name: ";
                cin >> input;
                cout << "Enter destination file name: ";
                cin >> input2;
                moveFile(currentDir + "/" + input, currentDir + "/" + input2);
                break;

            case 7:
                cout << "Exiting File Manager. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
