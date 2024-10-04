#include "mainwindow.h"
#include "ui_mainwindow.h"

//运算符重载，方便对User的读写
QDataStream &operator<<(QDataStream &stream, const User &user)
{
    stream << user.username;
    stream << user.port;
    stream << user.pokemon_num;
    stream << user.high_level_num;
    stream << user.victory_num;
    stream << user.battle_num;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, User &user)
{
    stream >> user.username;
    stream >> user.port;
    stream >> user.pokemon_num;
    stream >> user.high_level_num;
    stream >> user.victory_num;
    stream >> user.battle_num;

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

    if (!query.exec("DROP TABLE pokemon")) {
        qDebug() << "执行删除pokemon表的指令失败: " << query.lastError().text();
    } else {
        qDebug() << "pokemon表成功删除";
    }

    if (!query.exec("DROP TABLE users")) {
        qDebug() << "执行删除users表的指令失败: " << query.lastError().text();
    } else {
        qDebug() << "users表成功删除";
    }

    if (!query.exec("DROP TABLE virtual_pokemon")) {
        qDebug() << "执行删除virtual_pokemon表的指令失败: " << query.lastError().text();
    } else {
        qDebug() << "virtual_pokemon表成功删除";
    }

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
            password VARCHAR(255) NOT NULL,
            pokemon_num INT,
            high_level_pokemon INT,
            victory_num INT,
            battle_num INT
        )
    )";

    QString createVirPokemonTable = R"(
        CREATE TABLE IF NOT EXISTS virtual_pokemon (
            id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
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

    if (!query.exec(createPokemonTable))
    {
        qDebug() << "pokemon表创建失败: " << query.lastError();
    }
    else
    {
        qInfo() << "pokemon表创建成功";
    }

    if (!query.exec(createUsersTable))
    {
        qDebug() << "users表创建失败: " << query.lastError();
    }
    else
    {
        qInfo() << "users表创建成功";
    }

    if (!query.exec(createVirPokemonTable))
    {
        qDebug() << "virtual_pokemon表创建失败: " << query.lastError();
    }
    else
    {
        qInfo() << "virtual_pokemon表创建成功";
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

    // 清空表 virtual_pokemon
    if (!query.exec("TRUNCATE TABLE virtual_pokemon"))
    {
        qDebug() << "清空表virtual_pokemon失败。" << query.lastQuery();
    }
    else
    {
        qDebug() << "清空表virtual_pokemon成功。";
    }

    displayTable(ui->tableWidgetPokemon, "pokemon");
    displayTable(ui->tableWidgetUsers, "users");//在server窗口显示用户表
    displayTable(ui->tableWidgetvirPokemon, "virtual_pokemon");
}

MainWindow::~MainWindow()
{
    delete ui;

    delete server;
    delete client;
    delete db;
}

void MainWindow::displayTable(QTableWidget *tableWidget, const QString &tableName) const//展示数据库表
{
    QSqlQuery query("SELECT * FROM " + tableName);

    if (!query.exec())
    {
        qDebug() << "错误：不能执行选中数据库表中所有表项的指令" << tableName << ":" << query.lastError().text();
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

void MainWindow:: Create_pokemons(const QString& username, int num) const//给用户随机分配指定数量的小精灵并以udp的形式写入数据库中
{
    int n = 0;
    while(n < num)//num次分配
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 12);
        int random_value = dis(gen);
        string the_name = random_name(random_value);

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

        //保证用户最初分配到的是三个不同的小精灵
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
        UDPPokemon *a_pokemon_udp = the_pokemon.getUDP();
        this->PutIntoSql(username, a_pokemon_udp);//写入数据库中
        this->Change_users_Sql(username, 1, 0, 0, 0);//改变users中用户拥有小精灵的数目
        delete a_pokemon_udp;
        n++;
    }
}

string MainWindow:: random_name(const int& random_value) const//随机选中宠物小精灵名字
{
    string the_name;
    switch(random_value)
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
    return the_name;
}

void MainWindow:: PutIntoSql(const QString& username, const UDPPokemon* the_udppokemon) const//将用户名和小精灵信息写入数据库pokemon表中
{
    QSqlQuery query;

    query.prepare("INSERT INTO pokemon (username, name, kind, level, max_EXP, EXP, ATK, max_HP, HP, DF, speed, special_ATK_name, special_ATK) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(username);
    query.addBindValue(the_udppokemon->name);
    query.addBindValue(the_udppokemon->kind);
    query.addBindValue(the_udppokemon->level);
    query.addBindValue(the_udppokemon->max_EXP);
    query.addBindValue(the_udppokemon->EXP);
    query.addBindValue(the_udppokemon->ATK);
    query.addBindValue(the_udppokemon->max_HP);
    query.addBindValue(the_udppokemon->HP);
    query.addBindValue(the_udppokemon->DF);
    query.addBindValue(the_udppokemon->speed);
    query.addBindValue(the_udppokemon->special_ATK_name);
    query.addBindValue(the_udppokemon->special_ATK);

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

void MainWindow:: SentPokemon(QDataStream& dsOut, const QString& username) const//将某一用户的所有小精灵的数据写入数据流等待发送
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
        qDebug() << "在SentPokemon中发送了一个小精灵";
        dsOut << GetUdppokemon(query);
    }
}

void MainWindow:: Sentall_virPokemon(QDataStream &dsOut)//将目前所有虚拟精灵写入数据流
{
    QSqlQuery query;
    query.prepare("SELECT * FROM virtual_pokemon");

    if(!query.exec()) //尝试查询，如果查询失败，退出
    {
        qDebug() << "执行在virtual_pokemon表中取出所有虚拟小精灵指令失败:" << query.lastError();
        return;
    }
    else
    {
        qInfo() << "执行在virtual_pokemon表中取出所有虚拟小精灵的指令成功";
    }

    while(query.next())//将每一个虚拟小精灵写入数据流
    {
        dsOut << GetVirUdppok(query);
    }
}

void MainWindow:: Createvirpokemon()//创建一个虚拟小精灵(并调用virInroSql将它写入数据库中)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 12);
    int random_value = dis(gen);
    string the_name = random_name(random_value);

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

    Pokemon the_pokemon(the_name, this_kind);
    UDPPokemon *a_pokemon_udp = the_pokemon.getUDP();
    this->virIntoSql(a_pokemon_udp);//写入数据库中
    delete a_pokemon_udp;
}

