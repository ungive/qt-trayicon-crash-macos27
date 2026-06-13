cmake_minimum_required(VERSION 3.21)

project(QtTrayTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adjust this to your Qt installation root.
# Example:
#   /Users/me/Qt/6.9.3/macos
#
set(QT_ROOT "/Users/jonas/Qt/6.12.0/macos")

list(APPEND CMAKE_PREFIX_PATH "${QT_ROOT}")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(QtTrayTest
    main.cpp
)

target_link_libraries(QtTrayTest
    PRIVATE
        Qt6::Widgets
)
