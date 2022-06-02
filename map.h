/**
    @file map.h 
    @author Benedek Hauer (github.com/lumapools)
*/

#pragma once
#include <stddef.h>

/** Struct representing a key-value pair
*/
typedef struct {
  char* key;
  char* value;
} kv;

/** Struct representing a map/dictionary
*/
typedef struct {
  kv* map;
  size_t size;
} Map;


/** Initializes and returns a Map
*/
Map map_init(void);

/** Adds a key->value pair to map m
    @param m - Map to add to
    @param key - key to add to m
    @param value - value corresponding to key
*/
void add(Map* m, const char* key, const char* value);

/** Adds all keys and values to the map, where keys[i] maps to values[i]
    @param m - map to add to
    @param keys - key to add to m
    @param values - values to add to m
    @param size - number of elements to add
*/
void add_all(Map* m, const char* keys[], const char** values, size_t size);

/** Frees the memory previously allocated for a Map
    @param m - Map to free
*/
void release_map(Map* m);

/* Displays the contents of a Map m
   @param m - map to print
*/
void print_map(Map* m);

/** Checks if map m contains key k
    @param m - Map to check
    @param k - key to check
*/
int contains(Map* m, char* k);

/** Recovers the value (char*) from map m given key k
    @param m - map to get from
    @param k - key whose value to get
    @return char* the retrieved value, or NULL if it does not exist
*/
char* get(Map* m, char* k);
