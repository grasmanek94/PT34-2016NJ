#ifndef DEBUG
#define DEBUG
#endif

#ifndef DEBUG_MSG
#ifdef DEBUG
#include <iostream>
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif
#endif

//DEBUG_MSG("Hello" << ' ' << "World!" << 1);