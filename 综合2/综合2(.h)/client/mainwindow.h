#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork>
#include <QMainWindow>
#include <QButtonGroup>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>

#include "pokemon.h"
#include "battlecontroller.h"
#include "login.h"

struct User//在线用户
{
    QString username;//用户名
    unsigned int port;//用户对应的client端口

    bool operator==(const User &user) const//运算符重载，判断是否为同一个用户
    {
        return (this->username == user.username) && (this->port == user.port);
    }

    friend QDataStream &operator<<(QDataStream &stream, const User &user);//运算符重载，将User写入stream
    friend QDataStream &operator>>(QDataStream &stream, User &user);//运算符重载，从stream中读取User
};

struct UserData
{
    QString username;//用户名
    QList<UDPPokemon*> pokemon;//小精灵
    ~UserData()
    {
        for(int i = 0; i < 3; i++)
            delete this->pokemon[i];
    }
    friend QDataStream &operator<<(QDataStream &stream, const UserData &userdata);//运算符重载，将UserData写入stream
    friend QDataStream &operator>>(QDataStream &stream, UserData &userdata);//运算符重载，从stream中读取UserData
};

class Login;

namespace Ui
{
    class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT//使类可以定义和使用信号与槽

public:
    explicit MainWindow(QWidget *parent = nullptr, Login *login = nullptr);//构造函数
    ~MainWindow();//析构函数

private slots://私有槽函数
    void readPendingDatagrams();//处理更新用户的数据报
    void ReceiveSelect(QAbstractButton* button);//显示选择的小精灵信息
    QString getInfo(unsigned int index);//获取小精灵信息
    void Loginout_clicked();//关闭窗口
    void Online_clicked();//online按钮被点击时
    void Allusers_clicked();//当alluser按钮被点击时
    void Users_changed(int currentRow);//更换选中的用户时

private:
    Ui::MainWindow *ui;//通过ui成员变量访问类中描述的界面设计

    QUdpSocket *server;//用户发送的信息
    QUdpSocket *client;//用户接收的信息

    UDPPokemon **pokemon;//三个宠物小精灵
    QString username;//用户名
    unsigned int port;//client选择的随机端口
    QList<User*> onlineusers;//本地备份的在线用户列表
    QList<UserData*> allusers;//所有用户列表
    unsigned int mode;//显示模式 0:不显示，1:显示在线用户 2:显示所有用户
    QButtonGroup *m_pPkmGroup;//按钮组
};


#endif // MAINWINDOW_H
