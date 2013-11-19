#include "PathsPage.h"
#include <QtGui>

PathsPage::PathsPage(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *groupBox = new QGroupBox(tr("Paths configuration"));
    createListWidget();

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(listWidget);



    addPushButton = new QPushButton;
    addPushButton->setText(tr("Add"));
    connect(addPushButton, SIGNAL(clicked()),
            this, SLOT(add()));
    removePushButton = new QPushButton;
    removePushButton->setText(tr("Remove"));
    connect(removePushButton, SIGNAL(clicked()),
            this, SLOT(remove()));
    QHBoxLayout * hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(addPushButton);
    hBoxLayout->addWidget(removePushButton);

    vBoxLayout->addLayout(hBoxLayout);

    groupBox->setLayout(vBoxLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
//    mainLayout->addLayout(hBoxLayout);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void PathsPage::save()
{
    paths.clear();
    qint32 row = listWidget->count();
    if ( row == -1 ) {
        return;
    }
    for ( qint32 i = 0; i != row; ++i ) {
        QListWidgetItem *item = listWidget->item(i);
        paths << item->text();
    }
    QSettings setting;
    setting.setValue(tr("paths"), paths);
}

void PathsPage::add()
{
    QFileDialog d;
    d.setOption(QFileDialog::ShowDirsOnly);
    d.setFileMode(QFileDialog::DirectoryOnly);
    d.setDirectory("/");
    if (d.exec()) {
        QStringList dirs = d.selectedFiles();
        paths += dirs;
        listWidget->addItems(dirs);
    }
}

void PathsPage::remove()
{
    int i = listWidget->currentRow();
    listWidget->takeItem(i);
}


void PathsPage::createListWidget()
{

    listWidget = new QListWidget();
    listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadPath();
    listWidget->addItems(paths);
}

void PathsPage::loadPath()
{
    QSettings setting;

    paths = setting.value(tr("paths")).toStringList();

}

