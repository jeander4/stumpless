/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2023 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_ENTRY_H
#define __STUMPLESS_PRIVATE_ENTRY_H

#include <stdbool.h>
#include <stddef.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/facility.h>
#include <stumpless/severity.h>
#include "private/strbuilder.h"

/**
 * Frees entry cache
 *stumpless_entry
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources(entry cache)
 * that other threads can use.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to destroying
 * resources(entry cache) that might be used within a function.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to leaving memory in an undefined state.
 *
 */
void
entry_free_all( void );

/**
 * Gets the priority value from facility and severity parameters.
 * 
 * Priority value is calculated by left shifting the facility value by 3 
 * and adding it to the severity value which is according to the 
 * RFC 5424 Section 6.2.1. The shift operation is done prior to get_prival()
 * function with macros in "facility.h"
 *
 * **Thread Safety: MT-Safe[appropriate version]afe**
 * This function must be safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param facility Facility value. This should be a \c STUMPLESS_FACILITY value.
 * 
 * @param severity Severity value. This should be a \c STUMPLESS_SEVERITY value
 *
 * @return Priority value
 */
int
get_prival( enum stumpless_facility facility,
            enum stumpless_severity severity );

/**
 * Locks the mutex within the entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe **
 * This function is not safe to call from signal handlers due to the use of
 * mutexes that are not guarenteed to be async signal safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of lock that could be left in undefined state. 
 *
 * @param entry The entry to be locked.
 *
 */
void
lock_entry( const struct stumpless_entry *entry );

/**
 * Adds the element to the entry.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it doesn't use any synchronization 
 * or locking mechanisms while accessing shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * memory functions.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory functions that could leave the 
 * memory in undefined state.
 *
 * @param entry The entry to add the new element.
 *
 * @param element The new element to add to entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered NULL is returned.
 */
struct stumpless_entry *
locked_add_element( struct stumpless_entry *entry,
                    struct stumpless_element *element );

/**
 * Returns the element located at index within the entry.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it doesn't use any synchronization 
 * or locking mechanisms while accessing shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to use of
 * thread global structrues.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously 
 * canceled due to use of thread-global structure that may left in a
 * undefined state when cancelled.
 *
 * @param entry The entry to get the element from.
 *
 * @param index The index of element within the entry.
 *
 * @return The element if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_element *
locked_get_element_by_index( const struct stumpless_entry *entry,
                             size_t index );

/**
 * Retrieves an element by name from a Stumpless entry, ensuring thread safety.
 *
 * This function searches for an element within the given entry by its name. 
 * It locks each element during comparison to ensure thread safety. If the 
 * element with the specified name is found, it is returned.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it locks individual elements during the search process.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Unsafe to call from asynchronous signal handlers due to lock manipulation.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe in contexts of asynchronous cancellation, as it might involve lock manipulation.
 *
 * @since release 2.0.0
 *
 * @param entry The entry containing the elements to search through. Must not be NULL.
 * @param name The name of the element to find. Must be a NULL-terminated string.
 *
 * @return A pointer to the found element, or NULL if not found or an error occurs.
 */
struct stumpless_element *
locked_get_element_by_name( const struct stumpless_entry *entry,
                            const char *name );

/**
 * Creates a new Stumpless entry with specified parameters.
 *
 * This function allocates a new entry and initializes it with the provided facility,
 * severity, application name, message ID, and message. It uses internal cache
 * mechanisms for memory management and performs necessary validations and initializations.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it involves memory allocation and modification of
 * shared resources without synchronization.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Unsafe to call from asynchronous signal handlers due to memory allocation and
 * manipulation operations.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe in contexts of asynchronous cancellation, as it might leave allocated
 * resources in an inconsistent state.
 *
 * @since release v2.1.0
 *
 * @param facility The facility code for the entry.
 * @param severity The severity code for the entry.
 * @param app_name The application name for the entry. Can be NULL.
 * @param msgid The message ID for the entry. Can be NULL.
 * @param message The message for the entry. Can be NULL.
 * @param message_length The length of the message.
 *
 * @return A pointer to the newly created entry, or NULL if an error occurs.
 */
struct stumpless_entry *
new_entry( enum stumpless_facility facility,
           enum stumpless_severity severity,
           const char *app_name,
           const char *msgid,
           char *message,
           size_t message_length );

