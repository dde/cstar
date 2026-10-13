#include "Interactive.h"

int main() {
    Interactive *iact = Interactive::getInstance();

    std::cout << "Interactive Mode Active. Type 'exit' to quit.\n";

    while (true) {
        std::string cmd = iact->getCommand();

        if (cmd == "exit") {
            break;
        }

        std::cout << "Interpreter received: " << cmd << "\n";
    }

    delete iact;

    return 0;
}

