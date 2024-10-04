#include "login.h"
#include "ui_login.h"


//构造函数，默认无父窗口
Login::Login(QWidget *parent):
    QDialog(parent),//基类对话框的构造
    ui(new Ui::Login)//通过ui成员变量访问类中描述的界面设计
//申请内存，初始化成员变量ui，创建一个 Ui::Login 类的对象，->通过ui成员变量访问类中描述的界面设计
{
    ui->setupUi(this);//将界面设计应用到当前的Login对象上

    client = new QUdpSocket(this);//创建QUdpSocket，父对象是当前对象，当前对象销毁时，内存释放
    server = new QUdpSocket(this);
    //选择一个可用端口
    this->port = 6666;
    bool isOk=false;
    while(!isOk)//判断端口是否被占用，若是则默认端口加一
    {
        if(server->bind(QHostAddress::LocalHost, this->port))//将server绑定到本地地址和端口上，若端口未被占用，返回true，否则返回false
            isOk=true;
        else
            this->port++;
    }
    connect(ui->BtnSignUp, &QPushButton::clicked, this, &Login::SignUp_clicked);
    connect(ui->BtnSignIn, &QPushButton::clicked, this, &Login::SignIn_clicked);
}

Login::~Login()//析构函数
{
    delete ui;//释放ui的内存

    if(server)//如果指针不为空
    {
        server->close();//释放QUdpSoket占用的资源，并停止对该端口的监听
        delete server;//释放内存
    }
    if(client)//如果指针不为空
    {
        client->close();//释放QUdpSocket占用的资源，并停止对该端口的监听
        delete client;//释放内存
    }
}

QList<UDPPokemon*> Login::getPokemon()//只读，返回3个Pokemon
{
    return pokemon;
}

QString Login:: getUsername() const//只读，返回username
{
    return username;
}

unsigned int Login:: getPort() const//只读，返回端口号
{
    return port;
}

uint Login:: getpokemon_num() const
{
    return pokemon_num;
}

uint Login:: gethigh_level_pokemon() const
{
    return high_level_pokemon;
}

uint Login:: getvictory_num() const
{
    return victory_num;
}

uint Login:: getbattle_num() const
{
    return battle_num;
}

void Login:: readPendingDatagrams()//读取数据报
{
    QByteArray data;
    data.resize(server->pendingDatagramSize());//将data的大小调整到数据报的大小
    server->readDatagram(data.data(), data.size());//从server中读取一个数据报，存储到data中
    QDataStream dsIn(&data, QIODevice:: ReadOnly);//创建QDataStream对象 dsIn，用来对data进行读写操作
    SIGNAL_TYPE loginKind;
    QString username;
    QString pwd;
    dsIn>>loginKind;//从data中读取longinKind

    if(loginKind == SIGNINOK)//如果收到的消息是SIGNOK
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("登陆");
        msgBox.setText("登陆成功！");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应

        dsIn >> pokemon_num >> high_level_pokemon >> victory_num >> battle_num;
        for(uint i = 0; i < pokemon_num; i++)//读取服务端发送来的三个小精灵
        {
            UDPPokemon *udppokemon = new UDPPokemon;
            dsIn>>*udppokemon;
            pokemon.append(udppokemon);
            qDebug() << "接收到一个小精灵";
        }

        client->close();//释放client占用的资源，并停止对端口的监听
        delete client;//释放内存
        client = NULL;

        server->abort();//终止正在进行的任何网络操作
        server->close();//释放server占用的资源，并停止对端口的监听
        delete server;//释放内存

        server = nullptr;
        accept();//关闭对话框，触发accepted()信号
    }
    else if(loginKind == SIGNUPOK)//如果收到的消息是注册成功
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("注册");//标题为Sign Up
        msgBox.setText("注册成功！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        for(int i = 0; i < 3; i++)//接收服务端发送来的三个小精灵
        {
            qInfo() << "Signupok, 收到服务端发过来的一个小精灵";
            UDPPokemon *udppokemon = new UDPPokemon;
            dsIn>>*udppokemon;
            pokemon.append(udppokemon);
            qInfo() << udppokemon->name;
        }
        pokemon_num = 3;
        high_level_pokemon = 0;
        victory_num = 0;
        battle_num = 0;

        client->close();//释放资源
        delete client;
        client = NULL;

        server->abort();//终止正在进行的任何网络操作
        server->close();
        delete server;

        server = nullptr;
        accept();//关闭对话框，触发accepted()信号
    }
    else if(loginKind == NAMEEXIST)//如果收到的消息是用户名已存在
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("注册失败");
        msgBox.setText("用户名已存在。");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
    else if(loginKind == NOSUCHUSER)//没有这个用户
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("登录失败");
        msgBox.setText("用户不存在，请重新登录。");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
    else if(loginKind == PWDDIFF)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("登录失败");
        msgBox.setText("密码错误，请重新登录");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
    else if(loginKind == HAVESIGNIN)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("登陆失败");
        msgBox.setText("此帐号在线，无需登陆");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
}