/**
 * Appends the application name from a Stumpless entry to a string builder.
 *
 * This function takes the application name from the provided Stumpless entry and
 * appends it to the specified string builder. It is designed for building strings
 * that include the application name of log entries.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it accesses shared data (the entry's application name)
 * without synchronization mechanisms.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Unsafe to call from asynchronous signal handlers due to memory manipulation
 * and accessing shared data structures.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe in contexts of asynchronous cancellation, as it might lead to inconsistent
 * states of shared data.
 *
 * @since release 1.0.0
 *
 * @param builder A pointer to the string builder to append the application name.
 *                Must not be NULL.
 * @param entry The Stumpless entry containing the application name.
 *              Must not be NULL.
 *
 * @return The string builder with the application name appended, or NULL if an error occurs.
 */
struct strbuilder *
strbuilder_append_app_name( struct strbuilder *builder,
                            const struct stumpless_entry *entry );

/**
 * Appends the hostname to the string builder.
 *
 * This function retrieves the system's current hostname using `config_gethostname`
 * and appends it to the provided string builder. If the hostname cannot be
 * obtained, a hyphen ('-') is appended instead.
 *
 * **Thread Safety: MT-Safe**
 * Assuming `config_gethostname` is thread-safe, this function is also thread-safe
 * as it operates on local buffer and the provided string builder without
 * sharing data with other threads.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from asynchronous signal handlers as it
 * involves system calls and memory manipulation.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe for use in contexts of asynchronous cancellation due to potential
 * system call interruption and memory state inconsistency.
 *
 * @since release 1.0.0
 *
 * @param builder A pointer to the string builder to which the hostname is appended.
 *                Must not be NULL.
 *
 * @return The string builder with the hostname appended, or NULL if an error occurs.
 */
struct strbuilder *
strbuilder_append_hostname( struct strbuilder *builder );

/**
 * Appends the message ID from a Stumpless entry to a string builder.
 *
 * This function takes the message ID from the provided Stumpless entry and
 * appends it to the given string builder. It's designed for building strings
 * that include the message ID of log entries.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it accesses shared data (the entry's message ID)
 * without synchronization mechanisms.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Unsafe to call from asynchronous signal handlers due to memory manipulation
 * and accessing shared data structures.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe in contexts of asynchronous cancellation, as it might lead to inconsistent
 * states of shared data.
 *
 * @since release 1.0.0
 *
 * @param builder A pointer to the string builder to append the message ID.
 *                Must not be NULL.
 * @param entry The Stumpless entry containing the message ID.
 *              Must not be NULL.
 *
 * @return The string builder with the message ID appended, or NULL if an error occurs.
 */
struct strbuilder *
strbuilder_append_msgid( struct strbuilder *builder,
                         const struct stumpless_entry *entry );

/**
 * Appends the message from a Stumpless entry to a string builder.
 *
 * This function extracts the message from the provided Stumpless entry and
 * appends it to the specified string builder. It is useful for constructing
 * strings that include log messages.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it accesses shared data (the entry's message)
 * without synchronization mechanisms.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from asynchronous signal handlers as it
 * involves memory manipulation and access to shared data structures.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe for use in contexts where threads may be asynchronously cancelled,
 * as it could leave shared data in an inconsistent state.
 *
 * @since release 1.0.0
 *
 * @param builder A pointer to the string builder to which the entry's message is appended.
 *                Must not be NULL.
 * @param entry The Stumpless entry containing the message to be appended.
 *              Must not be NULL.
 *
 * @return The string builder with the message appended, or NULL if an error occurs.
 */
struct strbuilder *
strbuilder_append_message( struct strbuilder *builder,
                           const struct stumpless_entry *entry );

/**
 * Appends the process ID to the string builder.
 *
 * This function gets the current process ID using `config_getpid` and appends
 * it to the provided string builder object. It is useful for adding process
 * identification information to a string being constructed.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread-safe as it does not modify shared data and relies
 * on thread-safe underlying functions.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from asynchronous signal handlers as it
 * relies on functions that may not be async-signal-safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * The function is not safe in the context of asynchronous cancellation due to
 * potential resource cleanup issues.
 *
 * @since release v1.0.0
 *
 * @param builder A pointer to the string builder to which the process ID is appended.
 *                Must not be NULL.
 *
 * @return The string builder with the process ID appended, or NULL if an error occurs.
 */
struct strbuilder *
strbuilder_append_procid( struct strbuilder *builder );

