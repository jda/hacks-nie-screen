#include <iostream>
#include <fstream>
#include <vector>

struct Port {
    std::string swName;
    std::string portName;
    int inBps;
    int outBps;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <FILE>" << std::endl;
        return 1;
    }

    std::string infileName = argv[1];

    std::ifstream infile;
    infile.open(infileName);
    if (!infile.is_open()) {
        std::cerr << "Could not open file " << infileName << std::endl;
        return 1;
    }

    std::vector<Port> ports;
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.rfind("#") == 0) {
            continue;
        }

        std::cout << "Line: " << line << std::endl;
    }

    infile.close();
}
