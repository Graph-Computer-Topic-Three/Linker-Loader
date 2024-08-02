#include <fstream>
#include "../json.hpp"
#include <iostream>
using json = nlohmann::json;

int main(int argc, char *argv[]) {
    std::ifstream f(argv[1]);
    json data = json::parse(f);

    assert(data["type"] == ".obj");

    for (json::iterator it = data.begin(); it != data.end(); ++it) {
        if (it.key() == ".data") {
            std::vector<std::string> data = it.value();
        for (auto str : data) {
            std::cout << str << std::endl;
        }
        }

        
    }

    return 0;
}