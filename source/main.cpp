#include <igl/opengl/glfw/Viewer.h>
#include <vector>
#include "Input.h"

int main() {
    Input input1 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster1 = input1.rasterize();
    cluster1.generateRenderMeshes();


    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(cluster1.V, cluster1.F);
    viewer.launch();

    return 0;
}