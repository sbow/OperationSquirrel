#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include "standard_libs.h"
#include <opencv2/opencv.hpp>

std::string gstreamer_pipeline(int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method);
void openCamera(void);
void displayCameraFeed(const cv::Mat& frame);
void grabCameraFrames(cv::Mat& frame);

#endif // CAMERA_HANDLER_H
