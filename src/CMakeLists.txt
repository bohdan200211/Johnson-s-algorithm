add_executable(MyMain main.cpp)

target_link_libraries(MyMain PRIVATE libfort::fort JohnsonLib)
