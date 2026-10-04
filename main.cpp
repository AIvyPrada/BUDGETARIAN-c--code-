#include <iostream>
#include <fstream> //Para mag save ng file // ofstream para mag write // ifstream para sa read
#include <cstdlib>
#include <iomanip> //para sa decimals

using namespace std;
//para sa limitation ng user
const int MAX_EXP = 1000;
//categories
const int CAT_COUNT = 5;


//For E-wallet
struct Wallet {
  string name;
  float startBalance;
  float balance;
};


//func. decla.
void pauseScreen();
void displayBorder();
void displayWelcome();
void loginUser(string &currentUser, string &password);
void displayMenuOptions();
void addExpenses(string names[], string categories[], float amounts[], int &count, const string catList[], double &allowance, Wallet wallets[]);
string getDate();
double setAllowance();
int setupWallets(Wallet wallets[]);
void viewSummary(string user, string date, double allowance, double startAllowance, string categories[], float amounts[], int& count,
    const string catList[], Wallet wallets[]);


int main()
{
    string user, password, date;
    double allowance;
    int choice;

    string names[MAX_EXP];
    string categories[MAX_EXP];
    float amounts[MAX_EXP];
    int count = 0;
    string catList[CAT_COUNT] = {"Food", "Transport", "Bills", "Shopping", "Others"};

    Wallet wallets[3]; // GCash, Maya, ShopeePay
    int walletCount = 0;
    double startAllowance = 0; // para sa recap display

    displayBorder();
    displayWelcome();
    loginUser(user, password);

    displayBorder();
        allowance = setAllowance();
        startAllowance = allowance; // save original allowance
        date = getDate();
        walletCount = setupWallets(wallets); // setup e-wallets

    do {
        displayBorder();
        displayMenuOptions();
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice) {
        case 1: //Add expenses
            addExpenses(names, categories, amounts, count, catList, allowance, wallets);
            pauseScreen();
            system("cls");
            break;

        case 2: // View Summary
            viewSummary(user, date, allowance, startAllowance, categories, amounts, count, catList, wallets);
              pauseScreen();
              system("cls");
            break;

        case 3: //E-wallet tracker

            break;

        case 4: //Goals and Target
            break;

        case 5: //History of expense
            break;

        case 6:
            cout << "Thank you for using the Budgetarian System :)\n";
            break;

        default:
            cout << "Wrong input. Please try again.\n";
            pauseScreen();
            system("cls");
    }
    } while (choice != 6);

    return 0;
}

void displayBorder() {
    cout << "  ==========================================" << endl;
    cout << "         $  B U D G E T A R I A N  $        " << endl;
    cout << "              Tracking System               " << endl;
    cout << "  ==========================================" << endl;

}

void displayWelcome() {
    cout << "------------------ WELCOME ------------------\n";
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
    cout << endl;
}

//LOGIN PROCESS
void loginUser(string &currentUser, string &password) {
    string username;

    cout << "\n" << setw(30) << right << " >>> Login <<<\n" << endl;
    cout << "\nEnter your username: ";
    getline(cin, username);

    while (username.empty()) {
        cout << "\nUsername cannot be empty.\n\nEnter username:";
        getline(cin, username);
    }

 while (true) {
        cout << "Enter 4-character password: ";
        getline(cin, password);

        if (password.length() == 4) {
            break; // Valid length
        } else {
            cout << "\nPassword must be exactly 4 characters.\n\n";
        }
    }


    ifstream checkFile(username + ".txt");

    if (!checkFile) {
        cout << "\nNew user recognized. Creating account...\n";
        ofstream newFile(username + ".txt");
        newFile << password << endl;
        newFile.close();
        cout << "Account created successfully!\n";
    } else {
        string filePass;
        getline(checkFile, filePass);
        checkFile.close();

        if (filePass != password) {
            cout << "Incorrect password. Program will exit.\n";
            exit(0);
        }
        cout << "\nLogin successful!\n";
    }

    currentUser = username;
    pauseScreen();
    system("cls");
}

// para sa pag input ng allowance
double setAllowance() {
    double allowance = 0;

    cout << "\nHello, kindly set your allowance for this day :)\n";

    while(allowance <= 0) {
        cout << "\n>>> Allowance: P";
        cin >> allowance;
        cin.ignore();

    if(allowance <= 0){
        cout << "\nAllowance can't be 0 or less!\n" << endl;
        }
    }

    return allowance;
}

string getDate() {
    string date;

    while (true) {
        cout << "\nEnter date today (mm/dd/yy): ";
        getline(cin, date);

        // Check if empty
        if (date.empty()) {
            cout << "\nPlease enter a date.\n";
            continue;
        }

        // Check length (dapat 8 characters: 12/31/23)
        if (date.length() < 8) {
            cout << "\nDate should be in format mm/dd/yy (ex: 02/06/23)\n";
            continue;
        }

        break;
    }
    pauseScreen();
    system("cls");

    return date;
}

