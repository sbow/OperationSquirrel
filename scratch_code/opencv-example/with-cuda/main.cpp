#include "camera_handler.h"

int main()
{
    open_camera();

    cv::Mat cpuFrame;

    std::cout << "Hit ESC to exit" << "\n";

    std::cout << "CUDA device count: " << cv::cuda::getCudaEnabledDeviceCount() << std::endl;

    while (true)
    {
        grab_cameraFrames(cpuFrame);

        process_frameWithCuda(cpuFrame); // Process frame with CUDA

        display_cameraFeed(cpuFrame);

        int keycode = cv::waitKey(10) & 0xff;
        if (keycode == 27)
            break;
    }

    cv::destroyAllWindows();

    return 0;
}

