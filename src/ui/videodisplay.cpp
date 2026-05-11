#include "ui/videodisplay.h"
#include <QScreen>
#include <QApplication>

VideoDisplay::VideoDisplay(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    statusLabel = new QLabel("NOT CONNECTED", this);
    //videoWidget = new QVideoWidget(this);
    //mediaPlayer = new QMediaPlayer(this);

    //layout->addWidget(statusLabel);
    //layout->addWidget(videoWidget);

    //mediaPlayer->setVideoOutput(videoWidget);
}

VideoDisplay::~VideoDisplay()
{
    //delete mediaPlayer;
    //delete videoWidget;
    //delete statusLabel;
    delete layout;
}
