#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

// Expense Class -------------------------------------
class Expense {
public:
    string category;
    double amount;
    string date;

    Expense(string c, double a, string d) {
        category = c;
        amount = a;
        date = d;
    }
};

// Expense Manager -------------------------------------
class ExpenseManager {
private:
    vector<Expense> expenses;

public:

    void addExpense() {
        string category, date;
        double amount;

        cout << "\nEnter Category: ";
        cin >> category;

        cout << "Enter Amount: ";
        cin >> amount;

        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> date;

        expenses.push_back(Expense(category, amount, date));

        cout << "\nExpense Added Successfully!\n";
    }

    void viewExpenses() {
        if(expenses.empty()) {
            cout << "\nNo expenses recorded.\n";
            return;
        }

        cout << "\n------- All Expenses -------\n";
        cout << left << setw(15) << "Category"
             << setw(10) << "Amount"
             << setw(15) << "Date" << endl;

        for(auto &e : expenses) {
            cout << left << setw(15) << e.category
                 << setw(10) << e.amount
                 << setw(15) << e.date << endl;
        }
    }

    void showSummary() {
        double total = 0;
        for(auto &e : expenses) {
            total += e.amount;
        }

        cout << "\n------- Expense Summary -------\n";
        cout << "Total Spending: ₹" << total << endl;
    }

    // Save data to file -------------------------------------
    void saveToFile() {
        ofstream file("expenses.txt");

        for(auto &e : expenses) {
            file << e.category << " " << e.amount << " " << e.date << endl;
        }

        file.close();
        cout << "\nData Saved Successfully!\n";
    }

    // Load data from file -------------------------------------
    void loadFromFile() {
        ifstream file("expenses.txt");

        if(!file) return;  // File doesn't exist first time

        string category, date;
        double amount;

        while(file >> category >> amount >> date) {
            expenses.push_back(Expense(category, amount, date));
        }

        file.close();
        cout << "Data Loaded Successfully!\n";
    }
};

// Main Program -------------------------------------
int main() {
    ExpenseManager manager;
    manager.loadFromFile();

    int choice;

    while(true) {
        cout << "\n-------------------------------";
        cout << "\n   Personal Expense Tracker";
        cout << "\n-------------------------------";
        cout << "\n1. Add Expense";
        cout << "\n2. View All Expenses";
        cout << "\n3. Expense Summary";
        cout << "\n4. Save & Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: manager.addExpense(); break;
            case 2: manager.viewExpenses(); break;
            case 3: manager.showSummary(); break;
            case 4: manager.saveToFile(); exit(0);
            default: cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}
