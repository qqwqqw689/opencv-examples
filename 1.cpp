#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat GaussianNoise(char* image_path, double mean, double stddev);

int main()
{
    cv::Mat result = GaussianNoise("C:\\Users\\Lenovo\\projects\\opencvtest\\lenna.png", 125, 10);
    cv::imshow("OUTPUT",result);
    cv::waitKey(0);
    return 0;
}

cv::Mat GaussianNoise(char* image_path, double mean, double stddev)
{
    cv::Mat input = cv::imread(image_path);
    cv::Mat imGray;
    cv::cvtColor(input,imGray,cv::COLOR_BGR2GRAY);
    // COLOR_BGR2GRAY : convert between RGB/BGR and grayscale
    // int cv::Mat::type() const
    // Returns the type of a matrix element.
    // imGray.type() ： CV_8U
    // Each pixel in a CV_8U image is represented by a single byte
    // , which can store values from 0 to 255.
    cv::Mat noise = cv::Mat(imGray.size(),imGray.type());
    cv::randn(noise,mean,stddev);
    cv::Mat result;
    result = imGray + noise;
    return result;
}
