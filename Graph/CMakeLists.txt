project(Graph)

file(GLOB copyResources testG1.txt testG2.txt)
file(COPY ${copyResources} DESTINATION ${CMAKE_BINARY_DIR}/Graph)

add_executable(Graph main.cpp)
