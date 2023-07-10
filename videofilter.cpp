#include "videofilter.h"


class CXVideoFilter : public VideoFilter
{
public:
    std::vector<Task> tasks;
    QMutex mutex;

    CXVideoFilter(){}
    ~CXVideoFilter(){}
    void add(Task task)
    {
        mutex.lock();
        tasks.push_back(task);
        mutex.unlock();
    }
    cv::Mat filter(cv::Mat mat1,cv::Mat mat2)
    {
        mutex.lock();
        ImagePro p;
        p.set(mat1,mat2);
        int size = tasks.size();
        for(int i=0;i<size;i++)
        {
            switch(tasks[i].type)
            {
            case TASK_GAIN : {
                p.gain(tasks[i].para[0],tasks[i].para[1]);
                break;
            }
            case TASK_ROTATE_90 :{
                p.rotate90();
                break;
            }
            case TASK_ROTATE_180 : {
                p.rotate180();
                break;
            }
            case TASK_ROTATE_270 : {
                p.rotate270();
                break;
            }
            default : {
                break;
            }
            }
        }
        cv::Mat ret = p.get();
        mutex.unlock();
        return ret;
    }
    void clear()
    {
        mutex.lock();
        tasks.clear();
        mutex.unlock();
    }
};

VideoFilter::VideoFilter()
{

}

VideoFilter::~VideoFilter()
{

}

VideoFilter *VideoFilter::get()
{
    static CXVideoFilter f;
    return &f;
}
