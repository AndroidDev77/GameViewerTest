project(GameViewerTest CXX)

################################################################################
# Source groups
################################################################################
set(Headers
    "pch.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "pch.cpp"
    "test.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################

add_precompiled_header(${PROJECT_NAME} "pch.h" "pch.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/.../GameViewer;"
            "$ENV{MSBuildThisFileDirectory}include;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../Qt/5.12.2/msvc2017/include;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../Qt/5.12.2/msvc2017/include/QtGui;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../Scratch/vcpkg/installed/x86-windows/include;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../Scratch/curl-7.66.0/curl-7.66.0/include"
        ">"
    )
endif()

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "UNICODE;"
    "_UNICODE"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "X64;"
        "_CONSOLE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /RTC1;
                /MDd;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
                /MD;
                /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /RTC1;
                /MDd;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
                /MD;
                /Zi
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    GameViewer
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    GameViewer
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "libcurld;"
            "Qt5Cored;"
            "Qt5Guid;"
            "Qt5Widgetsd;"
            "Qt5Gamepadd;"
            "GameViewer"
        ">"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "F:/MobileApps/XMobilApp1/GameViewerTest;"
            "F:/Scratch/curl-7.66.0/curl-7.66.0/build/Win32/VC15/DLL Debug;"
            "F:/Qt/5.12.2/msvc2017/lib"
        ">"
    )
endif()

use_package(${PROJECT_NAME} Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn 1.8.1)
