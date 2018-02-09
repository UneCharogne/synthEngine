cmake_minimum_required( VERSION 2.6 )
project(my_engine)

#adding the headers directory
include_directories(include)

#add glm library
include_directories(src/glm)

SET(GCC_COMPILE_FLAGS "-Wc++11-extensions -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses")
SET(GCC_INCLUDE_FLAGS "")
SET(GCC_LINK_FLAGS   "")
add_definitions(${GCC_COMPILE_FLAGS} ${GCC_INCLUDE_FLAGS} ${GCC_LINK_FLAGS})

#add the sources
file(GLOB SOURCES "src/*.cpp")

add_executable(my_engine ${SOURCES})

#link the shaders
set (source "${CMAKE_SOURCE_DIR}/src/shaders")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/shaders")
add_custom_command(
 TARGET ${PROJECT_NAME} POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
 DEPENDS ${destination}
 COMMENT "symbolic link shaders folder from ${source} => ${destination}"
)

#link the assimp library
include_directories(assimp/include)
include_directories(assimp/build/include)
file(GLOB LIBRARIES "assimp/build/code/*.dylib")
target_link_libraries(my_engine ${LIBRARIES})

#link the opengl library
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(my_engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
