
#include "Interface.h"

using namespace std;

int main() {
    Interface *interface = new Interface();
    interface->run();
    delete interface;
}