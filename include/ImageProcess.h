/*************************************************************************
 *
 *              Author: b51
 *                Mail: b51live@gmail.com
 *            FileName: ImageProcess.h
 *
 *          Created On: Thu Jul  2 22:37:11 2020
 *     Licensed under The MIT License [see LICENSE for details]
 *
 ************************************************************************/

#ifndef TASK_01_IMAGE_PROCESS_H_
#define TASK_01_IMAGE_PROCESS_H_

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

// Bounding circle for detected ball
struct BCircle {
  public:
   BCircle() : x(-1), y(-1), radius(-1.) {}
   float x;  // bounding circle center pixel position at column
   float y;  // bounding circle center pixel position at row
   float radius; // circle radius in pixel
};

// Bounding box for detected object
struct BBox {
  public:
   BBox() : x(-1), y(-1), w(-1), h(-1) {}
   int x;  // bounding box up_left pixel position at column
   int y;  // bounding box up_left pixel position at row
   int w;  // bounding box width
   int h;  // bounding box height
};

class ImageProcess {
 public:
  ImageProcess();
  ~ImageProcess();

  /**
   *  Detect ball in a give image
   *  @param image Input image
   *  @param bcircle Bounding circle of detected ball
   */
  void DetectBall(const cv::Mat& image, BCircle& bcircle);

  /**
   *  Draw bounding box on a give image and display it
   *  @param image Image to display
   *  @param bcircle Bounding circle of detected ball
   */
  void DrawBCircle(const cv::Mat& image, const BCircle& bcircle);

  /**
   *  Draw bounding box on a give image and display it
   *  @param image Image to display
   *  @param bbox Bounding box of detected ball
   */
  void DrawBBox(const cv::Mat& image, const BBox& bbox);

 private:
  cv::Mat image_;
};

#endif
