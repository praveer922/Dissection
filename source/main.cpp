#include <igl/opengl/glfw/Viewer.h>
#include "Input.h"
#include "ClusterViewer.h"
#include "Dissection.h"
#include <iostream>

int main() {
    Input input1 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster1 = input1.rasterize();

    

    Input input2 = Input("input/pentagon.svg", 10, 10);
    Cluster cluster2 = input2.rasterize();



    //begin dissection algorithm
    std::vector<Cluster> seedfill_clusters1 = cluster1.randomSeedFill();
    std::vector<Cluster> seedfill_clusters2 = cluster2.randomSeedFill();

    Matching bestMatching = getClosestMatching(seedfill_clusters1, seedfill_clusters2);

    for (auto match : bestMatching.matching) {
        std::cout << "Match: " << match.first << "," << match.second << "\n";
    }


    // visualize results
    ClusterViewer clusterViewer;

    // input 1
    Window input1_window = Window(0, 400, 400, 400);
    cluster1.setColor(255, 255, 255);
    input1_window.addCluster(cluster1);
    clusterViewer.addWindow(input1_window);
    
    
    // input 2
    Window input2_window = Window(400, 400, 400, 400);
    cluster2.setColor(255, 255, 255);
    input2_window.addCluster(cluster2);
    clusterViewer.addWindow(input2_window);

    // input 1 seed fills
    Window seed1_window = Window(0, 0, 400, 400);
    seedfill_clusters1[0].setColor(255, 0, 0);
    seed1_window.addCluster(seedfill_clusters1[0]);
    seed1_window.addCluster(seedfill_clusters1[1]);
    clusterViewer.addWindow(seed1_window);

    // input 2 seed fills
    Window seed2_window = Window(400, 0, 400, 400);
    seedfill_clusters2[0].setColor(255, 0, 0);
    seed2_window.addCluster(seedfill_clusters2[0]);
    seed2_window.addCluster(seedfill_clusters2[1]);
    clusterViewer.addWindow(seed2_window);

    clusterViewer.launch();

    return 0;
}