/*
 * Copyright 2018, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <regex>
#include <stdlib.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"
#include "test/function/utf8.hpp"

void TestRFC5424Compliance(const char *syslog_msg){
  std::cmatch matches;
  std::regex rfcRegex(RFC_5424_REGEX_STRING);
  ASSERT_TRUE(std::regex_match(syslog_msg, matches, rfcRegex));

  int prival = std::stoi(matches[1]);
  EXPECT_GE(prival, RFC_5424_PRIVAL_MIN);
  EXPECT_LE(prival, RFC_5424_PRIVAL_MAX);
 
  EXPECT_EQ(matches[2], "1");

  int year = std::stoi(matches[RFC_5424_DATE_FULLYEAR_MATCH_INDEX]);
  EXPECT_GE(year, 0);

  int month = std::stoi(matches[RFC_5424_DATE_MONTH_MATCH_INDEX]);
  int day = std::stoi(matches[RFC_5424_DATE_MDAY_MATCH_INDEX]);
  EXPECT_GE(day, 1);
  switch(month){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      EXPECT_LE(day, 31);
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      EXPECT_LE(day, 30);
      break;
    case 2:
      if(month % 4 == 0){
        EXPECT_LE(day, 29);
      } else {
        EXPECT_LE(day, 28);
      }
      break;
    default:
      ADD_FAILURE() << "DATE-MONTH was not a value between 1 and 12";
  }

  TestRFC5424StructuredData(matches.str(RFC_5424_STRUCTURED_DATA_MATCH_INDEX).c_str());
 
  std::string msg_string = matches.str(RFC_5424_MSG_MATCH_INDEX);
  char *msg = (char *)malloc(msg_string.length() + 1);
  strcpy(msg, msg_string.c_str());
  if(msg[0] == '\xef' && msg[1] == '\xbb' && msg[2] == '\xbf'){
    TestUTF8Compliance(msg);
  }
}

void TestRFC5424StructuredData(const char *structured_data){
  enum sd_state {
    INIT_STATE,
    SD_ELEMENT_EMPTY,
    SD_ELEMENT_BEGIN,
    SD_ID_NAME,
    SD_ID_ENTERPRISE_NUMBER,
    SD_PARAM_NAME,
    SD_PARAM_VALUE_BEGIN,
    SD_PARAM_VALUE,
    SD_PARAM_VALUE_END
  };
  enum sd_state current_state = SD_ELEMENT_BEGIN;
  bool backslash_preceded = false;

  for(const char *c=structured_data; *c != '\0'; c++){
    switch(current_state){
      case INIT_STATE:
        if(*c == '-'){
          current_state = SD_ELEMENT_EMPTY;
        } else if( *c == '['){
          current_state = SD_ID_NAME;
        }
        break;

      case SD_ELEMENT_EMPTY:
        FAIL() << "an empty STRUCTURED-DATA had more than a '-' character";
        break;

      case SD_ELEMENT_BEGIN:
        ASSERT_EQ(*c, '[');
        current_state = SD_ID_NAME;
        break;

      // todo validate with RFC
      case SD_ID_NAME:
        if(*c == '@'){
          current_state = SD_ID_ENTERPRISE_NUMBER;
          break;
        }
        if(*c == ']'){
          current_state = SD_ELEMENT_BEGIN;
          break;
        }
        if(*c == ' '){
          current_state = SD_PARAM_NAME;
          break;
        }
        ASSERT_GT(*c, 32);
        ASSERT_LT(*c, 127);
        ASSERT_NE(*c, '=');
        ASSERT_NE(*c, '"');
        break;

      // todo validate with registry
      case SD_ID_ENTERPRISE_NUMBER:
        if(*c == ']'){
          current_state = SD_ELEMENT_BEGIN;
          break;
        }
        if(*c == ' '){
          current_state = SD_PARAM_NAME;
          break;
        }
        ASSERT_GE(*c, '0');
        ASSERT_LE(*c, '9');
        break;

      case SD_PARAM_NAME:
        if(*c == '='){
          current_state = SD_PARAM_VALUE_BEGIN;
          break;
        }
        ASSERT_GT(*c, 32);
        ASSERT_LT(*c, 127);
        ASSERT_NE(*c, ' ');
        ASSERT_NE(*c, ']');
        ASSERT_NE(*c, '"');
        break;

      case SD_PARAM_VALUE_BEGIN:
        ASSERT_EQ(*c, '"');
        current_state = SD_PARAM_VALUE;
        break;

      // todo need to do UTF-8 validation on this string
      case SD_PARAM_VALUE:
        if(backslash_preceded){
          backslash_preceded = false;
          break;
        } else {
          if(*c == '"'){
            current_state = SD_PARAM_VALUE_END;
            break;
          }
          ASSERT_NE(*c, '=');
          ASSERT_NE(*c, ']');
        }

        if(*c == '\\'){
          backslash_preceded = true;
        }
        break;

      case SD_PARAM_VALUE_END:
        if(*c == ' '){
          current_state = SD_PARAM_NAME;
          break;
        }
        if(*c == ']'){
          current_state = SD_ELEMENT_BEGIN;
          break;
        }
        FAIL() << "invalid ending of PARAM-VALUE";
        break;

      default:
        FAIL() << "invalid state reached during SD-ELEMENT parsing";
    }
  }
}
