#include <iostream>
#include <iomanip>
#include "InvestmentCalculator.h"

InvestmentCalculator::InvestmentCalculator() {
    initialInvestment = 0.0;
    monthlyDeposit = 0.0;
    annualInterest = 0.0;
    numYears = 0;
}

void InvestmentCalculator::getInput() {
    std::cout << "Initial Investment Amount: $";
    std::cin >> initialInvestment;

    std::cout << "Monthly Deposit: $";
    std::cin >> monthlyDeposit;

    std::cout << "Annual Interest (Compounded): ";
    std::cin >> annualInterest;

    std::cout << "Number of Years: ";
    std::cin >> numYears;
}

void InvestmentCalculator::calculateInvestment() {
    std::cout << std::fixed << std::setprecision(2);

    // Calculate and display year-end balances and earned interest
    std::cout << "Year    | Year-End Balance (Without Deposit) | Earned Interest (Without Deposit) | Year-End Balance (With Deposit) | Earned Interest (With Deposit)" << std::endl;

    calculateYearEndBalances(); // For no additional monthly deposits

    double additionalMonthlyDeposit = monthlyDeposit;
    while (additionalMonthlyDeposit > 0) {
        calculateYearEndBalances(additionalMonthlyDeposit);
        additionalMonthlyDeposit += 50.0; // Increment by $50 for next scenario
    }
}

void InvestmentCalculator::calculateYearEndBalances(double additionalMonthlyDeposit) {
    double total = initialInvestment;
    double earnedInterestWithoutDeposit = 0.0;
    double earnedInterestWithDeposit = 0.0;

    int totalMonths = numYears * 12;
    for (int month = 1; month <= totalMonths; ++month) {
        double interest = (total + additionalMonthlyDeposit) * ((annualInterest / 100) / 12);
        total += additionalMonthlyDeposit + interest;

        if (month % 12 == 0) {
            earnedInterestWithoutDeposit += interest;
            earnedInterestWithDeposit += interest;

            std::cout << std::setw(6) << month / 12
                << std::setw(26) << total - additionalMonthlyDeposit
                << std::setw(31) << earnedInterestWithoutDeposit
                << std::setw(30) << total
                << std::setw(26) << earnedInterestWithDeposit
                << std::endl;
        }
    }
}

void InvestmentCalculator::testScenarios() {
    char choice;
    std::cout << "Do you want to test different scenarios? (Y/N): ";
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Test different scenarios
        getInput();
        calculateInvestment();
        testScenarios();
    }
}