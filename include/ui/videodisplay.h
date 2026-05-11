#ifndef VIDEOSCREEN_H
#define VIDEOSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class VideoDisplay : public QWidget {
    Q_OBJECT

public:
    VideoDisplay(QWidget *parent = nullptr);
    ~VideoDisplay();

private:
    QVBoxLayout* layout;
    QLabel* statusLabel;
    //QVideoWidget *videoWidget;
    //QMediaPlayer *mediaPlayer;
};

#endif // VIDEOSCREEN_H