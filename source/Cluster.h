#pragma once
#ifndef CLUSTER_H
#define CLUSTER_H
#include <Eigen/Dense>
#include <vector>

class Cluster {

public:
    std::vector<float> xCoords;
    std::vector<float> yCoords;
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    Cluster();
    void generateRenderMeshes();
};

#endif