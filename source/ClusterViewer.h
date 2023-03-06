#pragma once
#ifndef CLUSTERVIEWER_H
#define CLUSTERVIEWER_H
#include "Cluster.h"
#include <igl/opengl/glfw/Viewer.h>
#include <vector>

class Window {

public:
    int originX;
    int originY;
    int width;
    int height;

    std::vector<Cluster> clusters;
    Window(int originX, int originY, int width, int height);
    void addCluster(Cluster cluster);
};

class ClusterViewer {

public:
    igl::opengl::glfw::Viewer viewer;
    std::vector<Window> windows;

    ClusterViewer();
    void addWindow(Window window);
    void launch();
};



#endif