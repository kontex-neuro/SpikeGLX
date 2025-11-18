cmake_minimum_required(VERSION 3.25)
project(SpikeGLX VERSION 4.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui OpenGLWidgets Network Svg)
find_package(xdaq REQUIRED)
find_package(libxdaqnp REQUIRED)
find_package(PkgConfig REQUIRED)

qt6_standard_project_setup()

# Platform-specific compile definitions
add_definitions(-DHAVE_IMEC)
if(WIN32)
    add_definitions(-DHAVE_VISA)
    add_definitions(-DHAVE_NIDAQmx)
endif()
add_definitions(-DOPENGL54)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDO_SNAPSHOTS)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SpikeGLX_SOURCES
    # Src-main
    Src-main/ConsoleWindow.cpp
    Src-main/DataDirCtl.cpp
    Src-main/main.cpp
    Src-main/Main_Actions.cpp
    Src-main/Main_Msg.cpp
    Src-main/Main_WinMenu.cpp
    Src-main/MainApp.cpp
    Src-main/MetricsWindow.cpp
    Src-main/MXLEDWidget.cpp
    Src-main/Util.cpp
    Src-main/Util_osdep.cpp
)

set(SpikeGLX_HEADERS
    # Src-main
    Src-main/ConsoleWindow.h
    Src-main/DataDirCtl.h
    Src-main/Main_Actions.h
    Src-main/Main_Msg.h
    Src-main/Main_WinMenu.h
    Src-main/MainApp.h
    Src-main/MetricsWindow.h
    Src-main/MXLEDWidget.h
    Src-main/Util.h
    Src-main/Version.h
)

# Add all other source directories
file(GLOB_RECURSE SRC_AUDIO_SOURCES "Src-audio/*.cpp")
file(GLOB_RECURSE SRC_AUDIO_HEADERS "Src-audio/*.h")

file(GLOB_RECURSE SRC_DATAFILE_SOURCES "Src-datafile/*.cpp")
file(GLOB_RECURSE SRC_DATAFILE_HEADERS "Src-datafile/*.h")

file(GLOB_RECURSE SRC_FILTERS_SOURCES "Src-filters/*.cpp")
file(GLOB_RECURSE SRC_FILTERS_HEADERS "Src-filters/*.h")

file(GLOB_RECURSE SRC_GATES_SOURCES "Src-gates/*.cpp")
file(GLOB_RECURSE SRC_GATES_HEADERS "Src-gates/*.h")

file(GLOB_RECURSE SRC_GRAPHS_SOURCES "Src-graphs/*.cpp")
file(GLOB_RECURSE SRC_GRAPHS_HEADERS "Src-graphs/*.h")

file(GLOB_RECURSE SRC_GUI_TOOLS_SOURCES "Src-gui_tools/*.cpp")
file(GLOB_RECURSE SRC_GUI_TOOLS_HEADERS "Src-gui_tools/*.h")

file(GLOB_RECURSE SRC_IMRO_SOURCES "Src-imro/*.cpp")
file(GLOB_RECURSE SRC_IMRO_HEADERS "Src-imro/*.h")

file(GLOB_RECURSE SRC_PARAMS_SOURCES "Src-params/*.cpp")
file(GLOB_RECURSE SRC_PARAMS_HEADERS "Src-params/*.h")

file(GLOB_RECURSE SRC_REMOTE_SOURCES "Src-remote/*.cpp")
file(GLOB_RECURSE SRC_REMOTE_HEADERS "Src-remote/*.h")

file(GLOB_RECURSE SRC_RUN_SOURCES "Src-run/*.cpp")
file(GLOB_RECURSE SRC_RUN_HEADERS "Src-run/*.h")

file(GLOB_RECURSE SRC_SHANK_SOURCES "Src-shank/*.cpp")
file(GLOB_RECURSE SRC_SHANK_HEADERS "Src-shank/*.h")

file(GLOB_RECURSE SRC_TRIGGERS_SOURCES "Src-triggers/*.cpp")
file(GLOB_RECURSE SRC_TRIGGERS_HEADERS "Src-triggers/*.h")

file(GLOB_RECURSE SRC_VERIFY_SOURCES "Src-verify/*.cpp")
file(GLOB_RECURSE SRC_VERIFY_HEADERS "Src-verify/*.h")

# Third-party sources
file(GLOB_RECURSE RTAUDIO_SOURCES "RtAudio/*.cpp")
file(GLOB_RECURSE RTAUDIO_HEADERS "RtAudio/*.h")

