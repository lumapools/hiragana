/**
    @file string.h
    @author Benedek Hauer (github.com/lumapools)
*/

#pragma once
#include <stddef.h>
#include "map.h"

/** Struct representing a string where we keep track of its size
*/
typedef struct {
  char* str;
  size_t size;
} String;

/** Struct representing a Substring of a String
*/
typedef struct {
  String s;
  size_t start; //inclusive
  size_t end; // exclusive
} Substring;

/** Struct representing a non-distinct set of Strings
*/
typedef struct {
  char** strings;
  size_t size;
} Strings;

/** Frees the memory previously allocated for a String
    @param str - the string to release
*/
void release_string(String str);

/** Prints a String
    @param str - the string to print
*/
void print_string(String str);

/** Transforms a substring into a String
    @param substr - the substring to transform
    @return String - the string substr corresponds to
*/
String to_string(Substring);


/** Reads a string from stdin
    @return String - the string read from stdin
*/
String read_string(void);

/** Transforms a string into its corresponding representation (String) according to a map
    @param str - the string to transform
    @param m - the tranformation Map
    @return Strings - the transformed representation of a String in the form of a Strings
*/
Strings transform(String str, Map* m);

/** Frees the memory previously allocated for a Strings variable
    @param strs - the strings to release
*/
void release_strings(Strings);

/** Prints all the strings of a Strings variable
    @param strs - the strings to print
*/
void print_strings(Strings strs);
