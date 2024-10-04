//2、类与对象实验
// 2.1编写C++程序完成“圆形”以下功能
// (1)定义一个 Point 类，其属性包括点的坐标，提供计算两点之间距离的方法；（要求当用户不输入坐标数据时，能够默认为坐标原点（0，0））
// (2)定义一个圆形类，其属性包括圆心和半径；
// (3)创建两个圆形对象，提示用户输入圆心坐标和半径，判断两个圆是否相交，并输出结果；
// (4)观察圆形对象以及 Point 类成员的构造函数与析构函数的调用。
// （提示及要求：1，可通过在构造与析构函数中加入输出提示信息的方式观察相关调用；可以使用 system("pause")进行程序的暂停；
// 2，能够理解并说明每一次构造与析构函数调用是哪个对象的调用，并观察和解释相关调用顺序及其原因）

// 定义一个基类point和派生类circle
// point需提供计算两点之间距离的方法
// 圆形类新增属性半径
// 圆形类需要提供函数判断两圆是否相交
// 函数功能：计算两点间的距离，需要通过circle访问point的点的坐标->point的x与y应定义为protected类型
// 需要将circle当作函数参数->定义拷贝构造函数


#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class Point
{
    public:
        Point(int x = 0, int y = 0);//构造函数，若不穿入坐标，则默认为x、y
        Point(const Point &another_point);//拷贝构造函数
        ~Point();//析构函数
        double compute_distance(int x1 = 0, int y1 = 0);
    protected: //只允许在本类或其派生类的成员函数中被访问
        int x;
        int y;
};

Point::Point(int x, int y)//构造函数
{
    this->x = x;
    this->y = y;
    cout << "这是Point的构造函数，构造了一个(" << this->x 
        << ", " << this->y << ")的Point。" << endl;
}

Point::Point(const Point &another_point)//拷贝构造函数
{
    this->x = another_point.x;
    this->y = another_point.y;
    cout << "这是Point的拷贝构造函数，拷贝了一个(" << this->x 
        << ", " << this->y << ")的Point。" << endl;
}

Point::~Point()//析构函数，没有需要释放的内存，仅打印说明查看调用
{
    cout << "这是Point的析构函数，作用于(" << this->x 
        << "，" << this->y << ")的Point。" << endl;
}

double Point::compute_distance(int x1, int y1)//计算并返回两点之间的距离
{
    double square_sum = (this->x - x1)*(this->x - x1) + (this->y - y1) * (this->y - y1);
    double distance = sqrt(square_sum);
    cout << "两点之间的距离为：" << distance << endl;
    cout << endl;
    return distance;
}

class Circle: private Point //Circle作为Point的派生类
{
    public:
        int is_cross(Circle another_circle);
        Circle(int radius, int circle_center_x, int circle_center_y);
        Circle(const Circle &another_circle);
        ~Circle();
    private:
        int radius;
};

Circle::Circle(int radius, int circle_center_x = 0, int circle_center_y = 0): //Circle的构造函数
    Point(circle_center_x, circle_center_y)
{
    this->radius = radius;
    cout << "这是Circle的构造函数，创建了一个半径为 " << this->radius 
        << " 圆心坐标为(" << circle_center_x << ", " << circle_center_y << ")" << "的圆。\n";
}

Circle::Circle(const Circle &another_circle): Point(another_circle) //Circle的拷贝构造函数，会自动调用过Point的拷贝构造函数
{
    this->radius = another_circle.radius;
    cout << "这是Circle的拷贝构造函数，拷贝了一个半径为 " << this->radius 
        << " 圆心坐标为(" << this->x << ", " << this->y << ")" << "的圆。\n";
}

Circle::~Circle()//Circle的析构函数，未申请内存，无需释放
{
    cout << "这是Circle的析构函数，析构了一个半径为 " << this->radius 
        << " 圆心坐标为(" << this->x << ", " << this->y << ")" << "的圆。\n";
}

