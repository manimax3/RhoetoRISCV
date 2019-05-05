add_library(Catch INTERFACE)
target_sources(Catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp)
target_include_directories(Catch INTERFACE .)

add_library(BetterEnum INTERFACE)
target_sources(BetterEnum INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/enum.h)
target_include_directories(BetterEnum INTERFACE .)
