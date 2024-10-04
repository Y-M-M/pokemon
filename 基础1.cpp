/*实验一
1.假定矩阵大小为4*5（整型）
2.矩阵空间采用new动态申请，保存在指针中
3.定义矩阵初始化函数，可以从cin中输入矩阵元素
4.定义矩阵输出函数，将矩阵格式化输出到cout
5.定义矩阵相加的函数，实现两个矩阵相加的功能，结果保存在另一个矩阵中
6.定义矩阵相减的函数，实现两个矩阵相减的功能，结果保存在另个矩阵中
7.动态申请三个矩阵，A1、A2、A3
8.初始化A1、A2
9.计算并输出A3=A1+A2， A3=A1-A2
10.释放矩阵空间*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <map>
#include <utility>
using namespace std;

class Matrix
{
    public:
        void add (const Matrix &A1, const Matrix &A2);//矩阵相加函数
        void minus(const Matrix &A1, const Matrix &A2);//矩阵相减函数
        void printit();//矩阵输出函数
        Matrix(int begin);//构造函数
        Matrix();
        ~Matrix();//析构函数
    private:
        int **A;//二维数组存储矩阵
};

Matrix::Matrix(int begin)//初始化矩阵A1、A2
{
    A = new int*[4];
    for(int i = 0; i < 4; i++){ 
        A[i] = new int[5];
        for(int j = 0; j < 5; j++){
            cin >> A[i][j];
        }
    }
}
Matrix::Matrix()//初始化矩阵A3
{
    A = new int*[4];
    for(int i = 0; i < 4; i++){ 
        A[i] = new int[5];
        for(int j = 0; j < 5; j++){
            A[i][j] = 0;
        }
    }
}

Matrix::~Matrix()//析构函数
{
    for(int i = 0; i < 4; i++){
        delete [] A[i];
    }
    delete []A;
}

void Matrix::printit()//打印矩阵
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void Matrix::add(const Matrix &A1, const Matrix &A2)//矩阵相加
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            A[i][j] = A1.A[i][j] + A2.A[i][j];
        }
    }
}

void Matrix::minus(const Matrix &A1, const Matrix &A2)//矩阵相减
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            A[i][j] = A1.A[i][j] - A2.A[i][j];
        }
    }
}

int main(){
    cout << "请输入一个4行5列的矩阵A1:" << endl;
    Matrix A1(2);
    cout << "请输入一个4行5列的矩阵A2:"  << endl;
    Matrix A2(1);
    Matrix A3;
    cout << "矩阵A1:" << endl;
    A1.printit();
    cout << "矩阵A2:" << endl;
    A2.printit();
    cout << "矩阵A3:" << endl;
    A3.printit();
    A3.add(A1, A2);
    cout << "A1+A2的结果为：" << endl;
    A3.printit();
    A3.minus(A1, A2);
    cout << "A1-A2的结果为：" << endl;
    A3.printit();
    return 0;
}
