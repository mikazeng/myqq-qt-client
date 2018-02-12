#include "toolbox.h"

toolbox::toolbox(QWidget *parent)
    :QToolBox(parent),hostip(IP),hostport(PORT),index(0)
{
       //根据登录对话框中用户输入的ID号设置主窗口标题
        //根据登录对话框中用户输入的服务器IP和端口号连接到服务器
      sockClient = new QTcpSocket(this);
      connect(sockClient,
              SIGNAL(error(QAbstractSocket::SocketError)),
              this,
              SLOT(sock_Error(QAbstractSocket::SocketError)));//设置socket出错时的槽函数

      connect(sockClient, SIGNAL(readyRead()),
              this,
              SLOT(read_Msg()));//设置socket收到消息的槽函数
      connect(sockClient,&QTcpSocket::connected,
              [=]()
      {
           QMessageBox::information(this,"连接成功","连接服务器成功");
      }
      );
      setWindowIcon(QPixmap(":/images/images/23.png"));
      this->setFixedSize(300,500);//设置固定大小
      init_username();
      init_toolBtn();//初始化所有的toolBtn
      sockClient->connectToHost(QHostAddress(hostip),hostport);
      //show();
     /////////////////////////////
      log = new Login(sockClient);
      log->exec();
      /////////////////////////////
      setWindowTitle(QString::number(userid));
}
void toolbox::init_toolBtn()//初始化所有的toolBtn
{
    QString imagename;
    for(int i = 0;i<CLINETCOUNT;i++ )
    {
        toolBtn[i] = new QToolButton();
       // toolBtn[i]->setObjectName(QString::number(i));//为每个toolBtn设置ObjectName属性
       toolBtn[i]->setText(username[i]);//设置toolBtn标题
        imagename.sprintf(":/images/images/%d.png", i);
        toolBtn[i]->setIcon(QPixmap(imagename));//设置toolBtn图像
        toolBtn[i]->setIconSize(QPixmap(imagename).size());//设置toolBtn大小和图像一致
        toolBtn[i]->setFixedSize(120,80);
        toolBtn[i]->setAutoRaise(true);//设置toolBtn自动浮起界面风格
        toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置toolBtn文字在图像旁边
        toolBtn[i]->setToolTip(tr("离线"));//设置toolBtn 鼠标提示为“未知”

        window[i] = new Chat(toolBtn[i]->icon(), i, toolBtn[i]->text(), this);
        window[i]->SetPutton(false);
        window[i]->SetBtName("离线消息未开发",10000);
        connect(toolBtn[i],&QToolButton::clicked,
                [=](){
        window[i]->show();
        });
    }
    for(int i =0; i<3;i++)
    {
        groupBox[i] = new QGroupBox;
        layout[i] = new QVBoxLayout(groupBox[i]);
        layout[i]->setMargin(10);//设置布局中各窗体的显示间距
        layout[i]->setAlignment(Qt::AlignHCenter);//设置布局中各窗体的位置     
    }
    layout[0]->addStretch();//插入一个占位符

    for(int i =0 ;i<CLINETCOUNT;++i)
    {
       layout[1]->addWidget(toolBtn[i]);
       toolBtn[i]->setToolTip(tr("离线"));//设置toolBtn鼠标提示为“离线”
    }

    addItem((QWidget *)groupBox[0], tr("在线好友"));
    addItem((QWidget *)groupBox[1], tr("离线好友"));
    addItem((QWidget *)groupBox[2], tr("陌生人"));

}
toolbox::~toolbox()
{
    ;
}
void toolbox::init_username()
{
    for(int i = 0;i<CLINETCOUNT;i++ )//将username[]数组中所有的成员初始化
    {
        username[i] = tr("曾润良") + QString::number(i);
    }
}

void toolbox::send_Msg(Value &val)
{
    char * endata = (char*)val.toStyledString().c_str();
    my_encrypt rsa_en(endata);
    sockClient->write(rsa_en.en,255);
}

void toolbox::Online(Value &data)
{
    toolBtn[index]->setText(QString::number(data["id"].asInt()));//设置toolBtn标题
    layout[1]->removeWidget(toolBtn[index]);//从离线列表中删除
    window[index]->SetBtName("发送",data["id"].asInt());
    window[index]->SetPutton(true);
    layout[0]->insertWidget(0,toolBtn[index++]);//添加到在线列表中
}

void toolbox::Offline(Value &data)
{
    for(int i =0; i<index;++i){
    if(toolBtn[i]->text().toInt() == data["id"].asInt())
    {
        window[i]->SetBtName("离线消息未开发",data["id"].asInt());
        window[i]->SetPutton(false);
        layout[0]->removeWidget(toolBtn[i]);//从在线列表中删除
        layout[1]->insertWidget(0,toolBtn[i]);//添加到离线列表中
    }
    }
}

void toolbox::GetMsg(Value &data)
{
    for(int i =0; i<index;++i){
    if(toolBtn[i]->text().toInt() == data["mid"].asInt())
    {
        window[i]->add_msg(QString::number(data["mid"].asInt()),
                QString(data["text"].toStyledString().c_str()));
        window[i]->setWindowTitle(QString::number(data["mid"].asInt()));
        window[i]->show();
    }
    }
}
void toolbox::sock_Error(QAbstractSocket::SocketError sockErr)
{
    switch (sockErr)
     {
     case QAbstractSocket::RemoteHostClosedError:
         break;
     default:
         QMessageBox::information(this, tr("链接服务器错误"), sockClient->errorString());
     }
}

void toolbox::read_Msg()
{
    QByteArray array = sockClient->readAll();
    QString  s =QString(array);
    //QMessageBox::information(this, tr("服务器消息"),s);
    Value val;
    Reader read;
    read.parse(s.toStdString(),val);
    //val["Msg_Type"] = LOGIN;
    qDebug()<<s<<endl;
    switch (val["Msg_Type"].asInt())
    {
    case SYS:
        if(val["flag"].asInt()==1){
                //QMessageBox::information(this, tr("服务器消息"),"登录成功");
                userid = log->userid;//本人id
                passwd = log->passwd;//本人密码
                log->close();
                this->show();
            }
        else
             QMessageBox::information(this, tr("服务器消息"),"用户名或密码错误");
        break;
    case BROAD_ADD:
        Online(val);//新好友上线
        break;
    case BROAD_DEL:
        Offline(val);
        break;
    case SEND:
         GetMsg(val);
         break;
    case SYS_REGI:
        if(val["re_flag"].asInt()==1){
               QMessageBox::information(this, tr("服务器消息"),"注册成功");
               val.toStyledString().c_str();
            }
        else
             QMessageBox::information(this, tr("服务器消息"),"注册失败，请更改用户名");
    break;

    default:
        break;
    }
}
