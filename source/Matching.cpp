#include "Matching.h"
#include "Dissection.h"

Matching::Matching(std::vector<Cluster> list1, std::vector<Cluster> list2, std::vector<std::pair<int, int>> matching) {
    this->list1 = list1;
    this->list2 = list2;
    this->matching = matching;
}

void Matching::addPair(std::pair<Cluster, Cluster> pair) {
    list1.push_back(pair.first);
    list2.push_back(pair.second);
    matching.push_back(std::pair<int, int>(list1.size() - 1, list2.size() - 1));
}

int Matching::calculateDistance() {
    int dist = 0;
    for (auto match : matching) {
        dist += calculateMinDistance(list1[match.first], list2[match.second]);
    }

    return dist;
}