#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/lunasvg.h"
#include "../include/stb_image_write.h"
#include "../include/igl/cotmatrix.h"
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

    std::cout << "rasterized bitmap\n";

    std::cout << "Bitmap height: " << bitmap.height() << "\n";
    std::cout << "Bitmap width: " << bitmap.width() << "\n";
    std::cout << "Bitmap stride: " << bitmap.stride() << "\n";

    Eigen::MatrixXi V(100, 2);
    int row = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width * 4 + (j*4) + 3;
            if (bitmap.data()[index] >= 100) {
                std::cout << ".";
                V.row(row) << j, i;
                row++;
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    stbi_write_png("output.png", int(bitmap.width()), int(bitmap.height()), 4, bitmap.data(), 0);


    Eigen::MatrixXi F(2, 3);
    F << 0, 1, 2,
        0, 2, 3;
    std::cout << "Hello, mesh: " << std::endl << V<< std::endl;

    return 0;
}


//for (int j = 3; j < width * 4; j += 4) {