/**
 * Adds the structured data of an entry to the given strbuilder, in the format
 * specified in RFC 5424.
 *
 * Assumes that the entry has already been locked.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it accesses the entry's element list
 * without any coordination.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * strbuilder functions which may allocate memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe.
 *
 * @param builder The strbuilder to append the characters to.
 *
 * @param entry The entry to extract the structured data from.
 *
 * @return The modified builder if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct strbuilder *
strbuilder_append_structured_data( struct strbuilder *builder,
                                   const struct stumpless_entry *entry );

/**
 * Destroys a Stumpless entry without performing any checks.
 *
 * This function deallocates resources associated with the given entry, including
 * unloading the entry and freeing its memory from the cache. It assumes the entry
 * is valid and does not perform any safety checks.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it modifies shared resources (the entry and
 * its associated data) without synchronization.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Not safe to call from signal handlers as it involves operations like memory
 * deallocation and mutex destruction.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * Not safe in the context of asynchronous cancellation due to potential resource
 * cleanup issues.
 *
 * @since release v1.5.0
 *
 * @param entry A pointer to the entry to be destroyed. Must not be NULL.
 */
void
unchecked_destroy_entry( const struct stumpless_entry *entry );

/**
 * Checks if the specified entry contains an element with the given name.
 *
 * **Thread Safety: MT-Safe race:entry race:name**
 * This function is thread-safe assuming that the 'entry' and 'name' arguments
 * are not modified concurrently by other threads. It relies on the immutability
 * of these parameters during execution to maintain thread safety.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from asynchronous signal handlers due to
 * potential manipulation of shared data structures.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe for contexts where threads might be asynchronously
 * cancelled, as it could leave shared data in an inconsistent state.
 *
 * @since release v1.6.0
 *
 * @param entry The entry to be checked for the element. Must not be NULL.
 * @param name The name of the element to look for. Must be a NULL-terminated string.
 *
 * @return Returns true if the element is found, false otherwise.
 */
bool
unchecked_entry_has_element( const struct stumpless_entry *entry,
                             const char *name );

/**
 * Loads an entry with the given parameters.
 *
 * **Thread Safety: MT-Safe race:app_name race:msgid race:message**
 * This function is thread safe, of course assuming that the string arguments
 * are not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap lock**
 * This function is not safe to call from signal handlers due to the possible
 * use of memory management functions to create parts of the new entry, as well
 * as the use of a mutex initialization routine.
 *
 * **Async Cancel Safety: AC-Unsafe heap lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions and a mutex
 * initialization routine.
 *
 * @since release v2.2.0
 *
 * @param entry The struct to load.
 *
 * @param facility The facility code of the entry. This should be a
 * \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the entry. This should be a
 * \c STUMPLESS_SEVERITY value.
 *
 * @param app_name The app_name of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The app name length is restricted
 * to be 48 characters or less.
 *
 * @param msgid The message id of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The string must be in the
 * ASCII printable range 33 <= character <= 126 as specified in RFC5424.
 *
 * @param message The message in the entry. This string will be owned by the
 * entry if (and only if) this call is successful.
 *
 * @param message_length The length of the message in bytes, without the NULL
 * terminator.
 *
 * @return The loaded entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
unchecked_load_entry( struct stumpless_entry *entry,
                      enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      char *message,
                      size_t message_length );

/**
 * Unloads the provided entry, without performing a NULL check.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param entry The entry to unload. Must not be NULL.
 */
void
unchecked_unload_entry( const struct stumpless_entry *entry );

/**
 * Note (to delete before merge) : i'm concern this comment is not 100% accurate,
 * i have some difficulties to understand the config_unlock_mutex macro
 * if it does something or not
 * (implement thread safety #136)
 * 
 * Unlocks the mutex of a given entry.
 * 
 * This function is used internally to ensure that the mutex of an entry
 * is properly unlocked after operations that required synchronization are
 * completed. It uses the config_unlock_mutex macro to perform the actual
 * unlocking.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread-safe as it directly manipulates the mutex
 * of the entry. The caller must ensure that this function is not called
 * concurrently with other functions that might be modifying the same entry.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from asynchronous signal handlers as it
 * involves lock manipulation which is not async-signal-safe.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed if a cancellation
 * request is received during execution.
 * 
 * @since release v2.0.0
 * 
 * @param entry The entry whose mutex is to be unlocked. The entry must not
 *              be NULL, and it must have a valid mutex initialized.
 */
void
unlock_entry( const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_ENTRY_H */