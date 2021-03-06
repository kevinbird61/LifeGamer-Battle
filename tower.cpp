#include "tower.h"

#include "minion.h"

#include <QDebug>

Tower::Tower(int hp, int atk, int attackRange, int group, int target, Battle *battle, QObject *parent)
    : Unit(hp, 0, 0, atk, attackRange, group, battle, parent)
{
    connect(battle, SIGNAL(signalLogHp()), this, SLOT(setPreviousHpRatio()));
    this->target = target;
}

void Tower::setPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}

QJsonObject Tower::toJsonObject(bool isNew)
{
    QJsonObject tower;
    QString name("p");
    name += QString::number(group);
    name += "_";
    switch(SN) {
    case 1:case 4:
        name += "top";
        break;
    case 2:case 5:
        name += "main";
        break;
    case 3: case 6:
        name += "down";
        break;
    }

    tower["name"] = name;
    tower["status"] = QString::number(getHpChange());

    return tower;
}

void Tower::active()
{
    for(Unit* iter : battle->UnitList) {
        if(Minion* temp = dynamic_cast<Minion*>(iter)) {
            if(temp->group != group && ((temp->fixed_y <= 23 && temp->group == 2) || (temp->fixed_y >= 28 && temp->group == 1))) {
                temp->onhit(atk);
                break;
            }
        }
    }
}
