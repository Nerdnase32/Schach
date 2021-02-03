
#ifndef FIGUR_H
#define FIGUR_H

#include "Field.h"

class Figur;

typedef std::shared_ptr<Figur> FigurPtr;
typedef std::vector<FigurPtr>  FigurVec;

class Figur : std::enable_shared_from_this<Figur>
{
public:
  Figur(Color color);
  ~Figur();

  void        setAttackers();
  void        clearAttackedField();
  void        setCoord(Coord coord)     { this->coord = coord; }
  void        setMoved(bool moved)      { this->moved = moved; }

  bool        hasMoved()          const { return moved; }
  bool        canJump()           const { return jump; }
  bool        isInvincible()      const { return invincible; }
  std::string getName()           const { return name; }
  Color       getColor()          const { return color; }
  Coord       getCoord()          const { return coord; }
  FieldSet    getAttackedFields() const { return attackedFields; }

  virtual bool validMove(Coord targetCord, bool capture) = 0;

private:
  virtual void setAttackedFields() = 0;

protected:
  void addAttacker(size_t x, size_t y);
  void setAttackersStraightFields();
  void setAttackersDiagonalFields();

protected:
  bool        invincible = false;
  bool        moved      = false;
  bool        jump       = false;
  double      value      = 0;
  Color       color      = Color::UNKNOWN;
  Coord       coord;
  FieldSet    attackedFields;
  std::string name;

};

class Pawn;

typedef std::shared_ptr<Pawn> PawnPtr;

class Pawn : public Figur
{
public:
  Pawn(Color color);
  ~Pawn();

  bool validMove(Coord targetCoord, bool capture) override;
  void setAttackedFields() override;
};

class Knight;

typedef std::shared_ptr<Knight> KnightPtr;

class Knight : public Figur
{
public:
  Knight(Color color);
  ~Knight();

  bool validMove(Coord targetCoord, bool capture) override;
  void setAttackedFields() override;
};

class Queen;

typedef std::shared_ptr<Queen> QueenPtr;

class Queen : public Figur
{
public:
  Queen(Color color);
  ~Queen();

  bool validMove(Coord targetCoord, bool capture) override;
  void setAttackedFields() override;
};

class King;

typedef std::shared_ptr<King> KingPtr;

class King : public Figur
{
public:
  King(Color color);
  ~King();

  bool validMove(Coord targetCoord, bool capture) override;
  void setAttackedFields() override;
};

class Rook;

typedef std::shared_ptr<Rook> RookPtr;

class Rook : public Figur
{
public:
  Rook(Color color);
  ~Rook();

  bool validMove(Coord targetCoord, bool capture) override;
  void setAttackedFields() override;
};

class Bishop;

typedef std::shared_ptr<Bishop> BishopPtr;

class Bishop : public Figur
{
public:
  Bishop(Color color);
  ~Bishop();

  bool validMove(Coord targetCoord, bool capture) override;
  void setAttackedFields() override;
};

#endif // !FIGUR_H