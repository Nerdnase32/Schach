
#ifndef ENGINE_H
#define ENGINE_H

#include "Checker.h"
#include "Player.h"

class Engine
{
private:
  Engine();
  ~Engine();

public:
  static Engine* getEngine();

  void init();
  void processLogFigures(Argument arg);
  void processNewCoords(Coord coord);

  const FieldMat& getBoard()            const { return board; }

  std::string getOutput();
  FieldPtr    getField(Coord coord);

private:
  FigurPtr getActiveFigur(Coord coord);

  void selectFigur(Coord coord);
  void selectTargetField(Coord coord);
  void switchPlayer();
  void changeField(FieldPtr targetField);
  void moveFigur(FieldPtr origField, FieldPtr targetField);
  void moveBack(FieldPtr origField, FieldPtr targetField);

  bool checkCheck();
  bool tryMove(FieldPtr origField, FieldPtr targetField);
  bool tryCaptureFigur(FieldPtr origField, FieldPtr targetField);
  bool tryMoveFigur(FieldPtr origField, FieldPtr targetField);

private:
  FieldMat  board;
  PlayerPtr black;
  PlayerPtr white;
  PlayerPtr activePlayer   = nullptr;
  PlayerPtr inactivePlayer = nullptr;
  FieldPtr  activeField    = nullptr;

  FigurPtr  tempCapturedFigure = nullptr;
  bool      tempMoved = false;

  Checker checker;

private:
  static Engine* instance;
};

#endif // !ENGINE_H