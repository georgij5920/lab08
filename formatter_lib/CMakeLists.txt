add_library(formatter STATIC formatter.cpp)

target_include_directories(formatter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS formatter
    EXPORT formatter-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(FILES formatter.h DESTINATION include)
install(EXPORT formatter-config DESTINATION cmake)
