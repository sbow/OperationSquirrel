#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
    // Create an empty image (width=800, height=600) with a white background
    cv::Mat image(600, 800, CV_8UC3, cv::Scalar(255, 255, 255));

    // Set the text to draw
    std::string text = "Hello, World!";

    // Set the position where the text will be drawn
    cv::Point textOrg(100, 300);

    // Choose the font
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;

    // Set the font scale and color
    double fontScale = 2;
    cv::Scalar color(0, 0, 0); // Black text

    // Set the thickness and line type
    int thickness = 2;
    int lineType = cv::LINE_AA;

    // Draw the text on the image
    cv::putText(image, text, textOrg, fontFace, fontScale, color, thickness, lineType);

    // Save the image as a PNG file
    cv::imwrite("hello_world.png", image);

    return 0;
}