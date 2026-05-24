add_library(banking STATIC Account.cpp Transaction.cpp)
add_library(banking::banking ALIAS banking)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(banking PUBLIC cxx_std_14)

install(TARGETS banking ARCHIVE DESTINATION lib)
install(FILES Account.h Transaction.h DESTINATION include)
