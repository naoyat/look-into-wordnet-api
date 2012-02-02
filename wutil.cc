// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#include "./wutil.h"

#include <ctype.h>

#include <string>
#include <vector>
#include <utility>

std::vector<std::pair<int, std::string> > tokenize(const char *text) {
  std::vector<std::pair<int, std::string> > tokens;

  const char *p = text, *w = NULL;
  while (true) {
    if (isalpha(*p)) {
      if (!w) w = p;
    } else {
      if (w) tokens.push_back(std::make_pair('w', std::string(w, p-w)));
      w = NULL;
      if (*p == 0) {
        break;
      } if (*p == ' ') {
        //
      } else {
        tokens.push_back(std::make_pair(*p, std::string(p, 1)));
      }
    }
    ++p;
  }

  return tokens;
}
