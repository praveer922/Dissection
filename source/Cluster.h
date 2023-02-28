#pragma once
#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>

class Cluster {

public:
    std::vector<float> xCoords;
    std::vector<float> yCoords;

    Cluster();
    void render();
};

#endif