#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>
#include <QMutex>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class VideoThread : public QThread
{
    Q_OBJECT;

    QMutex mutex;
    //打开一号视频源文件

protected:
    VideoThread();
    bool is_write = false;
    bool is_stop = true;
    cv::VideoWriter writer;
public:
    int fps;

    void run();
    static VideoThread* Get()
    {
        static VideoThread vthread;
        return &vthread;
    }
    bool open(const std::string file);
    ~VideoThread();
    double pos();
    bool seek(int frame);
    bool seek(double pos);
    bool start_save(const std::string filename,int width=0,int height=0);
    void stop_save();
    bool _start();
    bool _stop();
signals:
    void viewImage_1(cv::Mat mat);
    void viewImage_2(cv::Mat mat);
    void save_end();
};

#endif // VIDEOTHREAD_H
