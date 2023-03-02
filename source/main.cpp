#include <igl/opengl/glfw/Viewer.h>
#include <vector>
#include "Input.h"
#include <iostream>

int main() {
    Input input1 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster1 = input1.rasterize();
    cluster1.generateRenderMeshes();
    

    Input input2 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster2 = input2.rasterize();
    cluster2.generateRenderMeshes();

    //begin dissection algorithm
    std::pair<Cluster, Cluster> seedfill_clusters1 = cluster1.randomSeedFill();
    seedfill_clusters1.first.generateRenderMeshes();
    seedfill_clusters1.second.generateRenderMeshes();

    std::pair<Cluster, Cluster> seedfill_clusters2 = cluster2.randomSeedFill();
    seedfill_clusters2.first.generateRenderMeshes();
    seedfill_clusters2.second.generateRenderMeshes();


    // visualize results
    igl::opengl::glfw::Viewer viewer;
    
    // set up views
    viewer.core().viewport = Eigen::Vector4f(0, 400, 400, 400);
    int input1_view = viewer.core_list[0].id;
    int input2_view = viewer.append_core(Eigen::Vector4f(400, 400, 400, 400));
    int seedfill1_view = viewer.append_core(Eigen::Vector4f(0, 0, 400, 400));
    int seedfill2_view = viewer.append_core(Eigen::Vector4f(400, 0, 400, 400));

    // set mesh data
    // input 1
    viewer.data().set_mesh(cluster1.V, cluster1.F);
    cluster1.setColor(255, 255, 255);
    viewer.data().set_colors(cluster1.C);
    
    // input 2
    viewer.append_mesh();
    viewer.data().set_mesh(cluster2.V, cluster2.F);
    cluster2.setColor(255, 255, 255);
    viewer.data().set_colors(cluster2.C);
    
    // input 1 seed fills
    viewer.append_mesh();
    viewer.data().set_mesh(seedfill_clusters1.first.V, seedfill_clusters1.first.F);
    seedfill_clusters1.first.setColor(255, 255, 255);
    viewer.data().set_colors(seedfill_clusters1.first.C);
    viewer.append_mesh();
    viewer.data().set_mesh(seedfill_clusters1.second.V, seedfill_clusters1.second.F);

    //input 2 seed fills
    viewer.append_mesh();
    viewer.data().set_mesh(seedfill_clusters2.first.V, seedfill_clusters2.first.F);
    seedfill_clusters2.first.setColor(255, 255, 255);
    viewer.data().set_colors(seedfill_clusters2.first.C);
    viewer.append_mesh();
    viewer.data().set_mesh(seedfill_clusters2.second.V, seedfill_clusters2.second.F);


    int input1_id = viewer.data_list[0].id;
    int input2_id = viewer.data_list[1].id;
    int input1_seed1 = viewer.data_list[2].id;
    int input1_seed2 = viewer.data_list[3].id;
    int input2_seed1 = viewer.data_list[4].id;
    int input2_seed2 = viewer.data_list[5].id;

    //input 1 view
    viewer.data(input1_id).set_visible(true, input1_view);
    viewer.data(input2_id).set_visible(false, input1_view);
    viewer.data(input1_seed1).set_visible(false, input1_view);
    viewer.data(input1_seed2).set_visible(false, input1_view);
    viewer.data(input2_seed1).set_visible(false, input1_view);
    viewer.data(input2_seed2).set_visible(false, input1_view);
    
    //input 2 view
    viewer.data(input1_id).set_visible(false, input2_view);
    viewer.data(input2_id).set_visible(true, input2_view);
    viewer.data(input1_seed1).set_visible(false, input2_view);
    viewer.data(input1_seed2).set_visible(false, input2_view);
    viewer.data(input2_seed1).set_visible(false, input2_view);
    viewer.data(input2_seed2).set_visible(false, input2_view);

    // input1's seeds view
    viewer.data(input1_id).set_visible(false, seedfill1_view);
    viewer.data(input2_id).set_visible(false, seedfill1_view);
    viewer.data(input1_seed1).set_visible(true, seedfill1_view);
    viewer.data(input1_seed2).set_visible(true, seedfill1_view);
    viewer.data(input2_seed1).set_visible(false, seedfill1_view);
    viewer.data(input2_seed2).set_visible(false, seedfill1_view);

    // input2's seeds view
    viewer.data(input1_id).set_visible(false, seedfill2_view);
    viewer.data(input2_id).set_visible(false, seedfill2_view);
    viewer.data(input1_seed1).set_visible(false, seedfill2_view);
    viewer.data(input1_seed2).set_visible(false, seedfill2_view);
    viewer.data(input2_seed1).set_visible(true, seedfill2_view);
    viewer.data(input2_seed2).set_visible(true, seedfill2_view);

    viewer.launch(false, false, "Geometric Dissection", 800, 800);

    return 0;
}