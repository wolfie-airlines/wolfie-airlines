cmake_minimum_required(VERSION 3.27)
project(airport)

set(CMAKE_CXX_STANDARD 20)

add_executable(airport main.cpp
        EnvParser.h
        EnvParser.cpp
        Authentication.cpp
        User.cpp
        functions/printFunctions.h
        functions/printFunctions.cpp
        FlightConnection.h
        FlightConnection.cpp
        functions/handlingFunctions.cpp
        functions/handlingFunctions.h
)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

project(airport LANGUAGES CXX VERSION 1.0.0)
target_link_libraries(airport
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
)

find_package(mongocxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/mongo-cxx-driver_x64-windows")
find_package(bsoncxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/mongo-cxx-driver_x64-windows")

find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

