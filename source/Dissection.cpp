#include "Dissection.h"
#include <iostream>

// utility function to find total number of unmatched pixels between two clusters
int differenceInPixels(Cluster & cluster, Cluster& otherCluster) {
    std::set<std::pair<int, int>> union_set;
    std::set_union(cluster.pixels.begin(), cluster.pixels.end(),
        otherCluster.pixels.begin(), otherCluster.pixels.end(),
        std::inserter(union_set, union_set.begin()));

    std::set<std::pair<int, int>> intersection_set;
    std::set_intersection(cluster.pixels.begin(), cluster.pixels.end(),
        otherCluster.pixels.begin(), otherCluster.pixels.end(),
        std::inserter(intersection_set, intersection_set.begin()));

    return union_set.size() - intersection_set.size();
}

// function for calculating minimum distance between two clusters (after accounting for all valid rotations and flipping)
int calculateMinDistance(Cluster & cluster, Cluster& otherCluster) {
    Cluster origin_cluster = cluster.translateToOrigin();

    std::vector<Eigen::MatrixXi> all_valid_rotations_and_flips;

    Eigen::MatrixXi zero = Eigen::MatrixXi(2, 2);
    zero << 1, 0,
        0, 1;

    Eigen::MatrixXi ninety = Eigen::MatrixXi(2, 2);
    ninety << 0, -1,
        1, 0;

    Eigen::MatrixXi one_eighty = Eigen::MatrixXi(2, 2); //equivalent to a horizontal flip
    one_eighty << -1, 0,
        0, -1;

    Eigen::MatrixXi two_seventy = Eigen::MatrixXi(2, 2);
    two_seventy << 0, 1,
        -1, 0;

    Eigen::MatrixXi vertical_flip = Eigen::MatrixXi(2, 2);
    vertical_flip << -1, 0,
        0, 1;

    all_valid_rotations_and_flips.push_back(zero);
    all_valid_rotations_and_flips.push_back(ninety);
    all_valid_rotations_and_flips.push_back(one_eighty);
    all_valid_rotations_and_flips.push_back(two_seventy);
    all_valid_rotations_and_flips.push_back(vertical_flip);

    int minDist = INT_MAX;

    for (auto mat : all_valid_rotations_and_flips) {
        Eigen::MatrixXi rotated_matrix = (mat * origin_cluster.pixelsAsMatrix.transpose()).transpose();
        Cluster rotated_cluster = Cluster(rotated_matrix);
        Cluster rotated_and_translated_cluster = rotated_cluster.translateToCenterOfOtherCluster(otherCluster);
        int newDist = differenceInPixels(rotated_and_translated_cluster, otherCluster);
        if (newDist < minDist) {
            minDist = newDist;
        }
    }


    return minDist;
}

// helper function for generateAllPossibleMatchings(), which takes in lists of indexes and returns all possible index pairs
std::vector<std::vector<std::pair<int, int>>> generateAllPossibleMatchingIndexes(std::vector<int> list1, std::vector<int> list2) {
    std::vector<std::vector<std::pair<int, int>>> possible_matchings = std::vector<std::vector<std::pair<int, int>>>();

    if (list1.size() == 0 || list2.size() == 0) {
        return possible_matchings;
    } else if (list1.size() == 1 && list2.size() == 1) {
        //only one possible match exists
        std::vector<std::pair<int, int>> matching = std::vector<std::pair<int, int>>();
        matching.push_back(std::pair<int, int>(list1[0], list2[0]));
        possible_matchings.push_back(matching);
        return possible_matchings;
    } else {
        int firstIndex = list1[0];
        for (int i = 0; i < list2.size(); i++) {
            int secondIndex = list2[i];

            std::vector<int> list1_remaining = std::vector<int>(list1.begin() + 1, list1.end());
            std::vector<int> list2_remaining = std::vector<int>(list2);
            list2_remaining.erase(list2_remaining.begin() + i);
            std::vector<std::vector<std::pair<int, int>>> remaining_matchings = generateAllPossibleMatchingIndexes(list1_remaining, list2_remaining);

            for (int i = 0; i < remaining_matchings.size(); i++) {
                remaining_matchings[i].push_back(std::pair<int, int>(firstIndex, secondIndex));
            }
            possible_matchings.insert(possible_matchings.end(), remaining_matchings.begin(), remaining_matchings.end());
        } 
    }

    return possible_matchings;
}

// function that generates all possible matchings given two lists of clusters
std::vector<Matching> generateAllPossibleMatchings(std::vector<Cluster>& list1, std::vector<Cluster>& list2) {
    std::vector<int> list1_indexes;
    std::vector<int> list2_indexes;

    for (int i = 0; i < list1.size(); i++) {
        list1_indexes.push_back(i);
    }
    for (int i = 0; i < list2.size(); i++) {
        list2_indexes.push_back(i);
    }

    std::vector<std::vector<std::pair<int, int>>> matching_indexes = generateAllPossibleMatchingIndexes(list1_indexes, list2_indexes);

    std::vector<Matching> matchings;

    for (auto matching_index : matching_indexes) {
        Matching m = Matching(list1, list2, matching_index);
        matchings.push_back(m);
    }

    return matchings;

}

// given two lists of clusters, returns the minimum distance matching between them. A matching is returned as a list of pairs of clusters.
Matching getClosestMatching(std::vector<Cluster> &list1, std::vector<Cluster> &list2) {
    
    // first, generate all possible matchings
    std::vector<Matching> matchings = generateAllPossibleMatchings(list1, list2);

    //find the matching with the lowest distance
    int minDist = INT_MAX;
    int bestMatch;

    for (int i = 0; i < matchings.size(); i++) {
        int dist = matchings[i].calculateDistance();
        if (dist < minDist) {
            minDist = dist;
            bestMatch = i;
        }
    }

    return matchings[bestMatch];
}