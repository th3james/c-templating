all:
	clang main.c -o template_renderer
	./template_renderer template.hsh greeting: Aloha name: Terry

test:
	clang tests.c -o tests
	./tests