void MainWindow:: virIntoSql(const UDPPokemon* the_udppokemon)//将虚拟小精灵写入数据库中
{
    QSqlQuery query;

    query.prepare("INSERT INTO virtual_pokemon (name, kind, level, max_EXP, EXP, ATK, max_HP, HP, DF, speed, special_ATK_name, special_ATK) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(the_udppokemon->name);
    query.addBindValue(the_udppokemon->kind);
    query.addBindValue(the_udppokemon->level);
    query.addBindValue(the_udppokemon->max_EXP);
    query.addBindValue(the_udppokemon->EXP);
    query.addBindValue(the_udppokemon->ATK);
    query.addBindValue(the_udppokemon->max_HP);
    query.addBindValue(the_udppokemon->HP);
    query.addBindValue(the_udppokemon->DF);
    query.addBindValue(the_udppokemon->speed);
    query.addBindValue(the_udppokemon->special_ATK_name);
    query.addBindValue(the_udppokemon->special_ATK);

    if (!query.exec())//插入错误
    {
        qDebug() << "插入virtual_pokemon表失败" << query.lastError();
    }
    else
    {
        qInfo() << "插入virtual_pokemon表成功";
    }
    virpokemon_num++;
    displayTable(ui->tableWidgetvirPokemon, "virtual_pokemon");
    displayTable(ui->tableWidgetUsers, "users");
}

//更新数据库中的users
void MainWindow:: Change_users_Sql(const QString& username, int pokemon_num, int high_level_pokemon, int victory_num, int battle_num) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username); // 确保username是你想要查询的变量

    if (!query.exec()) {
        qDebug() << "执行从users中找到用户的指令失败" << query.lastError();
    } else {
        qInfo() << "从users中找到用户成功";
    }

    if (query.next()) {
        qInfo() << "定位到了想找的位置";
        // 你可以在这里处理查询到的记录，例如：
        QString foundUsername = query.value("username").toString();
        QString foundPassword = query.value("password").toString();
        qInfo() << "找到的用户名：" << foundUsername << "，密码：" << foundPassword;
    }
    else
    {
        qInfo() << "没有找到匹配的用户";
    }

    User save_user;
    save_user.pokemon_num = query.value(3).toInt();
    save_user.high_level_num = query.value(4).toInt();
    save_user.victory_num = query.value(5).toInt();
    save_user.battle_num = query.value(6).toInt();

    save_user.pokemon_num += pokemon_num;
    save_user.high_level_num += high_level_pokemon;
    save_user.victory_num += victory_num;
    save_user.battle_num += battle_num;

    QString sqlString = tr("UPDATE users SET pokemon_num=%1, "
                           "high_level_pokemon=%2, victory_num=%3,"
                           "battle_num=%4 WHERE username=\"%5\"").
                        arg(save_user.pokemon_num).arg(save_user.high_level_num).
                        arg(save_user.victory_num).
                        arg(save_user.battle_num).arg(username);

    if(!query.exec(sqlString))
    {
        qDebug() << "执行更新users表的指令失败" << query.lastError();
    }
    else
    {
        qDebug() << "执行更新users表的指令成功";
        qInfo() << save_user.pokemon_num;
    }
    displayTable(ui->tableWidgetUsers, "users");//在server窗口显示两个表
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
        dsOut << query.value(3).toInt();
        dsOut << query.value(4).toInt();
        dsOut << query.value(5).toInt();
        dsOut << query.value(6).toInt();
        qInfo() << "发送的用户名为" << query.value(1).toString();
        this->SentPokemon(dsOut, query.value(1).toString());
    }
    QHostAddress serverAddress = QHostAddress("127.0.0.1");//本地回环地址
    client->writeDatagram(dataOut.data(), dataOut.size(), serverAddress, port);
}

