#ifndef __STUMPLESS_PRIVATE_ADAPTER_INITIALIZER_H
#define __STUMPLESS_PRIVATE_ADAPTER_INITIALIZER_H

#include "private/type.h"

Exception *
InitializeAdapterByName
( const char * );

Adapter *
InitializeContextAdapter
( void );

Adapter *
InitializeLevelAdapter
( void );

#endif
