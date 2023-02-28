#include <igl/cotmatrix.h>
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>
#include "Input.h"

int main() {
    Input input1 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster1 = input1.rasterize();

    std::vector<float> xCoords = std::vector<float>(cluster1.xCoords);
    std::vector<float> yCoords = std::vector<float>(cluster1.yCoords);


    Eigen::MatrixXd V(xCoords.size()*4, 2);
    Eigen::MatrixXi F(xCoords.size()*2, 3);

    int Vrow = 0;
    int Frow = 0;
    for (int i = 0; i < xCoords.size(); i++) {
        V.row(Vrow) << xCoords[i] - 0.5, yCoords[i] - 0.5;
        V.row(Vrow +1) << xCoords[i] - 0.5, yCoords[i] + 0.5;
        V.row(Vrow +2) << xCoords[i] + 0.5, yCoords[i] + 0.5;
        V.row(Vrow +3) << xCoords[i] + 0.5, yCoords[i] - 0.5;

        F.row(Frow) << Vrow, Vrow + 1, Vrow + 2;
        F.row(Frow+1) << Vrow, Vrow + 3, Vrow + 2;

        Vrow += 4;
        Frow += 2;
    }


    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    //viewer.data().set_face_based(true);
    viewer.launch();

    return 0;
}