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
    
}

void FLE_exec(int argc, char *argv[]) {

}