void Login:: SignUp_clicked()//当注册按钮被点击时
{
    QString username = ui->lineEditName->text();//读取输入名字的文本框的数据
    this->username = username;
    QString pwd = ui->lineEditPwd->text();//读取输入密码的文本框的数据

    if(!username.isEmpty() && !pwd.isEmpty())//如果名字和密码读取成功
    {
        //将密码加密
        QByteArray temp;
        temp = QCryptographicHash:: hash(pwd.toUtf8(), QCryptographicHash:: Md5);
        pwd.clear();//清空pwd字符串
        pwd.append(temp.toHex());//将temp附加到pwd中

        QByteArray data;
        QDataStream dsOut(&data,QIODevice::ReadWrite);//用dsOut对data进行读写操作
        dsOut<<SIGNUP<<username<<pwd<<this->port;//写入data: 发送信号类型(SIGNUP)，用户名密码以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环
        client->writeDatagram(data.data(), data.size(),serverAddress, 6665);
        //将data写入client并发送到本地端口6665

        if(server->waitForReadyRead (600))//等待600ms以内
            this->readPendingDatagrams ();//读取收到的数据报
        else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
            msgBox.setWindowTitle("注册失败！");
            msgBox.setText("连接失败！");
            msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
            msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮，用户按下enter后会激活
            msgBox.exec(); // 同步地显示消息框并等待用户响应
        }
    }
    else//没能正确读取名字和密码
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("注册失败！");
        msgBox.setText("用户名和密码不能为空！");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
}

void Login:: SignIn_clicked()//当登录按钮被点击时
{
    QString username = ui->lineEditName->text ();//从文本框中读取username
    this->username = username;
    QString pwd = ui->lineEditPwd->text ();//从文本框中读取密码

    if(!username.isEmpty() && !pwd.isEmpty())//如果用户名和密码均不为空
    {
        //将密码转换为UTF-8编码的字节数组，加密
        QByteArray temp;
        temp = QCryptographicHash::hash ( pwd.toUtf8(), QCryptographicHash::Md5 );
        pwd.clear ();
        pwd.append(temp.toHex());

        QByteArray data;
        QDataStream dsOut(&data,QIODevice::ReadWrite);//通过dsOut对data进行读写操作
        dsOut<<SIGNIN<<username<<pwd<<this->port;//发送登录类型，用户名密码以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环
        client->writeDatagram(data.data(), data.size(),serverAddress, 6665);
        //将data写入client并写入本地端口6665

        if(server->waitForReadyRead (600))//如果在600ms内接收到了数据
            this->readPendingDatagrams ();//读取收到的数据报
        else//超时处理
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
            msgBox.setWindowTitle("Sign In Failed");
            msgBox.setText("Connect Failed");
            msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
            msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
            msgBox.exec(); // 同步地显示消息框并等待用户响应
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("登录失败！");
        msgBox.setText("用户名和密码均不能为空！");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮，enter键
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
}



