void displayMenuOptions() {
    cout << "--------------- MENU OPTIONS -----------------\n";
    cout << "[1] Add Expense\n";
    cout << "[2] View Summary\n";
    cout << "[3] E-Wallet Tracker\n" ;
    cout << "[4] Goals & Target\n";
    cout << "[5] History of Expenses\n";
    cout << "[6] Exit\n";
    cout << "-----------------------------------------------\n";
}

int setupWallets(Wallet wallets[]) {
    displayBorder();
    cout << "\n" << setw(35) << right << ">>> E-WALLET SETUP <<<\n" << endl;
    //cout << "\n---------------- E-WALLET SETUP ----------------\n";

    string input;
    char use;

    // VALIDATION LOOP PARA SA (y/n)
    while (true) {
        cout << "Do you want to track e-wallets? (y/n): ";
        getline(cin, input); // Ginagamit para mahuli kahit walang tinype (Enter lang)

        // 1. Check kung walang ni-input / Empty input
        if (input.empty()) {
            cout << "[Invalid]: An input is required. Choose Y or N.\n\n";
            continue; // Uulit sa itaas ng loop
        }

        // 2. Check kung higit sa isang character ang tinype (e.g., "yes" o "no")
        if (input.length() > 1) {
            cout << "[Invalid]: Isang letra lang po (y o n).\n\n";
            continue;
        }

        // Kuhanin ang nag-iisang character
        use = input[0];

        // 3. Check kung 'y' o 'n' lang talaga ang tinype
        if (use == 'y' || use == 'Y' || use == 'n' || use == 'N') {
            break; // Tapos na ang validation, pwedeng lumabas sa loop!
        } else {
            cout << "[Invalid]: Please enter 'Y' or 'N' only.\n\n";
        }
    }

    // Kung ayaw mag-track, i-set lahat sa 0
    if (use != 'y' && use != 'Y') {
        string wNames[3] = {"GCash", "Maya", "ShopeePay"};
        for (int i = 0; i < 3; i++)
            wallets[i] = {wNames[i], 0, 0};

        cout << "\nSkipping e-wallet setup...\n";
        pauseScreen();
        system("cls");
        return 3;
    }

    // --- MAGSISIMULA DITO ANG INPUT NG BALANCES ---
    cout << "\nEnter your current balances.\n";
    cout << "Enter 0 if you don't use that wallet.\n\n";

    string wNames[3] = {"GCash", "Maya", "ShopeePay"};
    for (int i = 0; i < 3; i++) {
        float bal = 0;

        //Para naman sa balance input (Bawal ang letra sa pera)
        while (true) {
            cout << ">> " << wNames[i] << " balance: P";
            if (cin >> bal) {
                if (bal < 0) {
                    cout << " [Invalid]: Negative balance is not allowed. Try again.\n";
                    continue;
                }
                cin.ignore(1000, '\n'); // Linisin ang basurang tira sa input stream
                break; // Valid ang number!
            } else {
                // Kakagat ito kapag nag-input ng letra (e.g., "isang libo") sa pera
                cout << " [Invalid]: Please enter numbers only.\n";
                cin.clear();            // I-reset ang error state ng cin
                cin.ignore(1000, '\n'); // Tapon ang maling input
            }
        }

        wallets[i] = {wNames[i], bal, bal};
    }

    // Show summary
    cout << "\n-------------------------------------------\n";
    for (int i = 0; i < 3; i++) {
        cout << ">> " << left << setw(12) << wallets[i].name
             << "P" << setw(8) << fixed << setprecision(2)
             << wallets[i].balance;
        if (wallets[i].balance > 0)
            cout << " registered\n";
        else
            cout << " skipped\n";
    }
    cout << "-------------------------------------------\n";
    cout << "\nE-wallet balances saved!\n";
    pauseScreen();
    system("cls");
    return 3;
}

void addExpenses(string names[], string categories[], float amounts[], int &count, const string catList[], double &allowance, Wallet wallets[])
{
  int num;
  cout << "---------- Add Expense ----------\n\n";
  cout << "How many expenses? (0 to exit): ";
  cin >> num; cin.ignore();

  if (num <= 0 || num > MAX_EXP) {
    cout << "Invalid number.\n";
    return;
  }

  for (int i = 0; i < num && count < MAX_EXP; i++) {
    cout << "\n---- EXPENSE (" << (i+1) << "/" << num << ") ----\n";

    // --- category ---
    cout << "\nSelect Category:\n";
    for (int c = 0; c < CAT_COUNT; c++)
      cout << (c+1) << ". " << catList[c] << "\n";

    int catChoice;
    cout << "Enter category (1-5): ";
    cin >> catChoice;
    cin.ignore();
    if (catChoice < 1 || catChoice > 5){
        cout << "Invalid.\n"; i--; continue;
    }

    categories[count] = catList[catChoice - 1];

    if (catChoice == 5) {
      string spec;
      cout << "Specify (Others): ";
      getline(cin, spec);

      if (!spec.empty())
        categories[count] = "Others - " + spec;
}

    // --- amount ---
    cout << "How much?: P ";
    cin >> amounts[count];
    cin.ignore();
    if (amounts[count] <= 0) { cout << "Amount invalid.\n"; i--; continue; }

    // --- payment method ---
    cout << "--------------------------\n";
    cout << "\nPayment Method:\n";
    cout << " [1] Cash (remaining: P" << fixed << setprecision(2) << allowance << ")\n";
    for (int w = 0; w < 3; w++)
      cout << " [" << (w+2) << "] " << wallets[w].name
           << " (balance: P" << wallets[w].balance << ")\n";

    int pay;
    cout << "--------------------------\n";
    cout << "Choice: ";
    cin >> pay;
    cin.ignore();

    // --- deduct from chosen payment ---
    if (pay == 1) {
      if (amounts[count] > allowance) {
        cout << "Not enough cash!\n";
         i--;
         continue;
      }
      allowance -= amounts[count];
      names[count] = "Cash";
      cout << "\nPaid via Cash. Remaining: P" << allowance << "\n";
    } else if (pay >= 2 && pay <= 4) {
      int w = pay - 2; // 0=GCash, 1=Maya, 2=ShopeePay
      if (amounts[count] > wallets[w].balance) {
        cout << "Not enough balance in " << wallets[w].name << "!\n";
        i--;
        continue;
      }
      wallets[w].balance -= amounts[count];
      names[count] = wallets[w].name;
      cout << "Paid via " << wallets[w].name
           << ". New balance: P" << wallets[w].balance << "\n";
    } else {
      cout << "Invalid choice.\n"; i--; continue;
    }

    count++;
  }

  cout << "\nAll expenses saved!\n";
}

