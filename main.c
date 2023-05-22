#include <stdio.h>
#include <string.h>

#include <string.h> 


int index = 0;

char text[] = "n = 0;
{ n - 2*5 ?
	< n;
	n = n + 1;
}
";
   

char* getToken() {
    char token = get()
    index++;
    return token
}

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


void P() {
    if(token == '.') {
        printf("end of the program\n");
        return;
    }
    
    C();
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

        default:
            token = getToken();
            A();
            break;

    }
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


void W () {
    E()
    token = getToken()
    if(token != "?") return printf("ERROR: Expression should follow '?' in while loop\n");

    C()
    for(; token != '}'; token = getToken()) {
        C();
    }

}



void A() {
    K()
    token=getToken()
    if(token != "=") {
        return printf("ERROR: Expression should follow '='\n");
    }
    token=getToken()
    E()
    token=getToken()
     if(token != ";") {
        return printf("ERROR: Expression should end with ';'\n");
    }
}

void O() {
    E()
    token=getToken()
    if(token != ";") return printf("ERROR: Expression should follow ';'\n");
}

void G() {
    K()
    token=getToken()
    if(token != ";") return printf("ERROR: Expression should follow ';'\n");
}

void E() {
    T();
    const char rules[] = {'+', '-'};
    for(token = getToken(); doesMatch(token, rules); token  = getToken()) {
        T();
    }
}

void T() {
    U();
    const char rules[] = {'*', '/', '%'};
    for(token = getToken(); doesMatch(token, rules); token = getToken()) {
        U();
    }
}

void U() {
    F();

    token = getToken();
   
   if(token == "^") {
    token = getToken();
     U();
   }

}


void F() {
   
   if(token == "(") {
        E();
        token = getToken();

        if(token != ")") {
            printf("ERROR: Sentence should follow ')'\n");
        }

   }else {
       int isKOkay= K();

       if(!isKOkay) {
            R();
       }
       
   }

  
}


int K() {

    char letters[] ="abcdefghijklmnopqrstuvwxyz"

    token = getToken();

    if (strchr(letters, token) == NULL) {
     return 0;
    }

    return 1;


}


void R() {

     char numbers[] ="0123456789"

    token = getToken();

    if (strchr(numbers, token) == NULL) {
      printf("Wrong grouping expression\n");
    }

}