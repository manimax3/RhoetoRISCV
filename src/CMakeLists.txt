add_library(rhoetoriscv SHARED 
	test.h
	test.cpp)

add_executable(rrv main.cpp)
target_link_libraries(rrv PUBLIC rhoetoriscv)

target_compile_options(rhoetoriscv PUBLIC 
	-std=c++17
	$<$<CONFIG:Debug>:-ggdb -fsanitize=address -fno-omit-frame-pointer>
)

target_link_options(rhoetoriscv PUBLIC
	-lasan
)
