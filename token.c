#define DEF
#define NORMAL
#include ".h/core.h"
#include "Err.c"
typedef struct {
  i8 set[2];
  size_t sz;
} Token;
// Initialize a Token with a given character set
vd initTkn(Token *token, i8 set[2]) {
  strncpy(token->set, set, 2);
  token->sz = strlen(set);
}
// Get the character at the specified index of the Token's set
char get_Tkn(const Token *token, size_t index) {
  if (index < token->sz) {
    return token->set[index];
  }
  return '\0'; // Return null character if index is out of bounds
}
// Insert a character into the Token's set at the specified index
void insert_Tkn(Token *token, char character, size_t index) {
  if (index < 2) {
    token->set[index] = character;
    if (index >= token->sz) {
      token->sz = index + 1;
    }
  }
}
// Compare two Tokens for equality
i32 tknCmp(const Token *token1, const Token *token2) {
  if (token1->sz != token2->sz) {
    return 0; // Size mismatch, tokens are not equal
  }
  return strncmp(token1->set, token2->set, token1->sz) == 0;
}
// Push back a character to the Token's set
vd pushBackTkn(Token *token, char character) {
  if (token->sz < 2) {
    token->set[token->sz] = character;
    token->sz++;
  }
}
