#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QUdpSocket>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QByteArray>

#include "pokemon.h"

enum SIGNAL_TYPE
{
    SIGNUP,//注册
    SIGNIN,//登陆
    NAMEEXIST,//用户名已被注册
    SIGNUPOK,//注册成功
    NOSUCHUSER,//用户不存在
    PWDDIFF,//密码错误
    SIGNINOK,//登陆成功
    POKEMONDATA,//小精灵数据
    SIGNOUT,//登出
    ONLINEUSERS,//在线用户
    ALLUSERS,//所有用户
    HAVESIGNIN//已经登陆过了
};

namespace Ui {
    class Login;
}

class Login : public QDialog
{
    Q_OBJECT//使类可以定义和使用信号与槽

    public:
        explicit Login(QWidget *parent = 0);//构造函数，默认无父窗口
        ~Login();//析构函数

        UDPPokemon **getPokemon();//只读，返回3个pokemon
        QString getUsername() const;//只读，返回username
        unsigned int getPort() const;//只读，返回端口号

    //私有槽函数，外部信号无法直接调用，只能通过信号触发
    private slots:
        void SignUp_clicked();//当注册按钮被点击时
        void SignIn_clicked();//当登录按钮被点击时
        void readPendingDatagrams();//读取数据报

    private:
        Ui::Login *ui;//通过ui成员变量访问类中描述的界面设计

        QUdpSocket *client;//用于发送
        QUdpSocket *server;//用于接收

        UDPPokemon *pokemon[3];//存放三个用户小精灵
        QString username;//用户名
        unsigned int port;//client方选定的随机端口
};

#endif // LOGIN_H
