#ifndef DEFAULTAPPPAGE_H
#define DEFAULTAPPPAGE_H

#include <QWidget>

class QTableWidget;
class QLabel;

class DefaultAppPage : public QWidget
{
    Q_OBJECT
public:
    explicit DefaultAppPage(QWidget *parent = 0);

    const static QString SettingName;

private:
    void createTableWidget();
    void loadData();
    void insertItem(QString filetype, QString openWith);

signals:

public slots:
    void save();

private:
    QTableWidget *tableWidget;
    QLabel *label;
};

#endif // DEFAULTAPPPAGE_H
