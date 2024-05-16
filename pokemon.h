//可达鸭 水 弱点：草、电 3434 攻击型
//小火龙 火 弱点：水、地面、岩石 3434 攻击型
//飞腿郎 格斗 弱点：飞行、超能力、妖精 3846 攻击型
//杰尼龟 水 弱点：草、电 3343 防御型
//卡拉卡拉 地面 弱点：水、草、冰 2342 防御型
//独角犀牛 地面、岩石 弱点：水、草、冰、格斗、地面、钢 5562 防御型
//皮皮 妖精 弱点：毒、钢 5333 肉盾型
//吉利蛋 一般 弱点：格斗 15 1 1 3 肉盾型
//呆呆兽 水、超能力 弱点：草、电、虫、幽灵、恶 6441 肉盾型
//皮卡丘 电 弱点：地面 3436 敏捷型
//妙蛙种子 草/毒 弱点：火、冰、飞行、超能力 3333
//小火马 火 弱点：水、地面、岩石 3546 敏捷型

#include <string>

#define POWER_TYPE 0
#define FLESH_SHIELD_TYPE 1
#define DEFENSIVE_TYPE 2
#define AGILE_TYPE 3

using namespace std;

class Pokemon{
    public:
        Pokemon(string the_name);
        virtual ~Pokemon();
        virtual void attack() = 0;
    private:
        char kind;
        string name;
        char grade;
        int experience_value;
        int attack_power;
        int defensive_power;
        int HP;
        int attack_interval;
};