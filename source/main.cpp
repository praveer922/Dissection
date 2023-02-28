#include <igl/opengl/glfw/Viewer.h>
#include <vector>
#include "Input.h"

int main() {
    Input input1 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster1 = input1.rasterize();
    cluster1.generateRenderMeshes();

    Input input2 = Input("input/rectangle.svg", 10, 10);
    Cluster cluster2 = input2.rasterize();
    cluster2.generateRenderMeshes();


    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    
    // set up views
    viewer.core().viewport = Eigen::Vector4f(0, 0, 640, 800);
    int left_view = viewer.core_list[0].id;
    int right_view = viewer.append_core(Eigen::Vector4f(640, 0, 640, 800));

    // set mesh data
    viewer.data().set_mesh(cluster1.V, cluster1.F);
    viewer.append_mesh();
    viewer.data().set_mesh(cluster2.V, cluster2.F);
    int input1_id = viewer.data_list[0].id;
    int input2_id = viewer.data_list[1].id;

    viewer.data(input1_id).set_visible(false, left_view);
    viewer.data(input2_id).set_visible(false, right_view);

    viewer.launch();

    return 0;
}