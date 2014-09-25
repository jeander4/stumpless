#ifndef __STUMPLESS_PRIVATE_LOGGER_LOG_H
#define __STUMPLESS_PRIVATE_LOGGER_LOG_H

#include "private/type.h"

Status *
Log
( void * );

Status *
LogChar
( Logger *, char );

Status *
LogCharArray
( Logger *, const char *, unsigned);

Status *
LogDouble
( Logger *, double );

Status *
LogDoubleArray
( Logger *, const double *, unsigned );

Status *
LogFloat
( Logger *, float );

Status *
LogFloatArray
( Logger *, const float *, unsigned );

Status *
LogInt
( Logger *, int );

Status *
LogIntArray
( Logger *, const int *, unsigned );

Status *
LogLoggerStatus
( Logger * );

Status *
LogLong
( Logger *, long );

Status *
LogLongArray
( Logger *, const long *, unsigned );

Status *
LogLongDouble
( Logger *, long double );

Status *
LogLongDoubleArray
( Logger *, const long double *, unsigned );

Status *
LogLongLong
( Logger *, long long );

Status *
LogLongLongArray
( Logger *, const long long *, unsigned );

Status *
LogShort
( Logger *, short );

Status *
LogShortArray
( Logger *, const short *, unsigned );

Status *
LogSignedChar
( Logger *, signed char );

Status *
LogSignedCharArray
( Logger *, const signed char *, unsigned );

Status *
LogString
( Logger *, const char * );

Status *
LogUnsignedChar
( Logger *, unsigned char );

Status *
LogUnsignedCharArray
( Logger *, const unsigned char *, unsigned );

Status *
LogUnsignedInt
( Logger *, unsigned int );

Status *
LogUnsignedIntArray
( Logger *, const unsigned int *, unsigned );

Status *
LogUnsignedLong
( Logger *, unsigned long );

Status *
LogUnsignedLongArray
( Logger *, const unsigned long *, unsigned );

Status *
LogUnsignedLongLong
( Logger *, unsigned long long );

Status *
LogUnsignedLongLongArray
( Logger *, const unsigned long long *, unsigned );

Status *
LogUnsignedShort
( Logger *, unsigned short );

Status *
LogUnsignedShortArray
( Logger *, const unsigned short *, unsigned );

Status *
LogVoid
( Logger *, const void *, unsigned, const char * );

#endif
