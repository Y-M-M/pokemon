//5、重载实验
// 5.2 对Point类重载＋＋和――运算符
//  编写C++程序完成以下功能：
// （1） Point 类的属性包括点的坐标（x，y）；
// （2） 实现 Point 类重载＋＋和――运算符：
//  ++p，--p，p++，p--；
//  ＋＋和――分别表示 x，y 增加或减少 1。

#include <iostream>
using namespace std;

class Point
{
    public:
        Point(const int x, const int y);//构造函数
        Point();//默认构造函数
        Point(const Point& anorher_point);//拷贝构造函数
        virtual ~Point();//析构函数
        Point& operator++();//运算符重载，作为成员函数
        Point& operator--();
        Point operator++(int t);
        Point operator--(int t);
        void printit();//打印点
    private:
        int x;
        int y;
};

Point::Point(const int x, const int y)//构造函数
{
    this->x = x;
    this->y = y;
}

Point::Point()//默认构造函数
{
    x = 0;
    y = 0;
}

Point::Point(const Point& another_point)//拷贝构造函数
{
    x = another_point.x;
    y = another_point.y;
}

Point::~Point()//析构函数
{
}

Point& Point::operator++()//前置自加运算符
{
    x++;
    y++;
    return *this;
}

Point& Point::operator--()//前置自减运算符
{
    x--;
    y--;
    return *this;
}

Point Point::operator++(int t)//后置自加运算符
{
    Point temp = *this;
    x++;
    y++;
    return temp;
}

Point Point::operator--(int t)//后置自减运算符
{
    Point temp = *this;
    x--;
    y--;
    return temp;
}

void Point::printit()//打印点的坐标
{
    cout << "(" << x << ", " << y << ")";
    cout << endl;
}

int main()
{
    cout << "请输入点的坐标: " << endl;
    int x = 0, y = 0;
    cin >> x >> y;
    Point one_point(x, y);
    Point new_point;
    cout << "目前点的坐标为：";
    one_point.printit();
    cout << "接下来进行运算" << endl;
    cout << "++Point的值为: ";
    new_point = ++one_point;
    new_point.printit();
    cout << "运算之后点的坐标为: ";
    one_point.printit();
    cout << "--Point的值为: ";
    new_point = --one_point;
    new_point.printit();
    cout << "运算之后的点的坐标为: ";
    one_point.printit();
    cout << "Point++的值为: ";
    new_point = one_point++;
    new_point.printit();
    cout << "运算之后的点的坐标为: ";
    one_point.printit();
    cout << "Point--的值为: ";
    new_point = one_point--;
    new_point.printit();
    cout << "运算之后的点的坐标为: ";
    one_point.printit();
    return 0;
}