int Circle::is_cross(Circle another_circle)//判断两圆是否相交
{
    int flag;
    double distance = this->compute_distance(another_circle.x, another_circle.y);
    double radius_sum = this->radius + another_circle.radius;
    double radius_difference = abs(this->radius - another_circle.radius);
    if(distance < radius_sum && distance > radius_difference) flag = 1;//若两点间距离小于半径之和大于半径之积，则相交
    else flag = 0;
    cin.get();
    cin.get();
    return flag;
}//析构拷贝的another_circle，析构顺序与构造时的顺序相反，先析构Circle，再析构Point

int main()
{
    int opt;
    cout << "请输入第一个圆的半径：" << endl;
    int radius;
    cin >> radius;
    cout << "如果你需要输入第一个圆的坐标，请输入1，否则请输入0，我们会默认圆心在原点：" << endl;//由用户选择是否需要输入圆心坐标
    cin >> opt;
    int x = 0, y = 0;
    if(opt)
    {    
        cout << "请依次输入第一个圆圆心坐标，输入格式为x y：" << endl;
        cin >> x >> y;
    }
    Circle circle1(radius, x, y);//先调用基类的构造函数，创造Point，再调用Circle的构造函数
    cout << "请输入第二个圆的半径：" << endl;
    cin >> radius;
    cout << "如果你需要输入第二个圆的坐标，请输入1，否则请输入0，我们会默认圆心在原点：" << endl;
    cin >> opt;
    if(opt)
    {
        cout << "请依次输入第二个圆的圆心坐标，输入格式为x y：" << endl;
        cin >> x >> y;
    }
    Circle circle2(radius, x, y);//先调用基类的构造函数，创造Point，再调用Circle的构造函数
    int judge = circle1.is_cross(circle2);//先调用Point的拷贝构造函数，再调用Circle的拷贝构造函数，拷贝Circle
    if(judge) cout << "两圆相交。" << endl; 
    else 
    {
        cout << "两圆不相交。" << endl;
        cout << endl;
    }
    cin.get();
    return 0;
}//在return 0之前调用析构函数，先析构后创建的，再析构先创建的

// 测试样例
// 2 0 2 1 4 0

// 输出
// 这是Point的构造函数，构造了一个(0, 0)的Point。
// 这是circle的构造函数，创建了一个半径为 2 圆心坐标为(0, 0)的圆。
// 这是Point的构造函数，构造了一个(4, 0)的Point。
// 这是circle的构造函数，创建了一个半径为 2 圆心坐标为(4, 0)的圆。

// 这是Point的拷贝构造函数，拷贝了一个(4, 0)的Point。
// 这是circle的拷贝构造函数，拷贝了一个半径为 2 圆心坐标为(4, 0)的圆。

// 两点之间的距离为：4

// 这是circle的析构函数，析构了一个半径为 2 圆心坐标为(4, 0)的圆。
// 这是Point的析构函数，作用于(4，0)的Point。
// 两圆相切。
// 这是circle的析构函数，析构了一个半径为 2 圆心坐标为(4, 0)的圆。
// 这是Point的析构函数，作用于(4，0)的Point。
// 这是circle的析构函数，析构了一个半径为 2 圆心坐标为(0, 0)的圆。
// 这是Point的析构函数，作用于(0，0)的Point。



// - 构造函数什么时候被调用？
//   - 全局对象变量
//     - 在开始执行main()函数代码前，全局对象变量的构造函数被调用
//   - 局部(自动)对象变量
//     - 在定义局部对象变量时，对象的构造函数被调用
//   - 动态创建对象
//     - 对象申请动态空间成功后被调用
//   - 对象的成员
//     - 在容器对象被创建时，其构造函数被调用时执行
// - 析构函数什么时候被调用？
//   - 全局对象变量
//     - 在main()函数退出前，全局对象变量的析构函数被调用
//   - 局部(自动)对象变量
//     - 在局部对象变量的生命期结束之前，对象的析构函数被调用
//   - 动态创建的对象
//     - 在释放对象的动态空间之前，其析构函数功被调用
//   - 成员对象
//     - 容器对象被销毁时，成员对象的析构函数功后被调用
