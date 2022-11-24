
#include "Interface.h"

using namespace std;

int main() {
    Interface *interface = new Interface();
    interface->run();
    //interface->test11();
    delete interface;
}