//
// Created by vito on 10.11.20.
//

#ifndef INC_05_GUESS_NUMBER_SYMBOL_EXPORT_H
#define INC_05_GUESS_NUMBER_SYMBOL_EXPORT_H
#if defined(EXTERN_C)
#define MANGLING extern "C"
#else
#define MANGLING

#ifdef DOCDOCTEST_CONFIG_IMPLEMENTATION_IN_DLL
#define MANGLING DOCTEST_SYMBOL_IMPORT
#endif
#endif
#endif //INC_05_GUESS_NUMBER_SYMBOL_EXPORT_H
