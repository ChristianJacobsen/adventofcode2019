add_executable(day05 "./main.cpp")
target_include_directories(day05 PRIVATE "../intcode")
target_link_libraries(day05 PRIVATE intcode)