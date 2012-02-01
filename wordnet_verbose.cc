// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#include "./wordnet_verbose.h"

#include <stdio.h>
#include <stdint.h>
#include <wn.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "./ansi_color.h"

using std::cout;
using std::endl;
using std::min;

int  g_choice = 1;  // 0 or 1
bool g_verbose = true;

// NOUN = 1, VERB = 2, ADJ = 3, ADV = 4,
// (ADJSAT = SATELLITE = 5), ALL_POS = 0 (for in_wn)
//
// PADJ = 1 (p), NPADJ = 2 (a), IPADJ = 3 (ip)

char *say_binary(unsigned int val, int width, const char *chars) {
  static char buf[33];

  char *p = buf+33;
  *(--p) = 0;

  for (int i = 0; i < min(32, width); ++i) {
    *(--p) = chars[(val & 1)];
    val >>= 1;
  }

  return p;
}

const char *choose_str(const char *normal_str, const char *verbose_str) {
  return g_choice ? verbose_str : normal_str;
}

const char *human_ptr_type(int ptr_type) {
  switch (ptr_type) {
    case ANTPTR:         // 1; Antonyms
      return choose_str("!", "antonyms");
    case HYPERPTR:       // 2 Hypernyms
      return choose_str("@", "hypernyms");
    case HYPOPTR:        // 3 Hyponyms
      return choose_str("~", "hyponyms");
    case ENTAILPTR:      // 4 Entailment
      return choose_str("*", "entailment");
    case SIMPTR:         // 5 Similar
      return choose_str("&", "similar");
    case ISMEMBERPTR:    // 6 Member meronym
      return choose_str("#m", "member-meronym");
    case ISSTUFFPTR:     // 7 Substance meronym
      return choose_str("#s", "substance-meronym");
    case ISPARTPTR:      // 8 Part meronym
      return choose_str("#p", "part-meronym");
    case HASMEMBERPTR:   // 9 Member holonym
      return choose_str("%m", "member-holonym");
    case HASSTUFFPTR:    // 10 Substance holonym
      return choose_str("%s", "substance-holonym");
    case HASPARTPTR:     // 11 Part holonym
      return choose_str("%p", "part-holonym");
    case MERONYM:        // 12 All meronyms
      return choose_str("%", "all-meronyms");
    case HOLONYM:        // 13 All holonyms
      return choose_str("#", "all-holonyms");
    case CAUSETO:        // 14 Cause
      return choose_str(">", "cause");
    case PPLPTR:         // 15 Participle of verb
      return choose_str("<", "participle-of-verb");
    case SEEALSOPTR:     // 16 Also see
      return choose_str("^", "also-see");
    case PERTPTR:        // 17 Pertains to noun or derived from adjective
      return choose_str("\\", "pertains-to-noun/derived-from-adj");
    case ATTRIBUTE:      // 18 Attribute
      return choose_str("=", "attribute");
    case VERBGROUP:      // 19 Verb group
      return choose_str("$", "verb-group");
    case DERIVATION:     // 20 Derivationally related from
      return choose_str("+", "derivationally-related-from");
    case CLASSIFICATION:  // 21 Domain of synset
      return choose_str(";", "domain-of-synset");
    case CLASS:           // 22 Member of this domain
      return choose_str("-", "member-of-this-domain");

    case SYNS:            // 23 Find synonyms
      return choose_str("-", "find-synonyms");
    case FREQ:            // 24 Polysemy
      return choose_str("-", "polysemy");
    case FRAMES:          // 25 Verb example sentences and generic frames
      return choose_str("-", "verb-example-sentences-and-generic-frames");
    case COORDS:          // 26 Noun coordinates
      return choose_str("-", "noun-coordinates");
    case RELATIVES:       // 27 Group related senses
      return choose_str("-", "group-related-senses");
    case HMERONYM:        // 28 Hierarchical meronym search
      return choose_str("-", "hierarchical-meronym-search");
    case HHOLONYM:        // 29 Hierarchical holonym search
      return choose_str("-", "hierarchical-holonym-search");
    case WNGREP:          // 30 Find keywords by substring
      return choose_str("-", "find-keywords-by-substring");
    case OVERVIEW:        // 31 Show all synsets for word
      return choose_str("-", "overview");

    case CLASSIF_CATEGORY:  // 32 Show domain topic
      return choose_str(";c", "CLASSIF_CATEGORY");
    case CLASSIF_USAGE:     // 33 Show domain usage
      return choose_str(";u", "CLASSIF_USAGE");
    case CLASSIF_REGIONAL:  // 34 Show domain regino
      return choose_str(";r", "CLASSIF_REGIONAL");
    case CLASS_CATEGORY:    // 35 Show domain terms for topic
      return choose_str("-c", "CLASS_CATEGORY");
    case CLASS_USAGE:       // 36 Show domain terms for usage
      return choose_str("-u", "CLASS_USAGE");
    case CLASS_REGIONAL:    // 37 Show domain terms for region
      return choose_str("-r", "CLASS_REGIONAL");
    case INSTANCE:          // 38 Instance of
      return choose_str("@i", "INSTANCE");
    case INSTANCES:         // 39 Show instances
      return choose_str("i", "INSTANCE");
    default:
      return "";
  }
}

