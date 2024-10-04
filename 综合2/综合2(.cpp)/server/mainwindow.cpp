#include "mainwindow.h"
#include "ui_mainwindow.h"


//运算符重载，方便对User的读写
QDataStream &operator<<(QDataStream &stream, const User &user)
{
    stream<<user.username;
    stream<<user.port;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, User &user)
{
    stream>>user.username;
    stream>>user.port;

    return stream;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);//初始化用户界面，设置界面元素的位置、大小和属性
    server = new QUdpSocket(this);//接收客户端消息
    server->bind(QHostAddress::LocalHost, 6665);//将服务器的套接字绑定到指定的地址和端口，只监听来自本地计算机的连接和数据包
    connect(server, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));//将server对象的readyRead()信号连接到槽函数readPendingDatagrams()

    client=new QUdpSocket(this);//向客户端发送的消息

    db = new QSqlDatabase();//创建sql数据库
    *db=QSqlDatabase::addDatabase ("QMYSQL");
    db->setDatabaseName ("Pokemon");
    db->setUserName("root");
    db->setPassword ("573515@Ymm");
    if(!db->open ())
    {
        qDebug()<<"打开数据库失败";
    }
    else
    {
        qInfo() << "成功打开数据库Pokemon";
    }
    QSqlQuery query(*db);

    QString createPokemonTable = R"(
        CREATE TABLE IF NOT EXISTS pokemon (
            id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
            username VARCHAR(255) NOT NULL,
            name VARCHAR(255) NOT NULL,
            kind VARCHAR(255),
            level INT,
            max_EXP INT,
            EXP INT,
            ATK INT,
            max_HP INT,
            HP INT,
            DF INT,
            speed INT,
            special_ATK_name VARCHAR(255),
            special_ATK INT
        )
    )";

    QString createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
            username VARCHAR(255) NOT NULL,
            password VARCHAR(255) NOT NULL
        )
    )";

    if (!query.exec(createPokemonTable)) {
        qDebug() << "pokemon表创建失败: " << query.lastError();
    }
    else
    {
        qInfo() << "pokemon表创建成功";
    }

    if (!query.exec(createUsersTable)) {
        qDebug() << "users表创建失败: " << query.lastError();
    }
    else
    {
        qInfo() << "users表创建成功";
    }

    // 清空表 pokemon
    if (!query.exec("TRUNCATE TABLE pokemon"))
    {
        qDebug() << "清空表pokemon失败。" << query.lastError().text();
    }
    else
    {
        qDebug() << "清空表pokemon成功。";
    }

    // 清空表 users
    if (!query.exec("TRUNCATE TABLE users"))
    {
        qDebug() << "清空表users失败。" << query.lastError().text();
    }
    else
    {
        qDebug() << "清空表users成功。";
    }

    displayTable(ui->tableWidgetPokemon, "pokemon");
    displayTable(ui->tableWidgetUsers, "users");//在server窗口显示两个表
}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
    delete server;
    delete client;
    delete db;
}

void MainWindow::displayTable(QTableWidget *tableWidget, const QString &tableName)
{
    QSqlQuery query("SELECT * FROM " + tableName);

    if (!query.exec())
    {
        qDebug() << "Error: Could not execute query for table" << tableName << ":" << query.lastError().text();
        return;
    }

    QSqlRecord record = query.record();
    tableWidget->setColumnCount(record.count());
    tableWidget->setRowCount(query.size());

    //设置表头
    QStringList headers;
    for (int i = 0; i < record.count(); ++i) {
        headers << record.fieldName(i);
    }
    tableWidget->setHorizontalHeaderLabels(headers);

    //显示表的内容
    int row = 0;
    while (query.next()) {
        for (int col = 0; col < record.count(); ++col)
        {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        ++row;
    }
}

void MainWindow:: Create_pokemons(QString username)//给新用户随机分配三个宠物小精灵，并以udp的形式写入数据库中
{
    int num = 0;
    while(num < 3)//三次分配
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 12);
        int random_value = dis(gen);
        string the_name;
        switch(random_value)//随机选中宠物小精灵名字
        {
            case 0:
                the_name = "可达鸭";
                break;
            case 1:
                the_name = "小火龙";
                break;
            case 2:
                the_name = "飞腿郎";
                break;
            case 3:
                the_name = "杰尼龟";
                break;
            case 4:
                the_name = "卡拉卡拉";
                break;
            case 5:
                the_name = "独角犀牛";
                break;
            case 6:
                the_name = "皮皮";
                break;
            case 7:
                the_name = "吉利蛋";
                break;
            case 8:
                the_name = "皮卡丘";
                break;
            case 9:
                the_name = "妙蛙种子";
                break;
            case 10:
                the_name = "小火马";
                break;
            case 11:
                the_name = "呆呆兽";
                break;
        }
        Pokemon_kind this_kind;
        switch(random_value/3)
        {
            case 0:
                this_kind = HIGH_ATK;
                break;
            case 1:
                this_kind = HIGH_DF;
                break;
            case 2:
                this_kind = HIGH_HP;
                break;
            case 3:
                this_kind = HIGH_SPEED;
                break;
        }

        QSqlQuery query;
        QString queryStr = "SELECT * FROM pokemon WHERE username = ? AND name = ?";
        query.prepare(queryStr);
        // 绑定参数
        QString name = QString::fromStdString(the_name);
        query.addBindValue(username);
        query.addBindValue(name);
        if (!query.exec())//检测指令是否执行成功
        {
            qDebug() << "Error: Failed to execute query:" << query.lastError().text();
            return;
        }
        if(query.next()) continue;//如果已经拥有该小精灵，跳过循环
        Pokemon the_pokemon(the_name, this_kind);
        this->pokemon = new Pokemon(the_pokemon);
        UDPPokemon *a_pokemon_udp = pokemon->getUDP();
        this->PutIntoSql(username, a_pokemon_udp);//写入数据库中
        delete a_pokemon_udp;
        delete this->pokemon;
        this->pokemon = nullptr;
        num++;
    }
}

