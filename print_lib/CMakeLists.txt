add_library(print STATIC print.cpp)
add_library(print::print ALIAS print)

target_include_directories(print PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(print PUBLIC formatter)
target_compile_features(print PUBLIC cxx_std_14)

install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(FILES print.hpp DESTINATION include)
install(EXPORT print-config DESTINATION cmake)
