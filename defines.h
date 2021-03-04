
#ifndef DEFINES_H
#define DEFINES_H

#define EXIT_SUCESS 0
#define EXIT_FAIL   1

#define TYPE_INIT L"INIT"
#define TYPE_QUIT L"QUIT"
#define TYPE_EXIT L"EXIT"

#define OPT_ONLY_MOVE L"-m"

typedef std::wstring WSTRING;

enum class Argument { ONLY_MOVED, UNKNOWN };
enum class Type     { INIT, EXIT, COORD, UNKNOWN };
enum class Color    { WHITE, BLACK, UNKNOWN };

#endif // !DEFINES_H