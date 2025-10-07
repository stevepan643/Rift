#ifndef TEST_H
#define TEST_H

#ifdef MODULE_EXPORT
    #define MODULE_API __declspec(dllexport)
#else
    #define MODULE_API __declspec(dllimport)
#endif

// #define MODULE_API

MODULE_API void test_function();

#endif