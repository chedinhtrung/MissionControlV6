#include "ui/mapview.h"
#include <QSurfaceFormat>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QWebEngineSettings>
#include <QTimer>
#include <QLocale>

MapView::MapView(QWidget* parent, QString map_api_key) : QWebEngineView(parent){
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    setZoomFactor(0.7);

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAutoFillBackground(false);

    QString html = loadHtml(map_api_key);
    setHtml(html);

    // test function
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MapView::onTestUpdate);
    timer->start(150);
}

void MapView::onTestUpdate(){
    static float lon=0.0, lat=0.0, head=0.0;
    lon += 0.001;
    lat += 0.001;
    head += 1;
    updateLocation(lon, lat, head);
}

MapView::~MapView(){

}

void MapView::updateLocation(float lon, float lat, float heading){
    const QLocale cLocale = QLocale::c();
    const QString JSCall = QString("update_location(%1, %2, %3)")
                               .arg(cLocale.toString(lon, 'f', 6))
                               .arg(cLocale.toString(lat, 'f', 6))
                               .arg(cLocale.toString(heading, 'f', 6));
    //qDebug() << JSCall;
    page()->runJavaScript(JSCall);
}

QString MapView::loadHtml(QString map_api_key) {
    QFile file(":googlemaps.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open googlemaps.html";
        return "";
    }

    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();
    return htmlContent.replace("{{API_KEY}}", map_api_key);
}
