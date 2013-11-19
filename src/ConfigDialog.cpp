#include "PathsPage.h"
#include "ConfigDialog.h"
#include "DefaultAppPage.h"

#include <QtGui>


ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent)
{
    createContentsWidget();

    pagesWidget = new QStackedWidget;
    pathsPage = new PathsPage;
    defaultAppPage = new DefaultAppPage;
    pagesWidget->addWidget(pathsPage);
    pagesWidget->addWidget(defaultAppPage);

    contentsWidget->setCurrentRow(0);

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
    resize(500, 400);
}

void ConfigDialog::closeEvent(QCloseEvent *event)
{
    pathsPage->save();
    event->accept();
}

void ConfigDialog::createContentsWidget()
{
    contentsWidget = new QListWidget;
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    QListWidgetItem *pathsItem = new QListWidgetItem(contentsWidget);
    pathsItem->setData(Qt::DisplayRole, tr("Paths"));
    pathsItem->setTextAlignment(Qt::AlignCenter);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));

    QListWidgetItem *deaultAppItem = new QListWidgetItem(contentsWidget);
    deaultAppItem->setData(Qt::DisplayRole, tr("Default App"));
    deaultAppItem->setTextAlignment(Qt::AlignCenter);
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
