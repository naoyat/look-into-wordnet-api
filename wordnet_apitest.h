// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#ifndef WORDNET_APITEST_H_
#define WORDNET_APITEST_H_

int wordnet_apitest(char *searchstr, int test_id);
void wordnet_apitest_usage();

void wordnet_test_findtheinfo(char *searchstr);
void wordnet_test_findtheinfo_ds(char *searchstr);
void wordnet_test_is_defined(char *searchstr);
void wordnet_test_in_wn(char *searchstr);
void wordnet_test_index_lookup(char *searchstr);
void wordnet_test_parse_index(char *searchstr);
void wordnet_test_getindex(char *searchstr);
void wordnet_test_read_synset(char *searchstr);
void wordnet_test_parse_synset(char *searchstr);
void wordnet_test_free_syns(char *searchstr);
void wordnet_test_free_synset(char *searchstr);
void wordnet_test_free_index(char *searchstr);
void wordnet_test_traceptrs_ds(char *searchstr);
void wordnet_test_do_trace(char *searchstr);

#endif  // WORDNET_APITEST_H_
