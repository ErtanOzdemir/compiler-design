#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TO() printf("TOKEN IS %c\n", token);

char code[3000];

int indx = 0;
char token = '\0';

int K();
void P();
void C();
void I();
void W();
void A();
void O();
void G();
void E();
void T();
void U();
void R();
void F();

// ANSI COLOR CODES
void red() {
  printf("\e[0;31m");
}


void green() {
  printf("\e[1;32m");
}

void reset () {
  printf("\033[0m");
}

void printErr(char *errMessage) {
    red();
    printf("ERROR: %s\n", errMessage);
    reset();
}

void removeWhitespace(char *text) {
    char *src = text;
    char *dst = text;
    
    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }

    *dst = '\0';
}

char getToken() {
    if(indx < strlen(code)){
        return code[indx++];
    } else {
        return '\0';
    }
}

int doesMatch(char token, const char chars[]) {
    
    for(int i = 0; i < strlen(chars); i++) {
        if(token == chars[i]) return 1;
    }

    return 0;
}

int K() {
    char letters[] ="abcdefghijklmnopqrstuvwxyz";

    if (strchr(letters, token) == NULL) {
     return 0;
    } else {
        token = getToken();
    }
    return 1;
}

void G() {
    K();
    token=getToken();
    if(token != ';') {
        printErr("Expression should follow ';'\n'");
    }
}

void R() {
    char numbers[] ="0123456789";

    if (strchr(numbers, token) == NULL) {
      printf("Wrong grouping expression\n");
    } else {
        token = getToken();
    }
}

void F() {
   if(token == '(') {
        E();
        token = getToken();

        if(token != ')') {
            printf("ERROR: Sentence should follow ')'\n");
            exit(1);
        }
   }else {
       int isKOkay= K();

       if(!isKOkay) {
            R();
       }   
   }
}

void U() {
   F();

   if(token == '^') {
    token = getToken();
     U();
   }
}

void T() {
    U();



    int f = 0;
    const char rules[] = {'*', '/', '%'};
    for(; doesMatch(token, rules); token = getToken()) {
        f = 1;
        token = getToken();
        U();
    }

    if(f && !(doesMatch(token, rules))) {
        indx -=  2;
        token = getToken();
    }
}

void E() {
    T();

    int f = 0;
    const char rules[] = {'+', '-'};
    for(; doesMatch(token, rules); token  = getToken()) {
        f = 1;
        token = getToken();
        T();
    }

       if(f && !(doesMatch(token, rules))) {
        indx =  indx - 2;
        token = getToken();
    }
}

void A() {

    K();
    if(token != '=') {
        printErr("Expression should follow '='");
        exit(1);
    } 

    token=getToken();

    E();

    if(token != ';') {
        printErr("Expression should end with ';'");
        exit(1);
    }

    token = getToken();
}

void O() {
    E();
    if(token != ';') printf("ERROR: Expression should follow ';'\n");
    token = getToken();
}

void C() {
    switch(token) {
        case '[':
            I();
            token = getToken();
            break;
        
        case '{':
            token = getToken();
            W();
            break;

        case '<':
            token = getToken();
            O();
            break;
        
        case '>':
            token = getToken();
            G();
            break;
        
        case '.':
            break;

        default:
            A();
            break;
    }
}

void W() {
    E();

    if(token != '?') printf("ERROR: Expression should follow '?' in while loop\n");

    token = getToken();

    C();

    int f = 0;
    for(; token != '}'; token = getToken()) {
        f = 1;
        C();

        if(token == '}') break;
    }


    if(token != '}') {
        printf("ERROR: While loop should end with '}' in\n");
    }

    token = getToken();

}

void I() {
    E();

    token = getToken();
    if(token != '?') printf("ERROR: Expression should follow '?' in IF clause\n");

    token = getToken();
    C();

    for(;token != ':' || token != ']'; token = getToken()) {
        C();
    }
    
    if(token == ']') return;

    if(token != ':') printf("ERROR: Sentence should follow ':' in IF clause\n");

    token = getToken();
    C();

    for(;token != ']'; token = getToken()) {
        C();
    }

    token = getToken();
    if(token == ']') return;
}

void P() {
    while(token != '.') {
        C();
    }

    if(token == '.') {
        green();
        printf("SUCCESS\n");
        reset();
        return;
    }
}


int main() {
 

    FILE *f = fopen("example.abe", "r");
    
    int c = getc(f);
    int i = 0;
    while (c != EOF) {
        code[i++] = c;
        c = getc(f);
    }

    removeWhitespace(code);

    token = getToken();

    P();

    return 0;
};
