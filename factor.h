#pragma once


struct factors
{
  uint64_t     plarge[2];
  uint64_t     p[26];
  unsigned char e[26];
  unsigned char nfactors;
};

void factor (std::uint64_t t0, struct factors *factors);
