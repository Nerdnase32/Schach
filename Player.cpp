#include "Player.h"

Player::Player(Color color) : color(color)
{
}

Player::~Player()
{
}

void Player::updateFigures()
{
  for (FigurPtr figur : figures)
    figur->updateAttackedFields();
}
