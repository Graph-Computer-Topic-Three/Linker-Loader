/**
 * @file file.cpp
 * @brief The binary utilities for FLE (Funny Little Executable).
 * 
 *
 * @details
 * - cc: compiles a C file (freestanding, nostdlib) to FLE object file
 * - [TODO] ld: link FLE object files as an FLE executable
 * - objdump: display object file information
 * - readfle: display FLE file information
 * - nm: display symbols (for executable FLEs only)
 * - [TODO] exec: execute a FLE file
 *
 *
 * @note
 * 
 *
 * @warning
 * 
 *
 * @author gaohongy
 * @date 2024-08-02
 * @version 1.0
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <fstream>
#include <utility>
#include <sstream>

#include "json.hpp"

using json = nlohmann::json;
using FunPtr = void(*) (int, char **);

void FLE_ld(int argc, char *argv[]);
void FLE_exec(int argc, char *argv[]);

std::string getLastPathComponent(const std::string& path) {
    // Find the position of the last '/'
    size_t lastSlashPos = path.find_last_of("/");

    // If '/' is found, return the substring after it
    if (lastSlashPos != std::string::npos) {
        return path.substr(lastSlashPos + 1);
    }

    // If '/' is not found, return the original path
    return path;
}

class Section {

    public:

    Section() : name(""), data() {}

    Section(std::string name, const std::vector<std::pair<std::string, std::string>> &data) : name(name), data(data) {}

    std::string getName() {
        return name;
    }

    std::vector<std::pair<std::string, std::string>> getData() {
        return data;
    }
    void setName(std::string name) {
        this->name = name;
    }
    
    void setData(const std::vector<std::pair<std::string, std::string>> &data) {
        this->data = data;
    }

    std::string toString() {
        std::stringstream ss;
        ss << "Section name: " << name << std::endl;
        ss << "Section data: " << std::endl;
        for (auto &pair : data) {
            ss << "\t" << pair.first << ": " << pair.second << std::endl;
        }
        return ss.str();
    }

    private:
    std::string name;
    std::vector<std::pair<std::string, std::string>> data;
};

int main(int argc, char *argv[]) {
    // Initialize the functions name and functional pointer mapping
    std::unordered_map<std::string, FunPtr> func_map = {
        {"FLE_ld", FLE_ld},
        {"FLE_exec", FLE_exec}
    };

    // Parse the parameter
    std::string tool = "FLE_" + getLastPathComponent(argv[0]);

    // Call the function
    if (func_map.find(tool) != func_map.end()) {
        func_map[tool](argc - 1, argv + 1);
    } else {
        std::cout << tool << " is not implemented." << std::endl;
    }
    
    //if (tool == "FLE_ld") {
    //    FLE_ld(argc - 1, argv + 1);
    //} else if (tool == "FLE_exec") {
    //    FLE_exec(argc - 1, argv + 1);
    //} else {
    //    std::cout << tool << " is not implemented." << std::endl;
    //}

    return 0;
}

/**
 * @brief Link FLE files as a single executable. Resolves all relocations.
 * 
 * 
 * @param argc The number of parameters.
 * @param argv The input parameters.
 */
void FLE_ld(int argc, char *argv[]) {

    std::string dest;
    std::unordered_map<std::string, std::vector<Section>> sections;

    //std::unordered_map<
    //                    std::string, 
    //                    std::vector<
    //                        std::pair<std::string, std::vector<std::pair<std::string, std::string>>>
    //                    >
    //> sections;

    #ifdef DEBUG
    std::cout << "==================== argc & argv ====================" << std::endl;
    std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    std::cout << "==================== end argc & argv ====================" << std::endl;
    #endif

    // 提取所有 section
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-o")) continue;

        if (i > 0 && !strcmp(argv[i - 1], "-o")) {
            // 提取链接输出文件名
            dest = std::string(argv[i]);
        } else {
            std::ifstream f(argv[i]);
            json j = json::parse(f);

            assert(j["type"] == ".obj");

            // 存储所有 section
            //for (json::iterator it = j.begin(); it != j.end(); ++it) {
            //    if (it.key()[0] == '.') { // is a section
            //        std::vector<std::string> section_data = it.value();
            //        std::vector<std::pair<std::string, std::string>> section_data_vec;

            //        for (std::string &data : section_data) {
            //            auto item = std::make_pair(data.substr(0, data.find(':')), data.substr(data.find(':') + 1));
            //            section_data_vec.push_back(item);
            //        }

            //        sections[argv[i]].push_back(std::make_pair(it.key(), section_data_vec));
            //    }
            //}

            for (json::iterator it = j.begin(); it != j.end(); ++it) {
                if (it.key()[0] == '.') { // is a section
                    std::vector<std::string> section_data = it.value();
                    std::vector<std::pair<std::string, std::string>> section_data_vec;

                    for (std::string &data : section_data) {
                        auto item = std::make_pair(data.substr(0, data.find(':')), data.substr(data.find(':') + 1));
                        section_data_vec.push_back(item);
                    }

                    sections[argv[i]].push_back(Section(it.key(), section_data_vec));
                }
            }

            f.close();
        }
    } 

    #ifdef DEBUG
    #ifdef extrace-section-test
    std::cout << "===== sections =====" << std::endl;

    std::cout << sections.size() << std::endl;

    for (auto &sections_single_file : sections) { // 枚举每一个文件下的 section
        std::cout << sections_single_file.first << std::endl;

        auto &section_vec = sections_single_file.second;
        for (auto &section : section_vec) {
            std::cout << section.toString() << std::endl;
        }

        std::cout << "-------------------" << std::endl << std::endl;
    }

    std::cout << "===== sections end =====" << std::endl;
    #endif // extrace-section-test
    #endif // DEBUG 


}

void FLE_exec(int argc, char *argv[]) {

}