
/*
 * CS-413 Spring 98
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%token	<string_val> WORD

%token 	NOTOKEN GREAT GGREAT NEWLINE PIPE

%union	{
		char   *string_val;
	}

%{
extern "C" 
{
	int yylex();
	void yyerror (char const *s);
}
#define yylex yylex
#include <stdio.h>
#include "command.h"
%}

%%

goal:	
	commands
	;

commands: 
	command
	| commands command 
	;

command: simple_command
        ;

simple_command:	
	command_and_args iomodifier_opt iomodifier_append iomodifier_pipe NEWLINE {
		printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE 
	| error NEWLINE { yyerrok; }
	;

command_and_args:
	command_word arg_list {
		Command::_currentCommand.
		insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;

arg_list:
	arg_list argument
	| /* can be empty */
	;

argument:
	WORD {
        printf("   Yacc: insert argument \"%s\"\n", $1);
		Command::_currentSimpleCommand->insertArgument( $1 );\
	}
	;

command_word:
	WORD {
        printf("   Yacc: insert command \"%s\"\n", $1);
	    Command::_currentSimpleCommand = new SimpleCommand();
	    Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

iomodifier_opt:
	GREAT WORD {
		printf("   Yacc: insert output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand.flagList = 0;
		Command::_currentCommand.flagRewrite = 1;
	}
	| /* can be empty */ 
	;

iomodifier_append:
	GGREAT WORD {
		printf("   Yacc: insert output append \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand.flagList = 0;
		Command::_currentCommand.flagAppend = 1;
	}
	| /* can be empty */ 
	;

iomodifier_pipe:
	PIPE WORD WORD{
		printf("   Yacc: insert pipe input \"%s\"\n", $3);
		Command::_currentCommand._pipeText = $3;
		Command::_currentCommand.flagCat = 0;
		Command::_currentCommand.flagPipe = 1;
	}
	| /* can be empty */ 
	;

%%

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

#if 0
main()
{
	yyparse();
}
#endif
