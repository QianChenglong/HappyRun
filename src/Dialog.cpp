#include "Dialog.h"
#include "qxtglobalshortcut.h"
#include "LineEdit.h"
#include "ConfigDialog.h"
#include "DefaultAppPage.h"


#include <QtGui>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{

    label = new QLabel;
    label->setText("Run:");

    button = new QPushButton();
    connect(button, SIGNAL(clicked()),
            this, SLOT(configure()));
    button->setIcon(QIcon(":/images/resources/images/setting_48.png"));
    button->setMinimumSize(QSize(20, 20));
    button->setMaximumSize(QSize(20, 20));

    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(button);

    lineEdit = new LineEdit;
    connect(lineEdit, SIGNAL(invalidCharacter()),
            this, SLOT(onInvalidCharacter()));

    layout = new QVBoxLayout;
    layout->addLayout(hBoxLayout);
    layout->addWidget(lineEdit);
    connect(lineEdit, SIGNAL(returnPressed()),
            this, SLOT(run()));
    setLayout(layout);
    setTabOrder(this, lineEdit);
    lineEdit->setFocus();

//    setShortcuts();
    loadDefaultApp();
}

void Dialog::reshow()
{
    setVisible(true);
    lineEdit->loadData();
    activateWindow();
    lineEdit->setFocus();
    lineEdit->selectAll();
}

void Dialog::handleMessage(const QString &msg)
{
    int msgType = msg.toInt();
    switch (msgType) {
    case 0:
        reshow();
        break;
    default:
        break;
    }
}

void Dialog::run()
{
    QString input = lineEdit->text();
    QString filename;

    QProcess *process = new QProcess;
//    QProcess process;

    QStringList paths = lineEdit->paths();
    foreach(const QString &path, paths) {
        filename = path + "/" + input;
        QFileInfo fileinfo(filename);
        if ( fileinfo.isDir() ) {
            process->start(defaultApp["Directory"].toString(), QStringList() << fileinfo.absoluteFilePath());
            setVisible(false);
//            close();
        } else if ( fileinfo.isFile() ) {
            process->start(defaultApp["File"].toString(), QStringList() << fileinfo.absoluteFilePath());
            setVisible(false);
//            close();
        } else {
            label->setText("No such file or directory!");
        }
    }
}

void Dialog::toggle()
{
    lineEdit->loadData();
    setVisible(!isVisible());
    lineEdit->setFocus();
    lineEdit->selectedText();
}

void Dialog::setShortcuts()
{
    shortcut = new QxtGlobalShortcut
                            (QKeySequence("Alt+r"), this);
    connect(shortcut, SIGNAL(activated()),this, SLOT(toggle()));

}

void Dialog::loadDefaultApp()
{
    QSettings s;
    QMap<QString, QVariant> map;
    map["Directory"] = "doublecmd";
    map["File"] = "gvim";
//    QProcess p;
//    p.start("", QStringList() << "/c" << "dir");
//    if (p.waitForStarted())
//    {
//       p.waitForFinished();
//       qDebug() << p.readAllStandardOutput();
//    }
    defaultApp = s.value(DefaultAppPage::SettingName, map).toMap();
}

void Dialog::configure()
{
    ConfigDialog *configDialog = new ConfigDialog;
    configDialog->exec();
    lineEdit->loadData();
}

void Dialog::onInvalidCharacter()
{
//    qDebug() <<QSound::isAvailable() ;
    QSound::play("://resources/sounds/click.wav");
}

//bool Dialog::event(QEvent *e)
//{
//    if (e->type() == QEvent::KeyPress) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
//        switch (keyEvent->key()) {
//        case Qt::Key_Escape:
//            hide();
//            break;
//        default:
//            QDialog::keyPressEvent(keyEvent);
//            break;
//        }
//        return true;
//    }

//    return QDialog::event(e);
//}
