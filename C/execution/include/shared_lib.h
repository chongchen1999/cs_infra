#ifndef SHARED_LIB_H
#define SHARED_LIB_H

/**
 * When creating a shared library, we need to specify the symbol visibility
 * This macro helps with exporting symbols properly on different platforms
 */
#if defined(_WIN32) || defined(__CYGWIN__)
  #define LIB_EXPORT __declspec(dllexport)
  #define LIB_IMPORT __declspec(dllimport)
#else
  #define LIB_EXPORT __attribute__((visibility("default")))
  #define LIB_IMPORT
#endif

#ifdef BUILDING_SHARED_LIB
  #define SHARED_API LIB_EXPORT
#else
  #define SHARED_API LIB_IMPORT
#endif

/**
 * Performs a simple operation and returns the result
 * This function is implemented in a shared library
 */
SHARED_API int shared_operation(int value);

/**
 * Returns information about the shared library
 */
SHARED_API const char* shared_lib_info(void);

#endif /* SHARED_LIB_H */