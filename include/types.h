#ifndef STUMPLESS_TYPES_H
#define STUMPLESS_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum StumplessStatusCode {
  STUMPLESS_SUCCESS = EXIT_SUCCESS,
  STUMPLESS_FAILURE,
  STUMPLESS_EMPTY_ARGUMENT,
  STUMPLESS_FILE_FAILURE,
  STUMPLESS_FILE_CLOSE_FAILURE,
  STUMPLESS_FILE_OPEN_FAILURE,
  STUMPLESS_FILE_READ_FAILURE,
  STUMPLESS_FILE_WRITE_FAILURE,
  STUMPLESS_INCORRECT_FILE_SIGNATURE,
  STUMPLESS_MEMORY_ALLOCATION_FAILURE,
  STUMPLESS_PARSE_FAILURE,
  STUMPLESS_STRING_WRITE_FAILURE
} StumplessStatusCode;

typedef struct {
  char * true_description;
  char * false_description;
} StumplessBooleanFormat;

typedef struct {
  short value;
  StumplessBooleanFormat * format;
} StumplessBoolean;

typedef enum StumplessValueType {
  STUMPLESS_UNSIGNED_SHORT,
  STUMPLESS_UNSIGNED_SHORT_POINTER,
  STUMPLESS_SHORT,
  STUMPLESS_SHORT_POINTER,
  STUMPLESS_UNSIGNED_INT,
  STUMPLESS_UNSIGNED_INT_POINTER,
  STUMPLESS_INT,
  STUMPLESS_INT_POINTER,
  STUMPLESS_UNSIGNED_LONG,
  STUMPLESS_UNSIGNED_LONG_POINTER,
  STUMPLESS_LONG,
  STUMPLESS_LONG_POINTER,
  STUMPLESS_UNSIGNED_LONG_LONG,
  STUMPLESS_UNSIGNED_LONG_LONG_POINTER,
  STUMPLESS_LONG_LONG,
  STUMPLESS_LONG_LONG_POINTER,
  STUMPLESS_UNSIGNED_CHAR,
  STUMPLESS_UNSIGNED_CHAR_POINTER,
  STUMPLESS_CHAR,
  STUMPLESS_CHAR_POINTER,
  STUMPLESS_FLOAT,
  STUMPLESS_FLOAT_POINTER,
  STUMPLESS_DOUBLE,
  STUMPLESS_DOUBLE_POINTER,
  STUMPLESS_LONG_DOUBLE,
  STUMPLESS_LONG_DOUBLE_POINTER,
  STUMPLESS_BOOLEAN,
  STUMPLESS_STRING,
  STUMPLESS_VOID_POINTER
} StumplessValueType;

typedef union {
  unsigned short u_s;
  unsigned short * u_s_p;
  signed short s;
  signed short * s_p;
  unsigned int u_i;
  unsigned int * u_i_p;
  signed int i;
  signed int * i_p;
  unsigned long u_l;
  unsigned long * u_l_p;
  signed long l;
  signed long * l_p;
  unsigned long long u_l_l;
  unsigned long long * u_l_l_p;
  signed long long l_l;
  signed long long * l_l_p;
  unsigned char u_c;
  unsigned char * u_c_p;
  signed char c;
  signed char * c_p;
  float f;
  float * f_p;
  double d;
  double * d_p;
  long double l_d;
  long double * l_d_p;
  StumplessBoolean * boolean;
  void * v_p;
} StumplessValueData;

typedef struct {
  const char * format;
  StumplessValueType type;
  StumplessValueData * data;
  unsigned length;
} StumplessValue;

typedef struct value_node {
  StumplessValue * value;
  struct value_node * next;
} StumplessValueListNode;

typedef struct {
  StumplessValueListNode * first;
  StumplessValueListNode * last;
} StumplessValueList;

typedef struct {
  const char * name;
  StumplessValue * value;
} StumplessEventAttribute;

typedef struct {
  StumplessEventAttribute * event_attribute;
  StumplessValue * value;
} StumplessEntryAttribute;

typedef struct {
  unsigned value;
  const char * name;
} StumplessLevel;

typedef struct {
  const char * name;
  StumplessLevel * level;
  StumplessEventAttribute ** attributes;
  unsigned attribute_count;
} StumplessEvent;

typedef struct {
  const char * description;
  StumplessEvent * event;
  StumplessEntryAttribute ** entry_attributes;
} StumplessEntry;

typedef unsigned char StumplessByte;

typedef struct {
  StumplessByte * bytes;
  unsigned byte_count;
} StumplessByteList;

typedef enum StumplessOutputFormat {
  STUMPLESS_BINARY,
  STUMPLESS_CSV,
  STUMPLESS_JSON,
  STUMPLESS_TEXT,
  STUMPLESS_XML
} StumplessOutputFormat;

typedef union {
  StumplessByteList * bytes;
  StumplessValueList * values;
} StumplessFormattedPayload;

typedef struct {
  StumplessOutputFormat format;
  StumplessFormattedPayload * payload;
} StumplessFormattedOutput;

typedef enum StumplessOutputMode {
  STUMPLESS_FILE_MODE,
  STUMPLESS_HTTP_MODE,
  STUMPLESS_MYSQL_MODE,
  STUMPLESS_STRING_MODE,
  STUMPLESS_TCP_MODE
} StumplessOutputMode;

typedef enum StumplessSortingMethod {
  STUMPLESS_BUBBLE_SORT,
  STUMPLESS_CUSTOM_SORT,
  STUMPLESS_INSERTION_SORT,
  STUMPLESS_MERGE_SORT,
  STUMPLESS_QUICK_SORT,
  STUMPLESS_SHELL_SORT
} StumplessSortingMethod;

typedef enum StumplessHTTPMethod {
  STUMPLESS_DELETE,
  STUMPLESS_GET,
  STUMPLESS_POST,
  STUMPLESS_PUT
} StumplessHTTPMethod;

typedef struct {
  FILE * current_file;
} StumplessFileConfiguration;

typedef struct {
  StumplessHTTPMethod method;
} StumplessHTTPConfiguration;

typedef struct {
  unsigned short enable_multithreading;
} StumplessMultithreadingConfiguration;

typedef struct {
  StumplessSortingMethod entry_method;
  StumplessSortingMethod log_method;
  unsigned short ascending;
  // function for custom entry sorting
  // function for custom log sorting
} StumplessSortingConfiguration;

typedef struct {
  size_t buffer_size;
} StumplessStringConfiguration;

typedef struct {
  StumplessFileConfiguration * file;
  StumplessHTTPConfiguration * http;
  StumplessMultithreadingConfiguration * multithreading;
  StumplessSortingConfiguration * sorting;
  StumplessStringConfiguration * string;
} StumplessConfiguration;

#endif
