#include "videodesignerwindow.h"
#include "./ui_videodesignerwindow.h"
#include <string>

#include <QFileDialog>
#include <QMessageBox>
#include <cstring>
#include <QDebug>
#include "videofilter.h"

static bool pressSlider = false;

videoDesignerWindow::videoDesignerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::videoDesignerWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    qRegisterMetaType<cv::Mat>("cv::Mat");
    QObject::connect(VideoThread::Get(),
                     SIGNAL(viewImage_1(cv::Mat)),
                     ui->video_1,
                     SLOT(setImage(cv::Mat))
                     );
    QObject::connect(VideoThread::Get(),
                     SIGNAL(viewImage_2(cv::Mat)),
                     ui->video_2,
                     SLOT(setImage(cv::Mat))
                     );
    QObject::connect(VideoThread::Get(),
                     SIGNAL(save_end()),
                     this,
                     SLOT(Export_end()));
   startTimer(40);
}

videoDesignerWindow::~videoDesignerWindow()
{
    delete ui;
}

void videoDesignerWindow::timerEvent(QTimerEvent *e)
{
    if(!pressSlider){
        double pos = VideoThread::Get()->pos();
        ui->video_1_slider->setValue(1000 * pos);
    }
}


void videoDesignerWindow::on_open_button_clicked()
{
    QString name = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("请选择视频文件"));
    if(name.isEmpty())
    {
        return;
    }
    std::string  s = name.toLocal8Bit().data();
    if(!VideoThread::Get()->open(s))
    {
        qDebug("123");
    }
    qDebug("456");
}



void videoDesignerWindow::on_close_button_clicked()
{
    close();
}

void videoDesignerWindow::SliderPress()
{
    pressSlider = true;
}

void videoDesignerWindow::SliderRelease()
{
    pressSlider = false;
}

void videoDesignerWindow::SetPos(int frame)
{
    VideoThread::Get()->seek((double)frame/1000.0);
}

void videoDesignerWindow::Set()
{
    VideoFilter::get()->clear();
    if(ui->bright->value() > 0 || ui->contrast->value() > 1)
    {
        VideoFilter::get()->add(Task{TASK_GAIN,{(double)ui->bright->value(),ui->contrast->value()}});
    }
    switch(ui->rotate_combo->currentIndex())
    {
    case 0 : {
        break;
    }
    case 1 : {
        VideoFilter::get()->add({TASK_ROTATE_90});
        break;
    }
    case 2 : {
        VideoFilter::get()->add({TASK_ROTATE_180});
        break;
    }
    case 3 : {
        VideoFilter::get()->add({TASK_ROTATE_270});
        break;
    }
    }
}

void videoDesignerWindow::Export()
{
    if(is_export)
    {
        VideoThread::Get()->stop_save();
        is_export = false;
        ui->_export->setText("导出");
        return;
    }
    QString name = QFileDialog::getSaveFileName(this,"save","out1.avi");
    if(name.isEmpty()) return;
    is_export = true;
    ui->_export->setText("停止导出");
    std::string filename = name.toLocal8Bit().data();
    VideoThread::Get()->start_save(filename);

}

void videoDesignerWindow::Export_end()
{
    is_export = false;
    ui->_export->setText("导出");
}

void videoDesignerWindow::Play()
{
    static bool is_play = false;
    if(is_play)
    {
        is_play = false;
        VideoThread::Get()->_stop();
        ui->play->setText("播放");
    }
    else
    {
        is_play = true;
        VideoThread::Get()->_start();
        ui->play->setText("暂停");
    }
}

