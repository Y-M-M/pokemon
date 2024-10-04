#ifndef POKEMON_H
#define POKEMON_H

//可达鸭Psyduck 水 弱点：草、电 3434 攻击型  water_pulse水之波动 speed
//小火龙Charmander 火 弱点：水、地面、岩石 3434 攻击型 fire_attack火焰攻击 ATK
//飞腿郎Hitmonlee 格斗 弱点：飞行、超能力、妖精 3846 攻击型 foot_kick下盘踢 DF
//杰尼龟Squirtle 水 弱点：草、电 3343 防御型 water_gun水枪 HP
//卡拉卡拉Cubone 地面 弱点：水、草、冰 2342 防御型 throw_mud掷泥 DF
//独角犀牛Rhyhorn 地面、岩石 弱点：水、草、冰、格斗、地面、钢 5562 防御型 hit撞击 ATK
//皮皮Clefairy 妖精 弱点：毒、钢 5333 肉盾型 sing唱歌 speed
//吉利蛋Chansey 一般 弱点：格斗 15 1 1 3 肉盾型 clap拍击 HP

//皮卡丘Pikachu 电 弱点：地面 3436 敏捷型 electric_shock电击 ATK
//妙蛙种子Bulbasaur 草/毒 弱点：火、冰、飞行、超能力 3333 rattan_whip藤鞭子 DF
//小火马Ponyta 火 弱点：水、地面、岩石 3546 敏捷型 spark火花 speed
//呆呆兽Slowpoke 水、超能力 弱点：草、电、虫、幽灵、恶 6441 肉盾型 Incantation咒术 HP

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <time.h>
#include <QTime>
#include <QDataStream>
using namespace std;

//枚举四种类型
enum Pokemon_kind
{
    HIGH_ATK,
    HIGH_DF,
    HIGH_HP,
    HIGH_SPEED
};


struct UDPPokemon
{
    QString name;//名字
    Pokemon_kind kind;//类别
    int level;//等级
    int max_EXP;//经验上限
    int EXP;//目前所获经验
    int ATK;//普通攻击
    int max_HP;//血量上限
    int HP;//目前血量
    int DF;//防御
    int speed;//速度
    QString special_ATK_name;//特攻名字
    int special_ATK;//特攻数值

    friend QDataStream &operator<<(QDataStream &stream, const UDPPokemon &the_pokemon);
    friend QDataStream &operator>>(QDataStream &stream, UDPPokemon &the_pokemon);
};

class Pokemon;

class BASE_Pokemon//基类宠物小精灵
{
public:
    BASE_Pokemon();//构造函数
    virtual ~BASE_Pokemon();//析构函数
    BASE_Pokemon(const BASE_Pokemon &the_pokemon);//拷贝构造函数
    //对副属性的额外增加
    void base_add_ATK();
    void base_add_DF();
    void base_add_HP();
    void base_add_speed();
    //升级时增加普通属性、对于主属性的基础额外增加
    void add_ATK();
    void add_DF();
    void add_HP();
    void add_speed();
    //获胜时增加经验，根据击败的精灵等级不同获得不一样多的经验
    void add_EXP(const BASE_Pokemon& fail_pokemon);
    void addgrade();//升级
    int check_grade() const;//查看等级，只读
    int check_DF() const; //查看防御，只读
    void less_HP(int damage);//只写，减少血量
    int check_ATK() const; //只读，查看普通攻击
    int check_speed() const; //只读，查看速度
    int check_max_EXP() const; //只读，查看经验上限
    int check_EXP() const;//只读，查看现有经验
    int check_max_HP() const;//只读，查看血量上限
    int check_HP() const;//只读，查看现有血量
    void top_HP();//只写，加满血量
    int zero_HP();//只读，判断血量是否降到0
    int isupdate() const; //只读，判断是否可以升级
    int dodge(const BASE_Pokemon& another_Pokemon) const;//判断是否能闪避
    int critical_strike(const BASE_Pokemon& another_Pokemon) const;//只读，概率性暴击
    void printbase() const;//打印精灵及其属性
    virtual void attack(Pokemon& another_Pokemon) = 0;//攻击函数
private:
    int grade;//等级
    int max_EXP;//本级经验上限
    int EXP;//目前所获得的经验
    int normal_ATK;//普通攻击所能造成的伤害
    int DF;//防御
    int HP;//血量
    int max_HP;//血量上限
    int speed;//速度
};

class TYPE_Pokemon: public BASE_Pokemon//区分三种类型的小精灵
{
public:
    TYPE_Pokemon(const Pokemon_kind& the_kind);//构造函数
    virtual ~TYPE_Pokemon();//析构函数
    TYPE_Pokemon(const TYPE_Pokemon &the_pokemon);//拷贝构造函数
    Pokemon_kind check_kind() const;//查看类型，只读
    void printtype() const;//打印private成员变量小精灵类型
private:
    Pokemon_kind kind;//宠物小精灵类型
};


class Pokemon: public TYPE_Pokemon//区分不同名字的小精灵
{
public:
    Pokemon(const string& the_name, const Pokemon_kind& this_kind);//构造函数
    ~Pokemon();//析构函数
    Pokemon(const Pokemon &the_pokemon);//拷贝构造函数
    //针对不同类型的宠物小精灵增加其主特长
    void special_add_ATK();
    void special_add_DF();
    void special_add_HP();
    void special_add_speed();
    void add_special_ATK();//升级时对于非主属性的特殊攻击的增加
    void update();//升级、更新参数
    void printname() const;//打印小精灵名字
    void printspecial() const;//对于具体的小精灵打印全部属性
    void printspecial_atk() const;//打印特攻的名字
    string check_name() const;//查看小精灵名
    void attack(Pokemon& another_Pokemon);//对另一只小精灵进行攻击 概率闪避、概率暴击
    UDPPokemon* getUDP() const;//做成UDPdata
private:
    string name;//小精灵名字
    int special_ATK;//特攻数值
    string special_ATK_name;//特攻名字
};
#endif // POKEMON_H
