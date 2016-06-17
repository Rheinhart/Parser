#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define LINE_BUF_SIZE (1024)

static Token st_look_ahead_token;
static int st_look_ahead_token_exists;

static void my_get_token(Token *token){

    if (st_look_ahead_token_exists) {
        *token = st_look_ahead_token;
        st_look_ahead_token_exists = 0;
    } else {
         get_token(token);
    }
}

static void unget_token(Token *token){
    st_look_ahead_token = *token;
    st_look_ahead_token_exists = 1;
}

double parse_expresssion(void);

static double parse_primary_expresssion(){
     Token token;
     my_get_token (&token);
     if(token.kind == NUMBER_TOKEN) {
         return token.value;
     }
     fprint(stderr, "syntax error.\n");
     exit(1);
     return 0.0;
}

static double parse_term(){
    double v1;
    double v2;

    v1 = parse_primary_expresssion();
    for(;;){
         my_get_token(&token);
         if (token.kind != MUL_OPERATOR_TOKEN && token.kind != DIV_OPERATOR_TOKEN){
            unget_token(&token);
            break;
         }
         v2 = parse_primary_expresssion();
         if(token.kind == MUL_OPERATOR_TOKEN) {
              v1 *= v2;
         } else if (token.kind == DIV_OPERATOR_TOKEN) {
            v1 /= v2;
         }
    }
    return v1;
}
