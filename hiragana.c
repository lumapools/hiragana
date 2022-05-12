#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIRAGANA_COUNT 139
#define MAX_STRING_SIZE 1000
#define HIRAGANA_SIZE (3*sizeof(char))

typedef struct {
  char* key;
  char* value;
} kv;

typedef struct {
  kv* map;
  size_t size;
} Map;

Map map_init(void) {
  Map m = {NULL, 0};
  return m;
}

typedef struct {
  char* str;
  size_t size;
} String;

typedef struct {
  String s;
  size_t start; //inclusive
  size_t end; // exclusive
} Substring;

typedef struct {
  char** strings;
  size_t size;
} Strings;

void release_strings(Strings strs);

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

void release_string(String s) {
  free(s.str);
  s.str = NULL;
  s.size = 0;
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

int contains(Map* m, String key) {
  for(size_t i = 0; i < m->size; i++) {
    if(!strcmp(m->map[i].key, key.str)) {
      return 1;
    }
  }
  return 0;
}

char* get(Map* m, String key) {
  for(size_t i = 0; i < m->size; i++) {
    if(!strcmp(m->map[i].key, key.str)) {
      return m->map[i].value;
    }
  }
  return NULL;
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
    while(!contains(m, sub_initial_str) && token_idx < initial.size) {
      subst.start = start;
      subst.end = ++token_idx;
      release_string(sub_initial_str);
      sub_initial_str = to_string(subst);
    }
    char* got = get(m, sub_initial_str);
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

int main(void) {
  Map m = map_init();
  const char* keys[HIRAGANA_COUNT] = {
	  "a",  "i",  "u",  "e",  "o" , 
	  "ka", "ki", "ku", "ke", "ko",
	  "kka", "kki", "kku", "kke", "kko",
	  "ga", "gi", "gu", "ge", "go", 
	  "gga", "ggi", "ggu", "gge", "ggo", 
	  "sa", "shi", "su", "se", "so",
	  "ja", "ji", "ju", "je", "jo",
          "jja", "jji", "jju", "jje", "jjo",
	  "ssa", "sshi", "ssu", "sse", "sso",
	  "za", "zu", "ze", "zo",
	  "zza", "zzu", "zze", "zzo",
	  "ta", "chi", "tsu", "te", "to", 
	  "tta", "cchi", "ttsu", "tte", "tto",
	  "da", "di", "du", "de", "do",
	  "dda", "ddi", "ddu", "dde", "ddo",
	  "na", "ni", "nu", "ne", "no",
	  "ha", "hi", "fu", "he", "ho",
	  "hha", "hhi", "ffu", "hhe", "hho",
	  "ba", "bi", "bu", "be", "bo",
	  "bba", "bbi", "bbu", "bbe", "bbo",
	  "pa", "pi", "pu", "pe", "po",
	  "ppa", "ppi", "ppu", "ppe", "ppo",
	  "ma", "mi", "mu", "me", "mo", 
	  "mma", "mmi", "mmu", "mme", "mmo",
	  "ya", "yu", "yo", 
	  "yya", "yyu", "yyo",
	  "ra", "ri", "ru", "re", "ro", 
	  "rra", "rri", "rru", "rre", "rro",
	  "wa", "wo", 
	  "wwa", "wwo",
	  "nn"};
  const char* values[HIRAGANA_COUNT] = {
	  "あ", "い", "う", "え", "お",
	  "か", "き", "く", "け", "こ",
	  "っか", "っき", "っく", "っけ", "っこ", 
	  "が", "ぎ", "ぐ", "げ", "ご",
	  "っが", "っぎ", "っぐ", "っげ", "っご",
	  "さ", "し", "す", "せ", "そ",
	  "じゃ", "じ", "じゅ", "じぇ", "じょ", 
	  "っじゃ", "っじ", "っじゅ", "っじぇ", "っじょ", 
	  "っさ", "っし", "っす", "っせ", "っそ",
	  "ざ", "ず", "ぜ", "ぞ",
	  "っざ", "っず", "っぜ", "っぞ",
	  "た", "ち", "つ", "て", "と",
	  "った", "っち", "っつ", "って", "っと", 
	  "だ", "ぢ", "づ", "で", "ど",
	  "っだ", "っぢ", "っづ", "っで", "っど",
	  "な", "に", "ぬ", "ね", "の",
	  "は", "ひ", "ふ", "へ", "ほ",
	  "っは", "っひ", "っふ", "っへ", "っほ",
	  "ば", "び", "ぶ", "べ", "ぼ",
	  "っば", "っび", "っぶ"," っべ", "っぼ",
	  "ぱ", "ぴ", "ぷ", "ぺ", "ぽ",
	  "っぱ", "っぴ", "っぷ", "っぺ", "っぽ",
	  "ま", "み", "む", "め", "も",
	  "っま", "っみ", "っむ", "っめ", "っも", 
	  "や", "ゆ", "よ",
	  "っや", "っゆ", "っよ", 
	  "ら", "り", "る", "れ", "ろ",
	  "っら", "っり", "っる", "っれ", "っろ",
	  "わ","を",
	  "っわ", "っを",
	  "ん"};
  add_all(&m, keys, values, HIRAGANA_COUNT);
  printf("Enter a string: ");
  String new = read_string();
  Strings result = transform(new, &m);
  if(result.size != 0) {
    print_strings(result);
    release_strings(result);
  }
  else {
    fprintf(stderr, "ERROR: Invalid input\n");
  }
  release_string(new);
  release_map(&m);
  return 0;
}
