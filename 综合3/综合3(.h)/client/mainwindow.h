#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork>
#include <QMainWindow>
#include <QButtonGroup>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>
#include <QTime>
#include <QtGlobal>

#include "pokemon.h"
#include "login.h"
#include "selectpokemon.h"

struct User//在线用户
{
    QString username;//用户名
    unsigned int port;//用户对应的client端口
    uint pokemon_num;//用户所拥有的小精灵的数量
    uint high_level_pokemon;//用户所拥有的15级小精灵的数量
    uint victory_num;//用户胜利的次数
    uint battle_num;//用户战斗的次数

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
    uint pokemon_num;//用户所拥有的小精灵的数量
    uint high_level_pokemon;//用户所拥有的15级小精灵数目
    uint victory_num;//用户胜利的次数
    uint battle_num;//用户战斗的次数

    QList<UDPPokemon*> pokemon;//小精灵
    ~UserData()
    {
        for(uint i = 0; i < pokemon_num; i++)
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
    void recvSelectResult(uint index);//接受用户选择的小精灵

    void Loginout_clicked();//关闭窗口
    void Online_clicked();//online按钮被点击时
    void Allusers_clicked();//当alluser按钮被点击时
    void Users_changed(int currentRow);//更换选中的用户时
    void Upgrade_botton_clicked();//当upgrade按钮被点击时
    void Duel_botton_clicked();//当duel按钮被点击时
    void CbxUser_Changed(int index);//当目前选中的用户小精灵改变时
    void Combox_Changed(int index);//当目前选中的虚拟小精灵被改变时
    void BtnConfirm_clicked();//确认按钮被点击时
    void BtnRate_clicked();//显示胜率的按钮被点击时
    void BtnBadge_clicked(bool checked);//显示奖牌的按钮被点击时


signals:
    void sentSelect(QList<UDPPokemon *> pkmList, uint *pkmIndex);//发送数据给类SelectPokemon

private:
    Ui::MainWindow *ui;//通过ui成员变量访问类中描述的界面设计

    QUdpSocket *server;//用户发送的信息
    QUdpSocket *client;//用户接收的信息

    QList<UDPPokemon*> pokemon;//三个宠物小精灵
    QList<UDPPokemon*> virtual_pokemon;
    QString username;//用户名
    unsigned int port;//client选择的随机端口
    QList<User*> onlineusers;//本地备份的在线用户列表
    QList<UserData*> allusers;//所有用户列表
    unsigned int mode;//显示模式 0:不显示，1:显示在线用户 2:显示所有用户
    uint gamemode;//游戏模式, 0为未进入游戏，1为升级赛，2为决斗赛
    uint pokemon_num;//用户拥有的宠物小精灵数目
    uint high_level_pokemon;//用户拥有的15级宠物小精灵数目
    uint virpokemon_num;
    uint victory_num;
    uint battle_num;

    uint pokemon_index[3];

    SelectPkm *selectPokemon = new SelectPkm(this);

    QString getInfo(unsigned int index) const;//获取小精灵信息
    QString getVirInfo(uint index);//获取选中的虚拟小精灵信息
    void reset();
};


#endif // MAINWINDOW_H
