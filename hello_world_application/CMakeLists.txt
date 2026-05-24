add_executable(hello_world hello_world.cpp)

target_link_libraries(hello_world formatter_ex)

install(TARGETS hello_world RUNTIME DESTINATION bin)
