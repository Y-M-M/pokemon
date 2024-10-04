// 3、继承与派生实验
// 编写C++程序完成“形状”的以下功能：
// （1） 声明一个基类 Shape（形状），其中包含一个方法来计算面积；
// （2） 从 Shape 派生两个类：矩形类和圆形类；
// （3） 从矩形类派生正方形类；
// （4） 分别实现派生类构造函数、析构函数和其他方法；
// （5） 创建派生类的对象，观察构造函数、析构函数调用次序；
// （提示及要求：1，可通过在构造与析构函数中加入输出提示信息的方式观察
// 相关调用；可以使用 system("pause")进行程序的暂停；2，能够理解并说明每
// 一次构造与析构函数调用是哪个对象的调用，并观察和解释相关调用顺序及
// 其原因）
// （6） 对不同对象计算面积。

#include <iostream>
using namespace std;

class Shape//基类Shape
{
    public:
        double compute_area()
        {
            cout << "这是Shape()中的compute_area()函数。" << endl << endl;
            return 0;
        }
        Shape()
        {
            cout << "这是基类Shape的构造函数。" << endl << endl;
        }
        virtual ~Shape()
        {
            cout << "这是基类Shape的析构函数" << endl << endl;
        }
};

class Rectangle: public Shape//Shape的派生类
{
    public:
        Rectangle(const int length, const int width);//构造函数
        virtual ~Rectangle()//析构函数
        {
            cout << "这是一个长为"<< length << "宽为" << width << "的Rectangle的析构函数。" << endl << endl;
            cout << endl;
        }
        double compute_area();//计算面积
    protected:
        int length;
        int width;
};

Rectangle::Rectangle(const int length, const int width): Shape()
{
    this->length = length;
    this->width = width;
    cout << "这是一个长为" << length << "宽为" << width << "的Rectangle的构造函数" << endl << endl;
}

double Rectangle::compute_area()
{
    cout << "这是Rectangle类的compute_area()函数。" << endl;
    return length * width;
}   

class Square: public Rectangle//Rectangle的派生类
{
    public:
        Square(const int length);//构造函数
        ~Square()//析构函数
        {
            cout << "这是一个边长为" << length << "的Square的析构函数。" << endl << endl;
        }
};

Square::Square(const int length): Rectangle(length, length)//派生类Square
{
    cout << "这是一个边长为" << length << "的Square的构造函数。" << endl << endl;
}

class Circle: public Shape
{
    public:
        Circle(const int radius, const int center_x, const int center_y);//构造函数
        ~Circle()//析构函数
        {
            cout << "这是一个圆心位于(" << center_x << "," << center_y << ")" 
                << ", 半径为" << radius << "的圆的析构函数。" << endl << endl;
        }
        double compute_area();//计算面积
    private:
        int radius;
        int center_x;
        int center_y;
};

Circle::Circle(const int radius, const int center_x, const int center_y): Shape()
{
    this->radius = radius;
    this->center_x = center_x;
    this->center_y = center_y;
    cout << "这是一个圆心位于(" << center_x << "," << center_y << ")" 
        << ", 半径为" << radius << "的圆的构造函数。" << endl << endl;
}

double Circle::compute_area()
{
    cout << "这是Circle类的compute_area()函数。" << endl;
    return radius*radius*3.14;
}


int main()
{
    int opt = 1;
    while(opt)
    {    
        cout << "请输入您需要构造的图形(输入1构造矩形，输入2构造正方形，输入3构造圆形，输入0结束程序): " << endl;
        cin >> opt;
        if(opt == 1)
        {
            cout << "请按顺序输入矩形的长与宽：" << endl;
            int length = 0, width = 0;
            cin >> length >> width;
            Rectangle shape1(length, width);
            cout << "矩形的面积为" << endl << shape1.compute_area() << endl << endl;
            Shape &a = shape1;
            cout << "a.compute():" << endl;
            a.compute_area();
        }
        else if(opt == 2)
        {
            cout << "请输入正方形的边长: " << endl;
            int length; 
            cin >> length;
            Square shape2(length);
            cout << "正方形的面积为" << endl << shape2.compute_area() << "。" << endl << endl;
            Shape &a = shape2;
            cout << "a.compute():" << endl;
            a.compute_area();
        }
        else if(opt == 3)
        {
            cout << "请依次输入圆的半径和圆心坐标的x、y值: " << endl;
            int radius = 0, center_x = 0, center_y = 0;
            cin >> radius >> center_x >> center_y;
            Circle shape3(radius, center_x, center_y);
            cout << "圆的面积为" << endl << shape3.compute_area() << "。" << endl << endl;
            Shape &a = shape3;
            cout << "a.compute():" << endl;
            a.compute_area();
        }
        cout << endl;
    }
    return 0;
}


