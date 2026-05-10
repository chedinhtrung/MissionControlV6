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
    setWindowTitle("Mission Control v5.0");
    //setWindowFlags(Qt::FramelessWindowHint);

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

    // init UI elements
    QMenu *viewMenu = menuBar()->addMenu("View");
    sidebar = new SideBar();
    tabbar = new TabBar();
    maintab = new MainTab();
    flightdisp = new FlightDisplay();
    map = new MapView(nullptr, config.value("GOOGLE_MAPS_API_KEY").toString());
    tabbar->addTab(maintab, "Mission Control");
    setCentralWidget(tabbar);

    QDockWidget *mapDock = new QDockWidget("Map", this);
    mapDock->setWidget(map);
    addDockWidget(Qt::LeftDockWidgetArea, mapDock);

    QDockWidget *flightDock = new QDockWidget("Flight Display", this);
    flightDock->setWidget(flightdisp);
    addDockWidget(Qt::LeftDockWidgetArea, flightDock);
    splitDockWidget(mapDock, flightDock, Qt::Vertical);
    viewMenu->addAction(mapDock->toggleViewAction());
    viewMenu->addAction(flightDock->toggleViewAction());
}

MainUI::~MainUI()
{
}
