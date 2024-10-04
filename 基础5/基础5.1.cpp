//5、重载实验
// 针对题目3的“形状”类，编写C++程序完成以下功能：
// （1） 将【形状】 中的基类计算面积的方法定义为虚函数，比较与【形状（A）】程
// 序的差异；
// （2） 将【形状】中的基类定义为抽象类，比较与【形状（A）】程序的差异。

#include <iostream>
using namespace std;

class Shape//基类Shape(抽象类)
{
    public:
        virtual double compute_area() = 0;//纯虚函数
        Shape()//构造函数
        {
            cout << "这是基类Shape的构造函数。" << endl << endl;
        }
        virtual ~Shape()//析构函数
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
        virtual double compute_area();//计算面积
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
    cout << "这是Rectangele的compute_area()函数。" << endl << endl;
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

Square::Square(const int length): Rectangle(length, length)
{
    cout << "这是一个边长为" << length << "Square的构造函数。" << endl << endl;
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
    cout << "这是Circle的compute_area()函数。" << endl << endl;
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
            cout << "矩形的面积为" << endl << shape1.compute_area() << "。" << endl << endl;
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