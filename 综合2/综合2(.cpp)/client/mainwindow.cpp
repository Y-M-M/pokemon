#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "login.h"

QDataStream &operator<<(QDataStream &stream, const User &user)//运算符重载，将User写入stream
{
    stream << user.username;
    stream << user.port;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, User &user)//运算符重载，从stream中读取User
{
    stream >> user.username;
    stream >> user.port;

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const UserData &userData)//运算符重载，将UserData写入stream
{
    stream<<userData.username;
    for(int i = 0; i < 3; i++)
        stream<<*(userData.pokemon[i]);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, UserData &userData)//运算符重载，从stream中读取UserData
{
    stream>>userData.username;
    for(int i = 0; i < 3; i++)
    {
        UDPPokemon *temp=new UDPPokemon;
        stream>>*temp;
        userData.pokemon.append (temp);
    }

    return stream;
}

MainWindow::MainWindow(QWidget *parent, Login *login)
    : QMainWindow(parent)//构造函数
    , ui(new Ui::MainWindow)
{
    pokemon = login->getPokemon();//将login的pokemon继承到MainWindow
    username = login->getUsername();//将login的用户名继承到MainWindow
    port = login->getPort();//将login的用户随机端口继承到MainWindow
    ui->setupUi(this);//将界面设计应用到当前的MainWindow对象上

    mode = 0;//初始设置为不显示用户模式

    client = new QUdpSocket(this);
    server = new QUdpSocket(this);
    server->bind(QHostAddress:: LocalHost, port);//将server和本地网络中client端口绑定，监听

    connect(server, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
    //将server的信号连接到this的槽函数，当readyRead()信号来临时，调用readPendingDatagrams()
    m_pPkmGroup=new QButtonGroup(this);//创建按钮组
    m_pPkmGroup->addButton (ui->radioButton_1, 0);//添加按钮到按钮组
    m_pPkmGroup->addButton (ui->radioButton_2, 1);
    m_pPkmGroup->addButton (ui->radioButton_3, 2);

    ui->radioButton_1->setChecked (true);//将radioButton_1的单选按钮设置为选中状态
    ui->labelWho->setText ("My Pokemon");//将ui中LabelWho的标签文本设置为My Pokemon
    ui->labelInfo->setText (this->getInfo (0));//将ui中LabelInfo的标签文本设置为getInfo(0)的返回值
    connect(m_pPkmGroup, &QButtonGroup::buttonClicked, this, &MainWindow::ReceiveSelect);
    //将m_pPkmGroup的信号与this的槽函数相关联，当buttonClicked发生时，调用ReceiveSelect
    connect(ui->BtnOnline, SIGNAL(clicked(bool)), this, SLOT(Online_clicked()));
    connect(ui->BtnAllUsers, SIGNAL(clicked(bool)), this, SLOT(Allusers_clicked()));
    connect(ui->BtnLoginOut, SIGNAL(clicked(bool)), this, SLOT(Loginout_clicked()));
    connect(ui->listWidgetUsers, &QListWidget::currentRowChanged, this, &MainWindow::Users_changed);

    ui->showInfo->setHidden (true);
    ui->listWidgetUsers->setHidden (true);//不显示用户
}

MainWindow::~MainWindow()//析构函数
{
    delete ui;

    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);//通过dsOut对data进行读写
    dsOut<<SIGNOUT<<username<<port;//登出的UDP
    QHostAddress serverAddress = QHostAddress("127.0.0.1");
    client->writeDatagram(data.data(), data.size(),serverAddress, 6665);
    //将data通过client发送给本地端口6665

    delete server;
    delete client;
}

