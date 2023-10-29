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
    cv::Mat noise = cv::Mat(imGray.size(),imGray.type());
    cv::randn(noise,mean,stddev);
    cv::Mat result;
    result = imGray + noise;
    return result;
}