std::string say_all_pointers(unsigned int flags) {
  std::stringstream ss;
  ss << "{ ";
  unsigned int mask = 1;
  bool first_one = true;
  for (int ptr_type = 0; ptr_type < 32; ++ptr_type) {
    if (flags & mask) {
      if (!first_one) ss << ", ";
      ss << human_ptr_type(ptr_type);
      first_one = false;
    }
    mask <<= 1;
  }
  ss << " }";
  return ss.str();
}

std::string say_fn_begin(const char *fnname) {
  std::stringstream ss;
  // ss << endl;
  // ss << ANSI_UNDERLINE_ON;
  // ss << ANSI_BOLD_ON << fnname << ANSI_BOLD_OFF;
  ss << fnname;
  ss << "(";
  return ss.str();
}

std::string say_fn_end(bool is_void_func) {
  std::stringstream ss;
  ss << ")";
  // ss << ANSI_UNDERLINE_OFF;
  if (is_void_func)
    ss << ";";
  else
    ss << " => ";
  return ss.str();
}

std::string say_searchstr(const char *searchstr) {
  std::stringstream ss;

  ss << "searchstr=" << ANSI_FGCOLOR_RED;
  ss << '"' << searchstr << '"';
  ss << ANSI_FGCOLOR_DEFAULT;
  return ss.str();
}

std::string say_pos_name(int pos) {
  const char *pos_name[5] = { "ALL_POS", "NOUN", "VERB", "ADJ", "ADV", };

  std::stringstream ss;
  ss << "pos=" << ANSI_FGCOLOR_RED;
  ss << pos_name[pos];
  ss << ANSI_FGCOLOR_DEFAULT;
  return ss.str();
}

std::string say_ptr_type(int ptr_type) {
  std::stringstream ss;
  ss << "ptr_type=" << ANSI_FGCOLOR_RED;
  ss << human_ptr_type(ptr_type);
  ss << ANSI_FGCOLOR_DEFAULT;
  return ss.str();
}

std::string say_sense_num(int sense_num) {
  std::stringstream ss;
  ss << "sense_num=" << ANSI_FGCOLOR_RED;
  if (sense_num == ALLSENSES)
    ss << "ALLSENSES";
  else
    ss << "#" << sense_num;
  ss << ANSI_FGCOLOR_DEFAULT;
  return ss.str();
}

