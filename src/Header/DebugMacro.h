#ifndef __DEBUGMACRO
#define __DEBUGMACRO

#define DEBUG 1

#if DEBUG > 0
    #define GIVE_ACCESS_DEBUG() friend class Debug;
#else
    #define GIVE_ACCESS_DEBUG() 
#endif


#endif

