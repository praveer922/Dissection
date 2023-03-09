#pragma once
#ifndef MATCHING_H
#define MATCHING_H
#include "Cluster.h"


class Matching {

public:
    std::vector<Cluster> list1;
    std::vector<Cluster> list2;
    // contains pairs of indexes into list1 and list2 to represent matching betweem clusters
    std::vector<std::pair<int, int>> matching;

    Matching(std::vector<Cluster> list1, std::vector<Cluster> list2, std::vector<std::pair<int, int>> matching);
    void addPair(std::pair<Cluster,Cluster> pair);
    int calculateDistance();
};

#endif