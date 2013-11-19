#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class PathsPage;
class DefaultAppPage;

class ConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createContentsWidget();

signals:
    
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    PathsPage *pathsPage;
    DefaultAppPage *defaultAppPage;
    
};

#endif // CONFIGDIALOG_H
