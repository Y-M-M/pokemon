#include "pokemon.h"
using namespace std;

//用vector存储宠物小精灵的名字和特殊攻击的名字
vector<string> pokemon_name = {"可达鸭", "小火龙", "飞腿郎", "杰尼龟", "卡拉卡拉", "独角犀牛",
                               "皮皮", "吉利蛋", "皮卡丘", "妙蛙种子", "小火马", "呆呆兽"};
vector<string> special_atk_name = {"水之波动", "火焰攻击", "下盘踢", "水枪", "掷泥",
                                   "撞击", "唱歌", "拍击", "电击", "藤鞭子",
                                   "火花", "咒术"};


QDataStream &operator<<(QDataStream &stream, const UDPPokemon& the_pokemon)//运算符重载，将UDPPokemon写入流
{
    stream << the_pokemon.name;
    stream << the_pokemon.kind;
    stream << the_pokemon.level;
    stream << the_pokemon.max_EXP;
    stream << the_pokemon.EXP;
    stream << the_pokemon.ATK;
    stream << the_pokemon.max_HP;
    stream << the_pokemon.HP;
    stream << the_pokemon.DF;
    stream << the_pokemon.speed;
    stream << the_pokemon.special_ATK_name;
    stream << the_pokemon.special_ATK;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, UDPPokemon& the_pokemon)//运算符重载，从流中读取UDPPokemon
{
    stream >> the_pokemon.name;
    stream >> the_pokemon.kind;
    stream >> the_pokemon.level;
    stream >> the_pokemon.max_EXP;
    stream >> the_pokemon.EXP;
    stream >> the_pokemon.ATK;
    stream >> the_pokemon.max_HP;
    stream >> the_pokemon.HP;
    stream >> the_pokemon.DF;
    stream >> the_pokemon.speed;
    stream >> the_pokemon.special_ATK_name;
    stream >> the_pokemon.special_ATK;
    return stream;
}

BASE_Pokemon::BASE_Pokemon()//构造函数
{
    grade = 1;
    max_EXP = 20;
    EXP = 0;
    normal_ATK = 20;
    DF = 15;
    HP = 90;
    max_HP = 90;
    speed = 10;
}
//BASE_Pokemon的构造函数
//初始经验为0，初始等级为1，基础攻击为30，基础防御为15，基础HP为90，基础速度为10
//针对每种类型优化其强项

BASE_Pokemon::~BASE_Pokemon(){}//析构函数，没有申请内存，不需要做什么

BASE_Pokemon::BASE_Pokemon(const BASE_Pokemon &the_pokemon)//拷贝构造函数
{
    grade = the_pokemon.grade;
    max_EXP = the_pokemon.max_EXP;
    normal_ATK = the_pokemon.normal_ATK;
    DF = the_pokemon.DF;
    HP = the_pokemon.HP;
    max_HP = the_pokemon.max_HP;
    speed = the_pokemon.speed;
}

//对副属性的额外增加
void BASE_Pokemon:: base_add_ATK()
{
    normal_ATK += 3 * grade;
}

void BASE_Pokemon:: base_add_DF()
{
    DF += 5 * grade;
}

void BASE_Pokemon:: base_add_HP()
{
    max_HP += 10 * grade;
    HP = max_HP;
}

void BASE_Pokemon:: base_add_speed()
{
    speed += 1 * grade;
}

//升级时增加普通属性、对于主属性的基础额外增加
void BASE_Pokemon:: add_ATK()
{
    normal_ATK += 10 * grade;
}

void BASE_Pokemon:: add_DF()
{
    DF += 15 * grade;
}

void BASE_Pokemon:: add_HP()
{
    max_HP += 60 * grade;
    HP = max_HP;
}

void BASE_Pokemon:: add_speed()
{
    speed += 4 * grade;
}

//获胜时增加经验，根据击败的精灵等级不同获得不一样多的经验
void BASE_Pokemon:: add_EXP(const BASE_Pokemon& fail_pokemon)//战胜时增加经验
{
    EXP += 10 * fail_pokemon.check_grade();
}

void BASE_Pokemon:: addgrade()//升级，提高升级所需经验上限
{
    grade++;
    max_EXP += 20 * grade;
}

int BASE_Pokemon:: check_grade() const//查看等级，只读
{
    return grade;
}

int BASE_Pokemon:: check_DF() const//查看防御，只读
{
    return DF;
}

void BASE_Pokemon:: less_HP(int damage)//只写，减少血量
{
    HP -= damage;
}

int BASE_Pokemon:: check_ATK() const//只读，查看普通攻击
{
    return normal_ATK;
}

int BASE_Pokemon:: check_speed() const//只读，查看速度
{
    return speed;
}

int BASE_Pokemon:: check_max_EXP() const//只读，查看经验上限
{
    return max_EXP;
}

int BASE_Pokemon:: check_EXP() const//只读，查看经验
{
    return EXP;
}

