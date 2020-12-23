#include "mainwindow.h"
#include "solveimage.h"
#include "videosurface.h"

#include <QApplication>
#include <QUrl>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    solveImage s;
    s.show();
    return a.exec();
}
