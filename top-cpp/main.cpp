#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Port {
    std::string swName;
    std::string portName;
    unsigned long inBps;
    unsigned long outBps;
    unsigned long sumBps;

    bool operator<(const Port& a) const {
        return sumBps < a.sumBps;
    }
};

// split string on comma
std::vector<std::string>SplitComma(const std::string &line) {
    std::vector<std::string> parts;

    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ',')) {
        parts.push_back(item);
    }

    return parts;
}

// Parse port line into port struct
Port ParsePort(const std::string &line) {
    std::vector<std::string> parts = SplitComma(line);
    if (parts.size() != 4) {
        std::cerr << "# malformed line, skipping: " << line << std::endl;
        return Port{};
    }

    Port port = {};
    port.swName = parts[0];
    port.portName = parts[1];
    port.inBps = std::stoul(parts[2]);
    port.outBps = std::stoul(parts[3]);
    port.sumBps = port.inBps + port.outBps;



    return port;
}

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
        // skip blank
        if (line.empty()) {
            continue;
        }

        // skip commented
        if (line.rfind("#") == 0) {
            continue;
        }

        Port p = ParsePort(line);
        if (p.portName.empty()) {
            continue;
        }

        ports.push_back(p);
    }
    infile.close();

    std::sort(ports.begin(), ports.end());
    std::reverse(ports.begin(), ports.end());

    for(auto const& port: ports) {
        std::cout << port.swName << "," << port.portName << "," << port.inBps << "," << port.outBps << std::endl;
    }
}
