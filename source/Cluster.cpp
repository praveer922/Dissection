#include "Cluster.h"

Cluster::Cluster() {
}

void Cluster::generateRenderMeshes() {
    // render each pixel as two triangles that make up a square
    // so this generates 4 points and 2 faces for each pixel

    V = Eigen::MatrixXd(pixels.size() * 4, 2);
    F = Eigen::MatrixXi(pixels.size() * 2, 3);

    int Vrow = 0;
    int Frow = 0;
    for (auto pixel : pixels) {
        V.row(Vrow) << pixel.first - 0.5, pixel.second - 0.5;
        V.row(Vrow + 1) << pixel.first - 0.5, pixel.second + 0.5;
        V.row(Vrow + 2) << pixel.first + 0.5, pixel.second + 0.5;
        V.row(Vrow + 3) << pixel.first + 0.5, pixel.second - 0.5;

        F.row(Frow) << Vrow, Vrow + 1, Vrow + 2;
        F.row(Frow + 1) << Vrow, Vrow + 3, Vrow + 2;

        Vrow += 4;
        Frow += 2;
    }
}