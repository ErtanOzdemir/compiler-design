#include <stdio.h>
#include <string.h>


// char text[] = ""

// char* getToken() {
//     return strtok(text, " ");
// }

int doesMatch(char token, const char chars[]) {
    
    for(int i = 0; i < strlen(chars); i++) {
        if(token == chars[i]) return 1;
    }

    return 0;
}


int main() {
    const char rules[] = {'$', '1', '.'};
    printf("isEqual %d\n", doesMatch('a', rules));

    return 0;
}


// void P() {
//     if(token == '.') {
//         printf("end of the program");
//         return;
//     }
    
//     C();
// }

// void C() {
//     switch(token) {
//         case '[':
//             I();
//             token = getToken();
//             break;
        
//         case '{':
//             token = getToken();
//             W();
//             break;

//         case '<':
//             token = getToken();
//             O();
//             break;
        
//         case '>':
//             token = getToken();
//             G();
//             break;

//         default:
//             token = getToken();
//             A();
//             break;

//     }
// }

// void I() {
//     E();

//     token = getToken();
//     if(token != '?') printf("ERROR: Expression should follow '?' in IF clause");

//     token = getToken();
//     C();

//     for(;token != ':' || token != ']'; token = getToken()) {
//         C();
//     }
    
//     if(token == ']') return;

//     if(token != ':') printf("ERROR: Sentence should follow ':' in IF clause");

//     token = getToken();
//     C();

//     for(;token != ']'; token = getToken()) {
//         C();
//     }

//     token = getToken();
//     if(token == ']') return;
// }

// void E() {
//     T();

//     for(token = getToken(); token == '+' || token == '-'; token = getToken()) {
//         T();
//     }
// }

// void T() {
    // U();
    // token == '*' || token == '/' || token == '%'
    // const char rules[] = {'*', '/', '%'};
    // for(token = getToken(); doesMatch(token, rules); token = getToken()) {
    //     U();
    // }
// }