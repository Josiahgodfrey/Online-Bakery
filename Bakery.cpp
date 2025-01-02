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

    // Load account information from the filesystem
    vector<userAccount> load() {
        vector<userAccount> accounts;
        ifstream file("/home/josiah/Documents/C++ DEV/ONLINE-BAKERY/Accounts/");
        if (!file.is_open()) {
            return accounts;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            userAccount account;
            getline(ss, account.name, '|');
            getline(ss, account.password, '|');
            ss >> account.balance;
            accounts.push_back(account);
        }

        return accounts;
    }

    // Save account information to a file
    void save() {
        ofstream file("/home/josiah/Documents/C++ DEV/ONLINE-BAKERY/Accounts/" + name + ".txt", ios::app);
        if (!file.is_open()) {
            throw runtime_error("Failed to open account file for writing");
        }
        file << name << " | " << hashPassword(password) << " | " << balance << endl;
    }

    // Record transaction history
    void recordTransaction(const string& product, int quantity, int amount) {
        ofstream file("/home/josiah/Documents/C++ DEV/ONLINE-BAKERY/Transactions/" + name + ".txt", ios::app);
        if (!file.is_open()) {
            throw runtime_error("Failed to open transaction file for writing");
        }
        file << product << " | " << quantity << " | " << amount << " | " << balance << endl;
    }
};