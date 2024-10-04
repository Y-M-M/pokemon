#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "login.h"

QDataStream &operator<<(QDataStream &stream, const User &user)//运算符重载，将User写入stream
{
    stream << user.username;
    stream << user.port;
    stream << user.pokemon_num;
    stream << user.high_level_pokemon;
    stream << user.victory_num;
    stream << user.battle_num;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, User &user)//运算符重载，从stream中读取User
{
    stream >> user.username;
    stream >> user.port;
    stream >> user.pokemon_num;
    stream >> user.high_level_pokemon;
    stream >> user.victory_num;
    stream >> user.battle_num;

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const UserData &userData)//运算符重载，将UserData写入stream
{
    stream << userData.username;
    stream << userData.pokemon_num;
    stream << userData.high_level_pokemon;
    stream << userData.victory_num;
    stream << userData.battle_num;
    for(uint i = 0; i < userData.pokemon_num; i++)
        stream<<*(userData.pokemon[i]);

    return stream;
}

QDataStream &operator>>(QDataStream &stream, UserData &userData)//运算符重载，从stream中读取UserData
{
    stream >> userData.username;
    stream >> userData.pokemon_num;
    stream >> userData.high_level_pokemon;
    stream >> userData.victory_num;
    stream >> userData.battle_num;
    for(uint i = 0; i < userData.pokemon_num; i++)
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
    pokemon_num = login->getpokemon_num();
    high_level_pokemon = login->gethigh_level_pokemon();
    victory_num = login->getvictory_num();
    battle_num = login->getbattle_num();

    ui->setupUi(this);//将界面设计应用到当前的MainWindow对象上

    mode = 0;//初始设置为不显示用户模式
    gamemode = 0;//初始设置为无比赛模式

    client = new QUdpSocket(this);
    server = new QUdpSocket(this);
    server->bind(QHostAddress:: LocalHost, port);//将server和本地网络中client端口绑定，监听

    connect(server, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
    //将server的信号连接到this的槽函数，当readyRead()信号来临时，调用readPendingDatagrams()
    connect(this, SIGNAL(sentSelect(QList<UDPPokemon*>,uint*)),
            this->selectPokemon, SLOT(recvSelect(QList<UDPPokemon*>,uint*)));
    connect(ui->BtnAllUsers, SIGNAL(clicked(bool)), this, SLOT(Allusers_clicked()));
    connect(ui->BtnOnline, SIGNAL(clicked(bool)), this, SLOT(Online_clicked()));
    connect(ui->BtnUpgrade, SIGNAL(clicked(bool)), this, SLOT(Upgrade_botton_clicked()));
    connect(ui->BtnDuel, SIGNAL(clicked(bool)), this, SLOT(Duel_botton_clicked()));
    connect(ui->BtnConfirm, SIGNAL(clicked(bool)), this, SLOT(BtnConfirm_clicked()));
    connect(ui->BtnLoginOut, SIGNAL(clicked(bool)), this, SLOT(Loginout_clicked()));

    connect(ui->listWidgetUsers, SIGNAL(currentRowChanged(int)), this, SLOT(Users_changed(int)));
    connect(ui->CbxUser, SIGNAL(currentIndexChanged(int)), this, SLOT(CbxUser_Changed(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(Combox_Changed(int)));
    connect(ui->BtnRate, SIGNAL(clicked(bool)), this, SLOT(BtnRate_clicked()));
    connect(ui->BtnBadge, SIGNAL(clicked(bool)), this, SLOT(BtnBadge_clicked(bool)));

    ui->labelUser->setText (tr("User:%1").arg(this->username));

    for(uint i = 0; i < this->pokemon_num; i++)//在combox中显示用户小精灵
        ui->CbxUser->addItem(this->pokemon[i]->name);
    ui->CbxUser->setCurrentIndex(0);

    ui->labelWho->setText (tr("%1's Pokemon").arg(this->username));
    ui->labelInfo->setText (this->getInfo (0));//显示选中小精灵的信息

    ui->showInfo->setHidden (true);
    ui->listWidgetUsers->setHidden (true);
    ui->labelServer->setHidden (true);
    ui->labelServer->setText ("Opponent");
    ui->comboBox->setHidden (true);
    ui->BtnConfirm->setHidden (true);
    ui->labelSPkm->setHidden (true);//暂不显示虚拟小精灵信息

    QPalette pa;//设置字体颜色
    pa.setColor(QPalette::WindowText,QColor(255,60,0));
    ui->labelInfo->setPalette(pa);
    ui->labelSPkm->setPalette (pa);

    ui->labelInfo->setObjectName ("labelInfo");
    ui->labelInfo->setStyleSheet ("#labelInfo{border-image:url(:/image/"+
                                 this->pokemon[0]->name+".webp);}");

    ui->labelSPkm->setObjectName ("labelSPkm");

    ui->labelNumBadge->setObjectName ("labelNumBadge");
    ui->labelNum->setText ("The Badge of Pkm Number:");
    ui->labelAdvBadge->setObjectName ("labelAdvBadge");
    ui->labelAdv->setText ("The Badge of Advanced Pkm:");//奖牌暂时隐藏
    ui->labelNum->setHidden (true);
    ui->labelNumBadge->setHidden (true);
    ui->labelAdv->setHidden (true);
    ui->labelAdvBadge->setHidden (true);
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

void MainWindow::readPendingDatagrams()//处理数据报
{
    QByteArray data;
    data.resize(server->pendingDatagramSize());
    server->readDatagram(data.data(), data.size());
    QDataStream dsIn(&data,QIODevice::ReadWrite);//用dsIn读写data

    SIGNAL_TYPE dataKind;
    dsIn >> dataKind;//从data中获取dataKind
    qDebug() << "dataKind为" << dataKind;
    qDebug() << "ANEWPOKEMON:" << ANEWPOKEMON;
    qDebug() << "是否相等" << (dataKind == ANEWPOKEMON);
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
            dsIn >> *userdata;
            qInfo() << userdata->username;
            qInfo() << "显示收到的用户的小精灵的数目" << userdata->pokemon.length() << userdata->pokemon_num;
            allusers.append(userdata);
        }
    }
    else if(dataKind == VIRPOKEMON)//收到发来的虚拟小精灵列表
    {
        qInfo() << "成功收到VIRPOKEMON的数据报";
        for(uint i = 0; i < virpokemon_num; i++)
        {
            delete virtual_pokemon[i];
        }
        virtual_pokemon.clear();

        dsIn >> virpokemon_num;
        qInfo() << "共收到了" << virpokemon_num << "个虚拟小精灵";
        for(uint i = 0; i < virpokemon_num; i++)
        {
            UDPPokemon* udppokemon = new UDPPokemon();
            dsIn >> *udppokemon;
            virtual_pokemon.append(udppokemon);
            qDebug() << "成功添加一个虚拟小精灵" << udppokemon->name << "至虚拟小精灵列表";
        }
    }
    else if(dataKind == UPGRADEWIN)//升级赛赢了
    {
        qInfo() << "成功收到UPGRADEWIN的数据报";

        for(uint i = 0; i < pokemon_num; i++)
        {
            delete pokemon[i];
        }
        pokemon.clear();
        ui->CbxUser->clear();

        UserData userdata;
        dsIn >> userdata;
        pokemon_num = userdata.pokemon_num;//更新用户胜率信息
        high_level_pokemon = userdata.high_level_pokemon;
        victory_num = userdata.victory_num;
        battle_num = userdata.battle_num;
        qDebug() << "userdata.pokemon.length=" << userdata.pokemon.length();

        for(uint i = 0; i < pokemon_num; i++)//读取服务端发送来的三个小精灵
        {
            UDPPokemon *udppokemon = new UDPPokemon;
            *udppokemon = *(userdata.pokemon[i]);
            pokemon.append(udppokemon);
            qDebug() << "接收到一个小精灵";
        }
        qDebug() << "更新用户小精灵列表成功";

        for(uint i = 0; i < this->pokemon_num; i++)//在combox中显示用户小精灵
            ui->CbxUser->addItem(userdata.pokemon[i]->name);
        qDebug() << "UPGRADEWIN之后, pokemon_num=" << pokemon_num << ", pokemon.length()=" << pokemon.length();
        qDebug() << "UPGRADEWIN之后，检查收到的数据报" << userdata.username
                 << userdata.pokemon_num << userdata.high_level_pokemon
                 << userdata.victory_num << userdata.battle_num
                 << userdata.pokemon[0]->name << userdata.pokemon[0]->level
                 << userdata.pokemon[0]->EXP;

        reset();
        ui->BtnUpgrade->setDisabled (false);
        QMessageBox msgBox;
        msgBox.setWindowTitle("升级赛结束");//标题
        msgBox.setText("恭喜您在升级赛中胜出！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else if(dataKind == UPGRADEFAIL)//升级赛输了
    {
        qInfo() << "成功收到UPGRADEFAIL的数据报" ;
        for(uint i = 0; i < virpokemon_num; i++)
        {
            delete virtual_pokemon[i];
        }
        virtual_pokemon.clear();
        UserData userdata;
        dsIn >> userdata;
        pokemon_num = userdata.pokemon_num;
        high_level_pokemon = userdata.high_level_pokemon;
        victory_num = userdata.victory_num;
        battle_num = userdata.battle_num;//更新用户的胜率信息
        dsIn >> virpokemon_num;
        for(uint i = 0; i < virpokemon_num; i++)//更新virpokemon表
        {
            UDPPokemon* udppokemon = new UDPPokemon();
            dsIn >> *udppokemon;
            virtual_pokemon.append(udppokemon);
        }
        reset();
        ui->BtnUpgrade->setDisabled (false);
        QMessageBox msgBox;
        msgBox.setWindowTitle("升级赛结束");//标题
        msgBox.setText("很遗憾您在升级赛中输掉了，请继续努力！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else if(dataKind == VICTORY)
    {
        qInfo() << "成功收到VICTORY的数据报";
        qDebug() << "收到VICTORY之后，pokemon_num=" << pokemon_num;
        qDebug() << "收到VICTORY之后，pokemon.length()=" << pokemon.length();
        qDebug() << "收到VICTORY之后，virpokemon_num=" << virpokemon_num;
        qDebug() << "收到VICTORY之后，virtual_pokemon.length()=" << virtual_pokemon.length();
        for(uint i = 0; i < pokemon_num; i++)
        {
            delete pokemon[i];
        }
        pokemon.clear();
        for(uint i = 0; i < virpokemon_num; i++)
        {
            delete virtual_pokemon[i];
        }

        qDebug() << "test3";

        virtual_pokemon.clear();

        qDebug() << "test4";

        UserData userdata;
        dsIn >> userdata;
        pokemon_num = userdata.pokemon_num;
        high_level_pokemon = userdata.high_level_pokemon;
        victory_num = userdata.victory_num;
        battle_num = userdata.battle_num;//更新用户信息

        for(uint i = 0; i < pokemon_num; i++)//读取服务端发送来的小精灵
        {
            UDPPokemon *udppokemon = new UDPPokemon;
            *udppokemon = *(userdata.pokemon[i]);
            pokemon.append(udppokemon);
            qDebug() << "接收到一个小精灵";
        }
        for(uint i = 0; i < virpokemon_num; i++)//更新虚拟小精灵列表
        {
            UDPPokemon* udppokemon = new UDPPokemon();
            dsIn >> *udppokemon;
            virtual_pokemon.append(udppokemon);
        }
        ui->CbxUser->clear();
        for(uint i = 0; i < this->pokemon_num; i++)//在combox中显示用户小精灵
            ui->CbxUser->addItem(this->pokemon[i]->name);
        reset();
        ui->BtnUpgrade->setDisabled (false);

        QMessageBox msgBox;
        msgBox.setWindowTitle("决斗赛结束");//标题
        msgBox.setText("恭喜您在决斗赛中获胜！获得了新的小精灵！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else if(dataKind == FAIL)
    {
        qInfo() << "成功收到FAIL的数据报";
        for(uint i = 0; i < virpokemon_num; i++)
        {
            delete virtual_pokemon[i];
        }
        //qDebug() << "test5";
        virtual_pokemon.clear();

        //qDebug() << "test6";

        UserData userdata;
        dsIn >> userdata;

        username = userdata.username;
        pokemon_num = userdata.pokemon_num;
        high_level_pokemon = userdata.high_level_pokemon;
        victory_num = userdata.victory_num;
        battle_num = userdata.battle_num;

        qDebug() << "打印FAIL携带的信息:";
        qDebug() << username;
        qDebug() << pokemon_num;
        qDebug() << high_level_pokemon;
        qDebug() << victory_num;
        qDebug() << battle_num;
        qDebug() << userdata.pokemon.length();

        dsIn >> virpokemon_num;

        qDebug() << virpokemon_num;
        for(uint i = 0; i < virpokemon_num; i++)//更新虚拟小精灵列表
        {
            UDPPokemon* udppokemon = new UDPPokemon();
            dsIn >> *udppokemon;
            virtual_pokemon.append(udppokemon);
        }
        reset();
        ui->BtnUpgrade->setDisabled (false);
        QMessageBox msgBox;
        msgBox.setWindowTitle("决斗赛结束");//标题
        msgBox.setText("很遗憾您输掉了这场决斗赛，现在您需要选择一个小精灵送出");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        QList<UDPPokemon *> selected;
        for(int i = 0; i < 3; i++)
        {
            pokemon_index[i] = i;
        }

        qDebug() << "test7";

        if(this->pokemon_num <= 3)
        {
            qDebug() << "test8";
            for(uint i = 0; i < this->pokemon_num; i++)
                selected.append(this->pokemon[i]);

            qDebug() << "test9";
            emit sentSelect(selected, pokemon_index);
            this->selectPokemon->show();
        }
        else
        {
            qDebug() << "test10";
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0, pokemon_num);

            int a, b, c;
            a = dis(gen);
            selected.append (this->pokemon[a]);
            pokemon_index[0] = a;

            b = dis(gen);
            while(a==b)
                b = dis(gen);
            selected.append (this->pokemon[b]);
            pokemon_index[1] = b;

            c = dis(gen);
            while(c == a || c == b)
                c = dis(gen);
            selected.append (this->pokemon[c]);
            pokemon_index[2]=c;

            qDebug() << "test11";

            emit sentSelect(selected, pokemon_index);
            this->selectPokemon->show();
        }
    }
    else if(dataKind == ANEWPOKEMON)
    {
        qDebug() << "收到了ANEWPOKEMON";
        UDPPokemon* udp_pokemon = new UDPPokemon;
        dsIn >> *udp_pokemon;
        pokemon.append(udp_pokemon);
        pokemon_num++;
        qDebug() << "收到ANEWPOKEMON包后，pokemon_num=" << pokemon_num;
        reset();
        ui->CbxUser->clear();
        for(uint i = 0; i < this->pokemon_num; i++)//在combox中显示用户小精灵
            ui->CbxUser->addItem(this->pokemon[i]->name);
        ui->CbxUser->setCurrentIndex(0);
    }
}

void MainWindow:: recvSelectResult(uint index)
{
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    dsOut << GIVEYOU;//发送类型
    dsOut<< this->username << this->port << index;//发送用户名以及端口号以及用户选择的小精灵

    selectPokemon->close();

    pokemon_num--;
    if(pokemon[index]->level == 15)
    {
        high_level_pokemon--;
    }

    pokemon.removeAt(index);

    QHostAddress serverAddress = QHostAddress("127.0.0.1");
    client->writeDatagram(data.data(), data.size(),serverAddress, 6665);

    qDebug() << "发送GIVEYOU后，pokemon_num=" << pokemon_num;
    if(pokemon_num == 0)
    {
        qDebug() << "test1";
        if(server->waitForReadyRead (600))
        {
            qDebug() << "test3";
            readPendingDatagrams();
        } 
    }
    else
    {
        qDebug() << "超时未收到消息";
    }
    qDebug() << "test2";
    reset();
    qDebug() << pokemon_num;
    ui->CbxUser->clear();
    for(uint i = 0; i < this->pokemon_num; i++)//在combox中显示用户小精灵
        ui->CbxUser->addItem(this->pokemon[i]->name);
    ui->CbxUser->setCurrentIndex(0);
}

QString MainWindow:: getInfo(unsigned int index) const//获取pokemon信息
{
    UDPPokemon *current_pokemon;
    qDebug() << "即将显示当前选中的小精灵，小精灵数目：";
    qDebug() << pokemon.length();
    if(index >= pokemon.size())
    {
        qDebug() << "Index out of range.";
        return QString();
    }

    if(this->mode != 2)//不是mode2，显示当前用户的小精灵模式
    {
        qDebug() << "获取当前用户的小精灵" << index;
        current_pokemon = pokemon[index];
    }
    else//mode = 2，显示全部用户
    {
        //获取当前选中用户的指定pokemon
        qDebug() << "获取当前选中用户的小精灵" << allusers[ui->listWidgetUsers->currentRow()-1]->username;
        current_pokemon = allusers[ui->listWidgetUsers->currentRow()-1]->pokemon[index];
    }
    qDebug() << "test1";

    if(current_pokemon == nullptr) {
        qDebug() << "Pokemon is null.";
        return QString();
    }

    QString information, temp;
    information = information + "name:" + current_pokemon->name;
    qDebug() << current_pokemon->name;
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
    qDebug() << temp;
    information = information + "\nmax_EXP:" + temp.setNum(current_pokemon->max_EXP);
    qDebug() << temp;
    information = information + "\nEXP:" + temp.setNum(current_pokemon->EXP);
    qDebug() << temp;
    information = information + "\nATK:" + temp.setNum(current_pokemon->ATK);
    qDebug() << temp;
    information = information + "\nmax_HP:" + temp.setNum(current_pokemon->max_HP);
    qDebug() << temp;
    information = information + "\nHP:" + temp.setNum(current_pokemon->HP);
    qDebug() << temp;
    information = information + "\nDF:" + temp.setNum(current_pokemon->DF);
    qDebug() << temp;
    information = information + "\nspeed:" + temp.setNum(current_pokemon->speed);
    qDebug() << temp;
    information = information + "\nspecial_ATK_name:" + current_pokemon->special_ATK_name;
    qDebug() << temp;
    information = information + "\nspecial_ATK:" + temp.setNum(current_pokemon->special_ATK);
    qDebug() << temp;
    information += '\n';



    qDebug() << "test2";
    return information;
}

QString MainWindow:: getVirInfo(uint index)
{
    UDPPokemon *the_udppokemon;
    the_udppokemon = this->virtual_pokemon[index];

    QString information, temp;
    information = information + "name:" + the_udppokemon->name;
    if(the_udppokemon->kind == HIGH_ATK)
    {
        information = information + "\nkind:" + "HIGH_ATK";
    }
    else if(the_udppokemon->kind == HIGH_DF)
    {
        information = information + "\nkind:" + "HIGH_DF";
    }
    else if(the_udppokemon->kind == HIGH_HP)
    {
        information = information + "\nkind:" + "HIGH_HP";
    }
    else if(the_udppokemon->kind == HIGH_SPEED)
    {
        information = information + "\nkind:" + "HIGH_SPEED";
    }
    information = information + "\nlevel:" + temp.setNum(the_udppokemon->level);
    information = information + "\nmax_EXP:" + temp.setNum(the_udppokemon->max_EXP);
    information = information + "\nEXP:" + temp.setNum(the_udppokemon->EXP);
    information = information + "\nATK:" + temp.setNum(the_udppokemon->ATK);
    information = information + "\nmax_HP:" + temp.setNum(the_udppokemon->max_HP);
    information = information + "\nHP:" + temp.setNum(the_udppokemon->HP);
    information = information + "\nDF:" + temp.setNum(the_udppokemon->DF);
    information = information + "\nspeed:" + temp.setNum(the_udppokemon->speed);
    information = information + "\nspecial_ATK_name:" + the_udppokemon->special_ATK_name;
    information = information + "\nspecial_ATK:" + temp.setNum(the_udppokemon->special_ATK);
    information += '\n';

    return information;
}

void MainWindow:: Loginout_clicked()//关闭窗口
{
    close();
}

void MainWindow:: Online_clicked()//online按钮被点击时(重复点击隐藏)
{
    if(((ui->showInfo->isHidden()) && (ui->listWidgetUsers->isHidden())) || mode == 2)
    {
        if(mode == 2)//如果当前是显示全部用户模式，将labelInfo的信息改为自己的小精灵的
        {
            this->mode=1;//转变为显示在线用户模式

            ui->CbxUser->clear();
            for(uint i = 0; i < this->pokemon_num; i++)//从显示选中用户改为显示自己
                ui->CbxUser->addItem(this->pokemon[i]->name);
            ui->CbxUser->setCurrentIndex(0);//显示当前用户的Pokemon
            ui->labelWho->setText(tr("%1's Pokemon").arg(this->username));
            ui->labelInfo->setText(this->getInfo(0));
            ui->labelInfo->setStyleSheet ("#labelInfo{border-image:url(:/image/"+
                                         this->pokemon[0]->name+".png);}");
        }

        this->mode = 1;//切换为显示在线用户模式
        QByteArray data;
        QDataStream dsOut(&data, QIODevice::ReadWrite);//用dsOut来控制data的输入输出
        dsOut<<ONLINEUSERS<<username<<port;//发送类型，用户名以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环
        client->writeDatagram(data.data(), data.size(), serverAddress, 6665);
        //将data写入client并发送到本地端口6665

        if(server->waitForReadyRead (600))//在600ms内收到数据报
        {
            readPendingDatagrams();//接收显示用户信息的数据报，更改在线用户列表

            //显示在线用户及其端口
            ui->listWidgetUsers->clear();
            ui->showInfo->setText("Online Users");
            ui->listWidgetUsers->addItem ("Username\tPort");

            for(int i = 0; i < this->onlineusers.length(); i++)
                ui->listWidgetUsers->addItem(tr("%1\t%2\t").
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
    if((ui->showInfo->isHidden() && ui->listWidgetUsers->isHidden ()) || mode == 1)//当前不是显示全部用户模式
    {
        this->mode=2;//切换为显示全部用户模式

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
            this->readPendingDatagrams();//阅读用户信息的数据报，接收allusers信息

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

        ui->CbxUser->clear();
        for(uint i = 0; i < this->pokemon_num; i++)
            ui->CbxUser->addItem(this->pokemon[i]->name);
        ui->CbxUser->setCurrentIndex(0);
        ui->labelWho->setText(tr("%1's Pokemon").arg(this->username));
        ui->labelInfo->setText(this->getInfo(0));
        ui->labelInfo->setStyleSheet ("#labelInfo{border-image:url(:/image/"+
                                     this->pokemon[0]->name+".webp);}");
    }
}

void MainWindow:: Upgrade_botton_clicked()//当upgrade按钮被点击时
{
    if(ui->labelServer->isHidden ())
    {
        this->gamemode = 1;//升级赛模式

        QByteArray data;
        QDataStream dsOut(&data,QIODevice::WriteOnly);
        dsOut << INGAME << this->username << this->port;//发送类型，发送用户名以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(data.data(), data.size(),serverAddress, 6665);

        if(server->waitForReadyRead (600))//判断连接超时
        {
            ui->comboBox->clear();
            readPendingDatagrams();
            qInfo() << "成功收到数据报" ;

            for(uint i = 0; i < this->virpokemon_num; i++)//显示系统小精灵
                ui->comboBox->addItem(this->virtual_pokemon[i]->name);
            ui->comboBox->setCurrentIndex (0);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
            msgBox.setWindowTitle("Get Data Failed");
            msgBox.setText("Connect Failed");
            msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
            msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
            msgBox.exec(); // 同步地显示消息框并等待用户响应
        }

        ui->BtnDuel->setDisabled (true);
        ui->labelServer->setHidden (false);
        ui->comboBox->setHidden (false);
        ui->BtnConfirm->setHidden (false);
        ui->labelSPkm->setHidden (false);
        ui->labelSPkm->setStyleSheet ("#labelSPkm{border-image:url(:/image/"+
                                     this->virtual_pokemon[0]->name+".webp);}");
    }
    else//重复点击隐藏
    {
        this->gamemode = 0;//无比赛模式
        ui->BtnDuel->setDisabled (false);
        ui->labelServer->setHidden (true);
        ui->comboBox->setHidden (true);
        ui->BtnConfirm->setHidden (true);
        ui->labelSPkm->setHidden (true);
    }
}

void MainWindow:: Duel_botton_clicked()
{
    if(ui->labelServer->isHidden ())
    {
        this->gamemode = 2;//决斗赛模式

        QByteArray data;
        QDataStream dsOut(&data,QIODevice::ReadWrite);
        dsOut << INGAME << this->username << this->port;//发送类型，发送用户名以及端口号
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(data.data(), data.size(),serverAddress, 6665);

        if(server->waitForReadyRead (600))//判断连接超时
        {
            ui->comboBox->clear();

            for(uint i = 0; i < this->virpokemon_num; i++)//显示系统小精灵
                ui->comboBox->addItem(this->virtual_pokemon[i]->name);
            ui->comboBox->setCurrentIndex (0);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
            msgBox.setWindowTitle("Get Data Failed");
            msgBox.setText("Connect Failed");
            msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
            msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
            msgBox.exec(); // 同步地显示消息框并等待用户响应
        }

        ui->BtnUpgrade->setDisabled (true);
        ui->labelServer->setHidden (false);
        ui->comboBox->setHidden (false);
        ui->BtnConfirm->setHidden (false);
        ui->labelSPkm->setHidden (false);
        ui->labelSPkm->setStyleSheet ("#labelSPkm{border-image:url(:/image/"+
                                     this->virtual_pokemon[0]->name+".webp);}");
    }
    else
    {
        this->gamemode=0;//无比赛模式
        ui->BtnUpgrade->setDisabled (false);
        ui->labelServer->setHidden (true);
        ui->comboBox->setHidden (true);
        ui->BtnConfirm->setHidden (true);
        ui->labelSPkm->setHidden (true);
    }
}

void MainWindow:: Users_changed(int currentRow)//更换选中的用户时
{
    if(currentRow != -1 && currentRow != 0 && this->mode == 2)
    {
        ui->labelWho->setText(tr("%1's Pokemon").arg(this->allusers[currentRow - 1]->username));
        ui->CbxUser->clear();
        for(uint i = 0; i < this->allusers[currentRow - 1]->pokemon_num;i++)
            ui->CbxUser->addItem(this->allusers[currentRow-1]->pokemon[i]->name);
        ui->CbxUser->setCurrentIndex(0);
        ui->labelInfo->setText (this->getInfo(0));
        ui->labelInfo->setStyleSheet ("#labelInfo{border-image:url(:/image/"+
                                     this->allusers[currentRow-1]->pokemon[0]->name+".webp);}");
    }
}

void MainWindow:: CbxUser_Changed(int index)//当选中的用户小精灵更换时
{
    if(index < 0)   //序号为负数不处理
    {
        return;
    }
    //正常序号
    ui->labelInfo->setText(this->getInfo(index));
    if(mode == 2)
    {
        ui->labelInfo->setStyleSheet ("#labelInfo{border-image:url(:/image/"+
                                     allusers[ui->listWidgetUsers->currentRow()-1]->pokemon[index]->name+".webp);}");
    }
    else
        ui->labelInfo->setStyleSheet ("#labelInfo{border-image:url(:/image/"+
                                this->pokemon[index]->name+".webp);}");
}

void MainWindow:: Combox_Changed(int index)//当目前选中的虚拟小精灵被改变时
{
    if(index < 0)   //序号为负数不处理
    {
        return;
    }
    //正常序号
    ui->labelSPkm->setText (this->getVirInfo(index));
    ui->labelSPkm->setStyleSheet ("#labelSPkm{border-image:url(:/image/"+
                                 this->virtual_pokemon[index]->name+".webp);}");
}

void MainWindow:: BtnConfirm_clicked()
{
    QByteArray data;
    QDataStream dsOut(&data,QIODevice::ReadWrite);
    QString who = ui->labelWho->text().split ("'")[0];
    if(who != this->username)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical); // 设置消息框的图标为“Critical”
        msgBox.setWindowTitle("ERROR");
        msgBox.setText("请换成你自己的小精灵！");
        msgBox.setStandardButtons(QMessageBox::Ok); // 设置标准按钮
        msgBox.setDefaultButton(QMessageBox::Ok); // 设置默认按钮
        msgBox.exec(); // 同步地显示消息框并等待用户响应
    }
    else
    {
        uint pokemon_index = ui->CbxUser->currentIndex();
        uint virtual_index = ui->comboBox->currentIndex();
        if(this->gamemode == 1)
        {
            dsOut << UPGRADE << username << port << pokemon_index
                  << virtual_index;
        }
        else
        {
            dsOut << DUEL << username << port << pokemon_index
                  << virtual_index;
        }
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(data.data(), data.size(),serverAddress, 6665);
        if(server->waitForReadyRead (600))//判断连接超时
        {
            this->readPendingDatagrams();//阅读战斗结果
        }
        else
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
}

void MainWindow:: BtnRate_clicked()
{
    if(this->mode != 3)//不是显示胜率模式
    {
        ui->CbxUser->clear ();
        for(uint i = 0; i < this->pokemon_num; i++)
            ui->CbxUser->addItem(this->pokemon[i]->name);
        ui->CbxUser->setCurrentIndex(0);//显示当前用户的Pokemon
        ui->labelWho->setText (tr("%1's Pokemon").arg(this->username));
        ui->labelInfo->setText (this->getInfo (0));

        if(this->mode == 0)
        {
            ui->showInfo->setHidden (false);
            ui->listWidgetUsers->setHidden (false);
        }

        this->mode = 3;//显示胜率模式
        ui->listWidgetUsers->clear();
        for(uint i = 0; i < allusers.length(); i++)
        {
            if(allusers[i]->battle_num + allusers[i]->victory_num == 0)
            {
                ui->listWidgetUsers->addItem((tr("%1\t0")).
                                             arg(allusers[i]->username));
            }
            else
            {
                ui->listWidgetUsers->addItem(tr("%1\t%2").
                                             arg(allusers[i]->username).
                                             arg((float)allusers[i]->victory_num/allusers[i]->battle_num));
            }
        }
    }
    else//重复点击隐藏
    {
        this->mode=0;//不显示模式
        ui->showInfo->setHidden(true);
        ui->listWidgetUsers->setHidden(true);
    }
}


void MainWindow:: BtnBadge_clicked(bool checked)
{
    if(checked)
    {
        QString badgeNum;
        if(pokemon_num <= 3)
            badgeNum="Bronze";
        else if(pokemon_num <= 6)
            badgeNum="Silver";
        else
            badgeNum="Golden";

        QString badgeAdvanced;

        if(high_level_pokemon < 1)
            badgeAdvanced = "Bronze";
        else if(high_level_pokemon < 3)
            badgeAdvanced = "Silver";
        else
            badgeAdvanced = "Golden";

        ui->labelNumBadge->setStyleSheet ("#labelNumBadge{border-image:url(:/image/"+
                                         badgeNum+".png);}");
        ui->labelAdvBadge->setStyleSheet ("#labelAdvBadge{border-image:url(:/image/"+
                                         badgeAdvanced+".png);}");

        ui->labelNum->setHidden(false);
        ui->labelNumBadge->setHidden(false);
        ui->labelAdv->setHidden(false);
        ui->labelAdvBadge->setHidden(false);
    }
    else
    {
        ui->labelNum->setHidden(true);
        ui->labelNumBadge->setHidden(true);
        ui->labelAdv->setHidden(true);
        ui->labelAdvBadge->setHidden(true);
    }
}

void MainWindow:: reset()
{
    ui->showInfo->setHidden (true);
    ui->listWidgetUsers->setHidden (true);
    ui->labelServer->setHidden (true);
    ui->labelServer->setText ("Opponent");
    ui->comboBox->setHidden (true);
    ui->BtnConfirm->setHidden (true);
    ui->labelSPkm->setHidden (true);//暂不显示虚拟小精灵信息
    ui->BtnDuel->setDisabled (false);
}
