//从数据库中读取选中的小精灵，封装成UDPPokemon包
UDPPokemon MainWindow:: GetUdppokemon(QSqlQuery& query) const
{
    UDPPokemon the_udppokemon;

    //第0列为序号，第一列为username
    the_udppokemon.name = query.value(2).toString();
    the_udppokemon.kind = static_cast<Pokemon_kind>(query.value(3).toUInt());
    the_udppokemon.level = query.value(4).toInt();
    the_udppokemon.max_EXP = query.value(5).toInt();
    the_udppokemon.EXP = query.value(6).toInt();
    the_udppokemon.ATK = query.value(7).toInt();
    the_udppokemon.max_HP = query.value(8).toInt();
    the_udppokemon.HP = query.value(9).toInt();
    the_udppokemon.DF = query.value(10).toInt();
    the_udppokemon.speed = query.value(11).toInt();
    the_udppokemon.special_ATK_name = query.value(12).toString();
    the_udppokemon.special_ATK = query.value(13).toInt();

    return the_udppokemon;
}

//从数据库中读取指定位置的虚拟小精灵，封装成UDPPokemon包
UDPPokemon MainWindow:: GetVirUdppok(QSqlQuery& query) const
{
    UDPPokemon udp_pokemon;
    //第0列为序号，第一列为name
    udp_pokemon.name = query.value(1).toString();
    udp_pokemon.kind = static_cast<Pokemon_kind>(query.value(2).toUInt());
    udp_pokemon.level = query.value(3).toInt();
    udp_pokemon.max_EXP = query.value(4).toInt();
    udp_pokemon.EXP = query.value(5).toInt();
    udp_pokemon.ATK = query.value(6).toInt();
    udp_pokemon.max_HP = query.value(7).toInt();
    udp_pokemon.HP = query.value(8).toInt();
    udp_pokemon.DF = query.value(9).toInt();
    udp_pokemon.speed = query.value(10).toInt();
    udp_pokemon.special_ATK_name = query.value(11).toString();
    udp_pokemon.special_ATK = query.value(12).toInt();

    return udp_pokemon;
}

