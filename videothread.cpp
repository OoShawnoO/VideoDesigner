#include "videothread.h"
#include "videofilter.h"


using namespace cv;

static bool is_exit = false;
static VideoCapture capture_1;

bool VideoThread::open(const std::string file)
{
    mutex.lock();
    if(!capture_1.open(file))
    {
        mutex.unlock();
        return false;
    }
    fps = capture_1.get(CAP_PROP_FPS);
    if(fps == 0)
    {
        fps = 25;
    }
    mutex.unlock();
    return true;
}

VideoThread::VideoThread()
{
    start();
}

void VideoThread::run()
{
    Mat mat_1,mat_2;
    while(true)
    {   mutex.lock();
        if(is_exit)
        {
            mutex.unlock();
            break;
        }
        if(!capture_1.isOpened())
        {
            mutex.unlock();
            msleep(5);
            continue;
        }
        if(is_stop && !is_write)
        {
            mutex.unlock();
            msleep(5);
            continue;
        }
        if(!capture_1.read(mat_1) || mat_1.empty())
        {
            mutex.unlock();
            if(is_write) {
                stop_save();
                emit save_end();
            }
            msleep(5);
            continue;
        }
        mat_2 = VideoFilter::get()->filter(mat_1,cv::Mat());

        int s = 1000/fps;
        if(is_write)
        {
            writer.write(mat_2);
            s = 1;
        }
        else
        {
            emit viewImage_1(mat_1);
            emit viewImage_2(mat_2);
        }
        msleep(s);
        mutex.unlock();


    }
}

VideoThread::~VideoThread()
{
    mutex.lock();
    is_exit = true;
    mutex.unlock();
    wait();
}

double VideoThread::pos()
{
    double pos = 0;
    mutex.lock();
    if(!capture_1.isOpened())
    {
        mutex.unlock();
        return 0;
    }
    double count = capture_1.get(CAP_PROP_FRAME_COUNT);
    double cur = capture_1.get(CAP_PROP_POS_FRAMES);
    if(count > 0.001)
    {
        pos = cur / count;
    }
    mutex.unlock();
    return pos;
}

bool VideoThread::seek(int frame)
{
    mutex.lock();
    if(!capture_1.isOpened())
    {
        mutex.unlock();
        return false;
    }
    bool ret = capture_1.set(CAP_PROP_POS_FRAMES,frame);
    mutex.unlock();
    return ret;
}

bool VideoThread::seek(double pos)
{
    double count = capture_1.get(CAP_PROP_FRAME_COUNT);
    int frame = pos * count;
    return seek(frame);
}

bool VideoThread::start_save(const std::string filename, int width, int height)
{
    seek(0.0);
    mutex.lock();
    is_write = true;
    if(width <=0 || height <=0)
    {
        width = capture_1.get(CAP_PROP_FRAME_WIDTH);
        height = capture_1.get(CAP_PROP_FRAME_HEIGHT);
    }

    if(!writer.open(filename,
                   VideoWriter::fourcc('X','2','6','4'),
                   fps,
                   {width,height}
                   ) || !writer.isOpened())
    {
        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}

void VideoThread::stop_save()
{
    mutex.lock();
    writer.release();
    is_write = false;
    mutex.unlock();
}

bool VideoThread::_start()
{
    mutex.lock();
    is_stop = false;
    mutex.unlock();
    return true;
}

bool VideoThread::_stop()
{
    mutex.lock();
    is_stop = true;
    mutex.unlock();
    return true;
}