std::string say_index(IndexPtr index) {
  std::stringstream ss;
  ss << "Index {" << endl;
  ss << "  byte offset of entry in index file : " << index->idxoffset << endl;
  ss << "  word string : \"" << index->wd << '"' << endl;
  ss << "  part of speech : " << index->pos << endl;
  ss << "  sense (collins) count : " << index->sense_cnt << endl;
  // ss << "  number of offsets : " << index->off_cnt << endl;
  ss << "  number senses that are tagged : " << index->tagged_cnt << endl;

  ss << "  offset of synsets containing word : { ";
  if (index->off_cnt > 0) {
    for (int i = 0; i < index->off_cnt; ++i) {
      if (i > 0) ss << ", ";
      ss << index->offset[i];
    }
  }
  ss << " }" << endl;

  ss << "  pointers used : { ";
  if (index->ptruse_cnt > 0) {
    // ss << "  number of pointers used : " << index->ptruse_cnt << endl;
    for (int i = 0; i < index->ptruse_cnt; ++i) {
      if (i > 0) ss << ", ";
      ss << index->ptruse[i];
    }
  }
  ss << " }" << endl;

  ss << "}";
  return ss.str();
}

std::string say_synset(SynsetPtr synset) {
  std::stringstream ss;
  ss << "Synset {" << endl;
  ss << "  current file position : " << synset->hereiam << endl;
  ss << "  type of ADJ synset : " << synset->sstype << endl;
  ss << "  file number that synset comes from : " << synset->fnum << endl;
  ss << "  part of speech : " << synset->pos << endl;

  if (synset->wcount > 0) {
    // ss << "  number of words in synset : " << synset->wcount << endl;
    ss << "  words in synset : {" << endl;
    for (int i = 0; i < synset->wcount; ++i) {
      ss << "    (" << 1+i << ") ";
      ss << synset->words[i];
      ss << endl;
    }
    ss << "  }" << endl;
  }

  ss << "  unique id in lexicographer file : "
     << *synset->lexid << endl;
  ss << "  sense number in wordnet : "
     << *synset->wnsns << endl;
  ss << "  which word in synset we're looking for : "
     << synset->whichword << endl;

  if (synset->ptrcount > 0) {
    // ss << "  number of pointers : " << synset->ptrcount << endl;
    ss << "  pointers : {" << endl;
    for (int i = 0; i < synset->ptrcount; ++i) {
      ss << "    (" << 1+i << ") ";
      ss << "type: " << synset->ptrtyp[i] << ", ";
      ss << "offset: " << synset->ptroff[i] << ", ";
      ss << "part of speech: " << synset->pos[i] << ", ";
      ss << "<to>field: " << synset->pto[i] << ", ";
      ss << "<from>field: " << synset->pfrm[i];
      ss << endl;
    }
    ss << "  }" << endl;
  }
  if (synset->fcount > 0) {
    // ss << "  number of verb frames : " << synset->fcount << endl;
    ss << "  verb frames : {" << endl;
    for (int i = 0; i < synset->fcount; ++i) {
      ss << "    (" << 1+i << ") ";
      ss << "frame number: " << synset->frmid[i] << ", ";
      ss << "frame <to>field: " << synset->frmto[i];
      ss << endl;
    }
    ss << "  }" << endl;
  }
  ss << "  synset gloss (definition) :" << endl;
  ss << "    " << synset->defn << endl;
  ss << "  unique synset key : " << synset->key << endl;
  // synset->nextss
  //  - struct ss* to next synset containing searchword
  // synset->nextform
  //  - struct ss* to list of synsets for alternate spelling of wordform
  ss << "  type of search performed : " << synset->searchtype << endl;
  // synset->ptrlist
  //  - struct ss* to synset list result of search
  if (strcmp(synset->pos, "s") == 0) {
    ss << "  [pos=\"s\"] cluster head word : " << synset->headword << endl;
  }
  ss << "  sense number of headword : " << synset->headsense << endl;
  ss << "}";
  if (synset->nextss) {
    ss << "," << endl;
    ss << say_synset(synset->nextss);
  }
  ss << endl;
  return ss.str();
}


