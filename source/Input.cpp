#include "Input.h"
#include <iostream>

Input::Input(const std::string filepath, int width, int height) {
    this->filepath = filepath;
    this->width = width;
    this->height = height;
    this->document = Document::loadFromFile(filepath);
    if (!document) {
        std::cout << "could not load doc\n";
    }
}


Cluster Input::rasterize() {
    auto bitmap = document->renderToBitmap(width, height);
    if (!bitmap.valid()) {
        std::cout << "bitmap not valid";
    }
    else {
        std::cout << "Rasterized " << filepath << " to bitmap\n";
    }
    
    bitmap.convertToRGBA();

    Cluster cluster = Cluster();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width * 4 + (j * 4) + 3;
            if (bitmap.data()[index] >= 100) {
                cluster.pixels.insert(std::pair(j, height - i - 1)); //flip y coordinate because bitmap format is flipped
            }
        }
    }

    return cluster;
}