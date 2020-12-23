#include "solveimage.h"
#include "ui_solveimage.h"
#include "mainwindow.h"
#include <bits/stdc++.h>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QFileDialog>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QSlider>
#include <QMatrix>
#include <QMessageBox>
#include <QIcon>
#include <QTranslator>

using namespace std;

int dir[8][2]={{-1,0},{1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};

void solveImage::reset(){
    token = false;
    aft = origin;
    ui->light_slider->setSliderPosition(50);
    ui->compare_slider->setSliderPosition(50);
    ui->horizontalSlider->setSliderPosition(50);
    ui->horizontalSlider_2->setSliderPosition(50);
    ui->horizontalSlider_3->setSliderPosition(50);
    ui->horizontalSlider_4->setSliderPosition(50);
}

void solveImage::showpic(QImage *tbd){
    ui->label->setPixmap(QPixmap::fromImage(*tbd));
}

bool solveImage::in_bound(int x,int y,int x11,int y11){
    if(x < 0 || x >= x11) return false;
    if(y < 0 || y >= y11) return false;
    return true;
}

solveImage::solveImage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::solveImage)
{
    token = false;
    state = 0;
    m_PTranslator = new QTranslator(this);
    ui->setupUi(this);
//    ui->label_2->setText(tr("亮度:"));
//    ui->label_3->setText(tr("对比度:"));
//    ui->label_4->setText(tr("渐红:"));
//    ui->label_5->setText(tr("二值化:"));
//    ui->label_6->setText(tr("渐蓝:"));
//    ui->label_7->setText(tr("渐绿:"));
}

solveImage::~solveImage()
{
    delete ui;
}

void solveImage::on_action_N_triggered()
{
    if(!token) qsl = QFileDialog::getOpenFileNames(this,"打开文件","D:\\","JPG (*.jpg);;PNG(*.png);;ALL(*.*)");
    else token = false;
    if(qsl.size() > 0){
        QString qss = qsl.at(0);
        cur_idx = 0;
        origin.load(qss);
        aft = origin;
        ui->label->setPixmap(QPixmap::fromImage(origin));
        ui->label_now_pic->setText(QString("%1/%2").arg(1).arg(qsl.size()));
    }
}

void solveImage::on_actionOpen_file_triggered()
{
    on_action_N_triggered();
}


