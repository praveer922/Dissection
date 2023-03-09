#pragma once
#ifndef DISSECTION_H
#define DISSECTION_H

#include "Cluster.h"
#include "Matching.h"

//functions used for the dissection algorithm
int differenceInPixels(Cluster& cluster, Cluster &otherCluster);
int calculateMinDistance(Cluster& cluster, Cluster& otherCluster);
std::vector<std::vector<std::pair<int, int>>> generateAllPossibleMatchingIndexes(std::vector<int> list1, std::vector<int> list2);
std::vector<Matching> generateAllPossibleMatchings(std::vector<Cluster>& list1, std::vector<Cluster>& list2);
Matching getClosestMatching(std::vector<Cluster>& list1, std::vector<Cluster>& list2);

#endif