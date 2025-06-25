// Smart Billing System in C++ / OOPS
#include <bits/stdc++.h>

using namespace std;

struct Item
{
    string name;
    float price;
    int quantity;

    float total() const { return price * quantity; }
};

class Bill
{
private:
    vector<Item> items;
    float subtotal, tax, discount, total;

public:
    Bill()
    {
        subtotal = 0.0;
        tax = 0.0;
        discount = 0.0;
        total = 0.0;
    }

    void addItem(const Item &item)
    {
        items.push_back(item);
        subtotal += item.total();
    }

    void calculate()
    {
        tax = subtotal * 0.18; // 18% GST
        discount = subtotal * 0.10; // 10% discount
        total = subtotal + tax - discount;
    }

    void display()
    {
        cout << fixed << setprecision(2);
        cout << "\n=== BILL ===\n";
        cout << left << setw(15) << "Item" << setw(10) << "Price" << setw(10) << "Qty" << "Total" << endl;
        for (auto &item : items)
        {
            cout << left << setw(15) << item.name << setw(10) << item.price << setw(10) << item.quantity << item.total() << endl;
        }
        cout << "---------------\n";
        cout << "Subtotal: Rs." << subtotal << endl;
        cout << "Tax (18%): Rs." << tax << endl;
        cout << "Discount (10%): Rs." << discount << endl;
        cout << "Total: Rs." << total << endl;
    }

    void saveToFile() const
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string filename = "bill_" + to_string(1900 + ltm->tm_year) + to_string(1 + ltm->tm_mon) + to_string(ltm->tm_mday) + ".txt";

        ofstream file(filename);
        if (file.is_open())
        {
            file << fixed << setprecision(2);
            file << "=== BILL ===\n";
            file << left << setw(15) << "Item" << setw(10) << "Price" << setw(10) << "Qty" << "Total" << endl;
            for (auto &item : items)
            {
                file << left << setw(15) << item.name << setw(10) << item.price << setw(10) << item.quantity << item.total() << endl;
            }
            file << "----------------\n";
            file << "Subtotal: Rs." << subtotal << endl;
            file << "Tax (18%): Rs." << tax << endl;
            file << "Discount (10%): Rs." << discount << endl;
            file << "Total: Rs." << total << endl;
            file.close();
            cout << "\nBill saved as: " << filename << endl;
        }
        else
        {
            cout << "\nError saving bill to file." << endl;
        }
    }
};

int main()
{
    int choice;
    Bill bill;
    cout << "=== SMART BILLING SYSTEM ===\n";
    cout << "Enter number of items: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        Item item;
        cout << "\nEnter details for item " << i + 1 << endl;
        cout << "Name: ";
        cin >> item.name;
        cout << "Price (in Rs): ";
        cin >> item.price;
        cout << "Quantity : ";
        cin >> item.quantity;
        bill.addItem(item);
    }

    bill.calculate();
    bill.display();
    bill.saveToFile();

    return 0;
}
