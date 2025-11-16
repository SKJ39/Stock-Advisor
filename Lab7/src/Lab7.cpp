//============================================================================
// Anh Truong
// truongdinhquanganh04@gmail.com
// Lab 7 - Stock Advisor
//============================================================================

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;

//Prototypes
int getData(ifstream&, string[], double[], double[], double[], string[], double[], int);
void output(ofstream&, double[], double[], double[], string[], double[], int);
double calcAvg(double[], int);
void pay(string[], double[], int);
int search(string[], string, int);
void sSort(string[], double[], double[], double[], string[], double[], int);
void signature(ofstream&);
void signature();

int main() {
	//Declare variables
	int count,								//Total number of stocks (array elements that have values)
		countgain,							//Total number of stocks that had a gain in price between 2019 and 2023
		loc,								//Index location of user-entered stock symbol
		computer;							//Holds a random index number
	double avg;								//Average of the gains/losses
	string target;							//User-entered stock symbol to search

	int max = 1000;							//Max array size
	string symbol[max];						//Array of stock symbols
	double price[max], 						//Array of current prices for each stock
		price19[max], 						//Array of prices at the close of 2019 for each stock
		price23[max],						//Array of prices at the close of 2023 for each stock
		change[max];						//Array of gains or losses (in percentage) between 2019 and 2023 for each stock
	string name[max];						//Array of stock names

	ifstream stockIS;						//Input stream for stockdata.txt
	ofstream stockOS;						//Output stream to output data of all available stocks

	//Open a new file for output
	stockOS.open("StockOut.txt");

	//Open the StockData.txt to take inputs
	stockIS.open("StockData.txt");
	if(!stockIS.is_open()) {
		cout << "File not found." << endl;
		exit(1);
	}

	//Input stream read input file and assign values to variables until end of file
	count = getData(stockIS, symbol, price, price19, price23, name, change, max);

	//Output (to a file) all stock info (except symbol)
	output(stockOS, price, price19, price23, name, change, count);

	//Calculate the average of the gains/losses
	avg = calcAvg(change, count);
	cout << setprecision(2) << fixed;
	cout << "Average of all gains/losses: " << avg << "%" << endl;
	cout << endl;

	//Print any stocks that have prices below the user's budget
	pay(symbol, price, count);

	//Ask user to enter a stock symbol
	cout << endl;
	cout << "Enter a stock symbol (in UPPERCASE): ";
	cin >> target;

	//Search for the symbol
	loc = search(symbol, target, count);
	if (loc == -1)
		cout << "No stock with symbol " << target << endl;
	else
		cout << name[loc] << ": $" << price[loc] << endl;

	//Sort stocks in descending order by percent gain/loss
	sSort(symbol, price, price19, price23, name, change, count);

	stockOS << "=========================" << endl << endl;
	output(stockOS, price, price19, price23, name, change, count);
	signature(stockOS);

	//Find and record the number of stocks that had a gain in price between 2019 and 2023
	countgain = 0;
	for (int i = 0; i < count; i++) {
		if (change[i] > 0)
			countgain++;
	}

	//Recommend a stock to the user based on a random number
	srand(time(0));
	computer = rand() % countgain;
	cout << endl;
	cout << "For the best possible return, I suggest you purchase " << symbol[computer] << endl;

	signature();

	stockIS.close();
	stockOS.close();
	return 0;
}//main()

////////////////////////////////////////////////////////////

