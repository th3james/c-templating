all:
	clang render_template.c -o render_template
	./render_template template.hsh

test:
	clang tests.c -o tests
	./tests
