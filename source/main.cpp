#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/lunasvg.h"
#include "../include/stb_image_write.h"
#include <igl/cotmatrix.h>
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iostream>


using namespace lunasvg;

int main()
{
    auto document = Document::loadFromFile("input/pentagon.svg");

    if (!document) {
        std::cout << "could not load doc\n";
    }

    std::uint32_t width = 10, height = 10;

    auto bitmap = document->renderToBitmap(width, height);

    if (!bitmap.valid()) {
        std::cout << "bitmap not valid";
    }
    bitmap.convertToRGBA();

    std::cout << "rasterized to bitmap\n";

    std::cout << "Bitmap height: " << bitmap.height() << "\n";
    std::cout << "Bitmap width: " << bitmap.width() << "\n";
    std::cout << "Bitmap stride: " << bitmap.stride() << "\n";

    std::vector<float> xCoords;
    std::vector<float> yCoords;

    

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width * 4 + (j*4) + 3;
            if (bitmap.data()[index] >= 100) {
                xCoords.push_back(float(j));
                yCoords.push_back(float(height-i-1)); //flip y coordinate because bitmap format is flipped
            }
        }
    }


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


//for (int j = 3; j < width * 4; j += 4) {