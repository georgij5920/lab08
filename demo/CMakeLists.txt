add_executable(demo main.cpp)
target_link_libraries(demo print::print)
install(TARGETS demo RUNTIME DESTINATION bin)
