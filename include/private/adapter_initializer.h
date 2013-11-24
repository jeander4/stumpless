#ifndef STUMPLESS_PRIVATE_ADAPTER_INITIALIZER_H
#define STUMPLESS_PRIVATE_ADAPTER_INITIALIZER_H

#include "private/type.h"

Status *
InitializeAdapterByName
( const char * );

Adapter *
InitializeContextAdapter
( void );

Adapter *
InitializeLevelAdapter
( void );

#endif
