add_library(formatter_ex STATIC formatter_ex.cpp)

target_include_directories(formatter_ex PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(formatter_ex PUBLIC formatter)

install(TARGETS formatter_ex
    EXPORT formatter_ex-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(FILES formatter_ex.h DESTINATION include)
install(EXPORT formatter_ex-config DESTINATION cmake)
