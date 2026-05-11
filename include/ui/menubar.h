#pragma once
#include <QMenuBar>

class MainMenuBar : public QMenuBar {
    Q_OBJECT
public:
    explicit MainMenuBar(QWidget *parent = nullptr);
    virtual ~MainMenuBar();

private:
    void createActions();
    void createMenus();
};