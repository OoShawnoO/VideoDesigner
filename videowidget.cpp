#include "videowidget.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cstring>
#include <QPainter>

VideoWidget::VideoWidget(QWidget* p) : QOpenGLWidget(p)
{

}

void VideoWidget::paintEvent(QPaintEvent *e)
{
    QPainter p;
    p.begin(this);
    p.drawImage(QPoint(0,0),image);
    p.end();
}

void VideoWidget::setImage(cv::Mat mat)
{
    if(image.isNull())
    {
        uchar* buf = new uchar[width() * height() * 3];
        image = QImage(buf,width(),height(),QImage::Format_RGB888);
    }
    cv::Mat dest;
    cv::resize(mat,dest,cv::Size(image.size().width(),image.size().height()));
    cv::cvtColor(dest,dest,cv::COLOR_BGR2RGB);
    memcpy(image.bits(),dest.data,dest.cols * dest.rows * dest.elemSize());
    update();
}
