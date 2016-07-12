all:
	clang render_template.c -o render_template
	./render_template template.hsh hat: boat

test:
	clang tests.c -o tests
	./tests
