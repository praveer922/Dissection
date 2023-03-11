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
    // V1 to V4 are used for adding edges for each pixel square
    Eigen::MatrixXd V1;
    Eigen::MatrixXd V2;
    Eigen::MatrixXd V3;
    Eigen::MatrixXd V4;
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