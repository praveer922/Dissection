#include "Cluster.h"

Cluster::Cluster() {
}

void Cluster::generateRenderMeshes()
{
    V = Eigen::MatrixXd(xCoords.size() * 4, 2);
    F = Eigen::MatrixXi(xCoords.size() * 2, 3);

    int Vrow = 0;
    int Frow = 0;
    for (int i = 0; i < xCoords.size(); i++) {
        V.row(Vrow) << xCoords[i] - 0.5, yCoords[i] - 0.5;
        V.row(Vrow + 1) << xCoords[i] - 0.5, yCoords[i] + 0.5;
        V.row(Vrow + 2) << xCoords[i] + 0.5, yCoords[i] + 0.5;
        V.row(Vrow + 3) << xCoords[i] + 0.5, yCoords[i] - 0.5;

        F.row(Frow) << Vrow, Vrow + 1, Vrow + 2;
        F.row(Frow + 1) << Vrow, Vrow + 3, Vrow + 2;

        Vrow += 4;
        Frow += 2;
    }
}