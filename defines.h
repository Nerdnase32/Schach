
#ifndef DEFINES_H
#define DEFINES_H

#define EXIT_SUCESS 0
#define EXIT_FAIL   1

#define TYPE_LOG  "LOG"
#define TYPE_QUIT "QUIT"
#define TYPE_EXIT "EXIT"

#define OPT_ONLY_MOVE "-m"

typedef unsigned int uint;

enum class Argument { ONLY_MOVED, UNKNOWN };
enum class Type   { LOG, EXIT, COORD, UNKNOWN };
enum class Color  { WHITE, BLACK, UNKNOWN };

#endif // !DEFINES_H