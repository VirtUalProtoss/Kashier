#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "service.h"
#include <QDebug>


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    //QCoreApplication::setApplicationName("multiple-values-program");
    //QCoreApplication::setApplicationVersion(Q_VERSION);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption appConfigOption(
        QStringList() << "c" << "config",
        QCoreApplication::translate("main", "Application configuration file, default to cient.ini"),
        QCoreApplication::translate("main", "config"),
        QString("client.ini")
    );
    parser.addOption(appConfigOption);
    parser.process(app);

    qDebug() << "Load common lib";
    Service* service = new Service();
    qDebug() << "Load configuration from file" << parser.values(appConfigOption);
    service->loadConfig(parser.value(appConfigOption));
    qDebug() << "Finish loading common lib";

    return app.exec();
}
