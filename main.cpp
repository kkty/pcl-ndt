#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/ndt.h>

#include <ctime>
#include <iostream>
#include <thread>

#define N 10

int main(int argc, char **argv) {
  if (argc != 3)
    return 1;

  pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(
      new pcl::PointCloud<pcl::PointXYZ>);

  if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *target_cloud) == -1) {
    return 1;
  }

  pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(
      new pcl::PointCloud<pcl::PointXYZ>);

  if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[2], *input_cloud) == -1) {
    return 1;
  }

  std::cerr << "target_size = " << target_cloud->size()
            << ", input_size = " << input_cloud->size() << std::endl;

  std::cout << "elapsed_init,elapsed_align,converged,score,iterations"
            << std::endl;

  for (int i = 0; i < N; i++) {
    double elapsed_init = 0, elapsed_align = 0;

    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;

    {
      clock_t begin = std::clock();
      ndt.setTransformationEpsilon(0.0001);
      ndt.setStepSize(0.1);
      ndt.setResolution(0.5);

      ndt.setMaximumIterations(50);

      ndt.setInputSource(input_cloud);
      ndt.setInputTarget(target_cloud);
      clock_t end = std::clock();
      elapsed_init = double(end - begin) / CLOCKS_PER_SEC;
    }

    // Set initial alignment estimate found using robot odometry.
    Eigen::AngleAxisf init_rotation(0.6931, Eigen::Vector3f::UnitZ());
    Eigen::Translation3f init_translation(1.79387, 0.720047, 0);
    Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();

    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(
        new pcl::PointCloud<pcl::PointXYZ>);

    {
      clock_t begin = std::clock();
      ndt.align(*output_cloud, init_guess);
      clock_t end = std::clock();
      elapsed_align = double(end - begin) / CLOCKS_PER_SEC;
    }

    std::cout << elapsed_init << "," << elapsed_align << ","
              << ndt.hasConverged() << "," << ndt.getFitnessScore() << ","
              << ndt.getFinalNumIteration() << std::endl;
  }

  return 0;
}
