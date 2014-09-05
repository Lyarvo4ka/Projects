#ifndef LIBSTRUCTSTORAGE_GLOBAL_H
#define LIBSTRUCTSTORAGE_GLOBAL_H

#ifdef LIBSTRUCTSTORAGE_EXPORTS
#define LIBSTRUCTSTORAGE_API __declspec(dllexport)
#else
#define LIBSTRUCTSTORAGE_API __declspec(dllimport)
#endif

#endif