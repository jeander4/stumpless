#ifndef STUMPLESS_PRIVATE_COMPARATOR_INITIALIZER_H
#define STUMPLESS_PRIVATE_COMPARATOR_INITIALIZER_H

#include "private/type.h"

Comparator *
InitializeComparatorByName
( const char * );

Comparator *
InitializeStringComparator
( void );

#endif
