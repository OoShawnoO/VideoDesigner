#ifndef VIDEODEISGNERWINDOW_H
#define VIDEODEISGNERWINDOW_H

#include <QMainWindow>
#include <videothread.h>
#include <videowidget.h>
#include <opencv2/core.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class videoDesignerWindow; }
QT_END_NAMESPACE

class videoDesignerWindow : public QMainWindow
{
    Q_OBJECT

public:
    videoDesignerWindow(QWidget *parent = nullptr);
    ~videoDesignerWindow();

    void timerEvent(QTimerEvent* e);

private slots:
    void on_open_button_clicked();

    void on_close_button_clicked();

    void SliderPress();
    void SliderRelease();
    void SetPos(int frame);
    void Set();
    void Export();
    void Export_end();
    void Play();
private:
    Ui::videoDesignerWindow *ui;
    bool is_export = false;
};
#endif // VIDEODEISGNERWINDOW_H
