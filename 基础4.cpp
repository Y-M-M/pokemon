//实验四：I/O流实验
// 编写 C++程序完成猜价格游戏的以下功能：
// （1） 假定有一件商品，程序用随机数指定该商品的价格（1-1000 的整数）；
// （2） 提示用户猜价格，并输入：若用户猜的价格比商品价格高或低，对用户作出相应的提示；
// （3） 直到猜对为止，并给出提示。
// （提示及要求：1，要求使用 C++的输入输出方式（cin, cout），不能使用 C 语言的 printf 等；2，注意检查输入的合法性）
// 用类表示商品
// 成员：价格、比较函数、构造函数、析构函数

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Goods
{
    public:
        Goods(int price);
        ~Goods();
        int compare(int guss_number);
    private:
        int m_price;
};

Goods::Goods(int price)//构造函数
{
    this->m_price = price;
}

int Goods::compare(int guss_number)//比较用户输入的价格与商品的价格
{
    if(guss_number == this->m_price) return 0;
    else if(guss_number < this->m_price) return 1;
    else return -1;
}

Goods::~Goods(){}//析构函数，未申请内存，无需释放

int test_it(int guss_number)//判断输入是否合法
{
    if(guss_number > 0 && guss_number <= 1000) return 0;
    else return 1;
}


int main()
{
    srand((unsigned int)time(0));
    Goods one_item(rand()%1000 + 1);//随机生成商品价格，1～1000的随机数

    int flag = 1;
    while(flag)
    {
        cout << "请猜测商品的价格，输入1-1000之间的整数:" << endl;
        int guss_number;
        cin >> guss_number;
        while(test_it(guss_number))
        {
            cout << "您猜测的数字超出了范围，请重新输入:" << endl;
            cin >> guss_number;
        }
        int t = one_item.compare(guss_number);
        flag = t;
        if(t == -1)
        {
            cout << "您输入的价格比商品的价格还要高呢～" << endl;
        }
        else if(t == 1)
        {
            cout << "您输入的价格比商品的价格低哦，这件商品比您想象的还要贵一点" << endl;
        }
        else
        {
            cout << "猜测正确！太棒了，商品的价格就是" << guss_number << "!" << endl;
        }
    }
    return 0;
}



