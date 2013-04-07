#ifndef STUMPLESS_FORMATTED_OUTPUT_H
#define STUMPLESS_FORMATTED_OUTPUT_H

#include <types.h>

StumplessStatusCode
StumplessAppendFormattedOutputs( StumplessFormattedOutput *,
                                 StumplessFormattedOutput * );

StumplessStatusCode
StumplessAppendStringToFormattedOutput( StumplessFormattedOutput *,
                                        const char * );

StumplessStatusCode
StumplessAppendUnsignedIntToFormattedOutput( StumplessFormattedOutput *,
                                             unsigned );

StumplessStatusCode
StumplessFormattedOutputIntoString( char *, StumplessFormattedOutput * );

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * );

#endif
