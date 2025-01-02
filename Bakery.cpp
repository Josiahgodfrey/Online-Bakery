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


class Loaf : public Bakery {
public:
    Loaf(int water, int flour, int oil)
        : Bakery(water, flour, oil) {}

    void commonIngredient() const override {
            std::cout << "Common ingredients for Loaf: Water: " << water 
             << ", Flour: " << flour << ", Oil: " << oil << endl;
    }

    void buyLoaf(int &noOfLoaf, userAccount &balance) {
        int amount = 1500;
        std::cout << "Enter the number of loaves you want to buy: ";
        std::cin >> noOfLoaf;

        int total = noOfLoaf * amount;
        std::cout << noOfLoaf << " loaves cost: " << total << endl;
        std::cout << "Confirm the payment please: ";
        std::cout << "Confirm the payment please (1 for yes, 0 for no):";
        int option;
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Payment cancelled." << endl;
                break;
            case 1:
                if (balance.balance >= total) {
                    balance.balance -= total;
                    std::cout << "Payment successful. Your new balance is: " << balance.balance << " Tsh" << endl;

                    //recording the transaction
                    balance.recordTransaction("Loaf", noOfLoaf, amount);
                } else {
                    std::cout << "Insufficient funds. Please add more money to your account." << endl;
                    std::cout << "****************************************************************" << endl;

                }
                break;
            default:
                std::cout << "Invalid option. Please try again." << endl;
                std::cout << "****************************************************************" << endl;

        }
    }
};

class Cake: public Bakery {
    private:
        int chocoPowder;
        int eggs;
        double prestige;

    public:
        Cake(int &water, int &flour, int &oil, int chocoPowder, int eggs, double prestige)
        :Bakery(water,flour, oil), chocoPowder(chocoPowder), eggs(eggs), prestige(prestige) {}

    void commonIngredient() const override {
        std::cout << "Common ingredients for Loaf: Water: " << water 
             << ", Flour: " << flour << ", Oil: " << oil << endl;
    }    


};
