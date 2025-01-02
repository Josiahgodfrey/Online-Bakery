#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

class Bakery {
protected:
    int water;
    int flour;
    int oil;

public:
    Bakery(int water, int flour, int oil)
        : water(water), flour(flour), oil(oil) {}

    virtual void commonIngredient() const = 0; // Corrected method name
};


class userAccount {
public:
    string name;
    string password;
    int balance;

    // Hashing function for password
    string hashPassword(const string& password) {
        // Simple hashing algorithm for demonstration purposes
        // In a real-world application, use a secure hashing algorithm like SHA-256 or bcrypt
        string hashedPassword = "";
        for (char c : password) {
            hashedPassword += to_string(static_cast<int>(c) * 2);
        }
        return hashedPassword;
    }

};