#include "testsrc/read_replacement_args_tests.c"
#include "testsrc/render_template_tests.c"

int main(int argc, char *argv[]) {
  testSuiteReplacementArgs();
  testSuiteRenderTemplate();
  return 0;
}
