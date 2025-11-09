// Account.h - base Account and two derived account types
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

class Account {
protected:
    std::string ownerName;
    double balance;

public:
    Account(const std::string& name = "", double bal = 0.0)
        : ownerName(name), balance(bal) {}

    double getBalance() const { return balance; }

    virtual void display() {
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: " << balance << std::endl;
    }

    virtual ~Account() {
        std::cout << "Account closed for " << ownerName << std::endl;
    }

    // combine balances: return new Account with left owner's name and summed balance
    Account operator+(const Account& other) const {
        return Account(ownerName, balance + other.balance);
    }

    // difference between balances (left - right)
    double operator-(const Account& other) const {
        return balance - other.balance;
    }

    bool operator==(const Account& other) const {
        return balance == other.balance;
    }

    // stream operators
    friend std::ostream& operator<<(std::ostream& os, const Account& a) {
        os << "Owner: " << a.ownerName << std::endl;
        os << "Balance: " << a.balance;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Account& a) {
        // read ownerName and balance without prompts
        is >> std::ws; // eat whitespace
        std::getline(is, a.ownerName, '\n');
        // If only name was entered on line, attempt to read balance next
        if (!(is >> a.balance)) {
            // clear failbit if no balance provided
            is.clear();
        } else {
            // consume trailing newline
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return is;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate; // percent

public:
    SavingsAccount(const std::string& name = "", double bal = 0.0, double rate = 0.0)
        : Account(name, bal), interestRate(rate) {}

    void display() override {
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
    }
};

class CheckingAccount : public Account {
private:
    double transactionFee;

public:
    CheckingAccount(const std::string& name = "", double bal = 0.0, double fee = 0.0)
        : Account(name, bal), transactionFee(fee) {}

    void display() override {
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Transaction Fee: " << transactionFee << std::endl;
    }
};

#endif // ACCOUNT_H
