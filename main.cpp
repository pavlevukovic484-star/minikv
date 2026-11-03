#include <iostream>
#include <string>
#include <sstream>
#include "store.h"

int main() {
    KeyValueStore kv;
    std::string line;

    std::cout << "=== Mini-Redis KV Store CLI ===\n";
    std::cout << "Commands: SET <key> <value> | GET <key> | DEL <key> | SIZE | EXIT\n\n";

    while (true) {
        std::cout << "db> ";
        if (!std::getline(std::cin, line)) break;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "EXIT" || cmd == "exit") {
            break;
        } else if (cmd == "SET" || cmd == "set") {
            std::string key, value;
            ss >> key >> value;
            if (!key.empty() && !value.empty()) {
                kv.set(key, value);
                std::cout << "OK\n";
            } else {
                std::cout << "ERROR: Usage: SET <key> <value>\n";
            }
        } else if (cmd == "GET" || cmd == "get") {
            std::string key, value;
            ss >> key;
            if (!key.empty()) {
                if (kv.get(key, value)) {
                    std::cout << value << "\n";
                } else {
                    std::cout << "(nil)\n";
                }
            } else {
                std::cout << "ERROR: Usage: GET <key>\n";
            }
        } else if (cmd == "DEL" || cmd == "del") {
            std::string key;
            ss >> key;
            if (!key.empty()) {
                if (kv.remove(key)) {
                    std::cout << "(integer) 1\n";
                } else {
                    std::cout << "(integer) 0\n";
                }
            } else {
                std::cout << "ERROR: Usage: DEL <key>\n";
            }
        } else if (cmd == "SIZE" || cmd == "size") {
            std::cout << "(integer) " << kv.size() << "\n";
        } else if (!cmd.empty()) {
            std::cout << "ERROR: Unknown command '" << cmd << "'\n";
        }
    }

    return 0;
}