#include "manager.h"

using namespace std;

int main(int argc, char * argv[]) {

  CommandManager CM;
  Manager setup {
    nullptr,
    nullptr,
    & CM
  };
  setup.play(argc, argv);
}