void viewSummary(string user, string date, double allowance, double startAllowance, string categories[],float amounts[], int& count,
                  const string catList[], Wallet wallets[]) {
  cout << fixed << setprecision(2);


  cout << "-------------------------------------------\n";
  cout << "|           QUICK SUMMARY EXPENSE         |\n";
  cout << "-------------------------------------------\n";
  cout << "User : " << user << "\n";
  cout << "Date : " << date << "\n";

  // compute total spent
  float total = 0;
  for (int i = 0; i < count; i++)
    total += amounts[i];
  float remaining = allowance; // allowance na naka-deduct na

  // budget track table
  cout << "\n************* BUDGET TRACK ****************\n";
  cout << left << setw(25) << "Starting Allowance:"
       << "P" << startAllowance << "\n";
  cout << left << setw(25) << "Total Expenses:"
       << "P" << total << "\n";
  cout << left << setw(25) << "Cash Remaining:"
       << "P" << remaining << "\n";
  cout << left << setw(25) << "Spending Rate:";
  if (startAllowance > 0)
    cout << (total / startAllowance * 100) << "%\n";
  else
    cout << "N/A\n";

    //PAYMENT METHOD
    cout << "\n------------- PAYMENT BREAKDOWN ------------\n";
    cout << left << setw(22) << "Method" << setw(12) << "Spent" << "Remaining\n";
    cout << string(44, '-') << "\n";

    // cash row
    float cashSpent = startAllowance - allowance;
    cout << left << setw(22) << "Cash"
         << "P" << setw(11) << cashSpent
         << "P" << allowance << "\n";

    // wallet rows
    for (int w = 0; w < 3; w++) {
    float wSpent = wallets[w].startBalance - wallets[w].balance;
        if (wallets[w].startBalance > 0 || wSpent > 0) {
        cout << left << setw(22) << wallets[w].name
             << "P" << setw(11) << wSpent
             << "P" << wallets[w].balance << "\n";
    }
}
    cout << string(44, '-') << "\n";
    cout << left << setw(22) << "TOTAL SPENT"
         << "P" << total << "\n";

    // expenses by category — table
  cout << "\n---------- EXPENSES BY CATEGORY ------------\n";

  if (count == 0) {
    cout << "No expenses yet.\n";
  } else {
    cout << left << setw(22) << "Category"
         << setw(12) << "Amount"
         << "Share\n";
    cout << string(44, '-') << "\n";

    for (int c = 0; c < CAT_COUNT; c++) {
      float catTotal = 0;
      for (int i = 0; i < count; i++)
        if (categories[i].find(catList[c]) != string::npos)
          catTotal += amounts[i];

      if (catTotal > 0) {
        cout << left << setw(22) << catList[c]
             << "P" << setw(11) << catTotal;
        if (total > 0)
          cout << (catTotal / total * 100) << "%";
        cout << "\n";
      }
    }
    cout << string(44, '-') << "\n";
  }

  // status
  cout << "\n             >>> STATUS <<< \n";

      if (count == 0) {
        cout << "No expenses recorded yet.\n";
      } else if (remaining < 0) {
        cout << "WARNING : Exceeded budget by P" << -remaining << "!\n";
      } else if (remaining == 0) {
        cout << "ALERT : Zero cash balance!\n";
      } else if (remaining <= startAllowance * 0.25) {
        cout << "ALERT : Only P" << remaining << " cash left!\n";
      } else if (remaining <= startAllowance * 0.5) {
        cout << "CAUTION : Budget getting low. P" << remaining << " left.\n";
      } else {
        cout << "GOOD : P" << remaining << " cash remaining. Keep it up!\n";
      }
   // cout << "******************************************\n";
    cout << "--------------------------------------------\n";
    }