void solveImage::on_light_slider_sliderMoved(int position)
{
    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    int change = (position - 50) * 2;
    for(int i=0; i < origin.width(); ++i){
        for(int j=0; j < origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int r = qc.red()   + change;  r=max(r,0); r=min(r,255);
            int g = qc.green() + change;  g=max(g,0); g=min(g,255);
            int b = qc.blue()  + change;  b=max(b,0); b=min(b,255);
            now->setPixel(i,j,qRgb(r,g,b));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_actionReset_triggered()
{
    reset();
    ui->label->setPixmap(QPixmap::fromImage(origin));
}

void solveImage::on_action_triggered()
{
    QImage *now = new QImage(aft.width(),aft.height(),QImage::Format_ARGB32);
    for(int i=0; i<aft.width(); ++i){
        for(int j=0; j<aft.height(); ++j){
            QColor qc = QColor(aft.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue();
            for(int k=0; k<8; ++k){
                int ti=i+dir[k][0];
                int tj=j+dir[k][1];
                if(in_bound(ti,tj,aft.width(),aft.height())){
                    qc = QColor(aft.pixel(ti,tj));
                    sr += qc.red();
                    sg += qc.green();
                    sb += qc.blue();
                }
            }
            sr/=9; sg/=9; sb/=9;
            now->setPixel(i,j,qRgb(sr,sg,sb));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_action_w_triggered()
{
    QImage *now = new QImage(aft.width(),aft.height(),QImage::Format_ARGB32);
    for(int i=0; i<aft.width(); ++i){
        for(int j=0; j<aft.height(); ++j){
            QColor qc = QColor(aft.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue();
            bool flag = false;
            int gap = 50;
            for(int k=0; k<8; ++k){
                int ti = i + dir[k][0];
                int tj = j + dir[k][1];
                if(in_bound(ti,tj,aft.width(),aft.height())){
                    qc = QColor(aft.pixel(ti,tj));
                    if(abs(qc.red() - sr) > gap || abs(qc.green() - sg) > gap ||
                            abs(qc.blue() - sb) > gap) flag = true;
                }
            }
            if(flag) now->setPixel(i,j,qRgb(255,255,255));
            else now->setPixel(i,j,qRgb(0,0,0));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_action_e_triggered()
{
    QImage *now = new QImage(aft.width(),aft.height(),QImage::Format_ARGB32);
    for(int i=0; i<aft.width(); ++i){
        for(int j=0; j<aft.height(); ++j){
            QColor qc = QColor(aft.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue(),sum = (sr + sg + sb)/3;
            now->setPixel(i,j,qRgb(sum,sum,sum));
        }
    }
    showpic(now);
    aft=*now;
}


void solveImage::on_action_r_triggered()
{
    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    for(int i=0; i<origin.width(); ++i){
        for(int j=0; j<origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue(),sum = (sr + sg + sb)/3;
            if(sum<180) now->setPixel(i,j,qRgb(min(255,sr+80),min(255,sg+80),min(255,sb+80)));
            else        now->setPixel(i,j,qRgb(sr,sg,sb));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_compare_slider_sliderMoved(int position)
{
    int change = position-50;

    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    for(int i=0; i<origin.width(); ++i){
        for(int j=0; j<origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue(),sum = (sr + sg + sb)/3;
            if(sum>130) now->setPixel(i,j,qRgb(min(max(135,sr+change),255),min(max(135,sg+change),255),min(max(135,sb+change),255)));
            else        now->setPixel(i,j,qRgb(min(max(0,sr-change),120),min(max(0,sg-change),120),min(max(0,sb-change),120)));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_horizontalSlider_sliderMoved(int position)
{
    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    for(int i=0; i<origin.width(); ++i){
        for(int j=0; j<origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue(),sum = (sr + sg + sb)/3;
            if(sum<position+100) now->setPixel(i,j,qRgb(0,0,0));
            else now->setPixel(i,j,qRgb(255,255,255));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_horizontalSlider_2_actionTriggered(int action)
{

}

void solveImage::on_horizontalSlider_2_sliderMoved(int position)
{
    int change = position - 50;

    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    for(int i=0; i<origin.width(); ++i){
        for(int j=0; j<origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue();
            sr += change*2;
            sr = min(sr, 255);
            now->setPixel(i,j,qRgb(sr,sg,sb));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_horizontalSlider_3_sliderMoved(int position)
{
    int change = position - 50;

    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    for(int i=0; i<origin.width(); ++i){
        for(int j=0; j<origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue();
            sb += change*2;
            sb = min(sb, 255);
            now->setPixel(i,j,qRgb(sr,sg,sb));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_horizontalSlider_4_sliderMoved(int position)
{
    int change = position - 50;

    QImage *now = new QImage(origin.width(),origin.height(),QImage::Format_ARGB32);
    for(int i=0; i<origin.width(); ++i){
        for(int j=0; j<origin.height(); ++j){
            QColor qc = QColor(origin.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue();
            sg += change*2;
            sg = min(sg, 255);
            now->setPixel(i,j,qRgb(sr,sg,sb));
        }
    }
    showpic(now);
    aft=*now;
}

void solveImage::on_actionSave_image_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,"保存文件","D:\\","JPG (*.jpg);;PNG (*.png)");
    aft.save(path);
}

void solveImage::on_toolButton_clicked()
{
    QMatrix matrix;
    matrix.rotate(-90.0);
    aft = aft.transformed(matrix,Qt::FastTransformation);
    showpic(&aft);
}

void solveImage::on_toolButton_4_clicked()
{
    aft = aft.mirrored(false, true);
    showpic(&aft);
}

void solveImage::on_toolButton_6_clicked()
{
    aft = aft.mirrored(true, false);
    showpic(&aft);
}

void solveImage::on_toolButton_2_clicked()
{
    QMatrix matrix;
    matrix.rotate(90.0);
    aft = aft.transformed(matrix,Qt::FastTransformation);
    showpic(&aft);
}

void solveImage::on_toolButton_7_clicked()
{
    reset();
    showpic(&aft);
}

void solveImage::on_toolButton_3_clicked()
{
//    QStringList ql = QFileDialog::getOpenFileNames(this,"打开文件","D:\\","JPG (*.jpg);;PNG(*.png");
//    for(int i=0; i<ql.size(); ++i) qDebug() << ql.at(i);
    if(cur_idx > 0){
        --cur_idx;
        QString tmp = qsl.at(cur_idx);
        origin.load(tmp);
        aft = origin;
        showpic(&aft);
        ui->label_now_pic->setText(QString("%1/%2").arg(cur_idx+1).arg(qsl.size()));
    }
}

void solveImage::on_toolButton_5_clicked()
{
    if(cur_idx < qsl.size()-1){
        ++cur_idx;
        QString tmp = qsl.at(cur_idx);
        origin.load(tmp);
        aft = origin;
        showpic(&aft);
        ui->label_now_pic->setText(QString("%1/%2").arg(cur_idx+1).arg(qsl.size()));
    }
}

void solveImage::on_actionTo_vedio_mode_triggered()
{
    this->close();
    MainWindow *w = new MainWindow;
    w->show();
}

void solveImage::on_actionAbout_triggered()
{
    //QMessageBox::about tmp = QMessageBox::about(this,"作者信息","作者:zzy 2020-12-21");
    QMessageBox tmp;
    tmp.setWindowTitle("关于作者");
    tmp.setText("作者:zzy 2020-12-21");
    QPixmap tp(":/img/images/qq_smile.png");
    tmp.setIconPixmap(tp);
    tp.load(":/img/images/codeforces.png");
    tmp.setWindowIcon(QIcon(tp));
    tmp.exec();
}

void solveImage::on_light_slider_actionTriggered(int action)
{

}

void solveImage::on_actionChange_triggered()
{
    if(!state){
        m_PTranslator->load(":/te/resources/tr_en.qm");
        state = 1;
    } else{
        m_PTranslator->load(":/te/resources/tr_zh.qm");
        state = 0;
    }
    qApp->installTranslator(m_PTranslator);
    ui->retranslateUi(this);
}

void solveImage::on_toolButton_8_clicked()
{
    if(qsl.size()==1){
        qsl.removeAt(0);
        QPixmap tmp1(":/img/images/404.png");
        ui->label->setPixmap(tmp1);
        cur_idx=-1;
    } else{
        int to;
        cerr<<cur_idx<<' '<<qsl.size()<<endl;
        if(cur_idx+1 == qsl.size()) to=cur_idx-1;
        else to=cur_idx;
        qsl.removeAt(cur_idx);
        cur_idx=to;
        QImage tmp2; tmp2.load(qsl.at(cur_idx));
        ui->label->setPixmap(QPixmap::fromImage(tmp2));
    }
    ui->label_now_pic->setText(QString("%1/%2").arg(cur_idx+1).arg(qsl.size()));
}
