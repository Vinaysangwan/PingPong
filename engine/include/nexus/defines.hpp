#pragma once

#ifdef NX_STATIC
  #define NX_API

#else
  #ifdef _WIN32
    #ifdef NX_ENGINE
      #define NX_API __declspec(dllexport)
    #else
      #define NX_API __declspec(dllimport)
    #endif // NX_ENGINE

  #else
    #ifdef NX_ENGINE
      #define NX_API __attribute__((visibility("default")))
    #else
      #define NX_API
    #endif  // NX_ENGINE

  #endif  // _WIN32
#endif // NX_STATIC
