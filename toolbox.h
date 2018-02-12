#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <QObject>
#include <QToolBox>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QToolButton>
#include <QCloseEvent>
#include <QGroupBox>
#include <string>
#include <QVBoxLayout>
#include <QEvent>
#include "chat.h"
#include "login.h"
#include "encrypt.h"
#define PORT 6666
#define IP "192.168.111.128"
//#define IP "39.107.94.67"
#define CLINETCOUNT 256//最大客户端数量
class Chat;
typedef enum
{
    SYS,
    REGIST,
    LOGIN,
    SEND,
    GROUP,
    BROAD_ADD,
    BROAD_DEL,
    SYS_REGI,
}MSG_TYPE;
using namespace std;
class toolbox : public QToolBox
{
Q_OBJECT
signals:

public slots:
    //socket的三个槽函数
    void sock_Error(QAbstractSocket::SocketError sockErr);
    //socket出错时候触发的
    void read_Msg();//收到消息的时候触发
public:
    explicit toolbox(QWidget *parent= 0);
    virtual ~toolbox();
    void  init_toolBtn();
    void  init_username();
    void  send_Msg(Value &data);
    void  Online(Value& data);
    void  Offline(Value& data);
    void  GetMsg(Value &data);

public:
    int userid;//本人id
    QString passwd;//本人密码
    QString hostip;//主机IP
    quint16 hostport;//主机端
    QTcpSocket  *sockClient;//与主机通信的SOCKET
    Login *log;//登录界面


    Chat* window[CLINETCOUNT];//好友的聊天窗口
    QToolButton *toolBtn[CLINETCOUNT];//好友位置


    int index;
    QGroupBox* groupBox[3];//两个分组
    QVBoxLayout*layout[3];//分组的布局方式
     //好友列表
     QString username[CLINETCOUNT];//用户名字
};

#endif
