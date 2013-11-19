#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class QListWidget;
class QPushButton;

class PathsPage : public QWidget
{
    Q_OBJECT
public:
    PathsPage(QWidget *parent = 0);

protected:

private:
    void createListWidget();
    void loadPath();

public slots:
    void save();
    void add();
    void remove();

private:
    QListWidget *listWidget;
    QStringList paths;
    QPushButton *addPushButton;
    QPushButton *removePushButton;
};

#endif // PAGE_H