// char* findtheinfo(char *searchstr,
//                   int pos,
//                   int ptr_type,
//                   int sense_num);
char *verbose_findtheinfo(char *searchstr,
                          int pos, int ptr_type, int sense_num) {
  cout << say_fn_begin("findtheinfo");
  cout << say_searchstr(searchstr) << ", ";
  cout << say_pos_name(pos) << ", ";
  cout << say_ptr_type(ptr_type) << ", ";
  cout << say_sense_num(sense_num);
  cout << say_fn_end();

  char *res = findtheinfo(searchstr, pos, ptr_type, sense_num);
  cout << ANSI_FGCOLOR_GREEN;
  if (g_verbose) {
    // res[0] seems to be '\n'
    cout << res;
  } else {
    cout << endl << "(..." << (res ? strlen(res) : 0) << " letters...)";
  }
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}


// SynsetPtr findtheinfo_ds(char *searchstr,
//                          int pos,
//                          int ptr_type,
//                          int sense_num);
SynsetPtr verbose_findtheinfo_ds(char *searchstr,
                                 int pos, int ptr_type, int sense_num) {
  cout << say_fn_begin("findtheinfo");
  cout << say_searchstr(searchstr) << ", ";
  cout << say_pos_name(pos) << ", ";
  cout << say_ptr_type(ptr_type) << ", ";
  cout << say_sense_num(sense_num);
  cout << say_fn_end();

  SynsetPtr synset = NULL;
  switch (ptr_type) {
    case SEEALSOPTR:
    case PERTPTR:
    case VERBGROUP:
    case FREQ:
    case FRAMES:
    case RELATIVES:
    case WNGREP:
    case OVERVIEW:
      cout << ANSI_FGCOLOR_GREEN;
      cout << "cannot do that";
      cout << ANSI_FGCOLOR_DEFAULT;
      cout << endl;
      break;
    default:
      synset = findtheinfo_ds(searchstr, pos, ptr_type, sense_num);
      // cout << ANSI_FGCOLOR_GREEN << res << ANSI_FGCOLOR_DEFAULT;
      // res[0] seems to be '\n'
      cout << endl;
      cout << ANSI_FGCOLOR_MAGENTA;
      cout << say_synset(synset);
      cout << ANSI_FGCOLOR_DEFAULT;
      break;
  }

  return synset;
}


// unsigned int is_defined(char *searchstr, int pos);
unsigned int verbose_is_defined(char *searchstr, int pos) {
  cout << say_fn_begin("is_defined");
  cout << say_searchstr(searchstr) << ", ";
  cout << say_pos_name(pos);
  cout << say_fn_end();

  unsigned int flags = is_defined(searchstr, pos);  // unsigned int
  cout << ANSI_FGCOLOR_BLUE << say_binary(flags, 32, ".o")
       << ANSI_FGCOLOR_DEFAULT << endl;
  cout << ANSI_FGCOLOR_GREEN << say_all_pointers(flags) << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return flags;
}


// unsigned int in_wn(char *searchstr, int pos);
unsigned int verbose_in_wn(char *searchstr, int pos) {
  cout << say_fn_begin("in_wn");
  cout << say_searchstr(searchstr) << ", ";
  cout << say_pos_name(pos);
  cout << say_fn_end();

  unsigned int res = in_wn(searchstr, pos);
  if (pos == ALL_POS) {
    cout << ANSI_FGCOLOR_BLUE
         << say_binary(res/2, 4, ".o") << ANSI_FGCOLOR_DEFAULT;
  } else {
    if (res)
      cout << ANSI_FGCOLOR_GREEN << "found" << ANSI_FGCOLOR_DEFAULT;
    else
      cout << ANSI_FGCOLOR_RED << "not found" << ANSI_FGCOLOR_DEFAULT;
  }
  cout << endl;

  return res;
}


// IndexPtr index_lookup(char *searchstr, int pos);
IndexPtr verbose_index_lookup(char *searchstr, int pos) {
  cout << say_fn_begin("index_lookup");
  cout << say_searchstr(searchstr) << ", ";
  cout << say_pos_name(pos);
  cout << say_fn_end();

  IndexPtr index = index_lookup(searchstr, pos);
  if (index) {
    cout << endl;
    cout << ANSI_FGCOLOR_CYAN;
    cout << say_index(index);
    cout << ANSI_FGCOLOR_DEFAULT;
    cout << endl;
  } else {
    cout << "(not found)" << endl;
  }

  return index;
}


