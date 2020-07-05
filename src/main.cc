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
  float ball_radius = 0.07; // ball radius = 7.0 cm
 
  // K: camera intrinsics
  Eigen::Matrix3d K;
  K << 490.0,   0.0, 480.0,
         0.0, 300.0, 273.5,
         0.0,   0.0,   1.0;

  // ball center position in camera coordinate
  /* float center_x = ?; */
  /* float center_y = ?; */
  /* float center_z = ?; */

  //----- Step 3: transform ball position from camera coordinate to robot coordinate -----//
  // R_rc, t_rc: camera in robot coordinate rotation matrix and translation
  Eigen::Matrix3d R_rc;
  Eigen::Vector3d t_rc;
  R_rc <<  0.0042244, 0.00280237, 0.999987,
           0.999979, 0.0048524, -0.004238,
           -0.004864, 0.99998, -0.0027818;
  
  t_rc << 0.05, 0.10, 0.20;

  // ball center position in robot coordinate
  /* float center_x = ?; */
  /* float center_y = ?; */
  /* float center_z = ?; */

  return 0;
}
