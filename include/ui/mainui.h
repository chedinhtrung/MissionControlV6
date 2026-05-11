#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QDockWidget>


#include "leftbar.h"
#include "flightdisplay.h"
#include "mapview.h"
#include "videodisplay.h"

struct Workspace
{
    QList<QDockWidget*> visibleDocks;
    QByteArray layout;
};

class MainUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainUI(QWidget *parent = nullptr);
    virtual ~MainUI();

    QJsonObject config;

    Activity current_activity;

    // Sidebar controls what activity we are in 
    SideBar* sidebar; 

    // All the docks 

    // Mission Control
    QDockWidget* mapDock;
    QDockWidget* flightDisplayDock;
    QDockWidget* videoDock;
    QDockWidget* vehicleInfoDock;
    QDockWidget* telemetryDock;

    // Planner


    // Debug 
    QDockWidget* logDock;
    QDockWidget* vehicleDebugTelemetryDock;
    QDockWidget* vehicleOrientationVizDock;
    QDockWidget* terminalDock;

    QList<QDockWidget*> allDocks;

    QMap<Activity, Workspace> workspaces;

    void setActivity(Activity activity);


    public slots:

    private: 
        void create_docks(); // initialize the UI element and put them into docks
        void setupMissionLayout();
        void setupDebugLayout();
};
