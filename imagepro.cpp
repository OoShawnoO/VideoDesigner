#include "imagepro.h"

using namespace cv;

ImagePro::ImagePro()
{

}

void ImagePro::set(cv::Mat mat1, cv::Mat mat2)
{
    if(mat1.empty()) return;
    src1 = mat1;
    src2 = mat2;
    src1.copyTo(dest);

}

void ImagePro::gain(double bright, double contrast)
{
    if(dest.empty()) return;
    dest.convertTo(dest,-1,contrast,bright);
}

void ImagePro::rotate90()
{
    if(dest.empty()) return;
    rotate(dest,dest,ROTATE_90_CLOCKWISE);
}

void ImagePro::rotate180()
{
    if(dest.empty()) return;
    rotate(dest,dest,ROTATE_180);
}

void ImagePro::rotate270()
{
    if(dest.empty()) return;
    rotate(dest,dest,ROTATE_90_COUNTERCLOCKWISE);
}
