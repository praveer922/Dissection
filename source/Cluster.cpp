#include "Cluster.h"
#include <random>
#include <queue>
#include <iostream>
#include <vector>
#include <Eigen/Geometry> 


Cluster::Cluster(std::set<std::pair<int, int>> pixels) {
    this->pixels = pixels;
    this->pixelsAsMatrix = Eigen::MatrixXi(pixels.size(), 2);
    int row = 0;
    for (auto pixel : pixels) {
        this->pixelsAsMatrix.row(row) << pixel.first, pixel.second;
        row++;
    }
    setColor(255, 255, 255);
}

Cluster::Cluster(Eigen::MatrixXi pixelsAsMatrix) {
    this->pixelsAsMatrix = pixelsAsMatrix;
    for (int i = 0; i < pixelsAsMatrix.rows(); i++) {
        this->pixels.insert(std::pair<int, int>(pixelsAsMatrix.coeff(i, 0), pixelsAsMatrix.coeff(i, 1)));
    }
    setColor(255, 255, 255);
}

void Cluster::setColor(int r, int g, int b) {
    C = Eigen::MatrixXd(pixels.size() * 2, 3);
    for (int i = 0; i < pixels.size() * 2; i++) {
        C.row(i) << r, g, b;
    }
}

void Cluster::generateRenderMeshes() {
    // render each pixel as two triangles that make up a square
    // so this generates 4 points and 2 faces for each pixel

    V = Eigen::MatrixXd(pixels.size() * 4, 2);
    V1 = Eigen::MatrixXd(pixels.size(), 2);
    V2 = Eigen::MatrixXd(pixels.size(), 2);
    V3 = Eigen::MatrixXd(pixels.size(), 2);
    V4 = Eigen::MatrixXd(pixels.size(), 2);
    F = Eigen::MatrixXi(pixels.size() * 2, 3);

    int Vrow = 0;
    int Virow = 0;
    int Frow = 0;
    for (auto pixel : pixels) {
        V.row(Vrow) << pixel.first - 0.5, pixel.second - 0.5;
        V1.row(Virow) << pixel.first - 0.5, pixel.second - 0.5;

        V.row(Vrow + 1) << pixel.first - 0.5, pixel.second + 0.5;
        V2.row(Virow) << pixel.first - 0.5, pixel.second + 0.5;

        V.row(Vrow + 2) << pixel.first + 0.5, pixel.second + 0.5;
        V3.row(Virow) << pixel.first + 0.5, pixel.second + 0.5;

        V.row(Vrow + 3) << pixel.first + 0.5, pixel.second - 0.5;
        V4.row(Virow) << pixel.first + 0.5, pixel.second - 0.5;

        F.row(Frow) << Vrow, Vrow + 1, Vrow + 2;
        F.row(Frow + 1) << Vrow, Vrow + 3, Vrow + 2;

        Vrow += 4;
        Virow++;
        Frow += 2;
    }
}

// generates two clusters from the given cluster and returns them in a list
std::vector<Cluster> Cluster::randomSeedFill() {
    // step 1: choose two random seeds
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, pixels.size()); // define the range

    int random_seed1 = distr(gen);
    int random_seed2 = distr(gen);
    while (random_seed2 == random_seed1) { // make sure second seed isn't same as first
        random_seed2 = distr(gen);
    }
    std::pair<int,int> seed_pixel1 = *std::next(pixels.begin(), random_seed1);
    std::pair<int,int> seed_pixel2 = *std::next(pixels.begin(), random_seed2);


    // begin flood-fill using queue 
    std::set<std::pair<int, int>> A_pixels;
    std::set<std::pair<int, int>> B_pixels;

    std::queue<std::pair<int,int>> q1;
    std::queue<std::pair<int, int>> q2;
    q1.push(seed_pixel1);
    q2.push(seed_pixel2);
    while (true) {
        if (q1.size() != 0) {
            std::pair<int, int> px = q1.front();
            q1.pop();
            if (this->pixels.count(px) == 1 && A_pixels.count(px) == 0 && B_pixels.count(px) == 0) { 
                // this condition ensures the current pixel is in the input shape + not already included + not in the other cluster
                A_pixels.insert(px);
                q1.push(std::pair<int, int>(px.first + 1, px.second));
                q1.push(std::pair<int, int>(px.first - 1, px.second));
                q1.push(std::pair<int, int>(px.first, px.second + 1));
                q1.push(std::pair<int, int>(px.first, px.second - 1));
            }

        } 
        
        if (q2.size() != 0) {
            std::pair<int, int> px = q2.front();
            q2.pop();
            if (this->pixels.count(px) == 1 && B_pixels.count(px) == 0 && A_pixels.count(px) == 0) { 
                B_pixels.insert(px);
                q2.push(std::pair<int, int>(px.first + 1, px.second));
                q2.push(std::pair<int, int>(px.first - 1, px.second));
                q2.push(std::pair<int, int>(px.first, px.second + 1));
                q2.push(std::pair<int, int>(px.first, px.second - 1));
            }
        }

        if (q1.size() == 0 && q2.size() == 0) {
            break;
        }
    }

    Cluster A = Cluster(A_pixels);
    Cluster B = Cluster(B_pixels);

    std::vector<Cluster> seeds;
    seeds.push_back(A);
    seeds.push_back(B);

    return seeds;
}

std::pair<int, int> Cluster::getBoundingBoxCenter() {
    int maxY = 0;
    int minY = 10;
    int maxX = 0;
    int minX = 10;

    for (auto pixel : pixels) {
        if (pixel.first > maxX) {
            maxX = pixel.first;
        }

        if (pixel.first < minX) {
            minX = pixel.first;
        }

        if (pixel.second > maxY) {
            maxY = pixel.second;
        }

        if (pixel.second < minY) {
            minY = pixel.second;
        }
    }

    int height = maxY - minY + 1;
    int width = maxX - minX + 1;

    return std::pair<int, int>(minX+(width/2), minY+(height/2));
}

Cluster Cluster::translateToCenterOfOtherCluster(Cluster& otherCluster) {
    std::pair<int, int> center = getBoundingBoxCenter();
    std::pair<int, int> otherCenter = otherCluster.getBoundingBoxCenter();

    Eigen::Vector2i translation;
    translation << otherCenter.first - center.first, otherCenter.second - center.second;


    Eigen::MatrixXi translated_pixels = pixelsAsMatrix.rowwise() + translation.transpose();
    return Cluster(translated_pixels);
}

Cluster Cluster::translateToOrigin() {
    std::pair<int, int> center = getBoundingBoxCenter();
    Eigen::Vector2i translation;
    translation << -center.first, -center.second;

    Eigen::MatrixXi translated_pixels = pixelsAsMatrix.rowwise() + translation.transpose();
    return Cluster(translated_pixels);
}