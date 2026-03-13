#include "../vendors/CLI11.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  short int threads;
  std::string input_file, pgen_file, output_file;
  std::string type = "pseudocode";

  CLI::App app{"aiecm"};

  app.add_option("-j,--jobs", threads, "threads")->check(CLI::ExistingFile);
  app.add_option("-o,--output", output_file, "output file");
  app.add_option("-f,--factor", type, "composite number");
  CLI11_PARSE(app, argc, argv);
  // pg.init_files(input_file, pgen_file, output_file);

  return 0;
}
