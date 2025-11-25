
/**
 * @file Loan.cpp
 * @brief Implementation of the Loan class methods.
 *
 * This file contains the implementation details for loan calculations,
 * including validation, monthly payment, total payment, and total interest.
 * It includes robust handling for high-exponent scenarios (LargeTenure fix).
 */
#include "LoanCalculator.h"    // Include the class definition
#include <cmath>     // Include for std::pow, std::round, and std::isfinite

/**
 * @brief Constructor for the Loan class.
 * @param a The principal amount of the loan.
 * @param r The annual interest rate (percentage).
 * @param y The term of the loan in years.
 */
Loan::Loan(long double a, long double r, int y) : amount(a), rate(r), years(y) {}

/**
 * @brief Checks if the loan parameters are valid.
 * @return true if amount > 0, rate >= 0, and years > 0.
 */
bool Loan::isValid() const {
    return amount > 0 && rate >= 0 && years > 0;
}

/**
 * @brief Calculates the Equal Monthly Installment (EMI).
 *
 * Formula: EMI = P * r * (1+r)^n / ((1+r)^n - 1)
 * Includes a special case for 0% interest and a check for floating-point overflow
 * in the exponentiation term (pow_term).
 *
 * @return The monthly payment amount (EMI), rounded to two decimal places.
 */
long double Loan::monthlyPayment() const {
    // Convert annual percentage rate to monthly decimal rate
    long double monthlyRate = rate / 12.0 / 100.0;
    int totalMonths = years * 12;
    
    long double emi;
    
    if (monthlyRate == 0) {
        // Special case: 0% interest (simple division)
        emi = amount / totalMonths;
    } else {
        // Standard EMI calculation logic
        long double pow_term = std::pow(1.0 + monthlyRate, totalMonths);
        
        // FIX for LargeTenure: Check if the exponent term has overflowed to infinity.
        if (!std::isfinite(pow_term)) {
            // If (1+r)^n overflows, the EMI simplifies to P * r (Interest only in perpetuity).
            // For extremely long terms, the principal component of payment approaches zero.
            emi = amount * monthlyRate;
        } else {
            // Standard EMI calculation
            long double numerator = amount * monthlyRate * pow_term;
            long double denominator = pow_term - 1.0;
            emi = numerator / denominator;
        }
    }

    // Round the EMI to 2 decimal places for financial accuracy
    return std::round(emi * 100.0) / 100.0;
}

/**
 * @brief Calculates the total payment made over the lifetime of the loan.
 * @return The total principal and interest paid.
 */
long double Loan::totalPayment() const {
    return monthlyPayment() * years * 12;
}

/**
 * @brief Calculates the total interest paid over the lifetime of the loan.
 * @return The total interest paid (Total Payment - Principal Amount).
 */
long double Loan::totalInterest() const {
    return totalPayment() - amount;
}