
#ifndef FIGUR_H
#define FIGUR_H

#include "Field.h"

class Figur;

typedef std::shared_ptr<Figur> FigurPtr;
typedef std::vector<FigurPtr>  FigurVec;
typedef std::set<FigurPtr>     FigurSet;

class Figur : std::enable_shared_from_this<Figur>
{
public:
  Figur(Color color);
  ~Figur();

  void     updateAttackedFields();
  void     clearAttackedField();
  void     setCoord(Coord coord)     { this->coord = coord; }
  void     setMoved(bool moved)      { this->moved = moved; }

  bool     hasMoved()          const { return moved; }
  bool     canJump()           const { return jump; }
  bool     isInvincible()      const { return invincible; }
  WSTRING  getName()           const { return name; }
  Color    getColor()          const { return color; }
  Coord    getCoord()          const { return coord; }
  FieldSet getAttackedFields() const { return attackedFields; }

  virtual bool validMove(FieldPtr targetField);

private:
  virtual void setAttackedFields() = 0;

protected:
  void addAttacker(size_t x, size_t y);
  void setAttackersStraightFields();
  void setAttackersDiagonalFields();

protected:
  bool     invincible = false;
  bool     moved      = false;
  bool     jump       = false;
  double   value      = 0;
  Color    color      = Color::UNKNOWN;
  Coord    coord;
  FieldSet attackedFields;
  WSTRING  name;

};

class Pawn;

typedef std::shared_ptr<Pawn> PawnPtr;

class Pawn : public Figur
{
public:
  Pawn(Color color);
  ~Pawn();

  bool validMove(FieldPtr targetField) override;
  void setAttackedFields() override;
};

class Knight;

typedef std::shared_ptr<Knight> KnightPtr;

class Knight : public Figur
{
public:
  Knight(Color color);
  ~Knight();

  void setAttackedFields() override;
};

class Queen;

typedef std::shared_ptr<Queen> QueenPtr;

class Queen : public Figur
{
public:
  Queen(Color color);
  ~Queen();

  void setAttackedFields() override;
};

class King;

typedef std::shared_ptr<King> KingPtr;

class King : public Figur
{
public:
  King(Color color);
  ~King();

  void setAttackedFields() override;
};

class Rook;

typedef std::shared_ptr<Rook> RookPtr;

class Rook : public Figur
{
public:
  Rook(Color color);
  ~Rook();

  void setAttackedFields() override;
};

class Bishop;

typedef std::shared_ptr<Bishop> BishopPtr;

class Bishop : public Figur
{
public:
  Bishop(Color color);
  ~Bishop();

  void setAttackedFields() override;
};

#endif // !FIGUR_H