#include <opencv2/opencv.hpp>

cv::Mat GaussianNoise(char* image_path, double mean, double stddev);

int main()
{
    cv::Mat result = GaussianNoise("C:\\Users\\Lenovo\\projects\\opencvtest\\lenna.png", 0, 0.1);
    cv::imshow("OUTPUT",result);
    cv::waitKey(0);
    cv::medianBlur(result,result,3);
    // arithmetric mean filter
    cv::imshow("OUTPUT",result);
    cv::waitKey(0);
    return 0;
}

cv::Mat GaussianNoise(char* image_path, double mean, double stddev)
{
    cv::Mat input = cv::imread(image_path);
    cv::Mat imGray;
    cv::Mat result;
    cv::cvtColor(input,imGray,cv::COLOR_BGR2GRAY);
    // COLOR_BGR2GRAY : convert between RGB/BGR and grayscale
    // int cv::Mat::type() const
    // Returns the type of a matrix element.
    // imGray.type() ： CV_8U
    // Each pixel in a CV_8U image is represented by a single byte
    // , which can store values from 0 to 255.
    // CV_64F:
    // CV_ - this is just a prefix
    // 64 - number of bits per base matrix element
    // F - type of the base element.
    // F (float)
    // S (signed)
    // U (unsigned)
    cv::Mat noise = cv::Mat(imGray.size(),CV_64F);
    cv::normalize(imGray,result,0,1.0,cv::NORM_MINMAX,CV_64F);
    cv::randn(noise,mean,stddev);
    result = result + noise;
    cv::normalize(result,result,0,1.0,cv::NORM_MINMAX,CV_64F);
    result.convertTo(result, CV_8U, 255, 0);
    return result;
}
