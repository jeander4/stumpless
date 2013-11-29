#ifndef STUMPLESS_PRIVATE_LOGGER_H
#define STUMPLESS_PRIVATE_LOGGER_H

#include "private/type.h"

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
SendStatus
( Logger * );

Status *
SendValue
( Logger *, Value * );

#endif
