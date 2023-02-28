#pragma once
#ifndef CLUSTER_H
#define CLUSTER_H
#include <Eigen/Dense>
#include <vector>
#include <set>

class Cluster {

public:
    std::set<std::pair<int, int>> pixels;
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    Cluster();
    void generateRenderMeshes();
};

#endif