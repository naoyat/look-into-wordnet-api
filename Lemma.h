// Copyright 2012 naoya_t.  All Rights Reserved.
// Use of this source code is governed by a LGPL-style
// license that can be found in the COPYING file.

#ifndef LEMMA_H_
#define LEMMA_H_

#include <string>

class Lemma {
 public:
  explicit Lemma(const char *surface, const char *lemma, int pos);
  Lemma(const Lemma& eword);
  ~Lemma();

  std::string description();

 private:
  std::string surface_;
  std::string lemma_;
  int pos_;
};

inline std::ostream& operator<<(std::ostream &s, Lemma lemma) {
  return s << lemma.description();
}

#endif  // LEMMA_H_
