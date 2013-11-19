#include "Dialog.h"

#include <qtsingleapplication.h>
#include <QTextCodec>
#include <QSettings>

int main(int argc, char* argv[])
{
    QtSingleApplication app(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QSettings::setDefaultFormat(QSettings::IniFormat);

    app.setOrganizationName(QObject::tr("Lily"));
    app.setApplicationName(QObject::tr("HappyRun"));


    if (app.sendMessage("0"))
        return 0;

    Dialog d;

    QObject::connect(&app, SIGNAL(messageReceived(const QString&)),
             &d, SLOT(handleMessage(const QString&)));

    if ( argc > 1 ) {
        if ( argv[1] == QString("--hide") ) {
            qDebug("1");
            d.hide();
        }
    } else {
        d.show();
    }


    return app.exec();
}
