#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtSql>
#include <QSqlQuery>
#include <QtGlobal>
#include <QTime>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include "pokemon.h"
#include "battlecontroller.h"


enum SIGNAL_TYPE
{
    SIGNUP,//注册
    SIGNIN,//登录
    NAMEEXIST,//用户名已存在
    SIGNUPOK,//注册成功
    NOSUCHUSER,//用户不存在
    PWDDIFF,//密码错误
    SIGNINOK,//登陆成功
    POKEMONDATA,//宠物小精灵信息
    SIGNOUT,//登出
    ONLINEUSERS,//在线用户
    ALLUSERS,//所有用户
    HAVESIGNIN//已经登陆过了
};

struct User
{
    QString username;//用户名
    unsigned int port;//端口号
    bool operator==(const User &user) const//判断用户是否存在
    {
        return(this->username == user.username && this->port == user.port);
    }
    //运算符重载，方便对User的读写
    friend QDataStream &operator<<(QDataStream &stream, const User &user);
    friend QDataStream &operator>>(QDataStream &stream, User &user);
};


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT//使类可以定义和使用信号与槽

    public:
        explicit MainWindow(QWidget *parent = nullptr);//构造函数
        ~MainWindow();//析构函数

        void Create_pokemons(QString username);//给新用户随机分配三个小精灵并以udp的形式写入数据库中
        void PutIntoSql(QString username, UDPPokemon *the_pokemon);//将用户名和小精灵信息写入数据库
        void SentPokemon(QDataStream &dsOut, QString username);//发送小精灵的数据
        void SentOnlineUsers(unsigned int port);//发送在线用户
        void SentAllUsers(unsigned int prot);//发送所有用户

    private slots:
        void readPendingDatagrams();//接收来自client的数据

    private:
        Ui::MainWindow *ui;//通过ui成员变量访问类中描述的界面设计

        QUdpSocket *server;//用于发送客户端消息
        QUdpSocket *client;//用于接收用户消息
        QSqlDatabase *db;//创立数据库，存储用户信息
        QList<User> onlineUsers;//在线用户列表

        Pokemon *pokemon;//当前处理的小精灵
        void displayTable(QTableWidget *tableWidget, const QString &tableName);
};
#endif // MAINWINDOW_H
