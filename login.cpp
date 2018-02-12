#include "login.h"
#include "ui_login.h"
#include "toolbox.h"
#include "encrypt.h"
Login::Login(QTcpSocket*hostfd,QWidget *parent) :
    QDialog(parent),sock(hostfd),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginBtn_clicked()
{
    if (ui->IDEdit->text().isEmpty()||ui->pass_Edit->text().isEmpty())
        //如果lineEditUserID控件内容为空，提示用户错误
       {
           QMessageBox::information(this, tr("错误"), tr("用户ID不能为空"));
           ui->IDEdit->setFocus();
       }
       else
       {
           bool ok;
           userid =  ui->IDEdit->text().toInt(&ok);
           if (!ok)//如果lineEditUserID控件内容不是数字，提示用户错误
           {
              QMessageBox::information(this, tr("错误"), tr("用户ID必须是数字"));
              ui->IDEdit->setFocus();
           }
           else if(userid < 10000||userid > 99999)//如果用户输入的ID ;10000 - 99999提示错误
           {
               QMessageBox::information(this, tr("错误"), tr("ID ;10000 - 99999"));
               ui->IDEdit->setFocus();
           }
           else
           {
               userid =  ui->IDEdit->text().toInt();
               passwd =  ui->pass_Edit->text();

              Value val;
              val["Msg_Type"] = LOGIN;
              val["password"] = passwd.toStdString();
              val["id"] = userid;
             // val[5] = 100;

              char * endata = (char*)val.toStyledString().c_str();
              //qDebug()<<endata;
             // qDebug()<<strlen(endata);
              my_encrypt rsa_en(endata);
             // qDebug()<<rsa_en.en<<endl;
              int len = sock->write(rsa_en.en,255);//发送账号密码
             // qDebug()<<"发送子节数：：："<<len<<endl;
           }
       }
}

void Login::on_eixtBtn_clicked()
{
     exit(1);
}

void Login::on_registbtn_clicked()
{
    if (ui->IDEdit->text().isEmpty()||ui->pass_Edit->text().isEmpty())
        //如果lineEditUserID控件内容为空，提示用户错误
       {
           QMessageBox::information(this, tr("错误"), tr("用户ID不能为空"));
           ui->IDEdit->setFocus();
       }
       else
       {
           bool ok;
           userid =  ui->IDEdit->text().toInt(&ok);
           if (!ok)//如果lineEditUserID控件内容不是数字，提示用户错误
           {
              QMessageBox::information(this, tr("错误"), tr("用户ID必须是数字"));
              ui->IDEdit->setFocus();
           }
           else if(userid < 10000||userid > 99999)//如果用户输入的ID ;10000 - 99999提示错误
           {
               QMessageBox::information(this, tr("错误"), tr("ID ;10000 - 99999"));
               ui->IDEdit->setFocus();
           }
           else
           {
              userid =  ui->IDEdit->text().toInt();
              passwd = ui->pass_Edit->text();
              Value val;
              val["Msg_Type"] = REGIST;
              val["password"] = passwd.toStdString();
              val["id"] = userid;
              char * endata = (char*)val.toStyledString().c_str();
              my_encrypt rsa_en(endata);
              sock->write(rsa_en.en,255);//发送账号密码注册
           }
       }

}
