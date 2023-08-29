#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include "standard_libs.h"
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp> // Include CUDA module
#include <opencv2/cudawarping.hpp> // Include CUDA module
#include "detectNet.h"

extern cv::VideoCapture cap; // Declare the VideoCapture object

std::string gstreamer_pipeline(int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method);
void open_camera();
void grab_cameraFrames(cv::Mat& frame);
void process_frameWithCuda(cv::Mat& frame);
void display_cameraFeed(const cv::Mat& frame);

#endif // CAMERA_HANDLER_H
