cmake_minimum_required (VERSION 3.11)
project(imtui_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define where to store imtui content
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

# Download zip file (method 1)
if(NOT EXISTS ${THIRD_PARTY_DIR}/imtui/imtui-1.0.5.tar.gz)
  message(STATUS "Downloading imtui v0.0.5!")

  set(IMTUI_ZIP_PATH ${THIRD_PARTY_DIR}/imtui/imtui-1.0.5.tar.gz)

  file(DOWNLOAD
    https://github.com/ggerganov/imtui/releases/download/v1.0.5/imtui-1.0.5.tar.gz
    ${IMTUI_ZIP_PATH}
    EXPECTED_HASH SHA256=82677597065b7e8c738db5677dde9126a9367b0a15345334ee41eba50692d064
    SHOW_PROGRESS
  )
endif()

# Cloning repo (method 2)
if(NOT EXISTS ${THIRD_PARTY_DIR}/imtui/imtui)
  message(STATUS "Cloning imtui v1.0.5!")

  set(IMTUI_ZIP_PATH ${THIRD_PARTY_DIR}/imtui/imtui)

  execute_process(
    COMMAND git clone --branch v1.0.5 --depth 1 https://github.com/ggerganov/imtui.git ${IMTUI_ZIP_PATH} --recursive
    RESULT_VARIABLE GIT_CLONE_RESULT
    OUTPUT_VARIABLE GIT_CLONE_OUTPUT
    ERROR_VARIABLE GIT_CLONE_ERROR
  )

  if(NOT GIT_CLONE_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to clone imtui: ${GIT_CLONE_ERROR}")
  endif()
endif()

# ---
include(FetchContent)

# --- Fetch IMTUI
FetchContent_Declare(imtui
  URL ${CMAKE_SOURCE_DIR}/third_party/imtui/imtui-1.0.5.tar.gz
  # GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/third_party/imtui/imtui
  # GIT_TAG v1.0.5
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_GetProperties(imtui)
if(NOT imtui_POPULATED)
  FetchContent_Populate(imtui)
  add_subdirectory(${imtui_SOURCE_DIR} ${imtui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

find_package(Curses REQUIRED)

# example using imtui_handler library
add_executable(imtui-handler-example)
target_sources(imtui-handler-example
  PRIVATE
  ./src/imtui_handler.cpp
  ./src/imtui_handler_example.cpp
)
target_include_directories(imtui-handler-example PUBLIC include)
target_link_libraries(imtui-handler-example imtui-ncurses)

# # example directly using imtui content
# add_executable(imtui-example)
# target_sources(imtui-example PRIVATE src/main.cpp)
# target_include_directories(imtui-example PRIVATE include)
# target_link_libraries(imtui-example PRIVATE imtui_glfw)
