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
