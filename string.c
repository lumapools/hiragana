/**
    @file string.h
    @author Benedek Hauer (github.com/lumapools)
*/

#include "map.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void release_string(String s) {
  free(s.str);
  s.str = NULL;
  s.size = 0;
}

void print_string(String s) {
  printf("%s\n", s.str);
}

String to_string(Substring substring) {
  String res = {NULL, 0};
  size_t new_size = substring.end-substring.start;
  res.str = calloc(new_size+1, sizeof(char));
  for(size_t i = substring.start; i < substring.end; i++) {
    res.str[i-substring.start] = substring.s.str[i];
  }
  res.str[new_size] = '\0';
  res.size = new_size;
  return res;
}

/*
 * Reads a string from stdin
 */
String read_string(void) {
  String new = {NULL, 0};
  char c;
  while((c = getc(stdin)) != '\n') {
    new.str = (new.size == 0) ? calloc(1, sizeof(char)) : realloc(new.str, (new.size+1) * sizeof(char));
    new.str[new.size] = c;
    new.size++;
  }
  new.str = realloc(new.str, (new.size+1) * sizeof(char));
  new.str[new.size] = '\0';
  return new;
}

Strings transform(String initial, Map* m) {
  String new = {NULL, 0};
  size_t token_idx = 0;
  size_t start = 0;
  size_t num_strings = 0;
  Strings result = {NULL, 0};
  while(initial.str[token_idx] != '\0') {
    Substring subst = {initial, start, token_idx};
    String sub_initial_str = to_string(subst);
    while(!contains(m, sub_initial_str.str) && token_idx < initial.size) {
      subst.start = start;
      subst.end = ++token_idx;
      release_string(sub_initial_str);
      sub_initial_str = to_string(subst);
    }
    char* got = get(m, sub_initial_str.str);
    if(got == NULL) {
      release_string(sub_initial_str);
      release_strings(result);
      return (Strings) {NULL, 0};
    }
    else {
      result.strings = (result.size == 0) ? malloc(sizeof(char*)) : realloc(result.strings, (result.size+1)*sizeof(char*));
      result.strings[result.size] = calloc(strlen(got)+1, sizeof(char));
      strcpy(result.strings[result.size], got);
      result.size++;
      release_string(sub_initial_str);
    }
    start = token_idx;
  }
  return result;
}


void release_strings(Strings s) {
  for(size_t i = 0; i < s.size; i++) {
    free(s.strings[i]);
    s.strings[i] = NULL;
  }
  free(s.strings);
  s.strings = NULL;
  s.size = 0;
}

void print_strings(Strings s) {
  for(size_t i = 0; i < s.size; i++) {
    printf("%s", s.strings[i]);
  }
  printf("\n");
}

