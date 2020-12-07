main: driver.o lexer.o stackdef.o grammar_parser.o treenode.o typeExpression.o
	@gcc -o run lexer.o stackdef.o grammar_parser.o treenode.o typeExpression.o driver.o
driver.o: driver.c grammar_parser.h lexer.h
	@gcc -c driver.c
grammar_parser.o: grammar_parser.c grammar_parser.h stackdef.h typeExpression.h treenode.h	
	@gcc -c grammar_parser.c
lexer.o: lexer.c lexer.h
	@gcc -c lexer.c
stackdef.o: stackdef.c stackdef.h	
	@gcc -c stackdef.c
typeExpression.o: typeExpression.c typeExpression.h
	@gcc -c typeExpression.c
treenode.o: treenode.c treenode.h
	@gcc -c treenode.c
clean:
	rm driver.o lexer.o stackdef.o grammar_parser.o treenode.o typeExpression.o
