#include <cstdio>
#include <cstdlib>
#include <string>
#include <array>

#include "parseuint8.h"

bool basic_test() {
  printf("basic_test\n");

  make_lut();

  for (uint i = 0; i < 256; i++) {
    std::string input = std::to_string(i);
    input.reserve(4);
    padded_string input_padded(input);

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
    parse_uint8_fastswar_bob(input.data(), input.size(), &result);
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
    parse_uint8_lut_padded(input_padded.buf.data(), input_padded.size, &result);
    if (result != expected) {
      printf("lut_padded FAILURE %d\n", i);
      return false;
    }
    parse_uint8_lut_masked(input.data(), input.size(), &result);
    if (result != expected) {
      printf("lut_masked FAILURE %d\n", i);
      return false;
    }
    parse_uint8_naive_md(input.data(), input.size(), &result);
    if (result != expected) {
      printf("naive FAILURE %d\n", i);
      return false;
    }
  }

  for (uint i = 256; i <= 1024; i++) {

    std::string input = std::to_string(i);
    input.reserve(4);
    padded_string input_padded(input);

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
    r = parse_uint8_fastswar_bob(input.data(), input.size(), &result);
    if (r) {
      printf("swarbob FAILURE %d\n", i);
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
    r = parse_uint8_naive_md(input.data(), input.size(), &result);
    if (r) {
      printf("naive FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_lut_padded(input_padded.buf.data(), input.size(), &result);
    if (r) {
      printf("lut_padded FAILURE %d\n", i);
      return false;
    }
    r = parse_uint8_lut_masked(input.data(), input.size(), &result);
    if (r) {
      printf("lut_masked FAILURE %d\n", i);
      return false;
    }
  }
  for (uint i = 0; i <= 0xffffff; i++) {
    int r1, r2;
    uint8_t result;
    r1 = parse_uint8_fastswar((const char*)&i, 1, &result);
    r2 = parse_uint8_naive((const char*)&i, 1, &result);
    if(r1 != r2) {
      printf("mismatch1 %d\n", i);
      return false;      
    }
    r1 = parse_uint8_fastswar((const char*)&i, 2, &result);
    r2 = parse_uint8_naive((const char*)&i, 2, &result);
    if(r1 != r2) {
      printf("mismatch2 %d\n", i);
      return false;      
    }
    r1 = parse_uint8_fastswar((const char*)&i, 3, &result);
    r2 = parse_uint8_naive((const char*)&i, 3, &result);
    if(r1 != r2) {
      printf("mismatch3 %d\n", i);
      return false;      
    }

    r1 = parse_uint8_fastswar_bob((const char*)&i, 1, &result);
    r2 = parse_uint8_naive((const char*)&i, 1, &result);
    if(r1 != r2) {
      printf("mismatch1 %d\n", i);
      return false;      
    }
    r1 = parse_uint8_fastswar_bob((const char*)&i, 2, &result);
    r2 = parse_uint8_naive((const char*)&i, 2, &result);
    if(r1 != r2) {
      printf("mismatch2 %d\n", i);
      return false;      
    }
    r1 = parse_uint8_fastswar_bob((const char*)&i, 3, &result);
    r2 = parse_uint8_naive((const char*)&i, 3, &result);
    if(r1 != r2) {
      printf("mismatch3 %d\n", i);
      return false;      
    }

    r1 = parse_uint8_naive_md((const char*)&i, 1, &result);
    r2 = parse_uint8_naive((const char*)&i, 1, &result);
    if(r1 != r2) {
      printf("parse_uint8_naive_md mismatch1 %d\n", i);
      return false;      
    }
    r1 = parse_uint8_naive_md((const char*)&i, 2, &result);
    r2 = parse_uint8_naive((const char*)&i, 2, &result);
    if(r1 != r2) {
      printf("parse_uint8_naive_md mismatch2 %d\n", i);
      return false;      
    }
    r1 = parse_uint8_naive_md((const char*)&i, 3, &result);
    r2 = parse_uint8_naive((const char*)&i, 3, &result);
    if(r1 != r2) {
      printf("parse_uint8_naive_md mismatch3 %d\n", i);
      return false;      
    }

    r1 = parse_uint8_lut_padded((const char*)&i, 1, &result);
    r2 = parse_uint8_naive((const char*)&i, 1, &result);
    if(r1 != r2) {
      printf("mismatch1 %d\n", i);
      // return false;      
    }
    r1 = parse_uint8_lut_padded((const char*)&i, 2, &result);
    r2 = parse_uint8_naive((const char*)&i, 2, &result);
    if(r1 != r2) {
      printf("mismatch2 %d\n", i);
      // return false;      
    }
    r1 = parse_uint8_lut_padded((const char*)&i, 3, &result);
    r2 = parse_uint8_naive((const char*)&i, 3, &result);
    if(r1 != r2) {
      printf("mismatch3 %d\n", i);
      // return false;      
    }

    r1 = parse_uint8_lut_masked((const char*)&i, 1, &result);
    r2 = parse_uint8_naive((const char*)&i, 1, &result);
    if(r1 != r2) {
      printf("mismatch1 %d\n", i);
      // return false;      
    }
    r1 = parse_uint8_lut_masked((const char*)&i, 2, &result);
    r2 = parse_uint8_naive((const char*)&i, 2, &result);
    if(r1 != r2) {
      printf("mismatch2 %d\n", i);
      // return false;      
    }
    r1 = parse_uint8_lut_masked((const char*)&i, 3, &result);
    r2 = parse_uint8_naive((const char*)&i, 3, &result);
    if(r1 != r2) {
      printf("mismatch3 %d\n", i);
      // return false;      
    }
  }

  printf("SUCCESS\n");
  return true;
}

int main() { return (basic_test()) ? EXIT_SUCCESS : EXIT_FAILURE; }
