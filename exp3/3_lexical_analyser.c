#include <stdio.h> 
#include <ctype.h>
#include <stdbool.h>

#define ROW 10
#define COL 40


void display_lexemes(int sl_number, char ch, char lexeme[], int line_number) {
	printf("%d\t%c\t%s\t%d\n", sl_number, ch, lexeme, line_number); 
}

void display_lexemes_string(int sl_number, char ch[], char lexeme[], int line_number) {
	printf("%d\t%s\t%s\t%d\n", sl_number, ch, lexeme, line_number); 
}


int main(int argc, char* argv[]) {

	if(argc != 3){
		printf("Input parameter mismatch\n"); 
		return 1; 
	}
	
	char keywords[20][50] = {
		"void","int","main","include","stdio","FILE",
		"argc","argv","printf","fgetc","fopen",
		"while","do","else","if","char",
		"size_t","ungetc","fprintf","for"
    };

	// Open files
	FILE* in = fopen(argv[1], "r"); 
	FILE* out = fopen(argv[2], "w"); 
	bool flag ; 
	char lexemes[ROW], next, ch; 
	int sl_number  = 1, line_number = 1, i; 
	while((ch = fgetc(in)) != EOF) {
		i = 0; 
		flag = false;
		if (ch == ' ' || ch == '\t')  ; 
		else if( ch == '\n'){
			line_number++; 
		}
		else if(ch == '(' || ch == '{' || ch == '[' ) {
			display_lexemes(sl_number, ch,"Open_bracket", line_number); 
			
		}
		else if (ch == ')' || ch == '}' || ch == ']' ) {
		
			display_lexemes(sl_number, ch,"Close_bracket", line_number); 
		
			
		} else if (ch == ';' ){
			display_lexemes( sl_number, ch,"Semicolon", line_number); 
			
		} else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			display_lexemes( sl_number, ch,"Arithmetic_operator", line_number); 
			
		} else if (ch == '#' || ch == '.' || ch == ':' || ch == ',' || ch == '_' || ch == '&') {
			display_lexemes( sl_number, ch,"Special_operator", line_number); 
		
		} else if (ch == '<' || ch == '>' || ch == '!' ) {
			
			lexemes[i++] = ch; 
			next = fgetc(in); 
			if(next == '=' ) lexemes[i++] = next; 
			lexemes[i++] = '\0';
			display_lexemes_string(sl_number , lexemes, "Relational_operator", line_number); 
			
		} else if (ch == '=') {
			lexemes[i++] = ch; 
			next = fgetc(in); 
			if(next == '=' ) {
				lexemes[i++] = next; 
				lexemes[i++] = '\0';
				display_lexemes_string(sl_number , lexemes, "Relational_operator", line_number);
				continue; 
			}
			ungetc(next, in);
			lexemes[i++] = '\0';
			display_lexemes_string(sl_number , lexemes, "Assignment_operator", line_number);
		} else if (isdigit(ch)) {
			lexemes[i++] = ch; 
			while(((ch = fgetc(in)) == isdigit(ch)) || ((ch = fgetc(in)) == '.')) {
				if(ch == '.') flag = true; 
				lexemes[i++] = ch ; 
			}
			
			if(flag) display_lexemes_string(sl_number , lexemes, "Floating_point", line_number);
			else display_lexemes_string(sl_number , lexemes, "number", line_number);
		} else if(isalpha(ch)) {
			lexemes[i++] = ch; 
			while((ch= fgetc(in)) == isalpha(ch)) lexemes[i++] = ch;
			lexemes[i++] = '\0';
			for(int i = 0 ;i < 20; i++) {
				if(keywords[i] == lexemes) flag = true; 
			}
			
			if(flag) display_lexemes_string(sl_number , lexemes, "keyword", line_number);
			else display_lexemes_string(sl_number , lexemes, "identifier", line_number);
		} else {
			display_lexemes(sl_number , ch, "Undefined", line_number);
		}
		
		
		
		
		sl_number++;
	}
	

	return 0; 
}
