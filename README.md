# wxWidgets Text Editor

**wxWidgets Text Editor** is a simple, cross-platform text editor built using the wxWidgets library. It demonstrates the core features of a basic text editor, including file opening, saving, and directory browsing.

## Project Structure

```text
.
├── CMakeLists.txt
├── build_and_package_app.sh
├── include
│   ├── texteditorapp.h
│   └── texteditorframe.h
├── src
│   ├── main.cpp
│   ├── texteditorapp.cpp
│   └── texteditorframe.cpp
└── vcpkg.json
```

## Features

- **File Operations**: Open and save text files.
- **Directory Browsing**: Browse directories and select files to edit.
- **Cross-Platform**: Built with wxWidgets, making it compatible with multiple platforms.

## Dependencies

This project uses the following dependencies managed via [vcpkg](https://github.com/microsoft/vcpkg):

- `wxwidgets`

## Build Instructions

### Prerequisites

- CMake 3.25 or higher
- wxWidgets (installed via vcpkg)
- A C++ compiler supporting C++23

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/owenthcarey/wxwidgets-text-editor.git
   cd wxwidgets-text-editor
   ```

2. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

### Packaging the App (macOS)

To package the application on macOS, use the provided script:

```bash
./build_and_package_app.sh
```

This will create a macOS `.app` bundle in the project directory.
