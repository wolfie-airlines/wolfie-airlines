cmake_minimum_required(VERSION 3.27)
project(airport)

set(CMAKE_CXX_STANDARD 20)

add_executable(airport main.cpp)

find_package(SDL2 REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/sdl2_x64-windows")
find_package(GLEW REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/glew_x64-windows")
find_package(mongocxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/mongo-cxx-driver_x64-windows")
find_package(bsoncxx REQUIRED HINTS "C:/Users/szymo/.vcpkg-clion/airport/packages/mongo-cxx-driver_x64-windows")

find_package(OpenGL REQUIRED)
target_link_libraries(airport PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(airport PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
target_link_libraries(airport PRIVATE GLEW::GLEW)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(airport
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(airport PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

