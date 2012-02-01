// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#include <stdio.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> split_cstr(const char *text, int delimiter) {
  vector<string> tokens;

  const char *p = text, *q;
  while (q = strchr(p, delimiter)) {
    tokens.push_back(string(p, q-p));
    p = q+1;
  }
  tokens.push_back(string(p));

  return tokens;
}


void sub(const char *text) {
  // テキストをスペースで区切って vector<string> に格納
  vector<string> words = split_cstr(text, ' ');
  for (int i=0; i<words.size(); ++i) {
    cout << i << " " << words[i] << endl;
  }
}



int main() {
  // なんか適当な英文。（これはアインシュタインだけど）
  sub("Anyone who has never made a mistake has never tried anything new.");
  return 0;
}
