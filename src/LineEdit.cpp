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
    if (rowCount == 1 && hasCompleted == false) {
        setText(completer->currentCompletion());
        completer->setCompletionMode(QCompleter::PopupCompletion);
        hasCompleted = true;
    }
}

bool LineEdit::event(QKeyEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

        int key = keyEvent->key();
        int nextRow;
        int rowCount;
        int cRow;

        switch ( key ) {
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
            QLineEdit::keyPressEvent(e);
            break;
        case Qt::Key_Backspace:
            QString tmp = this->text();
            if ( tmp.length() == 0 ) {
                hasCompleted = false;
            } else {
                hasCompleted = true;
            }
            QLineEdit::keyPressEvent(e);
            break;
        }
        if ( key > Qt::Key_0 && key < Qt::Key_Z ) {
            //        hasCompleted = false;
            QString tmp = this->text();
            QLineEdit::keyPressEvent(e);
            rowCount = completer->popup()->selectionModel()->model()->rowCount();
            if (rowCount == 0) {
                this->setText(tmp);
            }
        } else {
            //        hasCompleted = false;
            QLineEdit::keyPressEvent(e);
        }

        return true;
    }
    return QWidget::event(e);
}
