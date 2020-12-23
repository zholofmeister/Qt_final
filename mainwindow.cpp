#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videosurface.h"
#include "solveimage.h"

#include <bits/stdc++.h>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QFileDialog>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QSlider>

using namespace std;

bool exec = true,esub = true,eadd = true;
int todo = 0;
int cnt = 0, add = 0, sub = 0;
int kk = 0;
set<int> st;
int di[8][2] = {{-1,0},{1,0},{0,1},{0,-1},{-1,-1},{1,1},{-1,1},{1,-1}};

bool in_bound(int x,int y,int x11,int y11){
    if(x < 0 || x >= x11) return false;
    if(y < 0 || y >= y11) return false;
    return true;
}

void MainWindow::showTime(){
    qint64 sum=mediaPlayer->duration();
    qint64 now=mediaPlayer->position();
    sum/=1000; now/=1000;
    int ah=sum/3600, am=(sum-ah*3600)/60, as=sum-ah*3600-am*60;
    int bh=now/3600, bm=(now-bh*3600)/60, bs=now-bh*3600-bm*60;
    ui->time_label->setText(QString("%1:%2:%3/%4:%5:%6").arg(bh).arg(bm).arg(bs).arg(ah).arg(am).arg(as));
}

void MainWindow::to_ma(){
    for(int i=0; i<now.width(); i+=3){
        for(int j=0; j<now.height(); j+=3){
            QColor qc = QColor(now.pixel(i,j));
            int sr=qc.red(),sg=qc.green(),sb=qc.blue();
            if(i+1<now.width()) now.setPixel(i+1,j,qRgb(sr,sg,sb));
            if(i+2<now.width()) now.setPixel(i+2,j,qRgb(sr,sg,sb));
            if(j+1<now.height()) now.setPixel(i,j+1,qRgb(sr,sg,sb));
            if(j+2<now.height()) now.setPixel(i,j+2,qRgb(sr,sg,sb));
            if(i+1<now.width() && j+1<now.height()) now.setPixel(i+1,j+1,qRgb(sr,sg,sb));
            if(i+1<now.width() && j+2<now.height()) now.setPixel(i+1,j+2,qRgb(sr,sg,sb));
            if(i+2<now.width() && j+1<now.height()) now.setPixel(i+2,j+1,qRgb(sr,sg,sb));
            if(i+2<now.width() && j+2<now.height()) now.setPixel(i+2,j+2,qRgb(sr,sg,sb));
        }
    }
}

