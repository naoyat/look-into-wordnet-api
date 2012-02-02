// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#include <stdlib.h>

#include "./wordnet_apitest.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    wordnet_apitest_usage();
  } else {
    int   test_id   = atoi(argv[1]);
    char *searchstr = argv[2];
    if (wordnet_apitest(searchstr, test_id) != 0) wordnet_apitest_usage();
  }
  return 0;
}
