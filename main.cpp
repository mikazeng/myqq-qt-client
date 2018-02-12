#include <QApplication>
#include <QMessageBox>
#include "toolbox.h"
#include "json/json.h"
#include <iostream>
#include <QString>
#include <qDebug>
using namespace std;
using namespace Json;
extern "C"{
#include "openssl/applink.c"
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     toolbox*q= new toolbox;
   // Json::Value val;

    //   val["name"] = 123456;
    //   val["pw"] = "我是张三";
    //qDebug()<<val.toStyledString().c_str();

    return a.exec();
}
