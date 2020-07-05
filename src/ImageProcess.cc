/*************************************************************************
*
*              Author: b51
*                Mail: b51live@gmail.com
*            FileName: ImageProcess.cc
*
*          Created On: Thu Jul  2 22:51:06 2020
*     Licensed under The MIT License [see LICENSE for details]
*
************************************************************************/

#include "ImageProcess.h"

// Class constructor function
ImageProcess::ImageProcess() {}

// Class deconstructor function
ImageProcess::~ImageProcess() {}

// & symbol use variable as reference
void ImageProcess::DetectBall(const cv::Mat& image, BCircle& bcircle) {
  // get ball center pixel position and ball radius
  /* bcircle.x = ?; */
  /* bcircle.y = ?; */
  /* bcircle.radius = ?; */
}

void ImageProcess::DrawBCircle(const cv::Mat& image, const BCircle& bcircle) {
  // Check circle first
  if (bcircle.x < 0 or bcircle.x > image.cols or
      bcircle.y < 0 or bcircle.y > image.rows) {
    std::cout << "Ball center should locate in picture" << std::endl;
    return;
  }
  if (bcircle.radius < 0) {
    std::cout << "Ball radius should grater than 0" << std::endl;
    return;
  }

  cv::Mat image_display = image.clone();
  cv::Point center = cv::Point(bcircle.x, bcircle.y);
  double radius = bcircle.radius;

  // draw a circle on image_display, reference
  // https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#circle
  cv::circle(image_display, center, radius, cv::Scalar(0, 255, 255), 1);
  cv::imshow("display", image_display);
  std::cout << "Press any key to quit" << std::endl;
  cv::waitKey(0);
}

void ImageProcess::DrawBBox(const cv::Mat& image, const BBox& bbox) {
  // Check bbox first
  if (bbox.x < 0 or bbox.x > image.cols or
      bbox.y < 0 or bbox.y > image.rows) {
    std::cout << "BBox should locate in picture" << std::endl;
    return;
  }
  if (bbox.w < 0 or bbox.h < 0) {
    std::cout << "BBox width and height should grater than 0" << std::endl;
    return;
  }
  cv::Mat image_display = image.clone();
  cv::Point up_left = cv::Point(bbox.x, bbox.y);
  cv::Point down_right = cv::Point(bbox.x + bbox.w, bbox.y + bbox.h);

  // cv::rectangle reference
  // https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#rectangle
  cv::rectangle(image_display, up_left, down_right, cv::Scalar(0, 255, 255), 1);
  cv::imshow("display", image_display);
  std::cout << "Press any key to quit" << std::endl;
  cv::waitKey(0);
}
