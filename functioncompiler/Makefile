all: clean parser

run: clean parser1

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser1: lex.yy.c parser.tab.c parser.tab.h symboltable.h ast.h
	gcc -o parser parser.tab.c lex.yy.c
	./parser testProg.cmm


clean:
	rm -f parser lexer parser.tab.c lex.yy.c parser.tab.h parser.output
	ls -ls