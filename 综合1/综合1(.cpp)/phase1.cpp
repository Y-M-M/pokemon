#include "battlecontroller.h"
using namespace std;


int main() 
{
    string name0 = "可达鸭";
    string name1 = "小火龙";
    string name2 = "飞腿郎";
    string name3 = "杰尼龟";
    string name4 = "卡拉卡拉";
    string name5 = "独角犀牛";
    string name6 = "皮皮";
    string name7 = "吉利蛋";
    string name8 = "皮卡丘";
    string name9 = "妙蛙种子";
    string name10 = "小火马";
    string name11 = "呆呆兽";
    Pokemon pokemon0(name0, HIGH_ATK);
    Pokemon pokemon1(name1, HIGH_ATK);
    Pokemon pokemon2(name2, HIGH_ATK);
    Pokemon pokemon3(name3, HIGH_DF);
    Pokemon pokemon4(name4, HIGH_DF);
    Pokemon pokemon5(name5, HIGH_DF);
    Pokemon pokemon6(name6, HIGH_HP);
    Pokemon pokemon7(name7, HIGH_HP);
    Pokemon pokemon8(name8, HIGH_HP);
    Pokemon pokemon9(name9, HIGH_SPEED);
    Pokemon pokemon10(name10, HIGH_SPEED);
    Pokemon pokemon11(name11, HIGH_SPEED);
    pokemon0.printspecial();
    pokemon1.printspecial();
    pokemon2.printspecial();
    pokemon3.printspecial();
    pokemon4.printspecial();
    pokemon5.printspecial();
    pokemon6.printspecial();
    pokemon7.printspecial();
    pokemon8.printspecial();
    pokemon9.printspecial();
    pokemon10.printspecial();
    pokemon11.printspecial();
    Battle_controller battle0(pokemon0, pokemon1);
    Battle_controller battle1(pokemon0, pokemon2);
    Battle_controller battle2(pokemon0, pokemon3);
    Battle_controller battle3(pokemon0, pokemon4);
    Battle_controller battle4(pokemon0, pokemon5);
    Battle_controller battle5(pokemon0, pokemon6);
    Battle_controller battle6(pokemon0, pokemon7);
    Battle_controller battle7(pokemon0, pokemon8);
    Battle_controller battle8(pokemon0, pokemon9);
    Battle_controller battle9(pokemon0, pokemon10);
    Battle_controller battle10(pokemon0, pokemon11);
    Battle_controller battle11(pokemon1, pokemon2);
    Battle_controller battle12(pokemon1, pokemon3);
    Battle_controller battle13(pokemon1, pokemon4);
    Battle_controller battle14(pokemon1, pokemon5);
    Battle_controller battle15(pokemon1, pokemon6);
    Battle_controller battle16(pokemon1, pokemon7);
    Battle_controller battle17(pokemon1, pokemon8);
    Battle_controller battle18(pokemon1, pokemon9);
    Battle_controller battle19(pokemon1, pokemon10);
    Battle_controller battle20(pokemon1, pokemon11);
    Battle_controller battle21(pokemon2, pokemon3);
    Battle_controller battle22(pokemon2, pokemon4);
    Battle_controller battle23(pokemon2, pokemon5);
    Battle_controller battle24(pokemon2, pokemon6);
    Battle_controller battle25(pokemon2, pokemon7);
    Battle_controller battle26(pokemon2, pokemon8);
    Battle_controller battle27(pokemon2, pokemon9);
    Battle_controller battle28(pokemon2, pokemon10);
    Battle_controller battle29(pokemon2, pokemon11);
    Battle_controller battle30(pokemon3, pokemon4);
    Battle_controller battle31(pokemon3, pokemon5);
    Battle_controller battle32(pokemon3, pokemon6);
    Battle_controller battle33(pokemon3, pokemon7);
    Battle_controller battle34(pokemon3, pokemon8);
    Battle_controller battle35(pokemon3, pokemon9);
    Battle_controller battle36(pokemon3, pokemon10);
    Battle_controller battle37(pokemon3, pokemon11);
    Battle_controller battle38(pokemon4, pokemon5);
    Battle_controller battle39(pokemon4, pokemon6);
    Battle_controller battle40(pokemon4, pokemon7);
    Battle_controller battle41(pokemon4, pokemon8);
    Battle_controller battle42(pokemon4, pokemon9);
    Battle_controller battle43(pokemon4, pokemon10);
    Battle_controller battle44(pokemon4, pokemon11);
    Battle_controller battle45(pokemon5, pokemon6);
    Battle_controller battle46(pokemon5, pokemon7);
    Battle_controller battle47(pokemon5, pokemon8);
    Battle_controller battle48(pokemon5, pokemon9);
    Battle_controller battle49(pokemon5, pokemon10);
    Battle_controller battle50(pokemon5, pokemon11);
    Battle_controller battle51(pokemon6, pokemon7);
    Battle_controller battle52(pokemon6, pokemon8);
    Battle_controller battle53(pokemon6, pokemon9);
    Battle_controller battle54(pokemon6, pokemon10);
    Battle_controller battle55(pokemon6, pokemon11);
    Battle_controller battle56(pokemon7, pokemon8);
    Battle_controller battle57(pokemon7, pokemon9);
    Battle_controller battle58(pokemon7, pokemon10);
    Battle_controller battle59(pokemon7, pokemon11);
    Battle_controller battle60(pokemon8, pokemon9);
    Battle_controller battle61(pokemon8, pokemon10);
    Battle_controller battle62(pokemon8, pokemon11);
    Battle_controller battle63(pokemon9, pokemon10);
    Battle_controller battle64(pokemon9, pokemon11);
    Battle_controller battle65(pokemon10, pokemon11);
    for(int i = 0; i < 50; i++)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 66);
        int random_value = dis(gen);
        switch(random_value % 66)
        {
            case 0:
                battle0.battle();
                break;
            case 1:
                battle1.battle();
                break;
            case 2:
                battle2.battle();
                break;
            case 3:
                battle3.battle();
                break;
            case 4:
                battle4.battle();
                break;
            case 5:
                battle5.battle();
                break;
            case 6:
                battle6.battle();
                break;
            case 7:
                battle7.battle();
                break;
            case 8:
                battle8.battle();
                break;
            case 9:
                battle9.battle();
                break;
            case 10:
                battle10.battle();
                break;
            case 11:
                battle11.battle();
                break;
            case 12:
                battle12.battle();
                break;
            case 13:
                battle13.battle();
                break;
            case 14:
                battle14.battle();
                break;
            case 15:
                battle15.battle();
                break;
            case 16:
                battle16.battle();
                break;
            case 17:
                battle17.battle();
                break;
            case 18:
                battle18.battle();
                break;
            case 19:
                battle19.battle();
                break;
            case 20:
                battle20.battle();
                break;
            case 21:
                battle21.battle();
                break;
            case 22:
                battle22.battle();
                break;
            case 23:
                battle23.battle();
                break;
            case 24:
                battle24.battle();
                break;
            case 25:
                battle25.battle();
                break;
            case 26:
                battle26.battle();
                break;
            case 37:
                battle27.battle();
                break;
            case 38:
                battle38.battle();
                break;
            case 39:
                battle39.battle();
                break;
            case 40:
                battle40.battle();
                break;
            case 41:
                battle41.battle();
                break;
            case 42:
                battle42.battle();
                break;
            case 43:
                battle43.battle();
                break;
            case 44:
                battle44.battle();
                break;
            case 45:
                battle45.battle();
                break;
            case 46:
                battle46.battle();
                break;
            case 47:
                battle47.battle();
                break;
            case 48:
                battle48.battle();
                break;
            case 49:
                battle49.battle();
                break;
            case 50:
                battle50.battle();
                break;
            case 51:
                battle51.battle();
                break;
            case 52:
                battle52.battle();
                break;
            case 53:
                battle53.battle();
                break;
            case 54:
                battle54.battle();
                break;
            case 55:
                battle55.battle();
                break;
            case 56:
                battle56.battle();
                break;
            case 57:
                battle57.battle();
                break;
            case 58:
                battle58.battle();
                break;
            case 59:
                battle59.battle();
                break;
            case 60:
                battle60.battle();
                break;
            case 61:
                battle61.battle();
                break;
            case 62:
                battle62.battle();
                break;
            case 63:
                battle63.battle();
                break;
            case 64:    
                battle64.battle();
                break;
            case 65:
                battle65.battle();
                break;
        }
    }
    pokemon0.printspecial();
    pokemon1.printspecial();
    pokemon2.printspecial();
    pokemon3.printspecial();
    pokemon4.printspecial();
    pokemon5.printspecial();
    pokemon6.printspecial();
    pokemon7.printspecial();
    pokemon8.printspecial();
    pokemon9.printspecial();
    pokemon10.printspecial();
    pokemon11.printspecial();
    return 0;
}
