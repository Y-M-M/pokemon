#include "selectpokemon.h"
#include "ui_selectpokemon.h"

SelectPkm::SelectPkm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPkm)
{
    ui->setupUi(this);

    connect(this,SIGNAL(sentSelectResult(uint)),
            this->parentWidget(),SLOT(recvSelectResult(uint)));
    connect(ui->BtnCfm, SIGNAL(clicked(bool)), this, SLOT(BtnCfm_clicked()));
    connect(ui->comboBoxPkm, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxPkm_Index(int)));

    ui->labelPkmInfo->setObjectName("labelPkmInfo");
}

SelectPkm::~SelectPkm()
{
    delete ui;
}

QString SelectPkm::getInfo(uint index)
{
    UDPPokemon *current_pokemon;
    current_pokemon = this->pkms[index];

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

void SelectPkm::recvSelect(QList<UDPPokemon *> pkmList, uint *pkmIndex)
{
    this->pkms.clear ();
    this->pkms = pkmList;
    this->pkmIndex = pkmIndex;

    ui->comboBoxPkm->clear();
    for(int i = 0; i < pkmList.length();i++)
        ui->comboBoxPkm->addItem(pkmList[i]->name);
    ui->comboBoxPkm->setCurrentIndex (0);

    ui->labelPkmInfo->setText (this->getInfo (0));
    ui->labelPkmInfo->setStyleSheet ("#labelPkmInfo{border-image:url(/:image/"+
                                    this->pkms[0]->name+".webp);}");
}

void SelectPkm:: comboBoxPkm_Index(int index)
{
    if(index >= 0 && index < this->pkms.length ())
    {
        ui->labelPkmInfo->setText(this->getInfo (index));
        ui->labelPkmInfo->setStyleSheet ("#labelPkmInfo{border-image:url(/:image/"+
                                        this->pkms[index]->name+".webp);}");
    }
}

void SelectPkm:: BtnCfm_clicked()
{
    emit sentSelectResult(this->pkmIndex[ui->comboBoxPkm->currentIndex()]);
}