//将用户名和小精灵信息写入数据库中
void MainWindow:: PutIntoSql(QString username, UDPPokemon *the_pokemon)
{
    QSqlQuery query;

    query.prepare("INSERT INTO pokemon (username, name, kind, level, max_EXP, EXP, ATK, max_HP, HP, DF, speed, special_ATK_name, special_ATK) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(username);
    query.addBindValue(the_pokemon->name);
    query.addBindValue(the_pokemon->kind);
    query.addBindValue(the_pokemon->level);
    query.addBindValue(the_pokemon->max_EXP);
    query.addBindValue(the_pokemon->EXP);
    query.addBindValue(the_pokemon->ATK);
    query.addBindValue(the_pokemon->max_HP);
    query.addBindValue(the_pokemon->HP);
    query.addBindValue(the_pokemon->DF);
    query.addBindValue(the_pokemon->speed);
    query.addBindValue(the_pokemon->special_ATK_name);
    query.addBindValue(the_pokemon->special_ATK);

    if (!query.exec())//插入错误
    {
        qDebug() << "插入pokemon表失败" << query.lastError();
    }
    else
    {
        qInfo() << "插入pokemon表成功";
    }
    displayTable(ui->tableWidgetPokemon, "pokemon");
    displayTable(ui->tableWidgetUsers, "users");
}

void MainWindow:: SentPokemon(QDataStream &dsOut, QString username)//发送小精灵的数据
{
    QSqlQuery query;
    query.prepare("SELECT * FROM pokemon WHERE username = ?");
    query.addBindValue(username);//在数据库pokemon表项中中查询用户

    if (!query.exec())//尝试查询，如果查询失败，退出
    {
        qDebug() << "执行在pokemon表中查询用户指令失败:" << query.lastError();
        return;
    }
    else
    {
        qInfo() << "执行在pokemon表中查询用户的指令成功";
    }

    while(query.next())//若查询到小精灵，将小精灵封装
    {
        UDPPokemon udp_pokemon;
        //第0列为序号，第一列为username
        udp_pokemon.name = query.value(2).toString();
        udp_pokemon.kind = static_cast<Pokemon_kind>(query.value(3).toUInt());
        udp_pokemon.level = query.value(4).toInt();
        udp_pokemon.max_EXP = query.value(5).toInt();
        udp_pokemon.EXP = query.value(6).toInt();
        udp_pokemon.ATK = query.value(7).toInt();
        udp_pokemon.max_HP = query.value(8).toInt();
        udp_pokemon.HP = query.value(9).toInt();
        udp_pokemon.DF = query.value(10).toInt();
        udp_pokemon.speed = query.value(11).toInt();
        udp_pokemon.special_ATK_name = query.value(12).toString();
        udp_pokemon.special_ATK = query.value(13).toInt();

        dsOut << udp_pokemon;
    }
}

void MainWindow:: SentOnlineUsers(unsigned int port)//发送在线用户
{
    QByteArray dataOut;//存储要发送的数据
    QDataStream dsOut(&dataOut, QIODevice::ReadWrite);//dsOut与dataOut相关联，便于写入数据
    dsOut<<ONLINEUSERS;//将SIGNAL_TYPE写入dsOut

    for(int i = 0; i < this->onlineUsers.length(); i++)//把所有用户写入dsOut
    {
        dsOut << this->onlineUsers[i];
    }

    QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环地址
    client->writeDatagram(dataOut.data(), dataOut.size(), serverAddress, port);
}

void MainWindow:: SentAllUsers(unsigned int port)//发送所有用户
{
    QByteArray dataOut;//存储要发送的数据
    QDataStream dsOut(&dataOut, QIODevice::ReadWrite);//dsOut与dataOut相关联，便于写入数据
    dsOut<<ALLUSERS;

    QSqlQuery query;
    bool issuccess;
    issuccess = query.exec("select * from users");//从users表中选择所有记录
    if(issuccess) qInfo() << "在sentAllUsers中成功找到user表中用户的记录";
    else qDebug() << "在SentAllUsers中没有找到user表中用户记录";
    while(query.next())
    {
        qInfo() << "成功发送一个用户及其小精灵";
        dsOut << query.value(1).toString();
        qInfo() << "发送的用户名为" << query.value(1).toString();
        this->SentPokemon(dsOut, query.value(1).toString());
    }
    QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环地址
    client->writeDatagram(dataOut.data(), dataOut.size(), serverAddress, port);
}

void MainWindow:: readPendingDatagrams()//接收来自client的数据
{
    QByteArray dataIn;//读取数据
    dataIn.resize(server->pendingDatagramSize());//调整缓冲区大小以便接收完整数据
    server->readDatagram(dataIn.data(), dataIn.size());//从server中读取一个数据报文并存储在dataIn中
    QDataStream dsIn(&dataIn,QIODevice::ReadWrite);
    QString username;//用户名
    QString pwd;//密码
    unsigned int port;//端口号
    unsigned int loginKind;
    dsIn>>loginKind>>username;//报文中前两个字段读取给loginKind和username

    if(loginKind == SIGNIN || loginKind == SIGNUP)
    {
        dsIn>>pwd>>port;
    }

    QByteArray dataOut;
    QDataStream dsOut(&dataOut,QIODevice::ReadWrite);
    QSqlQuery query;
    if(loginKind == SIGNUP)
    {
        query.exec ("select * from users where username=\""+username+"\";");
        if(query.next ())//用户名已存在
            dsOut<<NAMEEXIST;//发回用户名已存在的信息
        else
        {
            User user;
            user.username = username;
            user.port = port;
            this->onlineUsers.append (user);

            //将新用户添加至users表
            query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
            query.bindValue(":username", username);
            query.bindValue(":password", pwd);
            int insert_success;
            insert_success = query.exec();
            if(insert_success) qInfo() << "用户成功写入users表";
            else qDebug() << "用户写入users表失败";
            this->Create_pokemons(username);//用户随机分配三个小精灵
            dsOut<<SIGNUPOK;//给用户发送注册成功的消息
            SentPokemon(dsOut,username);//发送小精灵的数据
        }
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(dataOut.data(), dataOut.size(),serverAddress, port);
    }
    else if(loginKind == SIGNIN)
    {
        query.exec ("select * from users where username=\""+username+"\";");
        if(!query.next ())//数据库不存在此用户
            dsOut<<NOSUCHUSER;//发送用户不存在消息
        else
        {
            QString my_pwd = query.value(2).toString();
            if(my_pwd != pwd)
                dsOut<<PWDDIFF;//发送密码错误消息
            else
            {
                User user;
                user.username = username;
                user.port = port;
                int contain = 0;
                for(int i = 0 ;i < onlineUsers.size(); i++)
                {
                    if(onlineUsers.at(i).username == username)
                        contain = 1;
                }
                if(!contain)
                {
                    this->onlineUsers.append(user);//加入在线用户行列

                    dsOut<<SIGNINOK;//登陆成功
                    SentPokemon(dsOut,username);//发送小精灵信息
                }
                else
                {
                    dsOut<<HAVESIGNIN;
                }
            }
        }
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(dataOut.data(), dataOut.size(),serverAddress, port);
    }
    else if(loginKind == SIGNOUT)//登出
    {
        dsIn>>port;
        User user;
        user.username = username;
        user.port = port;
        this->onlineUsers.removeOne (user);//从在线用户列表中移走
        qDebug()<<username<<"Login out";
        qDebug()<<this->onlineUsers.length ();
    }
    else if(loginKind == ONLINEUSERS)//在线用户的消息
    {
        dsIn>>port;
        this->SentOnlineUsers(port);//发送在线用户
    }
    else if(loginKind == ALLUSERS)//所有用户的消息
    {
        dsIn>>port;
        this->SentAllUsers(port);//发送所有用户
    }
}