int BASE_Pokemon:: check_max_HP() const //只读，查看血量上限
{
    return max_HP;
}

int BASE_Pokemon:: check_HP() const //只读，查看当前血量
{
    return HP;
}

void BASE_Pokemon:: top_HP()//只写，加满血量
{
    HP = max_HP;
}

int BASE_Pokemon:: zero_HP()//只读，判断血量是否降到0
{
    if(HP <= 0) return 1;
    else return 0;
}

int BASE_Pokemon:: isupdate() const//只读，判断是否可以升级
{
    if(EXP >= max_EXP) return 1;
    else return 0;
}

int BASE_Pokemon:: dodge(const BASE_Pokemon &another_Pokemon) const//判断是否闪避
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, speed);
    int random_value = dis(gen);
    int isdodge = (random_value > another_Pokemon.speed) ? 1 : 0;
    return isdodge;
}

int BASE_Pokemon:: critical_strike(const BASE_Pokemon& another_Pokemon) const//只读，概率性暴击
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, speed);
    int random_value = dis(gen);
    int isdodge = (random_value > another_Pokemon.speed) ? 1 : 0;
    return isdodge;
}

void BASE_Pokemon:: printbase() const//打印精灵及其属性
{
    cout << "等级: " << grade << endl;
    cout << "目前所获经验值: " << EXP << endl;
    cout << "升到下一级所需经验值: " << max_EXP << endl;
    cout << "血量上限: "  << max_HP << endl;
    cout << "当前血量: " << HP << endl;
    cout << "防御: " << DF << endl;
    cout << "速度: " << speed << endl;
    cout << "普通攻击: " << normal_ATK << endl;
}



TYPE_Pokemon:: TYPE_Pokemon(const Pokemon_kind& the_kind): BASE_Pokemon()//TYPE_Pokemon的构造函数
{
    kind = the_kind;
}

TYPE_Pokemon:: ~TYPE_Pokemon(){ }//TYPE_Pokemon的析构函数，没有申请内存，不需要做什么

Pokemon_kind TYPE_Pokemon:: check_kind() const//查看类型，只读
{
    return kind;
}

TYPE_Pokemon:: TYPE_Pokemon(const TYPE_Pokemon &the_pokemon): BASE_Pokemon(the_pokemon)//拷贝构造函数
{
    kind = the_pokemon.kind;
}

//打印private成员变量小精灵类型
void TYPE_Pokemon:: printtype() const
{
    cout << "kind: ";
    switch(kind)
    {
    case 0:
        cout << "HIGH_ATK" << endl;
        break;
    case 1:
        cout << "HIGH_DF" << endl;
        break;
    case 2:
        cout << "HIGH_HP" << endl;
        break;
    case 3:
        cout << "HIGH_SPEED" << endl;
        break;
    }
}

//构造函数，给不同的宠物小精灵不同的属性
Pokemon:: Pokemon(const string &the_name, const Pokemon_kind& this_kind): TYPE_Pokemon(this_kind)
{
    name = the_name;
    special_ATK = 60;
    switch(this_kind)//针对不同的类别增加主属性
    {
    case HIGH_ATK:
        special_add_ATK();
        break;
    case HIGH_DF:
        special_add_DF();
        break;
    case HIGH_HP:
        special_add_HP();
        break;
    case HIGH_SPEED:
        special_add_speed();
        break;
    }
    if(the_name == pokemon_name[0])
    {
        special_ATK_name = special_atk_name[0];
        base_add_speed();
    }
    else if(the_name == pokemon_name[1])
    {
        special_ATK_name = special_atk_name[1];
        base_add_ATK();
        special_ATK += 10;
    }
    else if(the_name == pokemon_name[2])
    {
        special_ATK_name = special_atk_name[2];
        base_add_DF();
    }
    else if(the_name == pokemon_name[3])
    {
        special_ATK_name = special_atk_name[3];
        base_add_HP();
    }
    else if(the_name == pokemon_name[4])
    {
        special_ATK_name = special_atk_name[4];
        base_add_DF();
    }
    else if(the_name == pokemon_name[5])
    {
        special_ATK_name = special_atk_name[5];
        base_add_ATK();
        special_ATK += 10;
    }
    else if(the_name == pokemon_name[6])
    {
        special_ATK_name = special_atk_name[6];
        base_add_speed();
    }
    else if(the_name == pokemon_name[7])
    {
        special_ATK_name = special_atk_name[7];
        base_add_HP();
    }
    else if(the_name == pokemon_name[8])
    {
        special_ATK_name = special_atk_name[8];
        base_add_speed();
    }
    else if(the_name == pokemon_name[9])
    {
        special_ATK_name = special_atk_name[9];
        base_add_ATK();
        special_ATK += 10;
    }
    else if(the_name == pokemon_name[10])
    {
        special_ATK_name = special_atk_name[10];
        base_add_DF();
    }
    else if(the_name == pokemon_name[11])
    {
        special_ATK_name = special_atk_name[11];
        base_add_HP();
    }
}

