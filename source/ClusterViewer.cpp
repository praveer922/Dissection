#include "ClusterViewer.h"
#include <iostream>

Window::Window(int originX, int originY, int width, int height) {
	this->originX = originX;
	this->originY = originY;
	this->width = width;
	this->height = height;
}

void Window::addCluster(Cluster cluster) {
	clusters.push_back(cluster);
}

ClusterViewer::ClusterViewer() {
}

void ClusterViewer::addWindow(Window window) {
	windows.push_back(window);
}

void ClusterViewer::launch() {
	// set up views
	Window* firstWindow = &(windows[0]);
	viewer.core().viewport = Eigen::Vector4f(firstWindow->originX, firstWindow->originY, firstWindow->width, firstWindow->height);
	for (int i = 1; i < windows.size(); i++) {
		viewer.append_core(Eigen::Vector4f(windows[i].originX, windows[i].originY, windows[i].width, windows[i].height), true);
	}

	// set mesh data
	for (int i = 0; i < windows.size(); i++) {
		for (int j = 0; j < windows[i].clusters.size(); j++) {
			// first generate render mesh for this cluster
			Cluster* cluster = &(windows[i].clusters[j]);
			cluster->generateRenderMeshes();

			// then set mesh data in the viewer
			cluster->viewer_mesh_id = viewer.append_mesh(false);
			viewer.data().set_mesh(cluster->V, cluster->F);
			viewer.data().set_colors(cluster->C);
		}
	}

	// set visibility of meshes in each window
	for (int i = 0; i < windows.size(); i++) {
		int window_id = viewer.core_list[i].id;
		for (int j = 0; j < windows[i].clusters.size(); j++) {
			viewer.data(windows[i].clusters[j].viewer_mesh_id).set_visible(true, window_id);
		}

	}

	//launch 
	viewer.launch(false, false, "Geometric Dissection", 800, 800);

}