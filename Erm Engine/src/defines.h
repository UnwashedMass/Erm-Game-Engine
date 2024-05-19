#pragma once




typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef int b32;
typedef char b8;

#define STATIC_ASSERT static_assert



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define EPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define EPLATFORM_LINUX 1
#elif defined(__unix__)
// Catch anything not caught by the above.
#define EPLATFORM_UNIX 1
#elif __APPLE__
// Apple platforms
#define EPLATFORM_APPLE 1
#include <TargetConditionals.h>
#else
#error "Unknown platform!"
#endif


#ifdef GEXPORT
// Exports
#ifdef _MSC_VER
#define EAPI __declspec(dllexport)
#else
#define EAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define EAPI __declspec(dllimport)
#else
#define EAPI
#endif
#endif