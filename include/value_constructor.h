#ifndef STUMPLESS_VALUE_CONSTRUCTOR_H
#define STUMPLESS_VALUE_CONSTRUCTOR_H

#include <type.h>

StumplessValue *
StumplessValueFromBoolean( const StumplessBoolean * );

StumplessValue *
StumplessValueFromChar( char );

StumplessValue *
StumplessValueFromDouble( double );

StumplessValue *
StumplessValueFromFloat( float );

StumplessValue *
StumplessValueFromInt( int );

StumplessValue *
StumplessValueFromLong( long );

StumplessValue *
StumplessValueFromLongDouble( long double );

StumplessValue *
StumplessValueFromLongLong( long long );

StumplessValue *
StumplessValueFromShort( short );

StumplessValue *
StumplessValueFromSignedChar( signed char );

StumplessValue *
StumplessValueFromString( const char * );

StumplessValue *
StumplessValueFromUnsignedChar( unsigned char );

StumplessValue *
StumplessValueFromUnsignedInt( unsigned );

StumplessValue *
StumplessValueFromUnsignedLong( unsigned long );

StumplessValue *
StumplessValueFromUnsignedLongLong( unsigned long long);

StumplessValue *
StumplessValueFromUnsignedShort( unsigned short );

#endif