void MainWindow::to_junzhi(){
    for(int i=0; i<now.width(); ++i){
        for(int j=0; j<now.height(); ++j){
            QColor qc = QColor(now.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue();
            for(int k=0; k<8; ++k){
                int ti=i+di[k][0];
                int tj=j+di[k][1];
                if(in_bound(ti,tj,now.width(),now.height())){
                    qc = QColor(now.pixel(ti,tj));
                    sr += qc.red();
                    sg += qc.green();
                    sb += qc.blue();
                }
            }
            for(int o=0; o<todo; ++o) now.setPixel(i,j,qRgb(sr/9,sg/9,sb/9));
        }
    }
}

void MainWindow::to_gray(){
    for(int i=0; i<now.width(); ++i){
        for(int j=0; j<now.height(); ++j){
            QColor qc = QColor(now.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue(),sum = (sr + sg + sb)/3;
            now.setPixel(i,j,qRgb(sum,sum,sum));
        }
    }
}

void MainWindow::to_erzhi(){
    for(int i=0; i<now.width(); ++i){
        for(int j=0; j<now.height(); ++j){
            QColor qc = QColor(now.pixel(i,j));
            int sr = qc.red(),sg = qc.green(),sb = qc.blue(),sum = (sr + sg + sb)/3;
            if(sum>120) now.setPixel(i,j,qRgb(255,255,255));
            else now.setPixel(i,j,qRgb(0,0,0));
        }
    }
}

void MainWindow::to_bigger(){

    if(eadd){
        ++add;
        eadd = false;
    }
    int res = 40 * add - 40 * sub;
    now = now.scaled(now.width()+res, now.height()+res, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MainWindow::to_smaller(){
    if(esub){
        ++sub;
        esub = false;
    }
    int res = 40 * add - 40 * sub;
    now = now.scaled(now.width()+res, now.height()+res, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MainWindow::ProcessFrame(QVideoFrame &frame)
{
//    qDebug() << "=============ProcessFrame===============";
//    qDebug() << "width : " << frame.width() << " height : " << frame.height();
//    qDebug() << "start time : " << frame.startTime()/1000 << "ms";
//    qDebug() << "end time : " << frame.endTime()/1000 << "ms";
//    qDebug() << "pixelFormat :" << frame.pixelFormat();

    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage recvImage(frame.bits(), frame.width(), frame.height(), QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    now=recvImage;

    if(!cnt){
        if(st.find(1) != st.end()) to_gray();
        if(st.find(2) != st.end()) to_bigger();
        if(st.find(3) != st.end()) to_smaller();
        if(st.find(4) != st.end()) to_erzhi();
        if(st.find(5) != st.end()) to_junzhi();
        if(st.find(6) != st.end()) to_ma();

        ui->label->setPixmap(QPixmap::fromImage(now));

    }

    showTime();

    //++cnt;
    //if(cnt == 2) cnt = 0;
    //qDebug() << "frame data size :" << frame.mappedBytes();
    //frame.unmap();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flag = 0;
    mediaPlayer = new QMediaPlayer;
    videoSurface = new VideoSurface;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_N_triggered()
{
    filename = QFileDialog::getOpenFileName(this,"打开文件","D:\\", "mv (*.mp4 *.mp3 *.flv)");

    ui->volume_slider->setSliderPosition(99); //初始化音量最大

    mediaPlayer->setVideoOutput(videoSurface);
    mediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    mediaPlayer->play();

    connect(videoSurface, SIGNAL(frameAvailable(QVideoFrame &)), this, SLOT(ProcessFrame(QVideoFrame &)));

    connect(mediaPlayer,&QMediaPlayer::durationChanged,ui->video_slider,&QSlider::setMaximum);
    connect(ui->video_slider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setPosition);
    connect(mediaPlayer,&QMediaPlayer::positionChanged,ui->video_slider,&QSlider::setValue);

    connect(ui->volume_slider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setVolume);
    connect(mediaPlayer,&QMediaPlayer::volumeChanged,ui->volume_slider,&QSlider::setValue);


}

void MainWindow::on_actionOpen_file_icon_triggered()
{
    on_action_N_triggered();
}

void MainWindow::on_actionPlay_icon_triggered()
{

}

void MainWindow::on_actionPause_icon_triggered()
{
    mediaPlayer->pause();
}

void MainWindow::on_toolButton_play_clicked()
{
    if(mediaPlayer->state()==QMediaPlayer::PausedState){
        mediaPlayer->play();
        QImage tmp(":/img/images/pause.png");
        ui->toolButton_play->setIcon(QPixmap::fromImage(tmp));
    } else{
        mediaPlayer->pause();
        QImage tmp(":/img/images/play.png");
        ui->toolButton_play->setIcon(QPixmap::fromImage(tmp));
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

}

void MainWindow::on_video_slider_actionTriggered(int action)
{

}

void MainWindow::on_verticalSlider_sliderPressed()
{

}

void MainWindow::on_actionTo_pic_mode_triggered()
{
    this->close();
    solveImage *si = new solveImage;
    si->show();
}


void MainWindow::on_action_Q_triggered()
{
    st.insert(1);
    flag = 1;
}

void MainWindow::on_actionVedio_reset_triggered()
{
    flag = 0;
    cnt = add = sub = 0;
    exec = true;
    esub = true; eadd = true;
    st.clear();
    todo = 0;
}

void MainWindow::on_actionBe_big_triggered()
{
    exec = true;
    eadd = true;
    flag = 2;
    st.insert(2);
}

void MainWindow::on_actionBe_small_triggered()
{
    exec = true;
    esub = true;
    flag = 3;
    st.insert(3);
}

void MainWindow::on_actionErzhihua_triggered()
{
    flag = 4;
    st.insert(4);
}

void MainWindow::on_actionGet_pic_triggered()
{
    on_toolButton_play_clicked();
    now.save("D:/temp.png");
    solveImage *si = new solveImage;
    si->qsl += "D:/temp.png";
    si->show();
    si->token = true;
    si->on_action_N_triggered();
}

void MainWindow::on_action_triggered()
{
    flag = 5;
    st.insert(5);
    ++todo;
    //cerr<<"yes"<<endl;

   // ui->label->setPixmap(QPixmap::fromImage(now));
}

void MainWindow::on_actionMa_triggered()
{
    flag=6;
    st.insert(6);
}
