
#include "Engine.h"

Engine* Engine::instance = nullptr;

Engine::Engine() : checker(board)
{
  white = std::make_shared<Player>(Color::WHITE);
  black = std::make_shared<Player>(Color::BLACK);

  for (int x = 0; x < 8; x++)
  {
    board.push_back(FieldVec());
    for (int y = 0; y < 8; y++)
      board[x].push_back(std::make_shared<Field>(x, y));
  }
}

Engine::~Engine()
{
}

Engine* Engine::getEngine()
{
  if (instance == nullptr)
    instance = new Engine();

  return instance;
}

void Engine::init()
{
  for (int i = 0; i < 8; i++)
  {
    board[1][i]->setActiveFigur(std::make_shared<Pawn>(Color::WHITE));
    board[6][i]->setActiveFigur(std::make_shared<Pawn>(Color::BLACK));
  }

  board[0][0]->setActiveFigur(std::make_shared<Rook>(Color::WHITE));
  board[0][7]->setActiveFigur(std::make_shared<Rook>(Color::WHITE));
  board[7][0]->setActiveFigur(std::make_shared<Rook>(Color::BLACK));
  board[7][7]->setActiveFigur(std::make_shared<Rook>(Color::BLACK));

  board[0][1]->setActiveFigur(std::make_shared<Knight>(Color::WHITE));
  board[0][6]->setActiveFigur(std::make_shared<Knight>(Color::WHITE));
  board[7][1]->setActiveFigur(std::make_shared<Knight>(Color::BLACK));
  board[7][6]->setActiveFigur(std::make_shared<Knight>(Color::BLACK));

  board[0][2]->setActiveFigur(std::make_shared<Bishop>(Color::WHITE));
  board[0][5]->setActiveFigur(std::make_shared<Bishop>(Color::WHITE));
  board[7][2]->setActiveFigur(std::make_shared<Bishop>(Color::BLACK));
  board[7][5]->setActiveFigur(std::make_shared<Bishop>(Color::BLACK));

  board[0][3]->setActiveFigur(std::make_shared<Queen>(Color::WHITE));
  board[7][3]->setActiveFigur(std::make_shared<Queen>(Color::BLACK));

  KingPtr whiteKing = std::make_shared<King>(Color::WHITE);
  white->setKing(whiteKing);
  board[0][4]->setActiveFigur(whiteKing);

  KingPtr blackKing = std::make_shared<King>(Color::BLACK);
  black->setKing(blackKing);
  board[7][4]->setActiveFigur(blackKing);

  for (int y = 0; y < 8; y++)
  {
    white->addFigure(board[0][y]->getActiveFigur());
    white->addFigure(board[1][y]->getActiveFigur());
    black->addFigure(board[6][y]->getActiveFigur());
    black->addFigure(board[7][y]->getActiveFigur());
  }

  white->updateFigures();
  black->updateFigures();

  activePlayer = white;
  inactivePlayer = black;
}

WSTRING Engine::processInitFigures(Argument arg)
{
  WSTRING result;

  for (size_t x = 0; x < 8; x++)
  {
    for (size_t y = 0; y < 8; y++)
    {
      FigurPtr activeFigur = getActiveFigur(Coord(x, y));
      if (activeFigur)
      {
        if (arg != Argument::ONLY_MOVED || activeFigur->hasMoved())
        {
          result += Tool::colorToString(activeFigur->getColor()) + L" " + activeFigur->getName() + L" on " + Tool::coordToString(activeFigur->getCoord());
          result += L", ";
        }
      }
    }
  }

  if (result.length())
    result.replace(result.length() - 2, result.length(), L" \n");

  return result;
}

WSTRING Engine::processNewCoords(Coord coord)
{
  bool result = false;

  if (activeField)
    result = selectTargetField(coord);
  else
    result = selectFigur(coord);

  return result ? Tool::coordToString(coord) : L"ERROR";
}

WSTRING Engine::getOutput()
{
  WSTRING output;

  if (activeField == nullptr)
    output = Tool::colorToString(activePlayer->getColor()) + L" choose figur\n";
  else
    output = L"choose target field or another figur\n";

  return output;
}

FieldPtr Engine::getField(Coord coord)
{
  FieldPtr field = nullptr;

  if (Checker::checkCoord(coord))
    field = board[coord.x][coord.y];

  return field;
}

FigurPtr Engine::getActiveFigur(Coord coord)
{
  FigurPtr activeFigur = nullptr;

  FieldPtr board = getField(coord);
  if (board)
    activeFigur = board->getActiveFigur();

  return activeFigur;
}

