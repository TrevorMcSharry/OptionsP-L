#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

int main(){
    double currPrice;
    string stockName;
    string optionType;
    double strikePrice;
    double premium;
    double breakevenPrice;

    cout << "Enter the name of the stock you would like to calculate: ";
    getline(cin, stockName);

    cout << "Enter " << stockName << "'s current price: $";
    while(!(cin >> currPrice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid current price: $";
    }

    cout << "Enter whether this is a call or a put: ";
    cin >> optionType;

    cout << "Enter the strike price for your option: $";
    while(!(cin >> strikePrice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid current price: $";
    }

    cout << "Enter the premium paid for one share of " << stockName << ": $";
    while(!(cin >> premium)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid premium for one share of " << stockName << ": $";
    }

//Calculates breakeven price based off if a call or a put
    if(optionType == "call"){
        breakevenPrice = strikePrice + premium;
    }
    else {
        breakevenPrice = strikePrice - premium;
    }
    cout << "\n" << stockName << ": " << "\n\n";
    cout << "Break even price: $" << breakevenPrice << "\n\n";
    cout << "Price      Percent      P/L at expiry" << endl;
    cout << "-------------------------------------" << endl;
//Prints out P/L if the price goes down
    for(int i = 10; i >= 1; i--){
        double profitLoss = 0;
        double percentChange = 0;
        double endPrice = currPrice;

        endPrice = endPrice * (1 - (i * .025));

        if(optionType == "call"){
            profitLoss = ((endPrice - strikePrice - premium) * 100);
        }
        else{
            profitLoss = ((strikePrice - endPrice - premium) * 100);
        }
        if(profitLoss < (premium * 100 * -1)){
            profitLoss = (premium * 100 * -1);
        }
        percentChange = ((endPrice - currPrice) / (currPrice)) * 100;
//Outputs P/L and percent change in a table and colors based on profit
        if(profitLoss > 0){
            cout << "\x1b[32m $";
        }
        else if(profitLoss < 0){
            cout << "\x1b[31m $";
        }
        else if(profitLoss == 0){
            cout << " $";
        }
        cout << fixed << setprecision(2) << endPrice << "     %" << percentChange << "      $" << profitLoss << endl << "\x1b[0m";
        cout << "-------------------------------------" << endl;
    }

    double profitLoss = 0;
    if(optionType == "call"){
        profitLoss = ((currPrice - strikePrice - premium) * 100);
    }
    else{
        profitLoss = ((strikePrice - currPrice - premium) * 100);
    }

    if(profitLoss < (premium * 100 * -1)){
        profitLoss = (premium * 100 * -1);
    }

    if(profitLoss == 0 || profitLoss == -0){
        cout << "$" << currPrice << "     %0" << "          $" << profitLoss;
    }
    else if(profitLoss > 0){
        cout << "\x1b[32m $" << currPrice << "     %0" << "          $" << profitLoss << "\x1b[0m";
    }
    else if(profitLoss < 0){
        cout << "\x1b[31m $" << currPrice << "     %0" << "          $" << profitLoss << "\x1b[0m";
    }
        cout << "\n-------------------------------------" << endl;

//Prints out P/L if the price goes up
    for(int i = 1; i <= 10; i++){
        double endPrice = currPrice;
        double percentChange = 0;
        double profitLoss = 0;
        endPrice = endPrice * (1 + (i * .025));
        percentChange = ((endPrice - currPrice) / (currPrice)) * 100;
        if(optionType == "call"){
            profitLoss = ((endPrice - strikePrice - premium) * 100);
            if(profitLoss < (premium * 100 * -1)){
                profitLoss = (premium * 100 * -1);
            }
        }
        else if(optionType == "put"){
            profitLoss = ((strikePrice - endPrice - premium) * 100);
            if(profitLoss < (premium * 100 * -1)){
                profitLoss = (premium * 100 * -1);
            }
        }
        if(profitLoss == 0.00 || profitLoss == -0.00){
            cout << " $" << fixed << setprecision(2) << endPrice << "     %" << percentChange << "      $" << profitLoss << endl;
        }
        else if(profitLoss > 0){
            cout << "\x1b[32m $" << fixed << setprecision(2) << endPrice << "     %" << percentChange << "      $" << profitLoss << endl << "\x1b[0m";
        }
        else if(profitLoss < 0){
            cout << "\x1b[31m $" << fixed << setprecision(2) << endPrice << "     %" << percentChange << "      $" << profitLoss << endl << "\x1b[0m";
        }
        cout << "-------------------------------------" << endl;
    }

    return 0;
} 