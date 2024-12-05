all: clean parser

1: clean parser1

2: clean parser2

3: clean parser3

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser1: lex.yy.c parser.tab.c parser.tab.h symbolTable.h AST.h
	gcc -o parser parser.tab.c lex.yy.c
	./parser testProg4.cmm

parser2: lex.yy.c parser.tab.c parser.tab.h symbolTable.h AST.h
	gcc -o parser parser.tab.c lex.yy.c
	./parser testProg5.cmm

parser3: lex.yy.c parser.tab.c parser.tab.h symbolTable.h AST.h
	gcc -o parser parser.tab.c lex.yy.c
	./parser testProg6.cmm

clean:
	rm -f parser lexer parser.tab.c lex.yy.c parser.tab.h parser.output
	ls -ls