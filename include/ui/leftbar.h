#pragma once
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>

class MainUI;

enum Activity {
    Mission,
    Planner,
    Debug,
    Setting
};

class SideBar : public QToolBar {
    Q_OBJECT

    public:
        SideBar(QWidget* parent=nullptr, MainUI* mainui=nullptr);
        ~SideBar();

        MainUI* mainUI;

        QPushButton* mission;
        QPushButton* planner;
        QPushButton* debug;
        QPushButton* setting;
};
