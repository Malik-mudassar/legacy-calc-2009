/**
 * @file main.cpp
 * @brief Contains the reference implementation for Loan calculations.
 *
 * This file demonstrates the standard, correct implementation of the
 * Loan::monthlyPayment method, intended as the final application logic.
 */
#include <cmath>
#include "LoanCalculator.h" // Include the header file

/**
 * @brief Calculates the Equal Monthly Installment (EMI) based on the standard amortization formula.
 *
 * This version serves as the canonical implementation. It handles the 0% rate case
 * but assumes the inputs are reasonable and does not include the explicit LargeTenure
 * overflow check, relying on standard library behavior.
 *
 * @return The monthly payment amount (EMI), rounded to two decimal places.
 */
long double Loan::monthlyPayment() const {
    long double monthlyRate = rate / 12.0 / 100.0;
    int totalMonths = years * 12;
    long double pow_term = pow(1.0 + monthlyRate, totalMonths); // Used 1.0 to match convention
    
    long double emi;
    
    if (monthlyRate == 0) {
        // Simple principal division for 0% rate
        emi = amount / totalMonths;
    } else {
        // Standard EMI calculation
        long double numerator = amount * monthlyRate * pow_term;
        long double denominator = pow_term - 1.0; // Used 1.0 to match convention
        emi = numerator / denominator;
    }

    // Round to 2 decimal places
    return std::round(emi * 100.0) / 100.0;
}
