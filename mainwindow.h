#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QImage>
#include "videosurface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString filename;
    QImage now;
    QMediaPlayer *mediaPlayer;
    VideoSurface *videoSurface;

    int flag;

    void to_gray();

    void to_bigger();

    void to_smaller();

    void to_erzhi();

    void to_junzhi();

    void to_ma();

    void solve(QImage *);

    void showTime();
public slots:
    void ProcessFrame(QVideoFrame &frame);
private slots:
    void on_action_N_triggered();

    void on_actionPlay_icon_triggered();

    void on_actionPause_icon_triggered();

    void on_actionOpen_file_icon_triggered();

    void on_toolButton_play_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_video_slider_actionTriggered(int action);

    void on_verticalSlider_sliderPressed();

    void on_actionTo_pic_mode_triggered();

    void on_action_Q_triggered();

    void on_actionVedio_reset_triggered();

    void on_actionBe_big_triggered();

    void on_actionBe_small_triggered();

    void on_actionErzhihua_triggered();

    void on_actionGet_pic_triggered();

    void on_action_triggered();

    void on_actionMa_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