void MainWindow::readPendingDatagrams()//处理更新用户的数据报
{
    QByteArray data;
    data.resize(server->pendingDatagramSize());
    server->readDatagram(data.data(), data.size());
    QDataStream dsIn(&data,QIODevice::ReadWrite);//用dsIn读写data

    SIGNAL_TYPE dataKind;
    dsIn >> dataKind;//从data中获取dataKind
    if(dataKind == ONLINEUSERS)//更新目前在线用户
    {
        for(int i = 0; i < onlineusers.length(); i++)
        {
            delete onlineusers[i];
        }
        onlineusers.clear();

        while(!dsIn.atEnd())
        {
            qInfo() << "成功收到一个在线用户";
            User *user = new User;
            dsIn>>*user;
            onlineusers.append(user);
        }
    }
    else if(dataKind == ALLUSERS)//更新所有用户
    {
        for(int i = 0; i < allusers.length(); i++)
        {
            delete allusers[i];
        }
        allusers.clear();

        while(!dsIn.atEnd())
        {
            qInfo() << "成功收到一个注册用户";
            UserData *userdata = new UserData;
            dsIn>>*userdata;
            qInfo() << userdata->username;
            allusers.append(userdata);
        }
    }
}

void MainWindow:: ReceiveSelect(QAbstractButton* button)//显示选择的小精灵信息
{
    int buttonId = m_pPkmGroup->id(button);
    switch(buttonId)
    {
        case 0:
            ui->labelInfo->setText (this->getInfo (0));//labelInfo显示第一个宠物小精灵的信息
            break;
        case 1:
            ui->labelInfo->setText (this->getInfo (1));//显示第二个宠物小精灵的信息
            break;
        case 2:
            ui->labelInfo->setText (this->getInfo (2));//显示第三个宠物小精灵的信息
            break;
    }
}

QString MainWindow:: getInfo(unsigned int index)//获取pokemon信息
{
    UDPPokemon *current_pokemon;
    if(this->mode != 2)
    {
        current_pokemon = pokemon[index];
    }
    else//mode = 2，显示全部用户
    {
        //或许当前选中用户的指定pokemon
        current_pokemon = allusers[ui->listWidgetUsers->currentRow()-1]->pokemon[index];
    }
    QString information, temp;
    information = information + "name:" + current_pokemon->name;
    if(current_pokemon->kind == HIGH_ATK)
    {
        information = information + "\nkind:" + "HIGH_ATK";
    }
    else if(current_pokemon->kind == HIGH_DF)
    {
        information = information + "\nkind:" + "HIGH_DF";
    }
    else if(current_pokemon->kind == HIGH_HP)
    {
        information = information + "\nkind:" + "HIGH_HP";
    }
    else if(current_pokemon->kind == HIGH_SPEED)
    {
        information = information + "\nkind:" + "HIGH_SPEED";
    }
    information = information + "\nlevel:" + temp.setNum(current_pokemon->level);
    information = information + "\nmax_EXP:" + temp.setNum(current_pokemon->max_EXP);
    information = information + "\nEXP:" + temp.setNum(current_pokemon->EXP);
    information = information + "\nATK:" + temp.setNum(current_pokemon->ATK);
    information = information + "\nmax_HP:" + temp.setNum(current_pokemon->max_HP);
    information = information + "\nHP:" + temp.setNum(current_pokemon->HP);
    information = information + "\nDF:" + temp.setNum(current_pokemon->DF);
    information = information + "\nspeed:" + temp.setNum(current_pokemon->speed);
    information = information + "\nspecial_ATK_name:" + current_pokemon->special_ATK_name;
    information = information + "\nspecial_ATK:" + temp.setNum(current_pokemon->special_ATK);
    information += '\n';

    return information;
}

void MainWindow:: Loginout_clicked()//关闭窗口
{
    close();
}

