#include "LineEdit.h"

#include <QtGui>
#include <cmath>

LineEdit::LineEdit( QWidget *parent) :
    QLineEdit(parent)
{
    completeFlag = true;

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
    if (rowCount == 1 && completeFlag == true) {
        setText(completer->currentCompletion());
//        completer->setCompletionMode(QCompleter::PopupCompletion);
//        completeFlag = false;
    }
}

bool LineEdit::event(QEvent *e)
{
    if (e->type() != QEvent::KeyPress) {
        return QWidget::event(e);
    }

    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

    int key = keyEvent->key();
    int nextRow;
    int rowCount;
    int cRow;

    if ( key > Qt::Key_0 && key < Qt::Key_Z ) {
        QString tmp = this->text();
        QLineEdit::keyPressEvent(keyEvent);
        rowCount = completer->popup()->selectionModel()->model()->rowCount();
        // 若接受该字符后，导致补全项为0,则还原字符串
        if (rowCount == 0) {
            emit invalidCharacter();
            this->setText(tmp);
            // 重新设置completer的补全前缀，为了弹出补全框
            completer->setCompletionPrefix(tmp);
//            qDebug() << completer->popup()->selectionModel()->model()->rowCount();
            completer->complete();

        }
        completeFlag = true;
    } else {
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
            QLineEdit::keyPressEvent(keyEvent);
            break;
        case Qt::Key_Backspace: {
            QLineEdit::keyPressEvent(keyEvent);
            QString tmp = this->text();
            rowCount = completer->popup()->selectionModel()->model()->rowCount();
            if ( tmp.length() == 0 || rowCount > 1) {
                completeFlag = true;
            } else {
                completeFlag = false;
                QLineEdit::keyPressEvent(keyEvent);
            }
            break;
        }
        default:
            QLineEdit::keyPressEvent(keyEvent);
            break;
        }
    }

    return true;
}
