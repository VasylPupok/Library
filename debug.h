#pragma once

#ifdef DEBUG_ON
    #define DEBUG_LOG(expr) qDebug() << expr;
    #define DEBUG_EXPR(expr) expr;
    #ifndef _ADD_DEBUG_CONSOLE
        #define _ADD_DEBUG_CONSOLE
    #endif
#else
#define DEBUG_LOG(expr) void;
#define DEBUG_EXPR(expr) void;
#endif
