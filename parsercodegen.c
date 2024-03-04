//Alan Pons
//Edward Rosales
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENT_LEN 11
#define MAX_NUM_LEN 5
#define MAX_CODE_LEN 1000
#define MAX_STR_LEN 256

// Token types
enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11,
    leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
    commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32, elsesym = 33
};


// Token structure
typedef struct {
    int type;
    char value[MAX_STR_LEN]; // +1 for null terminator
} Token;

// Array to store tokens
Token tokens[MAX_CODE_LEN];
int token_count = 0;

//Boolean is true while inside a comment
//initialized as false
int isComment = 0;


// Function to check if a word is a keyword and return its token type
int is_keyword( char *word) {

    if (strcmp(word, "null") == 0) return skipsym;
    if (strcmp(word, "begin") == 0) return beginsym;
    if (strcmp(word, "end") == 0) return endsym;
    if (strcmp(word, "if") == 0) return ifsym;
    if (strcmp(word, "fi") == 0) return fisym;
    if (strcmp(word, "then") == 0) return thensym;
    if (strcmp(word, "while") == 0) return whilesym;
    if (strcmp(word, "do") == 0) return dosym;
    if (strcmp(word, "call") == 0) return callsym;
    if (strcmp(word, "const") == 0) return constsym;
    if (strcmp(word, "var") == 0) return varsym;
    if (strcmp(word, "procedure") == 0) return procsym;
    if (strcmp(word, "write") == 0) return writesym;
    if (strcmp(word, "read") == 0) return readsym;
    if (strcmp(word, "else") == 0) return elsesym;
    return identsym;

    // If not a keyword, consider it an identifier
}

//Function used to check for valid symbols and returns its token type
int is_symbol( char *word) {
    if (strcmp(word, "+") == 0) return plussym;
    if (strcmp(word, "-") == 0) return minussym;
    if (strcmp(word, "*") == 0) return multsym;
    if (strcmp(word, "/") == 0) return slashsym;
    if (strcmp(word, "=") == 0) return eqlsym;
    if (strcmp(word, "<>") == 0) return neqsym;
    if (strcmp(word, "<") == 0) return lessym;
    if (strcmp(word, "<=") == 0) return leqsym;
    if (strcmp(word, ">") == 0) return gtrsym;
    if (strcmp(word, ">=") == 0) return geqsym;
    if (strcmp(word, "(") == 0) return lparentsym;
    if (strcmp(word, ")") == 0) return rparentsym;
    if (strcmp(word, ",") == 0) return commasym;
    if (strcmp(word, ";") == 0) return semicolonsym;
    if (strcmp(word, ".") == 0) return periodsym;
    if (strcmp(word, ":=") == 0) return becomessym;
    return -1;
}

//adds into token array
void add_token(int type,  char *value) {
    tokens[token_count].type = type;
    strcpy(tokens[token_count].value, value);
    token_count++;
}

void tokenize_line(char *line) {

    int lineCounter = 0, wordLen = 0;
    char c;

    if(!isComment)
        c = line[lineCounter++];

    //deals with string length of 1 (last line of ta case)
    if(strlen(line) < 2){
        c = line[0];
        if(isalpha(c)){
            add_token(is_keyword(line), line);
        }
        else if (isdigit(c)){
            add_token(numbersym,line);
        }
        else if (!isspace(c)){
            add_token(is_symbol(line),line);
        }
        return;
    }

    //loops to the end of the file
    while ((isComment || c != '\0') ) {

        char word[MAX_STR_LEN] = {0};

        // Check for comments
        if ( isComment == 1) {
            lineCounter++;
            // Move past the opening comment delimiter
            while (line[lineCounter] != '\0' && isComment) {
                if (line[lineCounter-1] == '*' && line[lineCounter] == '/') {

                    // Reset comment flag
                    isComment = 0;
                }
                lineCounter++;
            }
            c = line[lineCounter];
            // Ignore characters inside comments
            if (isComment) {
                return; // Skip further processing for this line
            }
        }

        //Keyword/Identifier loop
        else if (isalpha(c) && !isComment) {

            while (isalpha(c) || isdigit(c)) {

                word[wordLen++] = c;
                c = line[lineCounter++];
            }

            if (strlen(word) <= MAX_IDENT_LEN)
                add_token(is_keyword(word), word);

            else
                add_token(-2, word);


        }

            //Number loop
        else if (isdigit(c)) {

            while (isdigit(c)) {

                word[wordLen++] = c;
                c = line[lineCounter++];
            }
            if (strlen(word) <= MAX_NUM_LEN)
                add_token(numbersym, word);

            else
                add_token(-3, word);

        }

            //Symbol check
        else if (!isspace(c) ) {

            //while a symbol and not null
            while (!isspace(c) && !isalpha(c) && !isdigit(c) && !isComment && c != '\0' ) {
                //opening comment check
                if(line[lineCounter -1 ] == '/' && line[lineCounter] == '*'){
                    isComment = 1;

                }
                //not a comment therefore a symbols(s) that will later be checked
                else {
                    word[wordLen++] = c;
                    c = line[lineCounter++];
                }
            }
            //check for symbol in code that are no comments
            if(!isComment){
                int symType, i = 0;
                char sym[2];

                //separates invalid symbols from valid string
                if(is_symbol(word) == -1){
                    while(i < wordLen){
                        sym[0] = word[i];

                        i++;
                        symType = is_symbol(sym);
                        add_token(symType, sym);

                    }

                }
                else{
                    //no invalid symbols were found in "word" string
                    symType = is_symbol(word);
                    add_token(symType, word);

                }
            }
            //currently in a comment so we just increment through it and ignore it
            else{
                c = line[lineCounter++];
            }


        } else {    //a white space was encountered
            c = line[lineCounter++];
        }

        wordLen = 0;

    }

}


// Main function
int main(int argc, char *argv[]) {
    // Check if a file name is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file.\n");
        return 1;
    }

    char line[MAX_CODE_LEN];
    printf("SOURCE PROGRAM:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        tokenize_line(line);
    }

    printf("\n\nLEXEME TABLE\n\nLexeme\t\t\tToken Type\n");
    for (int i = 0; i < token_count; i++) {

        if (tokens[i].type > 0)
            printf("%s\t\t\t%d\n", tokens[i].value, tokens[i].type);
        else if (tokens[i].type == -1)
            printf("%s\t\t\tERROR: INVALID SYMBOL\n", tokens[i].value);
        else if (tokens[i].type == -2)
            printf("%s\t\tERROR: IDENTIFIER IS TOO LONG\n", tokens[i].value);
        else if (tokens[i].type == -3)
            printf("%s\t\t\tERROR: NUMBER IS TOO LONG\n", tokens[i].value);


    }

    printf("\nTOKEN LIST\n");
    for (int i = 0; i < token_count; i++) {

        if (tokens[i].type > 0)
            printf("%d ", tokens[i].type);

        if (tokens[i].type == 2 || tokens[i].type == 3)
            printf("%s ", tokens[i].value);


    }
    fclose(file);
    return 0;
}
