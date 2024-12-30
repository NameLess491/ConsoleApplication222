#include <iostream>
#include <string>
#include <functional>

class CreditCard {
public:
    using Event = std::function<void(const std::string&)>;

    CreditCard(const std::string& number, const std::string& owner, const std::string& expiryDate, int pin, double limit)
        : number(number), owner(owner), expiryDate(expiryDate), pin(pin), limit(limit), balance(0.0) {}

    // Події
    Event onDeposit;
    Event onWithdrawal;
    Event onCreditUsed;
    Event onLimitReached;
    Event onPinChanged;

    // Методи
    void deposit(double amount) {
        balance += amount;
        if (onDeposit) onDeposit("Deposited: " + std::to_string(amount));
    }

    void withdraw(double amount) {
        if (balance - amount < 0) {
            if (onCreditUsed) onCreditUsed("Using credit: " + std::to_string(amount));
        }

        balance -= amount;
        if (balance <= -limit) {
            if (onLimitReached) onLimitReached("Limit reached! Balance: " + std::to_string(balance));
        }

        if (onWithdrawal) onWithdrawal("Withdrawn: " + std::to_string(amount));
    }

    void changePin(int newPin) {
        pin = newPin;
        if (onPinChanged) onPinChanged("PIN changed successfully.");
    }

    void display() const {
        std::cout << "Credit Card Info:\n"
            << "Number: " << number << "\nOwner: " << owner
            << "\nExpiry Date: " << expiryDate
            << "\nBalance: " << balance
            << "\nLimit: " << limit << "\n";
    }

private:
    std::string number;
    std::string owner;
    std::string expiryDate;
    int pin;
    double limit;
    double balance;
};

int main() {
    CreditCard card("1234-5678-9876-5432", "John Doe", "12/25", 1234, 5000);

    // Реєстрація подій
    card.onDeposit = [](const std::string& msg) { std::cout << "Event: " << msg << "\n"; };
    card.onWithdrawal = [](const std::string& msg) { std::cout << "Event: " << msg << "\n"; };
    card.onCreditUsed = [](const std::string& msg) { std::cout << "Event: " << msg << "\n"; };
    card.onLimitReached = [](const std::string& msg) { std::cout << "Event: " << msg << "\n"; };
    card.onPinChanged = [](const std::string& msg) { std::cout << "Event: " << msg << "\n"; };

    card.display();
    card.deposit(1000);
    card.withdraw(6000);
    card.changePin(5678);

    return 0;
}
