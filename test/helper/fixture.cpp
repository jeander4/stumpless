// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2024 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstddef>
#include <fstream>
#include <string>
#include <stumpless.h>
#include <dirent.h>
#include "test/config.hpp"
#include "test/helper/fixture.hpp"

using namespace std;

struct stumpless_entry *
create_empty_entry( void ) {
  return stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                  STUMPLESS_SEVERITY_INFO,
                                  "fixture-app-name",
                                  "fixture-msgid",
                                  "fixture message" );
}

struct stumpless_entry *
create_entry( void ) {
  struct stumpless_entry *entry;

  entry = create_empty_entry(  );

  stumpless_add_new_element( entry, "fixture-element" );

  stumpless_add_new_param_to_entry( entry,
                                    "fixture-element",
                                    "fixture-param-1",
                                    "fixture-value-1" );

  stumpless_add_new_param_to_entry( entry,
                                    "fixture-element",
                                    "fixture-param-2",
                                    "fixture-value-2" );

  return entry;
}

struct stumpless_entry *
create_nil_entry( void ) {
  return stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                  STUMPLESS_SEVERITY_INFO,
                                  NULL,
                                  NULL,
                                  NULL );
}

const char *
load_corpus( const string& name ) {
  streamoff file_length;
  string corpora_dir ( FUZZ_CORPORA_DIR );
  ifstream corpus_file( corpora_dir + "/" + name, ifstream::binary );
  if( !corpus_file ) {
    return NULL;
  }

  corpus_file.seekg( 0, corpus_file.end );
  file_length = corpus_file.tellg(  );
  corpus_file.seekg( 0, corpus_file.beg );

  char *buffer = new char [file_length];
  corpus_file.read( buffer, file_length );
  if( !corpus_file ) {
    delete[] buffer;
    buffer = NULL;
  }

  corpus_file.close(  );

  return buffer;
}

stumpless_test_data
load_corpus_folder( const string& name){

  DIR *dir;
  struct dirent *ent;
  string corpora_dir ( FUZZ_CORPORA_DIR );
  int fileIndex = 0;

  char **test_strings;
  if((dir = opendir((corpora_dir + "/" + name).c_str())) != NULL){
    while((ent = readdir(dir)) != NULL){
      const char *test_string = load_corpus(name + "/" + ent->d_name);
      if(test_string != NULL){
        if(fileIndex > 0){
          test_strings = (char **) realloc(test_strings, sizeof(char *) * (fileIndex + 1));
        }
        else{
          test_strings = (char **) malloc(sizeof(char *));
        }
        test_strings[fileIndex] = (char *)test_string;
        ++fileIndex;
      }
    }
    closedir(dir);
  }
  return {fileIndex, test_strings};
}
