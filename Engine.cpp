
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

  activePlayer   = white;
  inactivePlayer = black;
}

void Engine::processLogFigures(Argument arg)
{
  std::string log;

  int counter = 0;
  for (size_t x = 0; x < 8; x++)
  {
    for (size_t y = 0; y < 8; y++)
    {
      FigurPtr activeFigur = getActiveFigur(Coord(x, y));
      if (activeFigur)
      {
        if (arg != Argument::ONLY_MOVED || activeFigur->hasMoved())
        {
          log += Tool::colorToString(activeFigur->getColor()) + " " + activeFigur->getName() + " on " + Tool::coordToString(activeFigur->getCoord());

          counter++;
          if (counter % 4 == 0)
            log += " \n";
          else
            log += ", ";
        }
      }
    }
  }

  if (log.length())
  {
    log.replace(log.length() - 2, log.length(), " \n");

    std::cout << log;
  }
}

std::string Engine::processNewCoords(Coord coord)
{
  if (activeField)
    selectTargetField(coord);
  else
    selectFigur(coord);

  return Tool::coordToString(coord);
}

std::string Engine::getOutput()
{
  std::string output;

  if (activeField == nullptr)
    output = Tool::colorToString(activePlayer->getColor()) + " choose figur\n";
  else
    output = "choose target field or another figur\n";

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

void Engine::selectFigur(Coord coord)
{
  FieldPtr field = getField(coord);
  if (field)
  {
    FigurPtr activeFigur = field->getActiveFigur();
    if (activeFigur)
    {
      if (activeFigur->getColor() == activePlayer->getColor())
      {
        activeField = field;
        std::cout << field->getActiveFigur()->getName() + " selected\n";
      }
      else
        std::cout << "figur has wrong color\n";
    }
    else
      std::cout << "no figur on field " << Tool::coordToString(coord) << "\n";
  }
  else
    std::cout << "invalid field " << Tool::coordToString(coord) << "\n";
}

void Engine::selectTargetField(Coord coord)
{
  FieldPtr targetField = getField(coord);
  if (targetField && tryMove(activeField, targetField))
  {
    switchPlayer();
    activeField = nullptr;
  }
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
    std::cout << "figur changed to " << targetField->getActiveFigur()->getName() + "\n";
  else
    std::cout << "no figur on field";
}

bool Engine::tryMove(FieldPtr origField, FieldPtr targetField)
{
  bool result = false;

  FigurPtr activeFigur = origField->getActiveFigur();
  if (activeFigur)
  {
    FigurPtr targetFigur = targetField->getActiveFigur();
    if (targetFigur)
    {
      if (targetFigur->getColor() == activePlayer->getColor())
      {
        changeField(targetField);
      }
      else if (targetFigur->isInvincible())
      {
        std::cout << "can't capture " + targetFigur->getName() + "\n";
      }
      else
      {
        if (tryCaptureFigur(origField, targetField))
        {
          if (!(result = checkCheck()))
            moveBack(origField, targetField);
        }
      }
    }
    else
    {
      if (tryMoveFigur(origField, targetField))
      {
        if (!(result = checkCheck()))
          moveBack(origField, targetField);
      }
    }
  }
  else
    std::cout << "no figur on field\n";
    
  return result;
}

void Engine::moveFigur(FieldPtr origField, FieldPtr targetField)
{
  FigurPtr activeFigur = origField->getActiveFigur();

  tempCapturedFigure = targetField->getActiveFigur();
  tempMoved          = activeFigur->hasMoved();

  origField->setActiveFigur(nullptr);
  targetField->setActiveFigur(activeFigur);
  activeFigur->setMoved(true);

  activePlayer->updateFigures();
  inactivePlayer->updateFigures();

  std::cout << activeFigur->getName() + " moved to " + targetField->getName() + "\n";
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
    std::cout << "Invalid move. Own King is checked\n";
    result = false;
  }

  if (inactiveCheck)
    std::cout << "check!\n";

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
      std::cout << targetFigur->getName() + " captured\n";

      inactivePlayer->addLostFigure(targetFigur);
      inactivePlayer->removeFigure(targetFigur);

      moveFigur(origField, targetField);

      result = true;
    }
  }
  else
    std::cout << "invalid move\n";

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
    std::cout << "invalid move\n";

  return result;
}
