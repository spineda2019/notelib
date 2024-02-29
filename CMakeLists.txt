# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set (PROJECT_NAME notelib)
project (${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STANDARD_REQUIRED true)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(SOURCE_FILES "src/main.cpp")
set(HEADER_FILES "src/include/MainWindow.hpp")
set(UI_FILES "src/ui/MainWindow.ui")

qt_add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC "src/include" "src/ui")

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

