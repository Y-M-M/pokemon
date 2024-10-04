#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QThreadPool>
#include <QRunnable>
#include <QUdpSocket>
#include <QtSql>
#include <QSqlQuery>
#include <QtGlobal>
#include <QTime>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QString>
#include "pokemon.h"
#include "battlecontroller.h"

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

struct User
{
    QString username;//用户名
    unsigned int port;//端口号
    uint pokemon_num;//小精灵数目
    uint high_level_num;//高级小精灵数目
    uint victory_num;//战胜次数
    uint battle_num;//战斗次数
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

    void Create_pokemons(const QString& username, int num) const;//给用户随机分配指定数量的小精灵并以udp的形式写入数据库中
    string random_name(const int& random_value) const;//随机选中宠物小精灵名字
    void PutIntoSql(const QString& username, const UDPPokemon* the_udppokemon) const;//将用户名和小精灵信息写入数据库pokemon表中
    void SentPokemon(QDataStream& dsOut, const QString& username) const;//将某一用户的所有小精灵的数据写入数据流等待发送
    void Sentall_virPokemon(QDataStream &dsOut);//将目前所有虚拟精灵写入数据流
    void Createvirpokemon();//创建一个虚拟小精灵(并调用virInroSql将它写入数据库中)
    void virIntoSql(const UDPPokemon* the_pokemon);//将虚拟小精灵写入数据库中
    void Change_users_Sql(const QString& username, int pokemon_num, int high_level_pokemon, int victory_num, int battle_num) const;
    //更新数据库中的users
    void SentOnlineUsers(unsigned int port);//发送在线用户
    void SentAllUsers(unsigned int port);//发送所有用户
    UDPPokemon GetUdppokemon(QSqlQuery& query) const;//从数据库中读取选中的小精灵，封装成UDPPokemon包
    UDPPokemon GetVirUdppok(QSqlQuery& query) const;//从数据库中读取指定位置的虚拟小精灵，封装成UDPPokemon包
    QSqlQuery GetChosnpokemon_query(const QString& username, const uint& index) const;//从数据库中找到选中小精灵的位置
    QSqlQuery GetChosVirpok_query(const uint& index) const;//找到选中的虚拟小精灵的位置
    UDPPokemon GetChosnpokemon(const QString& username, const uint& index) const;//从数据库中取出选定的用户小精灵
    UDPPokemon GetChosVirpokemon(const uint& index) const;//从数据库中取出选定的虚拟小精灵
    void UpdateIntoSql(const UDPPokemon& the_pokemon, const QString& username, const int* before_attr) const;//升级数据库中的用户小精灵
    void UpdateVirSql(const UDPPokemon& the_udppokemon, const int* before_attr) const;//升级数据库中的虚拟小精灵
    void Deletepokemon(const QString& username, const uint& index, const UDPPokemon* udppokemon) const;//从数据库中删除用户的战败的小精灵
    void DeleteVirpokemon(const uint& index, const UDPPokemon& udppokemon);//删除数据库中virtual_pokemon表中战败的小精灵

private slots:
    void readPendingDatagrams();//接收来自client的数据

private:
    Ui::MainWindow *ui;//通过ui成员变量访问类中描述的界面设计

    QUdpSocket *server;//用于发送客户端消息
    QUdpSocket *client;//用于接收用户消息
    QSqlDatabase *db;//创立数据库，存储用户信息
    QList<User> onlineUsers;//在线用户列表

    Pokemon *pokemon;//当前处理的用户小精灵
    void displayTable(QTableWidget *tableWidget, const QString &tableName) const;//展示数据库表
    uint virpokemon_num;//虚拟小精灵个数
    Pokemon *virpokemon;//当前处理的系统小精灵
};
#endif // MAINWINDOW_H