int getData(ifstream& stockIS, string symbol[], double price[], double price19[], double price23[], string name[], double change[], int max) {
	/* Pre: stockIS - Reference to a data file for input
	 * 		symbol[] - array of symbols of each stock
	 * 		price[] - array of current prices of each stock
	 * 		ptice19[] - array of prices of each stock in 2019
	 * 		price23[] - array of prices of each stock in 2023
	 * 		name[] - array of stock names
	 * 		change[] - array of percentage gains/losses for each stock between 2019 and 2023
	 * 		max - size of array
	 * Post: Number of stocks
	 * Purpose: Input the stock information from a data file
	 * 			and calculate the percentage of gain/loss for each stock */

	int count = 0;

	while (count < max && !stockIS.eof()) {
		stockIS >> symbol[count] >> price[count] >> price19[count] >> price23[count];
		getline(stockIS, name[count]);

		if(!stockIS.fail()) {
			//Scrape the last character off the string so that there will be no newline embedded in the string
			if (name[count].substr(name[count].size()-1) == "\n" || name[count].substr(name[count].size()-1) == "\r") {
				name[count] = name[count].substr(0, name[count].size()-1);
			}

			//Scrape the leading space off the string (name) present when reading the file input
			if (name[count].substr(0, 1) == " ") {
				name[count] = name[count].substr(1, name[count].size()-1);
			}

			//Compute change in stocks from 2019 to 2023
			change[count] = (price23[count] - price19[count]) / price19[count];
			change[count] *= 100;
			count++;
		}
	}

	return count;

}//getData()

////////////////////////////////////////////////////////////

void output(ofstream& stockOS, double price[], double price19[], double price23[], string name[], double change[], int count) {
	/* Pre: stockOS - Reference to a data file for output
	 * 		price[] - array of current prices of each stock
	 * 		ptice19[] - array of prices of each stock in 2019
	 * 		price23[] - array of prices of each stock in 2023
	 * 		name[] - array of stock names
	 * 		change[] - array of percentage gains/losses for each stock between 2019 and 2023
	 * 		count - number of stocks
	 * Post: None
	 * Purpose: Output (to file) name of company, current stock price, price at end of 2019,
	 * 			price at end of 2023, and percent gain or loss from end of 2019 to end of 2023 */

	int format = 25;

	//Print header
	stockOS << setprecision(2) << fixed;
	stockOS << left << setw(45) << "Name" << right << setw(format) << "Current Price";
	stockOS << setw(format) << "2019 Price" << setw(format) << "2023 Price";
	stockOS << setw(format) << "Gain/Loss" << endl;

	//Print all details
	for (int i = 0; i < count; i++) {
		stockOS << left << setw(45) << name[i];
		stockOS << right << setw(format) << price[i];
		stockOS << setw(format) << price19[i];
		stockOS << setw(format) << price23[i];
		stockOS << setw(format) << change[i] << "%";
		stockOS << endl;
	}

	stockOS << endl;

}//output()

////////////////////////////////////////////////////////////

double calcAvg(double change[], int count) {
	/* Pre: change[] - array of percentage gains/losses for each stock between 2019 and 2023
	 * 		count - number of stocks
	 * Post: Average of the gains/losses
	 * Purpose: Calculate the average of all gains/losses */

	//Declare variables
	double sum = 0;
	double avg;

	//Take the sum of all changes in each stock
	for (int i = 0; i < count; i++) {
		sum += change[i];
	}

	//Take the average
	avg = sum / count;
	return avg;

}//calcAvg()

////////////////////////////////////////////////////////////

void pay(string symbol[], double price[], int count) {
	/* Pre: symbol[] - array of stock symbols
	 * 		price[] - array of current prices of each stock
	 * 		count - number of stocks
	 * Post: None
	 * Purpose: Ask the user for the maximum they wish to pay per stock
	 * 			Print stocks and their prices equal or less than the specified amount */

	//Declare variables
	double max;
	int available = 0;

	//Ask the user for the maximum they wish to pay per stock
	cout << "How much do you want to pay per stock? $";
	cin >> max;
	cout << endl;

	//Find and print stocks with a price equal or less than the specified amount
	for (int i = 0; i < count; i++) {
		if (price[i] <= max) {
			cout << left << setw(10) << symbol[i];
			cout << right << setw(10) << price[i];
			cout << endl;
			available++;
		}
	}

	//If no stocks available at the specified price, print a special message
	if (available == 0)
		cout << "No stocks with a price less than $" << max << " in the list." << endl;

	/* Note: The instructions state to print these results to the screen (console), but the
			rubric mentions to put them onto the output FILE. I followed the instructions
			instead since it would be easier to format and keep track of the result of this
			function if both the input and the output are performed on the same screen.
	*/

}//pay()

