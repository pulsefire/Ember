// Simple include guard
#ifndef EMBER_CORE
#define EMBER_CORE

// TODO: Add support for other C++ calling conventions apart from standard __cdecl.
//       Emporting symbols with extern "C".

// If building DLL, export data and functionality else import.
#ifdef BUILD_EMBER_DLL
    #define EMBER_API __declspec(dllexport)
#else
    #define EMBER_API __declspec(dllimport)
#endif

#endif
