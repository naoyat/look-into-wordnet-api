
#include "./Lemma.h"

#include <wn.h>

#include <string>
#include <sstream>

Lemma::Lemma(const char *surface, const char *lemma, int pos) :
    surface_(surface), lemma_(lemma), pos_(pos)
{
}

Lemma::Lemma(const Lemma& lemma) {
  this->surface_ = lemma.surface_;
  this->lemma_   = lemma.lemma_;
  this->pos_     = lemma.pos_;
}

Lemma::~Lemma() {
}

std::string Lemma::description() {
  std::stringstream ss;
  ss << surface_ << " (" << lemma_ << ", " << partnames[pos_] << ")";
  return ss.str();
}
