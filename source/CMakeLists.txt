cmake_minimum_required(VERSION 3.13)
project(dissection)


set(SOURCES main.cpp Input.h Input.cpp Cluster.h Cluster.cpp ClusterViewer.h ClusterViewer.cpp Dissection.h Dissection.cpp Matching.h Matching.cpp)
add_executable(dissection ${SOURCES})


target_link_libraries(dissection lunasvg)
target_link_libraries(dissection glad)
target_link_libraries(dissection glfw3)
target_link_libraries(dissection X11)