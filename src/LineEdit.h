#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

#include <QStringList>

class QCompleter;

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);
    void setPaths(const QStringList &paths);
    void loadData();
    QStringList paths() const;
    bool event(QEvent *e);

signals:
    void invalidCharacter();

public slots:
    void onCompleterActivated(QString text);
    void onTextChanged();

private:
    QCompleter *completer;
    QStringList pathsList;
    bool completeFlag;   // 是否开启唯一补全
};

#endif // LINEEDIT_H
