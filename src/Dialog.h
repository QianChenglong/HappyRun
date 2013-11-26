#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include <QString>
#include <QVariant>

class LineEdit;
class QLabel;
class QVBoxLayout;
class QxtGlobalShortcut;
class QCompleter;
class QButton;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
//    bool event(QEvent *e);

    void reshow();
signals:

public slots:
    void handleMessage(const QString &msg);

private slots:
    void run();
    void toggle();
    void configure();
    void onInvalidCharacter();

private:
    void setShortcuts();
    void loadDefaultApp();


private:
    QLabel *label;
    LineEdit *lineEdit;
    QVBoxLayout *layout;
    QxtGlobalShortcut * shortcut;
    QCompleter *completer;
    QPushButton *button;
    QMap<QString, QVariant> defaultApp;
};

#endif // DIALOG_H
