#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "packagemanager.h"
#include "iconprovider.h"

#include <QObject>
#include <QString>
#include <QMainWindow>
#include <QDeclarativeView>
#include <QGraphicsObject>

#include <QDebug>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QtDeclarative>

#include "package.h"
#include "packagegroup.h"
#include "packagemarkings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QmlApplicationViewer viewer;

    PackageManager *pm = new PackageManager(&viewer);

    QDeclarativeContext *context = viewer.rootContext();
    context->setContextProperty("initialstate", "mainview");
    viewer.engine()->addImageProvider(QLatin1String("icons"), new IconProvider);
    viewer.engine()->addImportPath("/usr/lib/qt4/imports");

    qmlRegisterType<Package>("Package", 1,0, "Package");
    qmlRegisterType<PackageGroup>("Package", 1,0, "PackageGroup");
    qmlRegisterType<PackageMarkings>("Package", 1, 0, "PackageMarkings");

    viewer.setMainQmlFile(QLatin1String("qml/package-manager/main.qml"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);

    viewer.showExpanded();

    return app.exec();
}