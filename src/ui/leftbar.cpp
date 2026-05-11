#include "ui/leftbar.h"
#include "ui/mainui.h"
#include <QScreen>
#include <QApplication>

QString style_sidebar = R"(
    background-color: #181818;
    padding:0;
)";

QString style_sidebar_button = R"(
    QPushButton {padding: 4px;}
    QPushButton:hover {background-color:#595958;}
)";

SideBar::SideBar(QWidget *parent, MainUI* mainui) : QToolBar(parent)
{
    QScreen *screen = QApplication::primaryScreen();
    const int screenHeight = screen ? screen->geometry().height() : 1080;
    int icon_width = static_cast<int>(screenHeight * 0.03);
    if (icon_width < 20) icon_width = 20;
    if (icon_width > 44) icon_width = 44;

    setStyleSheet(style_sidebar);

    mission = new QPushButton();
    mission->setIcon(QIcon(":/login.png"));
    mission->setIconSize(QSize(icon_width, icon_width));
    mission->setStyleSheet(style_sidebar_button);

    debug = new QPushButton();
    debug->setIcon(QIcon(":/map.png"));
    debug->setIconSize(QSize(icon_width, icon_width));
    debug->setStyleSheet(style_sidebar_button);

    setting = new QPushButton();
    setting->setIcon(QIcon(":/log.png"));
    setting->setIconSize(QSize(icon_width, icon_width));
    setting->setStyleSheet(style_sidebar_button);

    planner = new QPushButton();
    planner->setIcon(QIcon(":/sos.png"));
    planner->setIconSize(QSize(icon_width, icon_width));
    planner->setStyleSheet(style_sidebar_button);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    addWidget(mission);
    addWidget(planner);
    addWidget(debug);
    
    addWidget(spacer);

    addWidget(setting);

    mainUI = mainui;

    connect(mission, &QPushButton::clicked, this, [this]() {
        if (mainUI)
            mainUI->setActivity(Activity::Mission);
    });

    connect(planner, &QPushButton::clicked, this, [this]() {
        if (mainUI)
            mainUI->setActivity(Activity::Planner);
    });

    connect(debug, &QPushButton::clicked, this, [this]() {
        if (mainUI)
            mainUI->setActivity(Activity::Debug);
    });

    connect(setting, &QPushButton::clicked, this, [this]() {
        if (mainUI)
            mainUI->setActivity(Activity::Setting);
    });

    
}

SideBar::~SideBar()
{
}
