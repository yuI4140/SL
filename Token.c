#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Token {
    char* value;
    int type;
} Token;

Token* createToken(char* value, int type) {
    Token* token = (Token*) malloc(sizeof(Token));
    token->value = value;
    token->type = type;
    return token;
}
void tokenCopy(Token *dest, const Token *src) {
    if (src == NULL || dest == NULL) {
        return;
    }
    dest->type = src->type;
    dest->start = src->start;
    dest->end = src->end;
    if (src->str != NULL) {
        dest->str = strdup(src->str);
    }
}

void tokenFree(Token *token) {
    if (token == NULL) {
        return;
    }
    free(token->str);
    token->str = NULL;
}

int tokenCompare(const Token *t1, const Token *t2) {
    if (t1 == NULL || t2 == NULL) {
        return -1;
    }
    if (t1->type != t2->type) {
        return t1->type - t2->type;
    }
    if (t1->str == NULL && t2->str == NULL) {
        return 0;
    }
    if (t1->str == NULL) {
        return -1;
    }
    if (t2->str == NULL) {
        return 1;
    }
    return strcmp(t1->str, t2->str);
}

void tokenPrint(const Token *token) {
    if (token == NULL) {
        return;
    }
    printf("Token type: %d\n", token->type);
    printf("Start: %d\n", token->start);
    printf("End: %d\n", token->end);
    if (token->str != NULL) {
        printf("String: %s\n", token->str);
    }
}
void freeToken(Token* token) {
    free(token->value);
    free(token);
}
int tokenLength(const Token *token) {
    if (token == NULL) {
        return 0;
    }
    if (token->str == NULL) {
        return 0;
    }
    return strlen(token->str);
}

int tokenToInt(const Token *token) {
    if (token == NULL || token->str == NULL) {
        return 0;
    }
    return atoi(token->str);
}

double tokenToDouble(const Token *token) {
    if (token == NULL || token->str == NULL) {
        return 0.0;
    }
    return atof(token->str);
}

bool tokenIsAlpha(const Token *token) {
    if (token == NULL || token->str == NULL) {
        return false;
    }
    int len = tokenLength(token);
    for (int i = 0; i < len; i++) {
        if (!isalpha(token->str[i])) {
            return false;
        }
    }
    return true;
}

bool tokenIsNumeric(const Token *token) {
    if (token == NULL || token->str == NULL) {
        return false;
    }
    int len = tokenLength(token);
    for (int i = 0; i < len; i++) {
        if (!isdigit(token->str[i])) {
            return false;
        }
    }
    return true;
}
void tokenReverse(Token *token) {
    if (token == NULL || token->str == NULL) {
        return;
    }
    int len = strlen(token->str);
    for (int i = 0; i < len / 2; i++) {
        char temp = token->str[i];
        token->str[i] = token->str[len - i - 1];
        token->str[len - i - 1] = temp;
    }
}

bool tokenIsPalindrome(const Token *token) {
    if (token == NULL || token->str == NULL) {
        return false;
    }
    int len = strlen(token->str);
    for (int i = 0; i < len / 2; i++) {
        if (token->str[i] != token->str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

void tokenToUpper(Token *token) {
    if (token == NULL || token->str == NULL) {
        return;
    }
    int len = strlen(token->str);
    for (int i = 0; i < len; i++) {
        token->str[i] = toupper(token->str[i]);
    }
}

void tokenToLower(Token *token) {
    if (token == NULL || token->str == NULL) {
        return;
    }
    int len = strlen(token->str);
    for (int i = 0; i < len; i++) {
        token->str[i] = tolower(token->str[i]);
    }
}

bool tokenStartsWith(const Token *token, const char *prefix) {
    if (token == NULL || token->str == NULL || prefix == NULL) {
        return false;
    }
    int prefixLen = strlen(prefix);
    if (strlen(token->str) < prefixLen) {
        return false;
    }
    return strncmp(token->str, prefix, prefixLen) == 0;
}

bool tokenEndsWith(const Token *token, const char *suffix) {
    if (token == NULL || token->str == NULL || suffix == NULL) {
        return false;
    }
    int suffixLen = strlen(suffix);
    int tokenLen = strlen(token->str);
    if (tokenLen < suffixLen) {
        return false;
    }
    return strncmp(token->str + tokenLen - suffixLen, suffix, suffixLen) == 0;
}
