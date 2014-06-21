#ifndef __STUMPLESS_LOGGER_H
#define __STUMPLESS_LOGGER_H

#include <stumpless/type.h>

Status *
AppendAdapterToLogger
( Logger *, Adapter * );

Status *
AppendFormatterToLogger
( Logger *, Formatter * );

Status *
AppendHandlerToLogger
( Logger *, Handler * );

Status *
CheckLoggerStatus
( Logger * );

void
ListenForValues
( Logger * );

Status *
ProcessValue
( Logger *, Value * );

Value *
ReceiveNextValue
( Logger * );

Status *
SendLoggerStatus
( Logger * );

Status *
SendValue
( Logger *, Value * );

#endif
