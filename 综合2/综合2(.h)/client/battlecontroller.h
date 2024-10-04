#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

#include "pokemon.h"

class Battle_controller
{
public:
    Battle_controller(Pokemon& Pokemon1, Pokemon& Pokemon2);//构造函数
    ~Battle_controller();//析构函数
    void attack_each_other();//在统一时间线下相互攻击
    void battle();//控制战斗的开始，输出信息、将血量加满
    int judge_end() const;//判断战斗是否结束，增加惊艳、升级
private:
    int time1;//第一个宠物小精灵的等待进度条
    int time2;//第二个宠物小精灵的等待进度条
    //根据速度增加等待进度条，增加到max_time时开始攻击并清零进度条
    //速度快的更早攻击
    Pokemon& pokemon1;//宠物小精灵1
    Pokemon& pokemon2;//宠物小精灵2
};


#endif // BATTLECONTROLLER_H
