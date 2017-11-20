cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(stack)

add_library(stack INTERFACE)

target_include_directories(stack INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "/examples/*.cpp")
  foreach(EXAMPLE_SOURCE )
    get_filename_component(EXAMPLE_NAME  NAME_WE)
    add_executable( )
    target_link_libraries( stack)
    install(TARGETS 
      RUNTIME DESTINATION bin
    )
  endforeach(EXAMPLE_SOURCE )
endif()

install(TARGETS stack
    EXPORT stack-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT stack-config DESTINATION cmake)

if(BUILD_TESTS)
enable_testing()
file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()