#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "parseuint8.h"

bool basic_test() {
  printf("basic_test\n");
  for (uint i = 0; i < 256; i++) {
    std::string input = std::to_string(i);
    input.reserve(4);
    uint8_t expected = i;
    uint8_t result;
    parse_uint8_swar(input.data(), input.size(), &result);
    if (result != expected) {
      printf("swar FAILURE %d\n", i);
      return false;
    }
    parse_uint8_fastswar(input.data(), input.size(), &result);
    if (result != expected) {
      printf("swar2 FAILURE %d\n", i);
      return false;
    }
    parse_uint8_fromchars(input.data(), input.size(), &result);
    if (result != expected) {
      printf("fromchars FAILURE %d\n", i);
      return false;
    }
    parse_uint8_naive(input.data(), input.size(), &result);
    if (result != expected) {
      printf("naive FAILURE %d\n", i);
      return false;
    }
  }

  for (uint i = 256; i <= 1024; i++) {
    std::string input = std::to_string(i);
    input.reserve(4);
    int r;
    uint8_t result;
    r = parse_uint8_swar(input.data(), input.size(), &result);
    if (r) {
      printf("swar FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fastswar(input.data(), input.size(), &result);
    if (r) {
      printf("swar2 FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_fromchars(input.data(), input.size(), &result);
    if (r) {
      printf("fromchars FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_naive(input.data(), input.size(), &result);
    if (r) {
      printf("naive FAILURE %d\n", i);
      return false;
    }
  }
  printf("SUCCESS\n");
  return true;
}

int main() { return (basic_test()) ? EXIT_SUCCESS : EXIT_FAILURE; }