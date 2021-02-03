
#ifndef FIELD_H
#define FIELD_H

#include "Tool.h"

class Figur;
class Field;

typedef std::shared_ptr<Figur> FigurPtr;
typedef std::shared_ptr<Field> FieldPtr;
typedef std::vector<FieldPtr>  FieldVec;
typedef std::vector<FieldVec>  FieldMat;
typedef std::set<FieldPtr>     FieldSet;

class Field
{
public:
  Field(size_t x, size_t y);
  ~Field();

  void        setActiveFigur(FigurPtr activeFigur);

  FigurPtr    getActiveFigur()                const { return activeFigur; }
  Coord       getCoord()                      const { return coord; }
  std::string getName()                       const { return Tool::coordToString(coord); }

private:
  FigurPtr    activeFigur = nullptr;
  Coord       coord;
};

#endif // !FIELD_H