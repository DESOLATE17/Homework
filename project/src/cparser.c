#include "cparser.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum {
    L_COLON,
    L_NR,
    L_ASSIGNMENT,
    L_SPACE,
    L_EMPTY,
    L_SEMICOLON,
    L_VALUE,
    L_NAME,
    L_COUNT,
    L_ERR
} lexem_t;

typedef enum {
    S_NAMEBEGIN,
    S_NAME,
    S_VALBEGIN,
    S_VALUE,
    S_NEWSTR,
    S_MOREHVALUE,
    S_HEND,
    S_COUNT,
    S_ERR
} state_t;

typedef bool (*action_t)(const char *s, const char *end, int* flag, char ** str);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static lexem_t get_lexem(const char *s, const char **end, lexem_t previous_lexem, state_t state);
static lexem_t get_complex_lex(const char *s, const char **end, lexem_t previous_lexem, state_t state);

void inf_out(char** str){
    if (str[0] != NULL) {
        printf("%s|", str[0]);
    }else {
        printf("|");
    }
    if (str[1] != NULL) {
        printf("%s|", str[1]);
    }else {
        printf("|");
    }
    if (str[2] != NULL) {
        printf("%s|", str[2]);
    } else {
        printf("|");
    }
}

bool check_special_characters(const char ** s) {
    if (**s == '\\') {
        char next = *(*s + 1);
        if (next == '"' || next == '\\' || next == '/' || next == 'b' || next == 'f' || next == 'n' ||
            next == 'r' || next == 't') {
            ++s;
        } 
        else {
            return false;
        }
    }
        return true;
}

bool on_value(const char *s, const char *end, int* flag, char ** str) {
    int count = 1;
    if (!flag || !str || !end || !s){
        return false;
    }
    if (*flag != -1 && *flag != 3)  {
        if (!str[*flag]){
        str[*flag] = strndup(s, end - s + 1);
        if (str[*flag] == NULL) {
            puts("Error");
            return false;
        }
        }
        else {
            char * tmp_str = malloc(strlen(str[*flag]) + end - s + 1);
            strcpy(tmp_str, str[*flag]); 
            tmp_str[strlen(str[*flag])] = ' ';
            char * tmp_copy = strndup(s, end - s + 1);
            strcat(tmp_str, tmp_copy);
            free(str[*flag]);
            str[*flag] = strndup(tmp_str, strlen(tmp_str) + 1);
            free(tmp_copy);
            free(tmp_str);
        }
    }
    if (*flag == 3) {
        if (*s == '\"') {++s;}
        if (*end == '\"') {
            count = 0;
            }
        //printf("\n%c\n", *end);
        str[3] = malloc(end - s + 3);
        memcpy(str[3] + 2, s, end - s + count); 
        // printf("\n%s\n", str[3]);
        str[3][0] = '-';
        str[3][1] = '-';
         //printf("\n%s\n", str[3]);
    }
    return true;
}
bool on_name(const char *s, const char *end, int* flag, char ** str) {
    if (!flag || !str || !end || !s){
        return false;
    }
    char *copy = strndup(s, end - s + 1);
    if (strncmp(copy, "From", sizeof("From") - 1) == 0) {
        *flag = 0;
    } else {
        if (strncmp(copy, "To", sizeof("To") - 1) == 0) {
            *flag = 1;
        } else {
            if (strncmp(copy, "Date", sizeof("Date") - 1) == 0) {
                *flag = 2;
            } else {
                if (strncmp(copy, "boundary", sizeof("boundary") - 1) == 0) {
                    *flag = 3;
                } else {
                    *flag = -1;
                }
            }
        }
    }
    free(copy);
    // printf("BEGIN:%c END: %c\n", *s, **end);
    return true;
}


static rule_t transitions[S_COUNT][L_COUNT] = {
//                     L_COLON                      L_NR                    L_ASSIGNMENT                L_SPACE                 L_EMPTY             L_SEMICOLON                 L_VALUE                 L_NAME
/* S_NAMEBEGIN */ {{ S_ERR, NULL},             { S_NAMEBEGIN, NULL },     { S_ERR, NULL },        { S_NAMEBEGIN, NULL },   { S_NAMEBEGIN, NULL }, { S_VALBEGIN, NULL },{ S_ERR, NULL },     { S_NAME, on_name }},
/* S_NAME */      {{ S_VALBEGIN, NULL},        { S_ERR, NULL },           { S_VALBEGIN, NULL },   { S_ERR, NULL },         { S_ERR, NULL },      { S_VALBEGIN, NULL },      { S_ERR, NULL },     { S_ERR, NULL }},
/* S_VALBEGIN */  {{ S_ERR, NULL },            { S_ERR, NULL },           { S_ERR, NULL },        { S_VALBEGIN, NULL },    { S_ERR, NULL },      { S_ERR, NULL },           { S_VALUE, on_value },      { S_ERR, NULL }},
/* S_VALUE */     {{ S_ERR, NULL },            { S_NEWSTR, NULL },        { S_ERR, NULL },        { S_ERR, NULL },         { S_ERR, NULL },      { S_NAMEBEGIN, NULL },     { S_ERR, NULL },     { S_ERR, NULL }},
/* S_NEWSTR */    {{ S_ERR, NULL },            { S_HEND, NULL },          { S_ERR, NULL },        { S_MOREHVALUE, NULL },  { S_NAMEBEGIN, NULL }, { S_ERR, NULL },          { S_ERR, NULL },     { S_ERR, NULL }},
/* S_MOREVALUE */ {{ S_ERR, NULL },            { S_ERR, NULL },           { S_ERR, NULL },        { S_MOREHVALUE, NULL },  { S_ERR, NULL },      { S_ERR, NULL },           { S_VALUE, on_value },{ S_ERR, NULL }},
/* S_HEND */      {{ S_ERR, NULL },            { S_ERR, NULL },           { S_ERR, NULL },        { S_ERR, NULL },         { S_ERR, NULL },      { S_ERR, NULL },           { S_ERR, NULL },     { S_ERR, NULL }},
};

