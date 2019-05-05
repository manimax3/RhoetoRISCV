add_executable(Tests main.cpp parser.cpp)
target_link_libraries(Tests PRIVATE Catch rhoetoriscv)