Pokemon:: ~Pokemon(){}//没有动态申请内存，不需要做什么

Pokemon::Pokemon(const Pokemon &the_pokemon): TYPE_Pokemon(the_pokemon)
{
    name = the_pokemon.name;
    special_ATK = the_pokemon.special_ATK;
    special_ATK_name = the_pokemon.special_ATK_name;
}

//针对不同类型的宠物小精灵增加其主特长
void Pokemon:: special_add_ATK()
{
    add_ATK();
    add_ATK();
    special_ATK += 30 * check_grade();
}

void Pokemon:: special_add_DF()
{
    add_DF();
    add_DF();
}

void Pokemon:: special_add_HP()
{
    add_HP();
    add_HP();
}

void Pokemon:: special_add_speed()
{
    add_speed();
    add_speed();
}

void Pokemon:: add_special_ATK()
{
    special_ATK += 20 * check_grade();
}

void Pokemon:: update()//升级、更新参数
{
    addgrade();
    switch(check_kind())
    {
    case 0:
        special_add_ATK();//增加主属性
        add_DF();//增加普通属性
        add_HP();
        add_speed();
        if(name == pokemon_name[0]) base_add_speed();//增加副属性
        else if(name == pokemon_name[1]) base_add_ATK();
        else if(name == pokemon_name[2]) base_add_DF();
        break;
    case 1:
        special_add_DF();
        add_ATK();
        add_HP();
        add_speed();
        if(name == pokemon_name[3]) base_add_HP();
        else if(name == pokemon_name[4]) base_add_DF();
        else if(name == pokemon_name[5]) base_add_ATK();
        break;
    case 2:
        special_add_HP();
        add_ATK();
        add_DF();
        add_speed();
        if(name == pokemon_name[6]) base_add_speed();
        else if(name == pokemon_name[7]) base_add_HP();
        else if(name == pokemon_name[8]) base_add_ATK();
    case 3:
        special_add_speed();
        add_ATK();
        add_DF();
        add_HP();
        if(name == pokemon_name[9]) base_add_DF();
        else if(name == pokemon_name[10]) base_add_speed();
        else if(name == pokemon_name[11]) base_add_HP();
    }
}

void Pokemon:: printname() const//打印小精灵名字
{
    cout << "name: " << name << endl;
}

void Pokemon:: printspecial() const//对于具体的小精灵打印全部属性
{
    printtype();
    printname();
    printbase();
    cout << special_ATK_name << ": " << special_ATK << endl;
    cout << endl;
}

void Pokemon:: printspecial_atk() const//打印特攻的名字
{
    cout << special_ATK_name << endl;
}

string Pokemon:: check_name() const//查看小精灵名
{
    return name;
}

void Pokemon:: attack(Pokemon& another_Pokemon)//对另一只小精灵进行攻击 概率闪避、概率暴击
{
    cout << endl;
    cout << this->name << " attack." << endl;
    if(another_Pokemon.dodge(*this))//闪避
    {
        cout << another_Pokemon.name << " miss." << endl;
    }
    else
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 1);
        double randomValue = dis(gen);
        int isspecial = (randomValue > 0.6) ? 1 : 0;
        //40%的概率进行特殊攻击，60%的概率进行普通攻击
        int damage = 0;
        if(isspecial)
        {
            printspecial_atk();
            damage = special_ATK - another_Pokemon.check_DF();
            damage = (damage > 0.1 * special_ATK) ? damage : (0.1 * special_ATK);
            if(critical_strike(another_Pokemon))
            {
                damage *= 2;
                cout << "效果拔群!" << endl;
            }
            cout << "造成了" << damage << "点伤害！" << endl;
            another_Pokemon.less_HP(damage);
        }
        else
        {
            damage = check_ATK() - another_Pokemon.check_DF();
            damage = (damage > 0.1 * check_ATK()) ? damage : (0.1 * check_ATK());
            if(critical_strike(another_Pokemon))
            {
                damage *= 2;
                cout << "效果拔群!" << endl;
            }
            cout << "普通攻击，造成了" << damage << "点伤害!" << endl;
            another_Pokemon.less_HP(damage);
        }
    }
}

UDPPokemon* Pokemon:: getUDP() const
{
    UDPPokemon *attr = new UDPPokemon();
    attr->name = QString::fromStdString(name);
    attr->kind = check_kind();
    attr->level = check_grade();
    attr->max_EXP = check_max_EXP();
    attr->EXP = check_EXP();
    attr->max_HP = check_max_HP();
    attr->HP = check_HP();
    attr->DF = check_DF();
    attr->speed = check_speed();
    attr->special_ATK_name = QString::fromStdString(special_ATK_name);
    attr->special_ATK = special_ATK;
    attr->ATK = check_ATK();
    return attr;
}