// IndexPtr parse_index(long offset, int dabase, char *line);
IndexPtr verbose_parse_index(int32_t offset, int dabase, char *line) {
  cout << say_fn_begin("parse_index");
  cout << "offset=" << offset << ", ";
  cout << "dabase=" << dabase << ", ";
  cout << "line=" << line;
  cout << say_fn_end();

  cout << ANSI_FGCOLOR_GREEN;
  IndexPtr res = parse_index(offset, dabase, line);
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}


// IndexPtr getindex(char *searchstr, int pos);
IndexPtr verbose_getindex(char *searchstr, int pos) {
  cout << say_fn_begin("getindex");
  cout << say_searchstr(searchstr) << ", ";
  cout << say_pos_name(pos);
  cout << say_fn_end();

  cout << ANSI_FGCOLOR_GREEN;
  IndexPtr res = getindex(searchstr, pos);
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}


// SynsetPtr read_synset(int pos, long synset_offset, char *searchstr);
SynsetPtr verbose_read_synset(int pos, int32_t synset_offset, char *searchstr) {
  cout << say_fn_begin("read_synset");
  cout << say_pos_name(pos) << ", ";
  cout << "synset_offset=" << synset_offset << ", ";
  cout << say_searchstr(searchstr);
  cout << say_fn_end();

  cout << ANSI_FGCOLOR_GREEN;
  SynsetPtr res = read_synset(pos, synset_offset, searchstr);
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}


// SynsetPtr parse_synset(FILE *fp, int pos, char *searchstr);
SynsetPtr verbose_parse_synset(FILE *fp, int pos, char *searchstr) {
  cout << say_fn_begin("parse_synset");
  cout << "fp, ";
  cout << say_pos_name(pos) << ", ";
  cout << say_searchstr(searchstr);
  cout << say_fn_end();

  cout << ANSI_FGCOLOR_GREEN;
  SynsetPtr res = parse_synset(fp, pos, searchstr);
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}


// void free_syns(SynsetPtr synptr);
void verbose_free_syns(SynsetPtr synptr) {
  cout << say_fn_begin("free_syns");
  cout << "synptr";
  cout << say_fn_end(true);
  free_syns(synptr);
  cout << endl;
}


// void free_synset(SynsetPtr synptr);
void verbose_free_synset(SynsetPtr synptr) {
  cout << say_fn_begin("free_synset");
  cout << "synptr";
  cout << say_fn_end(true);
  free_synset(synptr);
  cout << endl;
}


// void free_index(IndexPtr idx);
void verbose_free_index(IndexPtr idx) {
  cout << say_fn_begin("free_index");
  cout << "index";
  cout << say_fn_end(true);
  free_index(idx);
  cout << endl;
}


// SynsetPtr traceptrs_ds(SynsetPtr synptr, int ptr_type, int pos, int depth);
SynsetPtr verbose_traceptrs_ds(SynsetPtr synptr,
                               int ptr_type, int pos, int depth) {
  cout << say_fn_begin("traceptrs_ds");
  cout << "synptr, ";
  cout << say_ptr_type(ptr_type) << ", ";
  cout << say_pos_name(pos) << ", ";
  cout << "depth=" << depth;
  cout << say_fn_end();

  cout << ANSI_FGCOLOR_GREEN;
  SynsetPtr res = traceptrs_ds(synptr, ptr_type, pos, depth);
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}


// char *do_trace(SynsetPtr synptr, int ptr_type, int pos, int depth);
char *verbose_do_trace(SynsetPtr synptr, int ptr_type, int pos, int depth) {
  cout << say_fn_begin("do_trace");
  cout << "synptr, ";
  cout << say_ptr_type(ptr_type) << ", ";
  cout << say_pos_name(pos) << ", ";
  cout << "depth=" << depth;
  cout << say_fn_end();

  cout << ANSI_FGCOLOR_GREEN;
  char *res = do_trace(synptr, ptr_type, pos, depth);
  cout << ANSI_FGCOLOR_DEFAULT;
  cout << endl;

  return res;
}
