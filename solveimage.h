#ifndef SOLVEIMAGE_H
#define SOLVEIMAGE_H

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class solveImage;
}

class solveImage : public QMainWindow
{
    Q_OBJECT

public:
    explicit solveImage(QWidget *parent = 0);
    QStringList qsl;
    int cur_idx;
    QString picname;
    QImage origin,aft;
    void showpic(QImage *);
    void reset();
    bool in_bound(int x,int y,int x11,int y11);
    bool token;
    int state;
    ~solveImage();

public slots:

    void on_action_N_triggered();

private slots:

    void on_actionOpen_file_triggered();

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_light_slider_sliderMoved(int position);

    void on_actionReset_triggered();

    void on_action_triggered();

    void on_action_w_triggered();

    void on_action_e_triggered();

  //  void on_pushButton_clicked();

    void on_action_r_triggered();

    void on_compare_slider_sliderMoved(int position);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_actionTriggered(int action);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_actionSave_image_triggered();

    void on_toolButton_clicked();

    //void on_toolButton_2_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_3_clicked();

    void on_actionTo_vedio_mode_triggered();

   // void on_actionAbout_me_triggered();

    void on_actionAbout_triggered();

    void on_light_slider_actionTriggered(int action);

    void on_actionChange_triggered();

    void on_toolButton_8_clicked();

private:
    Ui::solveImage *ui;

    QTranslator *m_PTranslator;
};

#endif // SOLVEIMAGE_H