//从数据库中找到选中小精灵的位置
QSqlQuery MainWindow:: GetChosnpokemon_query(const QString& username, const uint& index) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM pokemon WHERE username = ?");
    query.addBindValue(username);//在数据库pokemon表项中中查询用户
    if(!query.exec())
    {
        qDebug() << "执行在pokemon表中查找用户的指令失败" << query.lastError();
    }
    else
    {
        qInfo() << "执行在pokemon表中查找用户的指令成功" ;
    }
    for(uint i = 0; i < index; i++)
    {
        query.next();
    }
    query.next();

    return query;
}

//找到选中的虚拟小精灵的位置
QSqlQuery MainWindow:: GetChosVirpok_query(const uint& index) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM virtual_pokemon");
    if(!query.exec())
    {
        qDebug() << "执行取出virtual_pokemon中全部表项的指令失败" << query.lastError();
    }
    else
    {
        qInfo() << "执行取出virtual_pokemon中全部表项的指令成功。" ;
    }
    for(uint i = 0; i < index; i++)
    {
        query.next();
    }
    query.next();

    return query;
}

//从数据库中取出选定的用户小精灵
UDPPokemon MainWindow:: GetChosnpokemon(const QString& username, const uint& index) const
{
    QSqlQuery query = GetChosnpokemon_query(username, index);
    UDPPokemon udp_pokemon = GetUdppokemon(query);
    return udp_pokemon;
}

//从数据库中取出选定的虚拟小精灵
UDPPokemon MainWindow:: GetChosVirpokemon(const uint& index) const
{
    QSqlQuery query = GetChosVirpok_query(index);
    UDPPokemon udp_pokmeon = GetVirUdppok(query);
    return udp_pokmeon;
}

//升级数据库中的用户小精灵
void MainWindow:: UpdateIntoSql(const UDPPokemon& the_pokemon, const QString& username, const int* before_attr) const
{
    QSqlQuery query;
    QString sqlString = QString::asprintf(
        "UPDATE pokemon SET level=%d, max_EXP=%d, EXP=%d, ATK=%d, max_HP=%d, "
        "HP=%d, DF=%d, speed=%d, special_ATK=%d WHERE username=\"%s\" "
        "and name=\"%s\" and EXP=%d LIMIT 1",
        the_pokemon.level,
        the_pokemon.max_EXP,
        the_pokemon.EXP,
        the_pokemon.ATK,
        the_pokemon.max_HP,
        the_pokemon.HP,
        the_pokemon.DF,
        the_pokemon.speed,
        the_pokemon.special_ATK,
        username.toUtf8().constData(),
        the_pokemon.name.toUtf8().constData(),
        before_attr[5]
        );


    qDebug() << "增加经验前的数值为：" << before_attr[5];
    qDebug() << "增加经验之后的数值为：" << the_pokemon.EXP;

    if(!query.exec(sqlString))
    {
        qDebug() << "执行在数据库中修改pokemon的指令失败" << query.lastQuery();
    }
    else
    {
        qInfo() << "执行在数据库中修改pokemon的指令成功";
    }
    displayTable(ui->tableWidgetPokemon, "pokemon");
    displayTable(ui->tableWidgetUsers, "users");//在server窗口显示用户表
}

