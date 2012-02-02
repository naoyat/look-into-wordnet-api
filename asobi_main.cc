// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#include <stdio.h>
#include <wn.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>

#include "./ansi_color.h"
#include "./wutil.h"
#include "./Lemma.h"

int lookup(char *searchstr) {
  strtolower(searchstr);

  std::vector<Lemma> lemmata;

  for (int pos = 1; pos <= 4; ++pos) {
    char *ms = morphstr(searchstr, pos);
    if (ms) {
      printf(" morphstr(pos=%s): %s\n", partnames[pos], ms);
      Lemma lemma(searchstr, ms, pos);
      lemmata.push_back(lemma);
    }
    // char *mw = morphword(searchstr, pos);
    // if (mw) printf(" morphword(pos=%s): %s\n", partnames[pos], mw);
  }

  for (int i = 0; i < lemmata.size(); ++i) {
    std::cout << lemmata[i] << std::endl;
  }

  int poss = in_wn(searchstr, ALL_POS);
  if (poss) {
    printf(" (%s%s%s%s )",
           (poss & (1<<NOUN)) ? " n" : "",
           (poss & (1<<VERB)) ? " v" : "",
           (poss & (1<<ADJ)) ? " a" : "",
           (poss & (1<<ADV)) ? " adv" : "");
    return __builtin_popcount(poss);
  } else {
    return 0;
  }
}

void sub(const char *text) {
  using namespace std;

  printf(":: %s\n", text);
  // テキストをスペースで区切って vector<string> に格納
  vector<pair<int, string> > words = tokenize(text);
  for (int i = 0; i < words.size(); ++i) {
    int type = words[i].first;
    char *token = const_cast<char*>(words[i].second.c_str());
    printf("%2d) <%c> " ANSI_BOLD_ON "%s" ANSI_BOLD_OFF, 1+i, type, token);
    if (type == 'w') lookup(token);
    printf("\n");
  }
}


int main(int argc, char **argv) {
  using namespace std;

  int wninit_status = wninit();
  if (wninit_status != 0) {
    printf("Cannot open WordNet database.\n");
    return 0;
  }
  int morphinit_status = morphinit();
  if (morphinit_status != 0) {
    printf("Cannot open WordNet database.\n");
    return 0;
  }

  if (argc == 1) {
    // なんか適当な英文。（これはアインシュタインだけど）
    // sub("Anyone who has never made a mistake has never tried anything new.");
    sub("A good medicine tastes bitter.");
  } else {
    stringstream ss;
    for (int i = 1; i < argc; ++i) {
      if (i > 1) ss << " ";
      ss << argv[i];
    }
    sub(ss.str().c_str());
  }
  return 0;
}
