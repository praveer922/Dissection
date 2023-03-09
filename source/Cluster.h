#pragma once
#ifndef CLUSTER_H
#define CLUSTER_H
#include <Eigen/Dense>
#include <vector>
#include <set>

class Cluster {

public:
    std::set<std::pair<int, int>> pixels;
    Eigen::MatrixXi pixelsAsMatrix;
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd C;
    int viewer_mesh_id;

    Cluster(std::set<std::pair<int, int>> pixels);
    Cluster(Eigen::MatrixXi pixelsAsMatrix);
    void generateRenderMeshes();
    std::vector<Cluster> randomSeedFill();
    void setColor(int r, int g, int b);
    std::pair<int, int> getBoundingBoxCenter();
    Cluster translateToCenterOfOtherCluster(Cluster& otherCluster);
    Cluster translateToOrigin();
};



#endif