bool Engine::selectFigur(Coord coord)
{
  bool result = false;

  FieldPtr field = getField(coord);
  if (field)
  {
    FigurPtr activeFigur = field->getActiveFigur();
    if (activeFigur)
    {
      if (activeFigur->getColor() == activePlayer->getColor())
      {
        activeField = field;
        _tprintf(L"%s selected\n", field->getActiveFigur()->getName().c_str());
        result = true;
      }
      else
        _tprintf(L"figur has wrong color\n");
    }
    else
      _tprintf(L"no figur on field %s\n", Tool::coordToString(coord).c_str());
  }
  else
    _tprintf(L"invalid field %s\n", Tool::coordToString(coord).c_str());

  return result;
}

bool Engine::selectTargetField(Coord coord)
{
  Result result = Result::R_ERROR;

  FieldPtr targetField = getField(coord);
  if (targetField)
  {
    result = tryMove(activeField, targetField);
    if (result == Result::MOVED)
    {
      switchPlayer();
      activeField = nullptr;
    }
  }

  return result != Result::R_ERROR;
}

void Engine::switchPlayer()
{
  PlayerPtr tempActivePlayer = activePlayer;
  activePlayer = inactivePlayer;
  inactivePlayer = tempActivePlayer;
}

void Engine::changeField(FieldPtr targetField)
{
  activeField = targetField;

  if (targetField->getActiveFigur())
    _tprintf(L"figur changed to %s\n", targetField->getActiveFigur()->getName().c_str());
  else
    _tprintf(L"no figur on field");
}

Result Engine::tryMove(FieldPtr origField, FieldPtr targetField)
{
  Result result = Result::R_ERROR;

  FigurPtr activeFigur = origField->getActiveFigur();
  if (activeFigur)
  {
    FigurPtr targetFigur = targetField->getActiveFigur();
    if (targetFigur)
    {
      if (targetFigur->getColor() == activePlayer->getColor())
      {
        changeField(targetField);
        result = Result::CHANGED;
      }
      else if (targetFigur->isInvincible())
      {
        _tprintf(L"can't capture %s\n", targetFigur->getName().c_str());
      }
      else
      {
        if (tryCaptureFigur(origField, targetField))
        {
          if (!(checkCheck()))
            moveBack(origField, targetField);
          else
            result = Result::MOVED;
        }
      }
    }
    else
    {
      if (tryMoveFigur(origField, targetField))
      {
        if (!(checkCheck()))
          moveBack(origField, targetField);
        else
          result = Result::MOVED;
      }
    }
  }
  else
    _tprintf(L"no figur on field");

  return result;
}

void Engine::moveFigur(FieldPtr origField, FieldPtr targetField)
{
  FigurPtr activeFigur = origField->getActiveFigur();

  tempCapturedFigure = targetField->getActiveFigur();
  tempMoved = activeFigur->hasMoved();

  origField->setActiveFigur(nullptr);
  targetField->setActiveFigur(activeFigur);
  activeFigur->setMoved(true);

  activePlayer->updateFigures();
  inactivePlayer->updateFigures();

  _tprintf(L"%s moved to %s\n", activeFigur->getName().c_str(), targetField->getName().c_str());
}

void Engine::moveBack(FieldPtr origField, FieldPtr targetField)
{
  FigurPtr movedFigur = targetField->getActiveFigur();
  if (movedFigur)
  {
    movedFigur->setMoved(tempMoved);
    origField->setActiveFigur(movedFigur);
    targetField->setActiveFigur(tempCapturedFigure);

    activePlayer->updateFigures();
    inactivePlayer->updateFigures();
  }
}

bool Engine::checkCheck()
{
  bool result = true;

  bool inactiveCheck = checker.checkCheck(activePlayer, inactivePlayer);
  bool activeCheck = checker.checkCheck(inactivePlayer, activePlayer);

  if (activeCheck)
  {
    _tprintf(L"Invalid move. Own King is checked\n");
    result = false;
  }

  if (inactiveCheck)
    _tprintf(L"check\n");

  return result;
}

bool Engine::tryCaptureFigur(FieldPtr origField, FieldPtr targetField)
{
  bool result = false;

  FigurPtr activeFigur = origField->getActiveFigur();
  if (activeFigur && activeFigur->validMove(targetField))
  {
    FigurPtr targetFigur = targetField->getActiveFigur();
    if (targetFigur)
    {
      _tprintf(L"%s captured\n", targetFigur->getName().c_str());

      inactivePlayer->addLostFigure(targetFigur);
      inactivePlayer->removeFigure(targetFigur);

      moveFigur(origField, targetField);

      result = true;
    }
  }
  else
    _tprintf(L"invalid move");

  return result;
}

bool Engine::tryMoveFigur(FieldPtr origField, FieldPtr targetField)
{
  bool result = false;

  FigurPtr activeFigur = origField->getActiveFigur();
  if (activeFigur && activeFigur->validMove(targetField))
  {
    moveFigur(origField, targetField);

    result = true;
  }
  else
    _tprintf(L"invalid move");

  return result;
}
