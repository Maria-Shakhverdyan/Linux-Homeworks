#include <iostream>
#include <vector>
#include <pthread.h>

class BankAccount {
private:
    int balance;
    pthread_mutex_t mutex;

public:
    BankAccount() : balance(0) {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~BankAccount() {
        pthread_mutex_destroy(&mutex);
    }

    void debit(int amount) {
        pthread_mutex_lock(&mutex);
        balance -= amount;
        pthread_mutex_unlock(&mutex);
    }

    void credit(int amount) {
        pthread_mutex_lock(&mutex);
        balance += amount;
        pthread_mutex_unlock(&mutex);
    }

    int getBalance() const {
        return balance;
    }
};

void* transactions(void* arg) {
    BankAccount* account = static_cast<BankAccount*>(arg);
    
    for (int i = 0; i < 10000; ++i) {
        account->debit(1);
        account->credit(1);
    }
    
    return nullptr;
}

int main() {
    BankAccount account;

    std::vector<pthread_t> threads(20);

    for (int i = 0; i < 20; ++i) {
        pthread_create(&threads[i], nullptr, transactions, &account);
    }

    for (int i = 0; i < 20; ++i) {
        pthread_join(threads[i], nullptr);
    }

    std::cout << "Balance " << account.getBalance() << std::endl;

    return 0;
}
