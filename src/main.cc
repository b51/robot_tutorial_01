/*************************************************************************
 *
 *              Author: b51
 *                Mail: b51live@gmail.com
 *            FileName: main.cc
 *
 *          Created On: Thu Jul  2 22:31:30 2020
 *     Licensed under The MIT License [see LICENSE for details]
 *
 ************************************************************************/

#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/opencv.hpp>

#include "ImageProcess.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " [image path]" << std::endl;
    return -1;
  }

  //----- Step 1: Detect ball and draw it on image -----//
  std::string image_file_path(argv[1]);
  cv::Mat image = cv::imread(image_file_path);
  int width = image.cols;
  int height = image.rows;

  std::cout << "image width: " << width
            << ", height: " << height << std::endl;

  ImageProcess image_process;

  // detect ball and fill in the bcircle
  BCircle bcircle;
  image_process.DetectBall(image, bcircle);

  std::cout << "circle center position: ("
            << bcircle.x << ", " << bcircle.y
            << "), circle radius: " << bcircle.radius
            << std::endl;

  image_process.DrawBCircle(image, bcircle);

  //----- Step 2: calculate ball center position in camera coordinate -----//
  double ball_radius = 0.07; // ball radius = 7.0 cm
 
  // K: camera intrinsics
  Eigen::Matrix3d K;
  K << 490.0,   0.0, 480.0,
         0.0, 300.0, 273.5,
         0.0,   0.0,   1.0;

  double Z = ball_radius * K(0, 0) / bcircle.radius;
  std::cout << Z << std::endl;

  double fu = K(0, 0);
  double fv = K(1, 1);
  double u0 = K(0, 2);
  double v0 = K(1, 2);

  double X = (bcircle.x - u0) * Z / fu;
  double Y = (bcircle.y - v0) * Z / fv;

  // P_cp: point in camera coordinate Pos
  Eigen::Vector3d P_cp = Eigen::Vector3d(X, Y, Z);
  /* std::cout << "P_cp: " << P_cp.transpose() << std::endl; */

  // ball center position in camera coordinate
  double P_cp_x = P_cp.x();
  double P_cp_y = P_cp.y();
  double P_cp_z = P_cp.z();
  std::cout << "ball center in robot coordinate: ("
            << P_cp_x << ", " << P_cp_y << ", " << P_cp_z << ")"
            << std::endl;

  //----- Step 3: transform ball position from camera coordinate to robot coordinate -----//
  // R_rc, t_rc: rotation and translation matrix of camera in robot coordinate 
  Eigen::Matrix3d R_rc;
  Eigen::Vector3d t_rc;
  R_rc <<  0.0042244, 0.00280237, 0.999987,
           0.999979, 0.0048524, -0.004238,
           -0.004864, 0.99998, -0.0027818;
  
  t_rc << 0.05, 0.10, 0.20;

  // P_rp: point in robot coordinate Pos
  Eigen::Vector3d P_rp = R_rc * P_cp + t_rc;
  /* std::cout << "P_rp: " << P_rp.transpose() << std::endl; */

  // ball center position in robot coordinate
  double P_rp_x = P_rp.x();
  double P_rp_y = P_rp.y();
  double P_rp_z = P_rp.z();
  std::cout << "ball center in robot coordinate: ("
            << P_rp_x << ", " << P_rp_y << ", " << P_rp_z << ")"
            << std::endl;

  return 0;
}
