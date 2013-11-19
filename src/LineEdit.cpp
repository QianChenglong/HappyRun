#include "LineEdit.h"

#include <QtGui>
#include <cmath>

LineEdit::LineEdit( QWidget *parent) :
    QLineEdit(parent)
{
    hasCompleted = false;

    completer = new QCompleter(QStringList(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    connect(completer, SIGNAL(activated(QString)),
            this, SLOT(onCompleterActivated(QString)));

    connect(this, SIGNAL(textChanged(QString)),
            this, SLOT(onTextChanged()));

    setCompleter(completer);
    loadData();
}

void LineEdit::setPaths(const QStringList &paths)
{
    QStringListModel *stringListModel =
            qobject_cast< QStringListModel* >(completer->model());
    stringListModel->setStringList(paths);
}

void LineEdit::loadData()
{
    QSettings s;
    pathsList = s.value(tr("paths")).toStringList();
    QStringList list;
    foreach(const QString &path, pathsList) {
        QDir dir(path);
        list += dir.entryList();
    }
    setPaths(list);
}

QStringList LineEdit::paths() const
{
    return pathsList;
}

void LineEdit::onCompleterActivated(QString text)
{
    setText(text);
}

void LineEdit::onTextChanged()
{
    int rowCount = completer->completionCount();
    if (rowCount == 1) {
        setText(completer->currentCompletion());
        completer->setCompletionMode(QCompleter::PopupCompletion);
        hasCompleted = true;
    }
}

bool LineEdit::event(QEvent *e)
{
    int nextRow;
    int rowCount;
    int cRow;

    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        switch ( keyEvent->key() ) {
        case Qt::Key_Tab:
            rowCount = completer->popup()->selectionModel()->model()->rowCount();
            // 若没有补全项，则直接返回
            if (rowCount == 0) {
                break;
            }
            cRow = completer->popup()->currentIndex().row();
            nextRow = (cRow + 1) % rowCount;

            completer->popup()->setCurrentIndex(completer->completionModel()->index(nextRow , 0));
            completer->setCurrentRow(nextRow);
            break;
        case Qt::Key_Backtab:
            rowCount = completer->popup()->selectionModel()->model()->rowCount();
            // 若没有补全项，则直接返回
            if (rowCount == 0) {
                break;
            }
            cRow = completer->popup()->currentIndex().row();
            if (cRow <= 0) {
                cRow = rowCount;
            }
            nextRow = (cRow - 1) % rowCount;

            completer->popup()->setCurrentIndex(completer->completionModel()->index(nextRow , 0));
            completer->setCurrentRow(nextRow);
            break;

        case Qt::Key_Return:
        case Qt::Key_Enter:
            hasCompleted = false;
            QLineEdit::keyPressEvent(keyEvent);
            break;
        default :
            QLineEdit::keyPressEvent(keyEvent);
            break;
        }
        return true;
    }

    return QLineEdit::event(e);
}
