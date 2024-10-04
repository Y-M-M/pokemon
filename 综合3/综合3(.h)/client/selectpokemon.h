#ifndef SELECTPKM_H
#define SELECTPKM_H

#include <QDialog>

#include "pokemon.h"


namespace Ui {
class SelectPkm;
}

class SelectPkm : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPkm(QWidget *parent = 0);
    ~SelectPkm();

    QString getInfo(uint index);//获取小精灵信息

signals:
    void sentSelectResult(uint index);//用户选择结果

private slots:
    void comboBoxPkm_Index(int index);

    void recvSelect(QList<UDPPokemon *> pkmList, uint *pkmIndex);//接受用于选择的小精灵

    void BtnCfm_clicked();

private:
    Ui::SelectPkm *ui;

    QList<UDPPokemon*> pkms;
    uint *pkmIndex;
};

#endif // SELECTPKM_H
