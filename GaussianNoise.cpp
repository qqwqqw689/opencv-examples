#include <opencv2/opencv.hpp>

cv::Mat GaussianNoise(char* image_path, double mean, double stddev);
cv::Mat SaltPepperNoise(char* image_path, double pa, double pb);

int main()
{
    cv::Mat result = SaltPepperNoise("C:\\Users\\Lenovo\\projects\\opencvtest\\lenna.png", 0.1, 0.1);
    cv::Mat result1;
    cv::Mat result2;
    cv::Mat result3;
    cv::imshow("OUTPUT",result);
    cv::waitKey(0);
    cv::medianBlur(result,result1,3);
    cv::imshow("OUTPUT",result1);
    cv::waitKey(0);
    cv::GaussianBlur(result,result2,cv::Size(3,3),0,0);
    cv::imshow("OUTPUT",result2);
    cv::waitKey(0);
    cv::bilateralFilter(result,result3,1,1,1);
    cv::imshow("OUTPUT",result3);
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


cv::Mat SaltPepperNoise(char* image_path, double pp, double ps)
{
    cv::RNG rng;
    cv::Mat input = cv::imread(image_path);
    cv::Mat imGray;
    cv::cvtColor(input,imGray,cv::COLOR_BGR2GRAY);
    int amount1=int(input.rows*input.cols*pp);
    int amount2=int(input.rows*input.cols*ps);
    for(int counter=0; counter<amount1; ++counter)
    {
        imGray.at<uchar>(rng.uniform( 0,imGray.rows), rng.uniform(0, imGray.cols)) =0;
    }
    for (int counter=0; counter<amount2; ++counter)
    {
        imGray.at<uchar>(rng.uniform( 0,imGray.rows), rng.uniform(0, imGray.cols)) = 255;
    }
    return imGray;
}
