#include "humanrifleman.h"

HumanRifleman::HumanRifleman(int group, Battle *battle, QObject *parent)
    : Minion('C', "human_rifleman", 500, 8, 0.2f, 10, 7, group, battle, parent)
{
    if(group == 1) setTarget(2);
    else setTarget(1);
}
