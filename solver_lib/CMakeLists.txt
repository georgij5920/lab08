add_library(solver_lib STATIC solver.cpp)

target_include_directories(solver_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS solver_lib
    EXPORT solver_lib-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(FILES solver.h DESTINATION include)
install(EXPORT solver_lib-config DESTINATION cmake)
