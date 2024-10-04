#include "battlecontroller.h"

//构造函数
Battle_controller:: Battle_controller(Pokemon& Pokemon1, Pokemon& Pokemon2)
    :pokemon1(Pokemon1), pokemon2(Pokemon2)
{
    time1 = 0;
    time2 = 0;
}

Battle_controller:: ~Battle_controller(){} //析构函数，没有动态申请内存，不需要做什么



int Battle_controller:: judge_end(int& iswin, int* before_attr) const//判断战斗是否结束、增加经验、升级
{
    int substained = 1;
    if(pokemon1.zero_HP())
    {
        iswin = 0;
        cout << "战斗结束, 宠物小精灵";
        cout << pokemon2.check_name();
        cout << "获胜。" << endl;
        cout << endl;
        pokemon2.add_EXP(pokemon1);
        while(pokemon2.check_grade() < 15 && pokemon2.isupdate())
        {
            pokemon2.update(before_attr);
            pokemon2.printname();
            cout << "升级了！" << endl;
            cout << "升级后: " << endl;
            pokemon2.printspecial();
        }
        substained = 0;
    }
    else if(pokemon2.zero_HP())
    {
        iswin = 1;
        cout << "战斗结束, 宠物小精灵";
        cout << pokemon1.check_name();
        cout << "获胜。" << endl;
        cout << endl;
        pokemon1.add_EXP(pokemon2);
        while(pokemon1.check_grade() < 15 && pokemon1.isupdate())
        {
            pokemon1.update(before_attr);
            pokemon1.printname();
            cout << "升级了！" << endl;
            cout << "升级后: " << endl;
            pokemon1.printspecial();
        }
        substained = 0;
    }
    return substained;
}

int Battle_controller:: attack_each_other(int* before_attr)//在同一时间线下相互攻击
{
    time1 = 0, time2 = 0;
    int sustained = 1;
    int iswin = 0;
    while(sustained)
    {
        //进行攻击
        int speed1 = pokemon1.check_speed();
        int speed2 = pokemon2.check_speed();
        int max_time = speed1 > speed2 ? speed1 * 2 : speed2 * 2;
        time1 += speed1;
        time2 += speed2;
        if(time1 >= max_time && time2 >= max_time)
        {
            if(speed1 < speed2)
            {
                pokemon1.attack(pokemon2);
                time1 = 0;
            }
            else if(speed1 > speed2)
            {
                pokemon2.attack(pokemon1);
                time2 = 0;
            }
            else
            {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> dis(0, 1);
                double randomValue = dis(gen);
                int is1 = (randomValue > 0.5) ? 1 : 0;
                if(is1) pokemon1.attack(pokemon2), time1 = 0;
                else pokemon2.attack(pokemon1), time2 = 0;
            }
        }
        else if(time1 >= max_time)
        {
            pokemon1.attack(pokemon2);
            time1 = 0;
        }
        else if(time2 >= max_time){
            pokemon2.attack(pokemon1);
            time2 = 0;
        }
        //判断战斗是否结束
        sustained = judge_end(iswin, before_attr);
    }
    return iswin;
}

//控制战斗的开始，输出信息、将血量加满
int Battle_controller:: battle(int* before_attr)
{
    cout << "战斗开始!" << endl;
    cout << endl;
    pokemon1.printspecial();
    pokemon2.printspecial();
    cout << "这是" << pokemon1.check_name() << "和" << pokemon2.check_name() << "之间的战斗！" << endl;
    cout << endl;
    pokemon1.top_HP();
    pokemon2.top_HP();
    int iswin = attack_each_other(before_attr);
    pokemon1.top_HP();
    pokemon2.top_HP();
    return iswin;
}
