cmake_minimum_required(VERSION 3.0.0)
project(Automaton2000 VERSION 0.1.0)

include_directories(/usr/include/mysql-cppconn-8/jdbc)
link_directories(/usr/lib/x86_64-linux-gnu/)

add_executable(
    Automaton2000 
    src/main.cpp
    src/database.cpp
    src/log.cpp)

target_link_libraries(Automaton2000 mysqlcppconn)