static lexem_t get_complex_lex(const char *s, const char **end, lexem_t previous_lexem, state_t state) {
    if ((*s == '\n' && *(s + 1) == '\r') || (*s == '\r' && *(s + 1) == '\n')) {
          *end = s + 1;
        return L_NR;
    }
    if (*s == '\n' || *s == '\r') {
        *end = s;
        return L_NR;
    }   
    if (previous_lexem == L_NR) {
        // putc('\n', stdout);
        return L_EMPTY;
    }
    if (previous_lexem == L_EMPTY || (previous_lexem ==  L_SEMICOLON && state == S_NAMEBEGIN)|| state == S_NAMEBEGIN) {

        while (*s != ':' && *s != '=' && *s != ';') {
            if (*s == '\0' || *s == '\n' || *s == '\r') {
                return L_ERR;
            }
            /*if (!check_special_characters(&s)) {
                return L_ERR;
            }*/
            //printf("%c", *s);
            ++s;
        }
        *end = s - 1;
        //putc('\n', stdout);
        return L_NAME;
    }
    else {
        if (previous_lexem == L_COLON || previous_lexem ==  L_ASSIGNMENT || previous_lexem == L_SPACE || (previous_lexem == L_SEMICOLON && state == S_VALBEGIN)) {
            while (*s != '\n' && *s != '\r') {
                if (state != S_MOREHVALUE && *s == ';') {
                    *end = s - 1;
                    return L_VALUE;
                }
                if (!check_special_characters(&s)){
                    return L_ERR;
                }
                printf("%c", *s);
                ++s;
            }
            
            *end = s - 1;
            
            return L_VALUE;
        } else {
            return L_ERR;
        }
    }
}

static lexem_t get_lexem(const char *s, const char **end, lexem_t previous_lexem, state_t state) {
    if (!s || !end) { return L_ERR; }
    if (!(state == S_NAMEBEGIN && previous_lexem == L_EMPTY)) {
    ++s;
    }
    *end = s;
    switch (*s) {
        case ':': {
            return L_COLON;
        }
        case ';': {
            return L_SEMICOLON;
        }
       
        case ' ': {
            return L_SPACE;
        }
        case '\t': {
            return L_SPACE;
        }
        case '=': {
            if (state == S_NAME){
                return L_ASSIGNMENT;
            } 
            return get_complex_lex(s, end, previous_lexem, state);
        }
        default: 
        // printf("%c", *s);
        return get_complex_lex(s, end, previous_lexem, state);
    }
}

bool parse(const char*s) {
    if (!s) {
        return false;
    }
    const char *end;
    state_t state = S_NAMEBEGIN;
    char ** str = malloc(4*sizeof(char*));
    lexem_t previous_lexem = L_EMPTY;
    bool multipart = false;
    size_t parts = 0;
    if (str == NULL) {
        puts("Error");
    } else {
        int flag = -1;
        while (*s && state != S_HEND) {
            lexem_t lexem = get_lexem(s, &end, previous_lexem, state);
            if (lexem == L_ERR) {
                return false;
            }
            rule_t rule = transitions[state][lexem];
            if (rule.state == S_ERR) {
                return false;
            }
            if (((lexem == L_NAME || lexem == L_VALUE) && previous_lexem == L_SPACE) || previous_lexem == L_ASSIGNMENT) {
                ++s;
            }
            if (rule.action != NULL) {
                if (!rule.action(s, end, &flag, str)) {
                    return false;
                }
            }
            if (flag == 3) {
                multipart = true;
            }
            state = rule.state;
           
            printf("%d %c %d\n",lexem, *end, state);
            s = end;
            previous_lexem = lexem;
        }
        inf_out(str);
        if (!multipart) {
            while (*s) {
                if (*s != '\n' && *s != '\r') {
                    ++parts;
                    break;
                }
                ++s;
            }
            printf("%ld", parts);
        } else {
            //printf("%s", str[3]);
            while (*s) {
                while (*end != '\n' && *end != '\r' && *end != EOF) {
                    ++end;
                }
                char * check_bound = strndup(s, end - s);
                // printf("%s\t", check_bound);
                if (strncmp(check_bound, str[3], strlen(str[3])) == 0) {
                    ++parts;
                }
                end += 1;
                s = end;
            }
            if (parts >= 1){
            printf("%ld", parts - 1);
            } else {
                 printf("%ld", parts);
            }
        }
    }
    return true;
}
