#include "camera_handler.h"

cv::VideoCapture cap;

std::string gstreamer_pipeline(int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) 
{
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

void open_camera()
{
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 30 ;
    int flip_method = 2 ;

    std::string pipeline = gstreamer_pipeline(capture_width,
                                            capture_height,
                                            display_width,
                                            display_height,
                                            framerate,
                                            flip_method);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";
 
    cap.open(pipeline, cv::CAP_GSTREAMER);
    if(!cap.isOpened()) 
    {
        std::cout << "Failed to open camera." << std::endl;
        return;
    }
}

void grab_cameraFrames(cv::Mat& frame)
{
    if (!cap.isOpened())
    {
        std::cout << "Camera is not opened." << std::endl;
        return;
    }

    cap.read(frame);
}

void display_cameraFeed(const cv::Mat& frame)
{
    if (!frame.empty())
    {
        cv::imshow("CSI Camera", frame);
    }
    else
    {
        std::cout << "Frame is empty." << std::endl;
    }
}