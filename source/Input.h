#pragma once
#ifndef INPUT_H
#define INPUT_H
#include "../include/lunasvg.h"
#include "Cluster.h"

using namespace lunasvg;

class Input {
private:
    std::string filepath;
    std::unique_ptr<Document> document;
    int width;
    int height;

public:
    Input(const std::string filepath, int width, int height);

    Cluster rasterize();

};

#endif