cmake_minimum_required(VERSION 3.25)
project(SpikeGLX VERSION 4.0.0 LANGUAGES CXX)

SET(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)

include(GNUInstallDirs)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui OpenGLWidgets Network Svg)
find_package(xdaq REQUIRED)
find_package(libxdaqnp REQUIRED)

qt6_standard_project_setup()


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
if(UNIX)
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
qt_add_executable(SpikeGLX MACOSX_BUNDLE
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
    IMEC/xdaq_npapi.cc
)

target_compile_features(SpikeGLX PRIVATE cxx_std_23)

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

target_compile_definitions(SpikeGLX PRIVATE
    HAVE_IMEC
    OPENGL54

	$<$<PLATFORM_ID:Linux>:OS_LINUX>
	$<$<PLATFORM_ID:Windows>:OS_WINDOWS>
	$<$<PLATFORM_ID:Darwin>:OS_MACOS>
)

# Linux specific settings
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
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
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    find_package(OpenGL REQUIRED)
    target_link_libraries(SpikeGLX PRIVATE ${OPENGL_LIBRARIES})
    target_compile_options(SpikeGLX PRIVATE $<$<CONFIG:Debug>:-Og>)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    find_package(OpenGL REQUIRED)
    target_link_libraries(SpikeGLX PRIVATE ${OPENGL_LIBRARIES} winmm)
endif()

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

include(deployQt)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    install(TARGETS SpikeGLX DESTINATION .)
    install(DIRECTORY ${XDAQ_DEVICE_MANAGER_DIR} DESTINATION .)
    install(DIRECTORY ${XDAQ_RESOURCES_DIR} DESTINATION .)
	install(IMPORTED_RUNTIME_ARTIFACTS xdaq::xdaq_npapi
		LIBRARY DESTINATION .
		RUNTIME DESTINATION .
	)
    deployqt($<TARGET_FILE_NAME:SpikeGLX>)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    install(TARGETS SpikeGLX DESTINATION .)
    set_target_properties(SpikeGLX PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks"
    )
	install(IMPORTED_RUNTIME_ARTIFACTS xdaq::xdaq_npapi
		LIBRARY DESTINATION SpikeGLX.app/Contents/Frameworks
		RUNTIME DESTINATION SpikeGLX.app/Contents/Frameworks
	)
    set_target_properties(SpikeGLX PROPERTIES
        MACOSX_BUNDLE_ICON_FILE "${ICON_NAME}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "io.kontex.SpikeGLX"
        MACOSX_BUNDLE_BUNDLE_NAME "SpikeGLX"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
    )
    deployqt("$<TARGET_FILE_NAME:SpikeGLX>.app")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS SpikeGLX DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(DIRECTORY ${XDAQ_DEVICE_MANAGER_DIR} DESTINATION ${CMAKE_INSTALL_LIBDIR}/SpikeGLX)
    install(DIRECTORY ${XDAQ_RESOURCES_DIR} DESTINATION ${CMAKE_INSTALL_LIBDIR}/SpikeGLX)
	set_target_properties(SpikeGLX PROPERTIES
		BUILD_WITH_INSTALL_RPATH TRUE
		INSTALL_RPATH "$ORIGIN/../lib/SpikeGLX"
	)
	install(IMPORTED_RUNTIME_ARTIFACTS xdaq::xdaq_npapi
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/SpikeGLX
		RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}/SpikeGLX
	)
endif()