//升级数据库中的虚拟小精
void MainWindow:: UpdateVirSql(const UDPPokemon& the_pokemon, const int* before_attr) const
{
    QSqlQuery query;
    QString sqlString = QString::asprintf(
        "UPDATE virtual_pokemon SET level=%d, max_EXP=%d, EXP=%d, ATK=%d, max_HP=%d, "
        "HP=%d, DF=%d, speed=%d, special_ATK=%d WHERE "
        "name=\"%s\" and EXP=%d LIMIT 1",
        the_pokemon.level,
        the_pokemon.max_EXP,
        the_pokemon.EXP,
        the_pokemon.ATK,
        the_pokemon.max_HP,
        the_pokemon.HP,
        the_pokemon.DF,
        the_pokemon.speed,
        the_pokemon.special_ATK,
        the_pokemon.name.toUtf8().constData(),
        before_attr[5]
        );


    if(!query.exec(sqlString))
    {
        qDebug() << "执行在数据库中修改virtual_pokemon的指令失败" << query.lastQuery();
    }
    else
    {
        qInfo() << "执行在数据库中修改virtual_pokemon的指令成功";
        qInfo() << "修改后的经验值为" << the_pokemon.EXP;
    }
    displayTable(ui->tableWidgetUsers, "users");//在server窗口显示用户表
    displayTable(ui->tableWidgetvirPokemon, "virtual_pokemon");
}

//从数据库中删除用户的战败的小精灵
void MainWindow:: Deletepokemon(const QString& username, const uint& index, const UDPPokemon* udppokemon) const
{
    QSqlQuery query = GetChosnpokemon_query(username, index);

    query.prepare("DELETE FROM pokemon WHERE username = :username AND name = :name AND level = :level LIMIT 1");
    query.bindValue(":username", username);
    query.bindValue(":name", udppokemon->name);
    query.bindValue(":level", udppokemon->level);

    if(!query.exec())
    {
        qDebug() << "执行删除pokemon中表项的指令失败" << query.lastError();
    }
    else
    {
        qInfo() << "执行删除pokemon中表项的指令成功";
    }
    displayTable(ui->tableWidgetPokemon, "pokemon");
    displayTable(ui->tableWidgetUsers, "users");
}

//删除数据库中virtual_pokemon表中战败的小精灵
void MainWindow:: DeleteVirpokemon(const uint& index, const UDPPokemon& udppokemon)
{
    QSqlQuery query = GetChosVirpok_query(index);
    query.prepare("DELETE FROM virtual_pokemon WHERE name = :name AND level = :level LIMIT 1");
    query.bindValue(":name", udppokemon.name);
    query.bindValue(":level", udppokemon.level);
    if(!query.exec())
    {
        qDebug() << "执行删除pokemon中表项的指令失败" << query.lastError();
    }
    else
    {
        qInfo() << "执行删除pokemon中表项的指令成功";
    }
    virpokemon_num--;
    displayTable(ui->tableWidgetvirPokemon, "virtual_pokemon");
}

