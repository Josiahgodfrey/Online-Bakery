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


    void buyCake(int noOfCake, userAccount &balance) {
        int amount = 2000;
        int option;

        std::cout << "Enter the number of cakes you want to buy: " << endl;
        std::cin >> noOfCake;
        int total = noOfCake * amount;        
        
        std::cout << noOfCake << " Cakes cost: " << total << endl;
        std::cout << "Confirm the payment please (1 for yes, 0 for no): " << endl;
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Payment cancelled." << endl;
                break;
            case 1:
                if (balance.balance >= total) {
                    balance.balance -= total;
                    std::cout << "Payment successful. Your new balance is: " << balance.balance << ".Tsh" << endl;

                    //recording the transaction
                    balance.recordTransaction("Cake", noOfCake, amount);
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

class Mandazi : public Bakery {
    private:
        int milk;
        int bakingPowder;

    public:
        Mandazi(int &water, int &flour, int &oil, int milk, int bakingPowder)
        :Bakery(water, flour, oil), milk(milk), bakingPowder(bakingPowder) {}

    void commonIngredient() const override {
        std::cout << "Common ingredients for Loaf: Water: " << water 
             << ", Flour: " << flour << ", Oil: " << oil << endl;
    }  

    void buyMandazi(int noOfMandazi, userAccount &balance) {
        std::cout << "Enter the number of Mandazi you want to buy: ";
        std::cin >> noOfMandazi;

        int amount = 1000;
        int total = noOfMandazi * amount;

        std::cout << noOfMandazi << " Mandazi cost: " << total << endl;
        std::cout << "Confirm the payment please (1 for yes, 0 for no): ";
        int option;
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Payment cancelled." << endl;
                break;
            case 1:
                if (balance.balance >= total) {
                    balance.balance -= total;
                    std::cout << "Payment successful. Your new balance is: " << balance.balance << ".Tsh" << endl;

                    //recording the transaction
                    balance.recordTransaction("Mandazi", noOfMandazi, amount);
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


class Chapati : public Bakery {
    private:
        int milk;
        int salt;
        int eggs;

    public:
        Chapati(int &water, int &flour, int &oil, int milk, int salt, int eggs)
        :Bakery(water, flour, oil), milk(milk), salt(salt), eggs(eggs) {}
    
    void commonIngredient() const override {
        std::cout << "Common ingredients for Loaf: Water: " << water 
             << ", Flour: " << flour << ", Oil: " << oil << endl;
    }

void buyChapati(int noOfChapati, userAccount &balance) {
    int amount = 500;
    std::cout << "Enter the number of  Chapati do you want to buy:" << endl;
    std::cin >> noOfChapati; 

    int total = noOfChapati * amount;
    std::cout << noOfChapati << " Chapati cost: " << total << endl;
    std::cout << "Confirm the payment please (1 for yes, 0 for no): ";
    int option;
    std::cin >> option;


    switch (option) {
        case 0:
            std::cout << "Payment cancelled." << endl;
            break;
        case 1:
            if (balance.balance >= total) {
                balance.balance -= total;
                std::cout << "Payment successful. Your new balance is: " << balance.balance << ".Tsh" << endl;

                //recording the transaction
                    balance.recordTransaction("Chapati", noOfChapati, amount);
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


class Kababu : public Bakery{
    private:
        int meat;
        int eggs;
        int salt;
        
    public:
        Kababu(int &water, int &flour, int &oil, int meat, int salt, int eggs)
        :Bakery(water, flour, oil), meat(meat), salt(salt), eggs(eggs) {}

    void commonIngredient() const override {
        std::cout << "Common ingredients for Loaf: Water: " << water 
             << ", Flour: " << flour << ", Oil: " << oil << endl;
    } 

    void buyKababu(int noOfKababu, userAccount &balance) {
        int amount = 700;
        std::cout << "Enter the number of  Kababu do you want to buy:" << endl;
        std::cin >> noOfKababu; 

        int total = noOfKababu * amount;
        std::cout << noOfKababu << " Kababu cost: " << total << endl;
        std::cout << "Confirm the payment please (1 for yes, 0 for no): ";
        int option;
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Payment cancelled." << endl;
                break;
            case 1:
                if (balance.balance >= total) {
                    balance.balance -= total;
                    std::cout << "Payment successful! Your new balance is: " << balance.balance << ".Tsh" << endl;

                    //recording the transaction
                        balance.recordTransaction("Kababu", noOfKababu, amount);
                } else {
                    std::cout << "Insufficient funds. Please refund your account, and Thanks!." << endl;
                    std::cout << "****************************************************************" << endl;
                }
                break;
            default:
                std::cout << "Invalid option. Please try again." << endl;
                std::cout << "****************************************************************" << endl;

        }
    }

};




int main() { 

while (true)
{

    //Object for user authentications
    userAccount userCredentials;           
    
    //Load account information from the filesystem
    vector<userAccount> accounts = userCredentials.load();
    
    //Total amount of engredients in the bakery
    int totalWater = 18540755;
    int totalFlour = 39579489;
    int totalOil = 49539345;
    std::cout << "WELCOME TO MEREOLONE BAKERY" << endl << endl;
    std::cout << "Choose one of the Options by Numbers below to continue..." << endl;

    //Array of entry options
    string entryOptions[3] = {"Login", "Signup", "Exit the program"};

    int choice; //variable to store the choices

        std::cout << "Choose one of the Options by Numbers to continue..." << endl;

        for (int x = 0; x < 3; x++) {
            std::cout << x + 1 << ". " << entryOptions[x] << endl; //Display Options
        }

        std::cout << "Enter your choice (1-3):" << endl;
        std::cin >> choice;  //Read User input

        //handle user choice
        switch (choice) {
            case 1: {    //login option
                std::cout << "Fill the Login Menu..." << endl << endl;

                // Load account information from the filesystem
                vector<userAccount> accounts = userCredentials.load();

                string inputName, inputPassword;
                std::cout << "Enter your username: ";
                std::cin >> inputName;
                std::cout << "Enter your password: ";
                std::cin >> inputPassword;

                // Validate username and password
                for (const auto& account : accounts) {
                    if (inputName == account.name && inputPassword == account.password) {
                        std::cout << "You logged in successfully as " << account.name << endl;
                        userCredentials = account;  // Assign the logged-in user's credentials
                        break;
                    }
                }

                if (userCredentials.name.empty()) {
                    std::cout << "Invalid username or password. Please try again." << endl;
                    continue;   // prompting the user for a valid choice
                }

                break;
            }

            case 2: { 
                // Creating a new user account and save it to the filesystem
                std::cout << "Fill the Signup Menu..." << endl << endl;
                userAccount newUser;
                std::cout << "Enter your username: ";
                std::cin >> newUser.name;
                std::cout << "Enter your password: ";
                std::cin >> newUser.password;

                // create a directory for the new user
                newUser.save();
                break;
             }

             case 3: {
                std::cout << "Exiting the program..." << endl;
                return 0;   //Exiting the program
             }

             default: {
                std::cout << "Invalid choice. Please try again." << endl;
                continue;
             }
        } 



}
     
 return 0;
}