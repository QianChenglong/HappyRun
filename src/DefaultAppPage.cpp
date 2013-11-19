#include "DefaultAppPage.h"

#include <QtGui>

const QString DefaultAppPage::SettingName = tr("DefaultApp");

DefaultAppPage::DefaultAppPage(QWidget *parent) :
    QWidget(parent)
{
    label = new QLabel;
    label->setText(tr("Default Application:"));
    createTableWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(tableWidget);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void DefaultAppPage::createTableWidget()
{
    tableWidget = new QTableWidget;
    QStringList header;
    header << tr("FileType") << tr("Open with");
    tableWidget->setHorizontalHeaderLabels(header);
    loadData();
}

void DefaultAppPage::loadData()
{
    QSettings s;
    QMap<QString, QVariant> map = s.value(SettingName).toMap();
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        insertItem(i.key(), i.value().toString());
    }

}

void DefaultAppPage::insertItem(QString filetype, QString openWith)
{
    qint32 row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DisplayRole, filetype);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    tableWidget->setItem(row, 0, item);

    QLineEdit *lineEdit = new QLineEdit(openWith);
    tableWidget->setCellWidget(row, 1, lineEdit);
}

void DefaultAppPage::save()
{
    QMap<QString, QVariant> map;

    qint32 row = tableWidget->rowCount();
    if ( row == -1 ) {
        return;
    }
    for ( qint32 i = 0; i != row; ++i ) {
        QLineEdit *widget = static_cast<QLineEdit*>(
                    tableWidget->cellWidget(i, 1));
        map[tableWidget->item(i, 0)->text()] =
                widget->text();
    }

    QSettings s;
    s.setValue(SettingName, map);
}
