# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.9)

set (PROJECT_NAME notelib)
project (${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STANDARD_REQUIRED true)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/src/ui")

# Run uic on all ui files and put them in include
file(GLOB UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.ui")
message("Generating ui file headers") 
foreach(file ${UI_FILES})
    get_filename_component(filename "${file}" NAME)
    # Remove the extension from the filename
    string(REGEX REPLACE "\\.[^.]+$" "" raw_filename "${filename}")
    execute_process(COMMAND uic "${file}" "-o" "${CMAKE_CURRENT_SOURCE_DIR}/src/include/ui_${raw_filename}.h")
endforeach()

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(SOURCE_FILES "src/main.cpp" "src/MainWindow.cpp")
set(HEADER_FILES "src/include/MainWindow.h")
set(UI_FILES "src/ui/MainWindow.ui")

qt_add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC "src/include")

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

