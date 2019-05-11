add_library(rhoetoriscv SHARED 
	asm.h
	parser.h
	parser.cpp)

add_executable(rrv main.cpp)
target_link_libraries(rrv PUBLIC rhoetoriscv)

target_compile_options(rhoetoriscv PUBLIC 
	-std=c++17
	$<$<CONFIG:Debug>:-ggdb -fsanitize=address -fno-omit-frame-pointer>
)

target_link_options(rhoetoriscv PUBLIC
	-lasan
)

# Boost Library
find_package(Boost 1.68 REQUIRED)

target_link_libraries(rhoetoriscv 
	PUBLIC BetterEnum
	PRIVATE ${Boost_LIBRARIES})
target_include_directories(rhoetoriscv PRIVATE ${Boost_INCLUDE_DIRS})
