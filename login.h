#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>
#include <json/json.h>

using namespace std;
using namespace Json;
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login( QTcpSocket*hostfd,QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginBtn_clicked();

    void on_eixtBtn_clicked();

    void on_registbtn_clicked();

public:
    Ui::Login *ui;
    int userid;//本人id
    QString passwd;//本人密码

    QTcpSocket  *sock;//与主机通信的SOCKET
};

#endif // LOGIN_H
