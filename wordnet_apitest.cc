// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#include "./wordnet_apitest.h"
#include <stdio.h>
#include <wn.h>

#include <iostream>

using std::cout;
using std::endl;

#include "./wordnet_verbose.h"

void wordnet_apitest_usage() {
  printf("usage: wordnet_apitest <test-id> <searchstr>\n");
  printf("    test 1: findtheinfo()\n");
  printf("    test 2: findtheinfo_ds()\n");
  printf("    test 3: is_defined()\n");
  printf("    test 4: in_wn()\n");
  printf("    test 5: index_lookup()\n");
  printf("    test 6: parse_index()\n");
  printf("    test 7: getindex()\n");
  printf("    test 8: read_synset\n");
  printf("    test 9: parse_synset\n");
  printf("    test 10: free_syns\n");
  printf("    test 11: free_synset\n");
  printf("    test 12: free_index\n");
  printf("    test 13: traceptrs_ds\n");
  printf("    test 14: do_trace\n");
}

int wordnet_apitest(char *searchstr, int test_id) {
  int init_status = wninit();
  if (init_status != 0) {
    printf("ERROR: cannot open WordNet database.\n");
    return -1;
  }

  if (test_id <= 0 || searchstr == NULL) return -1;

  if (!in_wn(searchstr, ALL_POS)) {
    printf("ERROR: \"%s\" is not found in WordNet.\n", searchstr);
    return -1;
  }

  // cout << "testing WordNet(R) " << wnrelease << "..." << endl;
  switch (test_id) {
    case 1: wordnet_test_findtheinfo(searchstr); break;
    case 2: wordnet_test_findtheinfo_ds(searchstr); break;
    case 3: wordnet_test_is_defined(searchstr); break;
    case 4: wordnet_test_in_wn(searchstr); break;
    case 5: wordnet_test_index_lookup(searchstr); break;
    case 6: wordnet_test_parse_index(searchstr); break;
    case 7: wordnet_test_getindex(searchstr); break;
    case 8: wordnet_test_read_synset(searchstr); break;
    case 9: wordnet_test_parse_synset(searchstr); break;
    case 10: wordnet_test_free_syns(searchstr); break;
    case 11: wordnet_test_free_synset(searchstr); break;
    case 12: wordnet_test_free_index(searchstr); break;
    case 13: wordnet_test_traceptrs_ds(searchstr); break;
    case 14: wordnet_test_do_trace(searchstr); break;
    default: break;
  }

  return 0;
}

void wordnet_test_in_wn(char *searchstr) {
  verbose_in_wn(searchstr, ALL_POS);
  for (int pos = 1; pos <= 4; ++pos) verbose_in_wn(searchstr, pos);
}

void wordnet_test_is_defined(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      unsigned int flags = verbose_is_defined(searchstr, pos);
    }
  }
}

void wordnet_test_findtheinfo(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      unsigned int flags = is_defined(searchstr, pos), mask = 1;
      for (int ptr_type = 1; ptr_type <= 31; ++ptr_type) {
        int sense_num = ALLSENSES;
        if (flags & mask) {
          char *textbuf =
              verbose_findtheinfo(searchstr, pos, ptr_type, sense_num);
        }
        mask <<= 1;
      }
    }
  }
}

void wordnet_test_findtheinfo_ds(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      unsigned int flags = is_defined(searchstr, pos), mask = 1;
      for (int ptr_type = 1; ptr_type <= 31; ++ptr_type) {
        int sense_num = ALLSENSES;
        if (flags & mask) {
          SynsetPtr synset =
              verbose_findtheinfo_ds(searchstr, pos, ptr_type, sense_num);
          // if (synset) verbose_free_syns(synset);
        }
        mask <<= 1;
      }
    }
  }
}

void wordnet_test_index_lookup(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      IndexPtr index = verbose_index_lookup(searchstr, pos);
      if (index) free_index(index);
    }
  }
}

void wordnet_test_parse_index(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      // IndexPtr index = verbose_index_lookup(searchstr, pos);
      // if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_getindex(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      IndexPtr index = verbose_getindex(searchstr, pos);
      if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_read_synset(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      // IndexPtr index = verbose_index_lookup(searchstr, pos);
      // if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_parse_synset(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      // IndexPtr index = verbose_index_lookup(searchstr, pos);
      // if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_free_syns(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      unsigned int flags = is_defined(searchstr, pos), mask = 1;
      for (int ptr_type = 1; ptr_type <= 31; ++ptr_type) {
        int sense_num = ALLSENSES;
        if (flags & mask) {
          SynsetPtr synset =
              findtheinfo_ds(searchstr, pos, ptr_type, sense_num);
          if (synset) verbose_free_syns(synset);
        }
        mask <<= 1;
      }
    }
  }
}

void wordnet_test_free_synset(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      // IndexPtr index = verbose_index_lookup(searchstr, pos);
      // if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_free_index(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      IndexPtr index = index_lookup(searchstr, pos);
      if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_traceptrs_ds(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      // IndexPtr index = verbose_index_lookup(searchstr, pos);
      // if (index) verbose_free_index(index);
    }
  }
}

void wordnet_test_do_trace(char *searchstr) {
  for (int pos = 1; pos <= 4; ++pos) {
    if (in_wn(searchstr, pos)) {
      // IndexPtr index = verbose_index_lookup(searchstr, pos);
      // if (index) verbose_free_index(index);
    }
  }
}
