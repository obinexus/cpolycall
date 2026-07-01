# cpolycall - C reference binding. Built when POLYCALL_BUILD_BINDINGS=ON.
# Links the shared core through the public ABI only (adapter boundary).
add_executable(cpolycall src/cpolycall.c)
target_link_libraries(cpolycall PRIVATE polycall::polycall)
set_target_properties(cpolycall PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

if(POLYCALL_BUILD_TESTS)
    add_test(NAME binding_cpolycall
             COMMAND cpolycall ${CMAKE_CURRENT_SOURCE_DIR}/../cpolycall/cpolycallrc)
endif()
