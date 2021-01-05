#include "Character.h"

Mage::Mage()
{
    this->base_attack += 5;
    this->base_health += 55;
    this->base_shield -= 50;
    this->crit_chance = 25;
    this->crit_multiplier = 0.30;
    this->player_moves = new Mage_moves();
}
