%{
// C declarations used in actions
#include <stdio.h>     
#include <stdlib.h>
#include <ctype.h>
int yylex();
%}
/* Yacc definitions */
%union {int num; char id;}	//yystype      
%start start
%token printTemp
%token exitTemp
%token <num> number
%token varName
%token str
%token typeTemp
%token programTemp
%token varTemp
%token beginTemp
%token endTemp

%%

//Acts like <start> PROGRAM<pname>; VAR ,dec-list>; BEGIN <stat-list> END
start   : programTemp pname ';'
          varTemp decList ';' 
          beginTemp statList
          endTemp             			{printf("Compiled Successfully\n");}
        | errorCalls
        | exitTemp 						{exit(EXIT_SUCCESS);};
//Used to check for possible errors after grammar has been checked     
errorCalls : 
		//PROGRAM missing
		error endTemp             		{printf("PROGRAM is expected\n"); } 

        //first ; missing
		| programTemp pname error endTemp {printf("';' is expected\n"); }
		
        // INTEGER missing
		| programTemp pname ';'
          error endTemp            		{printf("VAR is expected\n"); }
		  
        //second ; missing
		| programTemp pname ';'
          varTemp decList error endTemp {printf(";' is expected\n"); }
		  
        //BEGIN missing
		| programTemp pname ';'
          varTemp decList ';'
          error endTemp               	{printf("BEGIN is expected\n"); }
		  
		//code broken
		| programTemp pname ';'
          varTemp decList ';'
          beginTemp error endTemp   	{printf("Error in code section.\n"); };
		  
        //END. missing
		| programTemp pname ';'
          varTemp decList ';'
          beginTemp statList error endTemp   {printf("END. is expected\n"); };
        
		
pname   : varName; //varName is id

decList : dec ':' typeTemp;
        
dec     : varName
        | varName ',' dec;

statList: stat ';' statList 
        | stat ';';
        
stat    : print
        | assign;
    
print   : printTemp '(' output ')';
        
output  : str ',' output
        : varName; 

assign  : varName '=' expr;
            
expr    : term                  
        | expr '+' term         
        | expr '-' term;
        
term    : term '*' factor
        | term '/' factor
        | factor;

factor  : varName
        | number
        | '(' expr ')';
		
/***************************************
* number returned as number
* type returned as typeTemp
* digit returned as number
* letter is returned as varName
****************************************/

%%                     

int main (void) {
	int x = yyparse ( );
	printf("Parsing Completed");
	return x;
}

void yyerror (char *s) 
{
	fprintf (stderr, "%s\n", s);
} 

