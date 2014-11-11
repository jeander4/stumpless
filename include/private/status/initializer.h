#ifndef __STUMPLESS_PRIVATE_STATUS_INITIALIZER_H
#define __STUMPLESS_PRIVATE_STATUS_INITIALIZER_H

#include "private/type.h"

Status *
InitializeConstructorFailureStatus
( void );

Status *
InitializeDictionaryFailureStatus
( void );

Status *
InitializeDuplicateStatus
( void );

Status *
InitializeEmptyArgumentStatus
( void );

Status *
InitializeEventFailureStatus
( void );

Status *
InitializeForkFailureStatus
( void );

Status *
InitializeIncompatibleProfileStatus
( void );

Status *
InitializeListFailureStatus
( void );

Status *
InitializeMalformedStructureStatus
( void );

Status *
InitializeMemoryAllocationFailureStatus
( void );

Status *
InitializePipeFailureStatus
( void );

Status *
InitializeStatusByName
( const char * );

Status *
InitializeStreamWriteFailureStatus
( void );

Status *
InitializeStringWriteFailureStatus
( void );

Status *
InitializeValueProfileNotFoundStatus
( void );

#endif
