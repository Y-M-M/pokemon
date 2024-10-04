#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QUdpSocket>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QByteArray>

#include "pokemon.h"

enum SIGNAL_TYPE{
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
    HAVESIGNIN,//已经登陆过了
    INGAME,///进入游戏
    VIRPOKEMON,//虚拟小精灵信息
    DUEL,//选择进行决斗赛
    UPGRADE,//选择进行升级赛
    UPGRADEWIN,//升级赛胜利
    UPGRADEFAIL,//升级赛失败
    FAIL,//决斗赛战斗失败
    VICTORY,//决斗赛战斗胜利
    GIVEYOU,//送出选择的小精灵
    BATTLEPROGRESS,//战斗过程信息
    ANEWPOKEMON//用户小精灵数目为0时重新分配一个
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

    QList<UDPPokemon*> getPokemon();//只读，返回所有个pokemon
    QString getUsername() const;//只读，返回username
    unsigned int getPort() const;//只读，返回端口号
    uint getpokemon_num() const;//只读，返回宠物小精灵数目
    uint gethigh_level_pokemon() const;//只读，返回15级小精灵数目
    uint getvictory_num() const;//只读，返回战胜次数
    uint getbattle_num() const;//只读，返回战斗次数

    //私有槽函数，外部信号无法直接调用，只能通过信号触发
private slots:
    void SignUp_clicked();//当注册按钮被点击时
    void SignIn_clicked();//当登录按钮被点击时
    void readPendingDatagrams();//读取数据报

private:
    Ui::Login* ui;//通过ui成员变量访问类中描述的界面设计

    QUdpSocket* client;//用于发送
    QUdpSocket* server;//用于接收

    QList<UDPPokemon*> pokemon;//存放用户小精灵
    QString username;//用户名
    unsigned int port;//client方选定的随机端口
    uint pokemon_num;//用户拥有的宠物小精灵数目
    uint high_level_pokemon;//用户拥有的15级宠物小精灵数目
    uint victory_num;//用户战胜的次数
    uint battle_num;//用户战斗的总次数
};

#endif // LOGIN_H

