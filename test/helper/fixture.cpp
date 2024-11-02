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

#ifndef HAVE_WINDOWS_H
  #include <dirent.h>
#endif

#include <cstddef>
#include <fstream>
#include <string>
#include <stumpless.h>
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
load_corpus_folder( const char* name ) {
    char** test_strings = NULL;
    int fileIndex = 0;

#if defined(HAVE_WINDOWS_H)
    // Windows directory traversal
    char corpora_dir[MAX_PATH];
    snprintf( corpora_dir, sizeof( corpora_dir ), "%s\\%s\\*", FUZZ_CORPORA_DIR, name );

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile( corpora_dir, &findFileData );

    if ( hFind != INVALID_HANDLE_VALUE ) {
        do {
            if ( !( findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) ) {
                char filePath[MAX_PATH];
                snprintf( filePath, MAX_PATH, "%s\\%s\\%s", FUZZ_CORPORA_DIR, name, findFileData.cFileName );

                const char* test_string = load_corpus( filePath );
                if (test_string != NULL) {
                    test_strings = (char**) realloc( test_strings, sizeof(char*) * ( fileIndex + 1 ) ) ;
                    test_strings[fileIndex] = (char*) test_string;
                    ++fileIndex;
                }
            }
        } while ( FindNextFile( hFind, &findFileData ) != 0 );
        FindClose(hFind);
    }

#else
    // POSIX (macOS Unix/Linux) directory traversal
    char corpora_dir[PATH_MAX];
    snprintf( corpora_dir, sizeof( corpora_dir ), "%s/%s", FUZZ_CORPORA_DIR, name );

    DIR* dir = opendir( corpora_dir );
    dirent* ent;
    if (dir != NULL) {
        while ( ( ent = readdir(dir) ) != NULL ) {
            if ( ent->d_type == DT_REG ) {  // Only process regular files
                char filePath[1024];
                snprintf( filePath, sizeof(filePath), "%s/%s", corpora_dir, ent->d_name );

                const char* test_string = load_corpus( filePath );
                if ( test_string != NULL ) {
                    test_strings = (char**) realloc( test_strings, sizeof(char*) * ( fileIndex + 1 ) );
                    test_strings[fileIndex] = (char*) test_string;
                    ++fileIndex;
                }
            }
        }
        closedir( dir );
    }
#endif

    stumpless_test_data result;
    result.length = fileIndex;
    result.test_strings = test_strings;
    return result;
}
