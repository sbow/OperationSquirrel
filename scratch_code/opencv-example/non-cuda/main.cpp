#include "camera_handler.h"

int main()
{
    open_camera();

    cv::Mat frame;

    std::cout << "Hit ESC to exit" << "\n";
    while (true)
    {
        grab_cameraFrames(frame);
        
        display_cameraFeed(frame);

        int keycode = cv::waitKey(10) & 0xff;
        if (keycode == 27)
            break;
    }

    cv::destroyAllWindows();

    return 0;
}
