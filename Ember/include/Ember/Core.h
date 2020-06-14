// Simple include guard
#ifndef EMBER_CORE
#define EMBER_CORE

// TODO: Add support for other C++ calling conventions apart from standard __cdecl.
//       Emporting symbols with extern "C".

// If building DLL export data and functionality, else import.
#ifdef BUILD_EMBER_DLL
    #define EMBER_API __declspec(dllexport)
#else
    #define EMBER_API __declspec(dllimport)
#endif

// Enable Assertions.
#ifdef ER_ASSERTIONS_ENABLED
    #define ER_ASSERT(x, ...) { if(!(x)) { ER_ERR("Assertion Failed! ", __VA__ARGS); __debugbreak(); } }
    #define ER_CORE_ASSERT(x, ...) { if(!(x)) { ER_CORE_ERR("Assertion Failed! ", __VA_ARGS__); __debugbreak();}}
#else
    #define ER_ASSERT(x, ...)
    #define ER_CORE_ASSERT(x, ...)
#endif
 
#endif
