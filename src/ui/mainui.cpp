#include "ui/mainui.h"
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>

QString mainui_style = R"(
    background-color: #1F1F1F; margin:0px; padding:0px;
)";

MainUI::MainUI(QWidget *parent) : QMainWindow(parent)
{

    setStyleSheet(mainui_style);
    setWindowTitle("Mission Control v6.0");
    // setWindowFlags(Qt::FramelessWindowHint);

    // load config

    QFile file(":config.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Missing config.json file";
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    config = doc.object();

    // init UI elements and organize them

    create_docks();
    createViewMenu();
    setupMissionLayout();
    setupDebugLayout();

    setActivity(Mission);

    sidebar = new SideBar(this, this);
    addToolBar(Qt::LeftToolBarArea, sidebar);

    
}

MainUI::~MainUI()
{
}

void MainUI::create_docks()
{

    MapView *map = new MapView(nullptr, config.value("GOOGLE_MAPS_API_KEY").toString());
    mapDock = new QDockWidget("Map");
    mapDock->setObjectName("mapDock");
    mapDock->setWidget(map);
    addDockWidget(Qt::LeftDockWidgetArea, mapDock);

    FlightDisplay *flightdisp = new FlightDisplay();
    flightDisplayDock = new QDockWidget("Flight Display");
    flightDisplayDock->setObjectName("flightDisplayDock");
    flightDisplayDock->setWidget(flightdisp);
    addDockWidget(Qt::LeftDockWidgetArea, flightDisplayDock);

    VideoDisplay *video = new VideoDisplay();
    videoDock = new QDockWidget("Video");
    videoDock->setObjectName("videoDock");
    videoDock->setWidget(video);
    addDockWidget(Qt::RightDockWidgetArea, videoDock);

    // Vehicle Info
    vehicleInfoDock = new QDockWidget("Vehicle Info");
    vehicleInfoDock->setObjectName("vehicleInfoDock");
    vehicleInfoDock->setWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, vehicleInfoDock);

    
     // debug telemetry
    vehicleDebugTelemetryDock = new QDockWidget("Sensors");
    vehicleDebugTelemetryDock->setObjectName("vehicleDebugTelemetryDock");
    vehicleDebugTelemetryDock->setWidget(new QWidget());
    addDockWidget(Qt::LeftDockWidgetArea, vehicleDebugTelemetryDock);

    // Orientation viz
    vehicleOrientationVizDock = new QDockWidget("Orientation");
    vehicleOrientationVizDock->setObjectName("vehicleOrientationVizDock");
    vehicleOrientationVizDock->setWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, vehicleOrientationVizDock);
    
    // Logs
    logDock = new QDockWidget("Logs");
    logDock->setObjectName("logDock");
    logDock->setWidget(new QWidget());
    addDockWidget(Qt::LeftDockWidgetArea, logDock);

    // Terminal
    terminalDock = new QDockWidget("Terminal");
    terminalDock->setObjectName("terminalDock");
    terminalDock->setWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, terminalDock);

    allDocks =
        {
            mapDock,
            flightDisplayDock,
            videoDock,
            vehicleInfoDock,
            logDock,
            terminalDock,
            vehicleOrientationVizDock,
            vehicleDebugTelemetryDock};
}

void MainUI::createViewMenu()
{
    QMenu *viewMenu = menuBar()->addMenu("View");
    for (QDockWidget *dock : allDocks)
    {
        viewMenu->addAction(dock->toggleViewAction());
    }
}

void MainUI::setupMissionLayout()
{
    // Left column
    splitDockWidget(mapDock,
                    flightDisplayDock,
                    Qt::Vertical);

    // Right column
    splitDockWidget(videoDock,
                    vehicleInfoDock,
                    Qt::Vertical);

    // Video larger
    resizeDocks(
        {videoDock,
         vehicleInfoDock},
        {750,
         250},
        Qt::Vertical);

    workspaces[Activity::Mission].layout = saveState();
    workspaces[Activity::Mission].visibleDocks = {
        mapDock,
        flightDisplayDock,
        videoDock,
        vehicleInfoDock};
}

void MainUI::setupDebugLayout()
{

    splitDockWidget(
        vehicleDebugTelemetryDock,
        logDock,
        Qt::Vertical);

    workspaces[Activity::Debug].layout = saveState();
    workspaces[Activity::Debug].visibleDocks = {
        logDock,
        terminalDock,
        vehicleOrientationVizDock,
        vehicleDebugTelemetryDock};
    }

void MainUI::setActivity(Activity activity)
{
    restoreState(workspaces[activity].layout);
    for (QDockWidget *dock : allDocks)
    {
        dock->hide();
    }

    for (QDockWidget *dock :
         workspaces[activity].visibleDocks)
    {
        dock->show();
    }
}
