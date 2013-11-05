#include <stdlib.h>

#include "private/logger.h"
#include "private/type.h"

Status *
CheckLoggerStatus
( Logger * logger )
{
  // the invocating process will call this function to the check the
  // current status of a Logger, which will be the status of the last
  // logging attempt
  
  return NULL;
}

void
ListenForValues
( Logger * logger )
{
  // logging process calls this process, and returns when complete
  // a return will signify a fatal error which caused the logging to halt
  
  Value * value;
  Status * status;
  
  while( 1 ){
    value = ReceiveNextValue( logger );
    status = ProcessValue( logger, value );
  }
}

Status *
ProcessValue
( Logger * logger, Value * value )
{
  // this function actually logs the value
  
  // send to adapter
  // send to formatter
  // send to handler list
  
  return NULL;
}

Value *
ReceiveNextValue
( Logger * logger )
{
  // this function listens for values sent to the logging process
  // from the invocating process
  
  return NULL;
}

Status *
SendValue
( Logger * logger, Value * value )
{
  // multiprocessing will call send to other process
  // logging process will be listening with Listen function
  
  return ProcessValue( logger, value );
}
