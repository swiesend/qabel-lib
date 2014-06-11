/*
 * @file    qbl-base64.cpp
 * @brief   Main file encode strings (base64)
 * @author  Jan Schreiber <schreiber@praemandatum.de>
 *
 * This software is licenced under the Qabel Public Licence
 * (QaPL): https://qabel.de/qapl.txt
 */

#include "qbl-base64.h"

QblBase64::QblBase64(){}

QblBase64::~QblBase64(){}

std::string QblBase64::FromBase64(std::vector<char>& binary) {
  std::string result(binary.size() + 1, '\0');

  // requires c++11: contiguous string storage
  int rlength = b64_pton(&binary[0], reinterpret_cast<u_char *>(&result[0]), result.size());

  if(rlength < 0) {
    throw std::invalid_argument("Argument is not base64-encoded.");
  }

  assert(rlength < result.size());

  result.resize(rlength);
  return result;
}

std::vector<char> QblBase64::ToBase64(const std::string &str) {
  // use integer division properties: (n + 2) / 3 is n / 3 if n is divisible by 3,
  // n / 3 + 1 otherwise. That times four is the place needed for the base64 representation,
  // and then there's the null terminator b64_ntop insists on adding.
  std::vector<char> result(((str.size() + 2) / 3) * 4 + 1);

  int rlength = b64_ntop((const u_char *)str.data(), str.length(), &result[0], result.size());

  assert(rlength >= 0 && rlength < result.size());
  result.resize(rlength);

  return result;
}
