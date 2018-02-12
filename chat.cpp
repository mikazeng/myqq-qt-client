#include "chat.h"
#include "ui_chat.h"
#include <QDebug>
#include <QDateTime>
#include <QScrollBar>
Chat::Chat(const QIcon icon, int ID, QString name,
           toolbox *w, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    userID = ID;
    username = name;
    main_w = w;
    setWindowTitle(name);
    setWindowIcon(icon);
     //设置最大化最小化按钮无效
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
    setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::darkCyan));
    setPalette(palette);

}

Chat::~Chat()
{
    delete ui;
}
void Chat::add_msg(QString sendid, QString msg)//向textBrowser添加消息
{
    //得到当前时间，并把时间格式化为"yyyy-MM-dd hh:ss:ss"形式的字符串
    QString sTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:ss:ss");
    msg[msg.size()] ='\0';
    ui->textBrowser->append("["+sendid+"]" + sTime);
    ui->textBrowser->append(msg);

    //当消息textBrowser中消息过多出现滚动条时，自动滚动到最下方
    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
}

void Chat::SetPutton(bool fla)
{
    ui->sendButton->setEnabled(fla);
}

void Chat::SetBtName(QString s,int id)
{
    ui->sendButton->setText(s);
    userID =id;
    setWindowTitle(QString::number(id));
}
void Chat::on_sendButton_clicked()//发送按钮的槽函数
{
    if(ui->textEdit->toPlainText().isEmpty())//如果lineEdit控件内容为空，提示用户不能发送空消息
   {
       QMessageBox::information(this, tr("注意"), tr("不能发送空消息"));
   }
   else
   {
    qDebug()<<ui->textEdit->toPlainText();
      add_msg(tr("我的消息"), ui->textEdit->toPlainText());//将要发送的消息内容加入textBrowser控件中
      Value data;
      data["Msg_Type"]= SEND;
      data["id"] = userID;
      data["mid"] = main_w->userid;
      data["text"] = ui->textEdit->toPlainText().toStdString();
      main_w->send_Msg(data);
      // main_w->send_Msg(userID, lineEdit->text().toStdString().data());
       //调用主窗口的send_Msg方法向服务器提交send消息
       ui->textEdit->clear();//发送完成后，将lineEdit控件内容清空
   }
   ui->textEdit->setFocus();
}

