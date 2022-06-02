/**
    @file map.c
    @author Benedek Hauer (github.com/lumapools)
*/

#include "map.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Map map_init(void) {
  Map m = {NULL, 0};
  return m;
}

void add(Map* m, const char* key, const char* value) {
  size_t keyLength = strlen(key);
  size_t valueLength = strlen(value);
  m->map = (m->size == 0) ? malloc(sizeof(kv)) : realloc(m->map, (m->size+1) * sizeof(kv));
  m->map[m->size].key = calloc(keyLength+1, sizeof(char));
  strcpy(m->map[m->size].key, key);
  m->map[m->size].value = calloc(valueLength+1, sizeof(char));
  strcpy(m->map[m->size].value, value);
  m->size++;
}

void add_all(Map* m, const char* keys[], const char** values, size_t nb_elems) {
  for(size_t i = 0; i < nb_elems; i++) {
    add(m, keys[i], values[i]);
  }
}

void release_map(Map* m) {
  for(size_t i = 0; i < m->size; i++) {
    free(m->map[i].key);
    m->map[i].key = NULL;
    free(m->map[i].value);
    m->map[i].value = NULL;
  }
  free(m->map);
  m->map = NULL;
}

void print_map(Map* m) {
  printf("[");
  for(size_t i = 0; i < m->size; i++) {
    printf("%s -> ", m->map[i].key);
    printf("%s", m->map[i].value);
    if(i != m->size-1) {
      printf(", ");
    }
  }
  printf("]\n");
}

int contains(Map* m, char* k) {
  for(size_t i = 0; i < m->size; i++) {
    if(!strcmp(m->map[i].key, k)) {
      return 1;
    }
  }
  return 0;
}

char* get(Map* m, char* k) {
  for(size_t i = 0; i < m->size; i++) {
    if(!strcmp(m->map[i].key, k)) {
      return m->map[i].value;
    }
  }
  return NULL;
}

