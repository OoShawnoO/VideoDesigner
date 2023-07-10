#ifndef IMAGEPRO_H
#define IMAGEPRO_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

class ImagePro
{
public:
    ImagePro();
    void set(cv::Mat mat1,cv::Mat mat2);
    cv::Mat get() { return dest; }
    // bright 亮度 contrast 对比度
    ///@para bright double 亮度 0~100
    ///@para constrast double 对比度 1.0~3.0
    void gain(double bright,double contrast);

    void rotate90();
    void rotate180();
    void rotate270();

private:
    cv::Mat src1,src2;
    cv::Mat dest;
};

#endif // IMAGEPRO_H
