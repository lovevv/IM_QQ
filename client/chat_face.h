#ifndef CHAT_FACE_H
#define CHAT_FACE_H

#include <QWidget>
#include "myQlable.h"
#include <QMovie>

namespace Ui {
    class chat_face;
}

class chat_face : public QWidget
{
    Q_OBJECT

public:
    explicit chat_face(QWidget *parent = 0);
    ~chat_face();

private slots:
   // void on_label_linkActivated(const QString &link);
    void myqlable_clicked();
signals:
    void load_face(QString myqlabel_name);

private:
    Ui::chat_face *ui;
    myQLabel *lable;
};

#endif // CHAT_FACE_H