////////////////////////////////////////////////////////////

int search(string symbol[], string target, int count) {
	/* Pre: symbol[] - array of stock symbols
	 * 		target - user-entered stock symbol to search
	 * 		count - number of stocks
	 * Post: Index location of user-entered stock symbol
	 * Purpose: Ask user for a stock symbol to search in the array
	 * 			Return the index location of the stock symbol
	 * 			If symbol doesn't exist, return -1 */

	//Sequential Search
	for (int i = 0; i < count; i++) {
		if (symbol[i] == target)
			return i;
	}

	return -1;

}//search()

////////////////////////////////////////////////////////////

void sSort(string symbol[], double price[], double price19[], double price23[], string name[], double change[], int count) {
	/* Pre: symbol[] - array of stock symbols
	 * 		price[] - array of current prices of each stock
	 * 		ptice19[] - array of prices of each stock in 2019
	 * 		price23[] - array of prices of each stock in 2023
	 * 		name[] - array of stock names
	 * 		change[] - array of percentage gains/losses for each stock between 2019 and 2023
	 * 		count - number of stocks
	 * Post: None
	 * Purpose: Sort stocks in descending order by percent gain/loss */

	//Declare variables
	string tempString;
	double tempDouble;
	int index;

	//Selection Sort
	for (int i = 0; i < count-1; i++) {
		index = i;
		for (int j = i+1; j < count; j++) {
			if (change[index] < change[j])
				index = j;
		}

		//Change the order for all arrays
		tempDouble = change[index];
		change[index] = change[i];
		change[i] = tempDouble;

		tempString = symbol[index];
		symbol[index] = symbol[i];
		symbol[i] = tempString;

		tempDouble = price[index];
		price[index] = price[i];
		price[i] = tempDouble;

		tempDouble = price19[index];
		price19[index] = price19[i];
		price19[i] = tempDouble;

		tempDouble = price23[index];
		price23[index] = price23[i];
		price23[i] = tempDouble;

		tempString = name[index];
		name[index] = name[i];
		name[i] = tempString;
	}

}//sSort()

////////////////////////////////////////////////////////////

void signature(ofstream& stockOS) {
	/* Pre: stockOS - Reference to a data file for output
	 * Post: None
	 * Purpose: Print programmer's name and email along with the title of the lab
	 * 			to an output file */

	stockOS << "=========================" << endl;
	stockOS << "Programmed by: Anh Truong" << endl;
	stockOS << "truongdinhquanganh04@gmail.com" << endl;
	stockOS << "Lab 7 - Stock Advisor" << endl;
}//signature()

////////////////////////////////////////////////////////////

void signature() {
	/* Pre: None
	 * Post: None
	 * Purpose: Print programmer's name and email along with the title of the lab
	 * 			to the screen (console) */

	cout << "=========================" << endl;
	cout << "Programmed by: Anh Truong" << endl;
	cout << "truongdinhquanganh04@gmail.com" << endl;
	cout << "Lab 7 - Stock Advisor" << endl;
}//signature()

////////////////////////////////////////////////////////////

/*
Average of all gains/losses: 82.87%

How much do you want to pay per stock? $100

INTC           52.34
CMCSA          50.63
KO             57.95
BAC            45.76
XOM            68.97
CSCO           57.53
PFE            45.67
ORCL           83.73
VZ             53.67
MRK            80.16
NEE            86.39
NVS            95.53

Enter a stock symbol (in UPPERCASE): V
Visa Inc.: $228.60

For the best possible return, I suggest you purchase MA
=========================
Programmed by: Anh Truong
truongdinhquanganh04@gmail.com
Lab 7 - Stock Advisor
*/

// Note: When viewing the output file, you should expand the file window to see all the data format
