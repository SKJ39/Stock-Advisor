# Stock-Advisor
This C++ program is a "Stock Advisor" that reads stock data from an input file (`StockData.txt`), performs various analyses, and provides interactive feedback and recommendations to the user. It also generates a formatted report (StockOut.txt) with the results.

## Features
  - **File Input**: Reads stock data (symbol, name, current price, 2019 price, 2023 price) from `StockData.txt`
  - **Data Processing:**
    - Calculates the percentage gain/loss for each stock from the end of 2019 to the end of 2023
    - Strips leading/trailing whitespace from company names for clean output
  - **Analysis & Reporting:**
    - Calculates and displays the average percent gain/loss of all stocks in the list
    - Generates a formatted report named `StockOut.txt` containing all stock details
  - **Interactive Console:**
    - Prompts the user for a maximum price and lists all stocks at or below that price
    - Allows the user to search for a specific stock by its symbol (e.g., "AAPL")
  - **Sorting:**
    - Sorts all stocks in descending order based on their percentage gain/loss
    - Outputs the sorted list to `StockOut.txt` after the initial, unsorted report
  - **Recommendation:**
    - Provides a stock recommendation by randomly selecting from the list of stocks that had a positive gain

## Algorithms Used
This program demonstrates two fundamental data structure algorithms:
  - **Sequential Search:** Implemented in the `search()` function to find a stock based on the user-provided symbol
  - **Selection Sort:** Implemented in the `sSort()` function to sort the stocks in descending order of performance. The sort correctly maintains the integrity of the parallel arrays, sorting all data based on the change[] array

## Run Instructions
1. **Prerequisites**
  - A C++ compiler (e.g., `g++`, `clang++`, or MSVC)
  - An input file named `StockData.txt` located in the same directory as the executable

2. **Input File Format**
  - The `StockData.txt` file must follow a specific format for the program to parse it correctly. Each line should contain:
    - `SYMBOL | CURR_PRICE | 2019_PRICE | 2023_PRICE | Company Name`
    - Example `StockData.txt`:
```
AAPL 170.15 73.41 193.58 Apple Inc.
MSFT 330.66 157.70 376.17 Microsoft Corporation
GOOGL 130.80 68.37 139.73 Alphabet Inc.
AMZN 151.94 92.34 151.94 Amazon.com, Inc.
V 228.60 187.90 262.37 Visa Inc.
INTC 52.34 59.80 50.48 Intel Corporation
CMCSA 50.63 45.00 44.57 Comcast Corporation
KO 57.95 55.30 59.26 The Coca-Cola Company
BAC 45.76 35.22 34.02 Bank of America Corp
XOM 68.97 70.38 102.32 Exxon Mobil Corp
CSCO 57.53 47.96 50.36 Cisco Systems, Inc.
PFE 45.67 39.18 28.53 Pfizer Inc.
ORCL 83.73 53.68 105.81 Oracle Corp
VZ 53.67 61.40 37.89 Verizon Communications Inc
MRK 80.16 91.07 108.62 Merck & Co., Inc.
NEE 86.39 63.81 61.64 NextEra Energy, Inc
NVS 95.53 93.31 103.56 Novartis AG
MA 370.18 296.88 425.43 Mastercard Incorporated
```

3. **Compile and Execute**

## Output File (`StockOut.txt`)
The program generates `StockOut.txt`, which contains two sections separated by "===":
  - A formatted report of all stocks as they were read from the file
  - A second formatted report of all stocks after being sorted by their 2019-2023 gain/loss (highest to lowest)

## Disclaimer
This project was created for academic purposes.
