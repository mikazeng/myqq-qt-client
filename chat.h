#ifndef CHAT_H
#define CHAT_H
#include <QWidget>
#include "toolbox.h"
#include <QMessageBox>
#include <string>
namespace Ui {
class Chat;
}
using namespace std;
class toolbox;
class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(const QIcon icon, int ID,
                  QString name, toolbox *w,
                  QWidget *parent = 0);

    ~Chat();
   void  add_msg(QString sendid, QString msg);
   void SetPutton(bool fla);
   void SetBtName(QString s,int id);

private slots:
    void on_sendButton_clicked();

private:
   Ui::Chat *ui;
    int userID;
    QString username;
    toolbox*main_w;
};

#endif // CHAT_H