void MainWindow:: Online_clicked()//online按钮被点击时
{
    if(((ui->showInfo->isHidden()) && (ui->listWidgetUsers->isHidden())) || mode == 2)
    {
        if(mode == 2)//如果当前是显示全部用户模式，将labelInfo的信息改为自己的小精灵的
        {
            ui->radioButton_1->setChecked(true);//默认选中第一个宠物小精灵并显示信息
            ui->labelWho->setText ("My Pokemon");
            ui->labelInfo->setText(this->getInfo(0));
        }

        this->mode = 1;//显示在线用户模式
        QByteArray data;
        QDataStream dsOut(&data, QIODevice::ReadWrite);//用dsOut来控制data的输入输出
        dsOut<<ONLINEUSERS<<username<<port;//发送类型，用户名以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环
        client->writeDatagram(data.data(), data.size(), serverAddress, 6665);
        //将data写入client并发送到本地端口6665

        if(server->waitForReadyRead (600))//在600ms内收到数据报
        {
            readPendingDatagrams();//接收显示用户信息的数据报

            //显示在线用户及其端口
            ui->listWidgetUsers->clear();
            ui->showInfo->setText("Online Users");
            ui->listWidgetUsers->addItem ("Username\tPort");

            for(int i = 0; i < this->onlineusers.length(); i++)
                ui->listWidgetUsers->addItem(tr("%1\t%2").
                                             arg (this->onlineusers[i]->username).
                                             arg(this->onlineusers[i]->port));

            ui->showInfo->setHidden(false);
            ui->listWidgetUsers->setHidden(false);
        }
        else//连接超时
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
            msgBox.setWindowTitle("Get Data Failed");
            msgBox.setText("Connect Failed");
            msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
            msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
            msgBox.exec(); // 同步地显示消息框并等待用户响应
        }
    }
    else//当前已经在显示online用户，重复点击隐藏
    {
        ui->showInfo->setHidden(true);
        ui->listWidgetUsers->setHidden(true);
        this->mode=0;//不显示的模式
    }
}

void MainWindow::Allusers_clicked()//当alluser按钮被点击时
{
    if((ui->showInfo->isHidden() && ui->listWidgetUsers->isHidden ()) || mode == 1)
    {
        this->mode=2;//显示全部用户模式

        if (client == nullptr || server == nullptr)
        {
            QMessageBox::critical(this, "Error", "Client or Server is not initialized.");
            return;
        }

        QByteArray data;
        QDataStream dsOut(&data, QIODevice::ReadWrite);//通过dsOut对data进行读写
        dsOut<<ALLUSERS<<username<<port;//发送类型，用户名以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(data.data(), data.size(),serverAddress, 6665);

        if(server->waitForReadyRead(600))//在600ms以内收到消息
        {
            qInfo() << "成功收到allusers的数据报" ;
            this->readPendingDatagrams();//阅读用户信息的数据报

            ui->listWidgetUsers->clear();
            qDebug() << "listWigetUsers cleared()";
            ui->showInfo->setText("ALL Users");
            ui->listWidgetUsers->addItem("Username");

            for(int i = 0; i < this->allusers.length(); i++)//显示每一个用户的用户名
            {
                qDebug() << "成功显示一个用户";
                ui->listWidgetUsers->addItem(tr("%1").
                                             arg (this->allusers[i]->username));
            }

            if (!this->allusers.isEmpty() && this->allusers[0] != nullptr)
            {
                ui->listWidgetUsers->setCurrentRow(1); // 默认选中第一个用户
                ui->labelWho->setText(tr("%1's Pokemon").arg(this->allusers[0]->username));
            }

            ui->showInfo->setHidden (false);
            ui->listWidgetUsers->setHidden (false);
        }
        else//连接超时
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
            msgBox.setWindowTitle("Get Data Failed");
            msgBox.setText("Connect Failed");
            msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
            msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
            msgBox.exec(); // 同步地显示消息框并等待用户响应
        }
    }
    else//被重复点击时，切换为mode 0
    {
        ui->showInfo->setHidden(true);
        ui->listWidgetUsers->setHidden(true);

        this->mode = 0;//不显示的模式

        ui->radioButton_1->setChecked(true);
        ui->labelWho->setText ("My Pokemon");
        ui->labelInfo->setText (this->getInfo (0));
    }
}

void MainWindow:: Users_changed(int currentRow)//更换选中的用户时
{
    if(currentRow > 0 && this->mode == 2)//显示当前选中用户的小精灵的全部信息
    {
        ui->labelWho->setText(tr("%1's Pokemon").arg(this->allusers[currentRow-1]->username));
        ui->radioButton_1->setChecked (true);
        ui->labelInfo->setText(this->getInfo(0));
    }
}

