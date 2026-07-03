cmake_minimum_required(VERSION 3.16)

project(cpolycall VERSION 1.0.0 LANGUAGES C)

include(CTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(CPOLYCALL_BUILD_EXAMPLE "Build the cpolycall example executable" OFF)
set(CPOLYCALL_CORE_LIBRARY "" CACHE FILEPATH
    "Path to a libpolycall v1.5 library for the example executable")

add_library(cpolycall STATIC src/cpolycall.c)
add_library(cpolycall::cpolycall ALIAS cpolycall)

target_compile_features(cpolycall PUBLIC c_std_11)
target_include_directories(cpolycall
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/generated)
set_target_properties(cpolycall PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    OUTPUT_NAME cpolycall)

if(MSVC)
    target_compile_options(cpolycall PRIVATE /W4)
else()
    target_compile_options(cpolycall PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_TESTING)
    add_executable(cpolycall_test
        tests/cpolycall_test.c
        tests/polycall_ffi_mock.c)
    target_link_libraries(cpolycall_test PRIVATE cpolycall::cpolycall)
    target_include_directories(cpolycall_test PRIVATE tests)
    add_test(NAME cpolycall_adapter COMMAND cpolycall_test)
endif()

if(CPOLYCALL_BUILD_EXAMPLE)
    add_executable(cpolycall_example examples/basic.c)
    target_link_libraries(cpolycall_example PRIVATE cpolycall::cpolycall)
    set_target_properties(cpolycall_example PROPERTIES OUTPUT_NAME cpolycall)

    if(TARGET polycall::polycall)
        target_link_libraries(cpolycall_example PRIVATE polycall::polycall)
    elseif(CPOLYCALL_CORE_LIBRARY)
        target_link_libraries(cpolycall_example PRIVATE ${CPOLYCALL_CORE_LIBRARY})
    else()
        message(FATAL_ERROR
            "CPOLYCALL_BUILD_EXAMPLE requires polycall::polycall or "
            "-DCPOLYCALL_CORE_LIBRARY=/path/to/libpolycall")
    endif()
endif()

install(TARGETS cpolycall
    EXPORT cpolycallTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES include/cpolycall.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_package_config_file(
    cmake/cpolycallConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cpolycallConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpolycall)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cpolycallConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(EXPORT cpolycallTargets
    FILE cpolycallTargets.cmake
    NAMESPACE cpolycall::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpolycall)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cpolycallConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cpolycallConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpolycall)
