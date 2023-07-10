#ifndef VIDEOFILTER_H
#define VIDEOFILTER_H

#include <opencv2/core.hpp>
#include <vector>
#include <imagepro.h>
#include <QMutex>
enum TaskType
{
    TASK_NONE,
    TASK_GAIN,
    TASK_ROTATE_90,
    TASK_ROTATE_180,
    TASK_ROTATE_270
};

struct Task
{
    TaskType type;
    std::vector<double> para;
};

class VideoFilter
{
public:
    VideoFilter();
    virtual ~VideoFilter();
    virtual void add(Task task) = 0;
    virtual cv::Mat filter(cv::Mat mat1,cv::Mat mat2) = 0;
    virtual void clear() = 0;
    static VideoFilter* get();

};

#endif // VIDEOFILTER_H