void MainWindow:: readPendingDatagrams()
{
    QByteArray dataIn;//读取数据
    dataIn.resize(server->pendingDatagramSize());//调整缓冲区大小以便接收完整数据
    server->readDatagram(dataIn.data(), dataIn.size());//从server中读取一个数据报文并存储在dataIn中
    QDataStream dsIn(&dataIn,QIODevice::ReadWrite);
    QString username;//用户名
    QString pwd;//密码
    unsigned int port;//端口号
    unsigned int loginKind;//消息类型
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

            qInfo() << username << pwd;
            //将新用户添加至users表
            query.prepare("INSERT INTO users (username, password, pokemon_num, "
                          "high_level_pokemon, victory_num, battle_num"
                          ") VALUES (:username, :password, :pokemon, :high_level_pokemon,"
                          ":victory_num, :battle_num)");
            query.bindValue(":username", username);
            query.bindValue(":password", pwd);
            query.bindValue(":pokemon_num", 0);
            query.bindValue(":high_level_pokemon", 0);
            query.bindValue(":victory_num", 0);
            query.bindValue(":battle_num", 0);
            int insert_success;
            insert_success = query.exec();
            if(insert_success) qInfo() << "用户成功写入users表";
            else qDebug() << "用户写入users表失败" << query.lastError();
            this->Create_pokemons(username, 3);//用户随机分配三个小精灵，并修改数据库信息
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
                user.pokemon_num = query.value(3).toInt();
                user.high_level_num = query.value(4).toInt();
                user.victory_num = query.value(5).toInt();
                user.battle_num = query.value(6).toInt();
                int contain = 0;
                for(int i = 0 ;i < onlineUsers.size(); i++)
                {
                    if(onlineUsers.at(i).username == username)
                        contain = 1;
                }
                if(!contain)
                {
                    this->onlineUsers.append(user);//加入在线用户行列

                    dsOut << SIGNINOK;//登陆成功
                    dsOut << user.pokemon_num << user.high_level_num
                          << user.victory_num << user.battle_num;
                    SentPokemon(dsOut,username);//发送小精灵信息
                }
                else
                {
                    dsOut<<HAVESIGNIN;
                }
            }
        }
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(dataOut.data(), dataOut.size(), serverAddress, port);
    }
    else if(loginKind == SIGNOUT)//登出
    {
        dsIn>>port;
        User user;
        user.username = username;
        user.port = port;
        this->onlineUsers.removeOne (user);//从在线用户列表中移走
        qDebug() << username << "Login out";
        qDebug() << this->onlineUsers.length ();
    }
    else if(loginKind == INGAME)
    {
        dsIn >> port;
        dsOut << VIRPOKEMON;
        while(virpokemon_num < 5)//保证虚拟小精灵的数目最少为五个
        {
            Createvirpokemon();
            qDebug() << "虚拟小精灵数目为:" << virpokemon_num;
        }
        dsOut << virpokemon_num;

        Sentall_virPokemon(dsOut);

        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        client->writeDatagram(dataOut.data(), dataOut.size(), serverAddress, port);
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
    else if(loginKind == UPGRADE || loginKind == DUEL)
    {
        uint pokemon_index;
        uint virtual_index;
        dsIn >> port >> pokemon_index >> virtual_index;
        UDPPokemon user_pokemon = GetChosnpokemon(username, pokemon_index);
        UDPPokemon vir_pokemon = GetChosVirpokemon(virtual_index);
        Pokemon pokemon1(user_pokemon);
        Pokemon pokemon2(vir_pokemon);
        Battle_controller battlecontroller(pokemon1, pokemon2);
        int before_attr[6];
        int isWin = battlecontroller.battle(before_attr);
        if(loginKind == UPGRADE)
        {
            if(isWin)
            {
                UDPPokemon* winner = pokemon1.getUDP();
                UpdateIntoSql(*winner, username, before_attr);
                if((before_attr[0] == 14) && (winner->level == 15))
                {
                    Change_users_Sql(username, 0, 1, 1, 1);
                }
                else
                {
                    Change_users_Sql(username, 0, 0, 1, 1);
                }
                dsOut << UPGRADEWIN;
                query.exec ("select * from users where username=\""+username+"\";");
                query.next();
                dsOut << username << query.value(3).toInt() << query.value(4).toInt()
                      << query.value(5).toInt() << query.value(6).toInt();
                SentPokemon(dsOut, username);
                delete winner;
            }
            else
            {
                UDPPokemon* winner = pokemon2.getUDP();
                UpdateVirSql(*winner, before_attr);
                Change_users_Sql(username, 0, 0, 0, 1);
                dsOut << UPGRADEFAIL;
                query.exec ("select * from users where username=\""+username+"\";");
                query.next();
                dsOut << username << query.value(3).toInt() << query.value(4).toInt()
                      << query.value(5).toInt() << query.value(6).toInt();
                dsOut << virpokemon_num;
                Sentall_virPokemon(dsOut);
                delete winner;
            }
        }
        else
        {
            if(isWin)
            {
                UDPPokemon* winner = pokemon1.getUDP();
                UpdateIntoSql(*winner, username, before_attr);
                DeleteVirpokemon(virtual_index, vir_pokemon);
                PutIntoSql(username, &vir_pokemon);//获得小精灵，写入数据库
                if((before_attr[0] == 14) && (winner->level == 15))
                {
                    if(vir_pokemon.level == 15)
                        Change_users_Sql(username, 1, 2, 1, 1);
                    else
                        Change_users_Sql(username, 1, 1, 1, 1);
                }
                else
                {
                    if(vir_pokemon.level == 15)
                        Change_users_Sql(username, 1, 1, 1, 1);
                    else
                        Change_users_Sql(username, 1, 0, 1, 1);
                }
                dsOut << VICTORY;
                query.exec ("select * from users where username=\""+username+"\";");
                query.next();
                dsOut << username << query.value(3).toInt() << query.value(4).toInt()
                      << query.value(5).toInt() << query.value(6).toInt();
                SentPokemon(dsOut, username);
                dsOut << virpokemon_num;
                Sentall_virPokemon(dsOut);
                delete winner;
            }
            else
            {
                UDPPokemon* winner = pokemon2.getUDP();
                UpdateVirSql(*winner, before_attr);
                Change_users_Sql(username, 0, 0, 0, 1);
                dsOut << FAIL;
                query.exec ("select * from users where username=\""+username+"\";");
                query.next();

                qDebug() << "FAIL将传递如下信息：";
                qDebug() << username;
                qDebug() << query.value(3).toInt();
                qDebug() << query.value(4).toInt();
                qDebug() << query.value(5).toInt();
                qDebug() << query.value(6).toInt();
                qDebug() << virpokemon_num;
                dsOut << username << query.value(3).toInt() << query.value(4).toInt()
                      << query.value(5).toInt() << query.value(6).toInt();
                SentPokemon(dsOut, username);
                dsOut << virpokemon_num;
                Sentall_virPokemon(dsOut);
                delete winner;
            }
        }
        QHostAddress serveraddress = QHostAddress("127.0.0.1");
        client->writeDatagram(dataOut.data(), dataOut.size(), serveraddress, port);
    }
    else if(loginKind == GIVEYOU)
    {
        uint pokemon_index;
        dsIn >> port >> pokemon_index;
        UDPPokemon udp_pokemon = GetChosnpokemon(username, pokemon_index);
        Deletepokemon(username, pokemon_index, &udp_pokemon);
        virIntoSql(&udp_pokemon);
        if(udp_pokemon.level == 15)
        {
            Change_users_Sql(username, -1, -1, 0, 0);
        }
        else
        {
            Change_users_Sql(username, -1, 0, 0, 0);
        }
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE username=:username");
        query.addBindValue(username);
        if(!query.exec())
        {
            qDebug() << "执行从users中寻找用户的指令失败" << query.lastError();
        }
        else
        {
            qInfo() << "执行从users中寻找用户的指令成功。";
        }
        if(query.next())
        {
            int num = query.value(3).toInt();
            qDebug() << "收到GIVEYOU后，用户的小精灵数目为" << num;
            if(num == 0)
            {
                Create_pokemons(username, 1);
                dsOut << ANEWPOKEMON;
                SentPokemon(dsOut, username);
                qDebug() << "发送了ANEWPOKEMON";
                QHostAddress serveraddress = QHostAddress("127.0.0.1");
                client->writeDatagram(dataOut.data(), dataOut.size(), serveraddress, port);
            }
        }
    }

}






























