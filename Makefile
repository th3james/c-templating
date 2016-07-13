all:
	clang main.c -o template_renderer
	./template_renderer template.hsh hat: boat

test:
	clang tests.c -o tests
	./tests
