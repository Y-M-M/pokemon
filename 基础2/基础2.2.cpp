//2、类与对象实验
// 2.2 编写C++程序完成“矩阵”类以下功能：
// （1） 用类来实现矩阵，定义一个矩阵的类，属性包括：
//  矩阵大小，用 lines, rows（行、列来表示）；
//  存贮矩阵的数组指针，根据矩阵大小动态申请（new）。
// （2） 矩阵类的方法包括：
//  构造函数，参数是矩阵大小，需要动态申请存贮矩阵的数组；
//  析构函数，需要释放矩阵的数组指针；
//  拷贝构造函数，需要申请和复制数组；
//  输入，可以从 cin 中输入矩阵元素；
//  输出，将矩阵格式化输出到 cout；
//  矩阵相加的函数，实现两个矩阵相加的功能，结果保存在另一个矩阵类，但必须矩阵大小相同；
//  矩阵相减的函数，实现两个矩阵相减的功能，结果保存在另一个矩阵类，但必须矩阵大小相同。
// （3） 定义三个矩阵：A1、A2、A3；
// （4） 初始化 A1、A2；
// （5） 计算并输出 A3 = A1 加 A2，A3=A1 减 A2；（要求及提示：最好能实现对赋值操作符“=”的重载；注意检查“自赋值”、释放“旧元素”）
// （6） 用 new 动态创建三个矩阵类的对象：pA1、pA1、pA3；
// （7） 初始化 pA1、pA2；
// （8） 计算并输出 pA3=pA1 加 pA2，pA3=pA1 减 pA2；
// （9） 释放 pA1、pA2、pA3。

// 定义Matrix类 成员包括构造函数、析构函数，行、列、数组首地址、矩阵相加函数、矩阵相减函数
// 定义三个矩阵A1，A2，A3，用指针pA1、pA2和pA3指向三个矩阵

#include <iostream>
using namespace std;

class Matrix
{
    public:
        Matrix(int lines, int rows, int input);//构造函数
        Matrix(int lines, int rows);
        Matrix(const Matrix &another_matrix);//拷贝构造函数
        ~Matrix();//析构函数
        Matrix &operator=(const Matrix &ans);//=重载，作为类成员函数
        friend Matrix operator+(const Matrix &A1, const Matrix &A2);//+重载，作为友元函数
        friend Matrix operator-(const Matrix &A1, const Matrix &A2);//-重载，作为友元函数
        friend ostream& operator <<(ostream& Ostr, Matrix &A);//<<重载，作为友元函数
    private:
        int lines;//行
        int rows;//列
        int **matrix;//矩阵存储元素
};

Matrix::Matrix(int lines, int rows, int input)//需要用户输入元素的构造函数
{
    this->lines = lines;
    this->rows = rows;
    int **matrix = new int*[lines];
    this->matrix = matrix;
    for(int i = 0; i < lines; i++)
    {
        matrix[i] = new int[rows];
        for(int j = 0; j < rows; j++)
        {
            cin >> matrix[i][j];
        }
    }
}

Matrix::Matrix(int lines, int rows)//构造全部值为0的矩阵
{
    this->lines = lines;
    this->rows = rows;
    int **matrix = new int*[lines];
    this->matrix = matrix;
    for(int i = 0; i < lines; i++)
    {
        matrix[i] = new int[rows];
        for(int j = 0; j < rows; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &another_matrix)//拷贝构造函数
{
    this->lines = another_matrix.lines;
    this->rows = another_matrix.rows;
    int **matrix = new int*[this->lines];
    for(int i = 0; i < this->lines; i++)
    {
        matrix[i] = new int[this->rows];
        for(int j = 0; j < this->rows; j++)
        {
            matrix[i][j] = another_matrix.matrix[i][j];
        }
    }
}

Matrix::~Matrix()//析构函数
{
    for(int i = 0; i < lines; i++)
    {
        delete []matrix[i];
    }
    delete []matrix;
}



Matrix & Matrix:: operator=(const Matrix &ans)//"="重载
{
    if(this != &ans)//检查自赋值
    {
        for(int i = 0; i < lines; i++) delete [] matrix[i];
        delete []matrix;//释放旧元素
        matrix = new int*[lines];
        for(int i = 0; i < lines; i++)
        {
            matrix[i] = new int[rows];
            for(int j = 0; j < rows; j++)
            {
                matrix[i][j] = ans.matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix operator+(const Matrix &A1, const Matrix &A2)//"+"运算符重载
{
    Matrix A3(A1.lines, A1.rows);
    for(int i = 0; i < A3.lines; i++)
    {
        for(int j = 0; j < A3.rows; j++)
        {
            A3.matrix[i][j] = A1.matrix[i][j] + A2.matrix[i][j];
        }
    }
    return A3;
}

Matrix operator-(const Matrix &A1, const Matrix &A2)//"-"运算符重载
{
    Matrix A3(A1.lines, A1.rows);
    for(int i = 0; i < A3.lines; i++)
    {
        for(int j = 0; j < A3.rows; j++)
        {
            A3.matrix[i][j] = A1.matrix[i][j] - A2.matrix[i][j];
        }
    }
    return A3;
}

ostream &operator <<(ostream &Ostr, Matrix &A)//"<<"运算符重载，输出矩阵
{
    for(int i = 0; i < A.lines; i++)
    {
        for(int j = 0; j < A.rows; j++)
        {
            Ostr << A.matrix[i][j] << " "; 
        }
        Ostr << endl;
    }
    return Ostr;
}

int main()
{
    cout << "本程序实现矩阵相加和相减。" << endl;
    cout << "请输入需要进行计算的两个矩阵的行和列(您需要保证两个矩阵的行与列分别相等)：" << endl;
    int lines, rows;
    cin >> lines >> rows;

    cout << "接下来请输入第一个矩阵A1：" << endl;
    Matrix A1(lines, rows, 1);
    cout << "请检查您输入的矩阵A1，如下所示：" << endl;
    cout << A1;

    cout << "接下来请输入第二个矩阵A2：" << endl;
    Matrix A2(lines, rows, 1);
    cout << "请检查您输入的矩阵A2，如下所示：" << endl;
    cout << A2;

    Matrix A3(lines, rows);

    A3 = A1 + A2;
    cout << "矩阵A1+A2的结果如下：" << endl;
    cout << A3;

    A3 = A1 - A2;
    cout << "矩阵A1-A2的结果如下：" << endl;
    cout << A3;
    return 0;
}
