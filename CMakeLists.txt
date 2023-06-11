cmake_minimum_required(VERSION 3.25)

# The path to vcpkg.cmake file provided by `vcpkg integrate install`
set(CMAKE_TOOLCHAIN_FILE /Users/owenthcarey/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(wxwidgets_text_editor)

set(CMAKE_CXX_STANDARD 23)

# Find the wxWidgets library
find_package(wxWidgets REQUIRED COMPONENTS net core base richtext html xml stc)
include(${wxWidgets_USE_FILE})

# Add your executable
add_executable(wxwidgets_text_editor src/main.cpp src/texteditorapp.cpp include/texteditorapp.h src/texteditorframe.cpp include/texteditorframe.h)

# Link wxWidgets to your target
target_link_libraries(wxwidgets_text_editor ${wxWidgets_LIBRARIES})
