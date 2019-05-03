add_library(Catch INTERFACE)
target_sources(Catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp)
target_include_directories(Catch INTERFACE .)
