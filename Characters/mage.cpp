#include "Character.h"

Mage::Mage()
{
    this->base_attack += 10;
    this->base_health += 30;
    this->base_shield -= 20;
    this->player_moves = new Mage_moves();
}
