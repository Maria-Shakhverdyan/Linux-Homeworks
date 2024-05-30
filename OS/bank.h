#ifndef BANK_H
#define BANK_H

#include <vector>
#include <mutex>

struct Account {
    int current_balance;
    int min_balance;
    int max_balance;
    bool is_frozen;
    std::mutex mtx;

    Account(int current, int min, int max)
        : current_balance(current), min_balance(min), max_balance(max), is_frozen(false) {}
};

class Bank {
public:
    Bank(int n, int max_balance);
    bool freezeAccount(int account_number);
    bool unfreezeAccount(int account_number);
    bool transfer(int from_account, int to_account, int amount);
    bool updateAllBalances(int amount);
    bool setMinBalance(int account_number, int min_balance);
    bool setMaxBalance(int account_number, int max_balance);
    int getCurrentBalance(int account_number);
    int getMinBalance(int account_number);
    int getMaxBalance(int account_number);

private:
    std::vector<Account> accounts;
    std::mutex bank_mtx;
};

#endif // BANK_H

