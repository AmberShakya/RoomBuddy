#include <iostream>

unsigned int simple_hash(const std::string& str) {
    unsigned int hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int main() {
    std::string message;
    std::cin >> message;
    unsigned int hash = simple_hash(message);
    std::cout << "Hash of '" << message << "': " << hash << std::endl;
    return 0;
}