# Exclude Windows-specific ASIO files on Linux
if(UNIX AND NOT APPLE)
    list(FILTER RTAUDIO_SOURCES EXCLUDE REGEX ".*asio.*")
    list(FILTER RTAUDIO_SOURCES EXCLUDE REGEX ".*asiodrivers.*")
    list(FILTER RTAUDIO_SOURCES EXCLUDE REGEX ".*asiolist.*")
    list(FILTER RTAUDIO_SOURCES EXCLUDE REGEX ".*iasiothiscallresolver.*")
    list(FILTER RTAUDIO_HEADERS EXCLUDE REGEX ".*asio.*")
    list(FILTER RTAUDIO_HEADERS EXCLUDE REGEX ".*iasio.*")
endif()

file(GLOB_RECURSE SAMPLERATE_SOURCES "Samplerate/*.cpp")
file(GLOB_RECURSE SAMPLERATE_HEADERS "Samplerate/*.h")

# UI forms
file(GLOB UI_FORMS "Forms/*.ui")

# Resource files
set(QRC_FILES
    Resources/CommonResources.qrc
    Resources/QLED.qrc
)

# Set the UI directory for AutoUIC
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/Forms)

# Process UI files and resources
qt6_add_resources(QRC_SOURCES ${QRC_FILES})

# Create executable - Qt6 will automatically process .ui files
qt_add_executable(SpikeGLX
    ${SpikeGLX_SOURCES}
    ${SpikeGLX_HEADERS}
    ${SRC_AUDIO_SOURCES}
    ${SRC_AUDIO_HEADERS}
    ${SRC_DATAFILE_SOURCES}
    ${SRC_DATAFILE_HEADERS}
    ${SRC_FILTERS_SOURCES}
    ${SRC_FILTERS_HEADERS}
    ${SRC_GATES_SOURCES}
    ${SRC_GATES_HEADERS}
    ${SRC_GRAPHS_SOURCES}
    ${SRC_GRAPHS_HEADERS}
    ${SRC_GUI_TOOLS_SOURCES}
    ${SRC_GUI_TOOLS_HEADERS}
    ${SRC_IMRO_SOURCES}
    ${SRC_IMRO_HEADERS}
    ${SRC_PARAMS_SOURCES}
    ${SRC_PARAMS_HEADERS}
    ${SRC_REMOTE_SOURCES}
    ${SRC_REMOTE_HEADERS}
    ${SRC_RUN_SOURCES}
    ${SRC_RUN_HEADERS}
    ${SRC_SHANK_SOURCES}
    ${SRC_SHANK_HEADERS}
    ${SRC_TRIGGERS_SOURCES}
    ${SRC_TRIGGERS_HEADERS}
    ${SRC_VERIFY_SOURCES}
    ${SRC_VERIFY_HEADERS}
    ${RTAUDIO_SOURCES}
    ${RTAUDIO_HEADERS}
    ${SAMPLERATE_SOURCES}
    ${SAMPLERATE_HEADERS}
    ${UI_FORMS}
    ${QRC_SOURCES}
)

# Include directories
target_include_directories(SpikeGLX PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-audio
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-datafile
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-filters
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-gates
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-graphs
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-gui_tools
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-imro
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-main
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-params
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-remote
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-run
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-shank
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-triggers
    ${CMAKE_CURRENT_SOURCE_DIR}/Src-verify
    ${CMAKE_CURRENT_SOURCE_DIR}/RtAudio
    ${CMAKE_CURRENT_SOURCE_DIR}/Samplerate
    ${CMAKE_CURRENT_SOURCE_DIR}/IMEC
)

# Link libraries
target_link_libraries(SpikeGLX PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::OpenGLWidgets
    Qt6::Network
    Qt6::Svg
    xdaq::xdaq_npapi
)

# Linux specific settings
if(UNIX AND NOT APPLE)
    # Find required system libraries
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ALSA REQUIRED alsa)
    pkg_check_modules(PULSE REQUIRED libpulse)
    find_package(X11 REQUIRED)
    
    target_compile_definitions(SpikeGLX PRIVATE
        __LINUX_ALSA__
        __LINUX_PULSE__
    )
    
    target_link_libraries(SpikeGLX PRIVATE
        ${ALSA_LIBRARIES}
        ${PULSE_LIBRARIES}
        ${X11_LIBRARIES}
        pulse-simple
        pthread
        GL
        GLU
    )
    
    target_include_directories(SpikeGLX PRIVATE
        ${ALSA_INCLUDE_DIRS}
        ${PULSE_INCLUDE_DIRS}
        ${X11_INCLUDE_DIR}
    )
endif()

# Install target
install(TARGETS SpikeGLX
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)

# Copy for development
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    file(COPY ${XDAQ_DEVICE_MANAGER_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${XDAQ_RESOURCES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    file(COPY ${XDAQ_DEVICE_MANAGER_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/SpikeGLX.app/Contents/PlugIns)
    file(COPY ${XDAQ_RESOURCES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/SpikeGLX.app/Contents/PlugIns)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    file(COPY ${XDAQ_DEVICE_MANAGER_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${XDAQ_RESOURCES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()