#include <iostream>

using namespace std;

void cinFailed();

class BankAccount
{
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accountNumber, double balance)
    {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->interestRate = 0;
    }

    void Deposit(double bal)
    {
        if (bal > 0)
        {
            balance += bal;
        }
        else
        {
            cout << "Не удается внести средства." << endl;
        }
    }

    void WithDraw(double bal)
    {
        if (balance >= bal && bal > 0)
        {
            balance -= bal;
        }
        else
        {
            cout << "Не удается снять средства!" << endl;
        }
    }

    double GetBalance()
    {
        return balance;
    }

    double GetInterest()
    {
        return balance * interestRate / 12;
    }

    void SetInterestRate(double rate)
    {
        if (rate > 0 && rate < 1)
        {
            interestRate = rate;
        }
        else if (rate < 0)
        {
            cout << "Процентная ставка не может быть меньше нуля!" << endl;
        }
        else
        {
            cout << "Не удается обновить процентную ставку!" << endl;
        }
    }

    int GetAccountNumber()
    {
        return accountNumber;
    }

public:
    friend double Transfer(BankAccount& _from)
    {
        int other;
        double transBalance;

        cout << "Введите номер банковского счета. " << endl;
        cin >> other;
        cinFailed();

        cout << "Введите сумму перевода." << endl;
        cin >> transBalance;
        cinFailed();

        bool tranferSuccess;
        
        if (transBalance <= _from.balance && transBalance >= 0 && other != _from.accountNumber)
        {
            BankAccount another(other, transBalance);
            _from.balance -= another.balance;
            tranferSuccess = true;
            cout << tranferSuccess << " - \t" << another.balance << " переведены успешно." << endl;

            return another.balance;
        }
        else
        {
            tranferSuccess = false;
            cout << tranferSuccess << " - \t перевод осуществить не удалось." << endl;
        }
    }
};

void cinFailed()
{
    if (!cin)
    {
        cout << "\n\t   ERROR" << endl;
        cout << "Чтобы предотвратить возникновение ошибок, везде вводите числа." << endl;
        exit(1);
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    int accNum;
    double balance;
    int opt;

    cout << "Введите номер банковского счета. " << endl;
    cin >> accNum;
    cinFailed();
    cout << "Введите баланс. " << endl;
    cin >> balance;
    cinFailed();

    BankAccount accBank(accNum, balance);
    BankAccount* bank = new BankAccount(accNum, balance);

    while (true)
    {
        cout << "\n\tЧто вы хотите сделать?" << endl;
        cout << "\n1. Внести средства" << endl;
        cout << "2. Вывести средства" << endl;
        cout << "3. Посмотреть текущий баланс" << endl;
        cout << "4. Посмотреть текущую сумму" << endl;
        cout << "5. Обновить процентную ставку" << endl;
        cout << "6. Получить номер банковского счета" << endl;
        cout << "7. Перевести с одного счета на другой" << endl;
        cout << "8. Выйти из программы" << endl;

        cin >> opt;
        switch (opt)
        {
            case 1:
                double newBalance;
                cout << "Введите средства. " << endl;
                cin >> newBalance;
                cinFailed();
                bank->Deposit(newBalance);
                break;
            case 2:
                double withDrew;
                cout << "Введите количество средств, которое желаете снять. " << endl;
                cin >> withDrew;
                cinFailed();
                bank->WithDraw(withDrew);
                break;
            case 3:
                cout << "Текущий баланс: " << bank->GetBalance() << endl;
                break;
            case 4:
                cout << "Текущая сумма: " << bank->GetInterest() << endl;
                break;
            case 5:
                double newRate;
                cout << "Введите процентную ставку. " << endl;
                cin >> newRate;
                cinFailed();
                bank->SetInterestRate(newRate);
                break;
            case 6:
                cout << "Номер банковского счета: " << bank->GetAccountNumber() << endl;
                break;
            case 7:
                double trans;
                trans = Transfer(accBank);
                bank->WithDraw(trans);
                break;
            case 8:
                exit(0);
                break;
            default:
                cout << "Такого функционала нет." << endl;
                break;
        }
    }  
}
