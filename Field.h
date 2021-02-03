
#ifndef FIELD_H
#define FIELD_H

#include "Tool.h"

class Figur;
class Field;

typedef std::shared_ptr<Figur> FigurPtr;
typedef std::shared_ptr<Field> FieldPtr;
typedef std::vector<FieldPtr>  FieldVec;
typedef std::vector<FieldVec>  FieldMat;

typedef std::set<Figur*> FigurSet;
typedef std::map<Color, FigurSet> FigurSetMap;

class Field
{
public:
  Field(size_t x, size_t y);
  ~Field();

  void        setActiveFigur(FigurPtr activeFigur);
  void        addAttacker(Figur* attacker);
  void        removeAttacker(Figur* attacker);

  bool               hasAttackers(Color color);
  const FigurSet&    getAttackers(Color color)   const { return attackers.at(color); }
  const FigurSetMap& getAtackers()               const { return attackers; }

  FigurPtr    getActiveFigur()                const { return activeFigur; }
  Coord       getCoord()                      const { return coord; }
  std::string getName()                       const { return Tool::coordToString(coord); }

private:
  FigurPtr    activeFigur = nullptr;
  FigurSetMap attackers;
  Coord       coord;
};

#endif // !FIELD_H