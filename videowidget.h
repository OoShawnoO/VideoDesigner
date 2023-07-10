#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QOpenGLWidget>
#include <opencv2/core.hpp>

class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
protected:
    QImage image;
public:
    VideoWidget(QWidget* p);
    void paintEvent(QPaintEvent* e);
public slots:
    void setImage(cv::Mat mat);
};

#endif // VIDEOWIDGET_H
