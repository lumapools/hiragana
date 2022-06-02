/**
    @file string.h
    @author Benedek Hauer (github.com/lumapools)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "string.h"
#include "consts.h"

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
