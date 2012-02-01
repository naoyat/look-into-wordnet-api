// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#ifndef WORDNET_VERBOSE_H_
#define WORDNET_VERBOSE_H_

#include <stdint.h>
#include <wn.h>

#include <string>

char *say_binary(unsigned int val, int width, const char *chars = "01");

const char *choose_str(const char *verbose_str, const char *normal_str);
const char *human_ptr_type(int ptr_type);

std::string say_all_pointers(unsigned int flags);
std::string say_fn_begin(const char *fnname);
std::string say_fn_end(bool is_void_func = false);
std::string say_searchstr(const char *searchstr);
std::string say_pos_name(int pos);
std::string say_ptr_type(int ptr_type);
std::string say_sense_num(int sense_num);

std::string say_index(IndexPtr index);
std::string say_synset(SynsetPtr synset);

char *verbose_findtheinfo(char *searchstr,
                          int pos, int ptr_type, int sense_num);
SynsetPtr verbose_findtheinfo_ds(char *searchstr,
                                 int pos, int ptr_type, int sense_num);
unsigned int verbose_is_defined(char *searchstr, int pos);
unsigned int verbose_in_wn(char *searchstr, int pos);
IndexPtr verbose_index_lookup(char *searchstr, int pos);
IndexPtr verbose_parse_index(int32_t offset, int dabase, char *line);
IndexPtr verbose_getindex(char *searchstr, int pos);
SynsetPtr verbose_read_synset(int pos, int32_t synset_offset, char *searchstr);
SynsetPtr verbose_parse_synset(FILE *fp, int pos, char *searchstr);
void verbose_free_syns(SynsetPtr synptr);
void verbose_free_synset(SynsetPtr synptr);
void verbose_free_index(IndexPtr idx);
SynsetPtr verbose_traceptrs_ds(SynsetPtr synptr,
                               int ptr_type, int pos, int depth);
char* verbose_do_trace(SynsetPtr synptr, int ptr_type, int pos, int depth);

#endif  // WORDNET_VERBOSE_H_
