/*
#include <iostream>

unsigned int simple_hash(const std::string& str) {
    int hash = 9562845;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    hash = std::to_string(hash);
    return hash;
}

int main() {
    std::string message;
    std::cin >> message;
    unsigned int hash = simple_hash(message);
    std::cout << "Hash of '" << message << "': " << hash << std::endl;
    return 0;
}
*/

#include <iostream>
#include <string>
#include <functional>

int main() {
    std::string str;
    std::cin >> str;
    std::hash<std::string> hash_fn; // create a hash function object for std::string
    size_t hash_value = hash_fn(str); // generate hash value for the string
    std::cout << "Hash value of \"" << str << "\" is: " << hash_value << std::endl;
    return 0;
}

