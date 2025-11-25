/**
 * @file Loan.h
 * @brief Defines the Loan class for calculating loan metrics (EMI, total payment, interest).
 *
 * This header defines the structure and public interface for the Loan class,
 * which is used to model a simple amortizing loan.
 */
#ifndef LOAN_H
#define LOAN_H

/**
 * @class Loan
 * @brief Represents a single fixed-rate, amortizing loan.
 *
 * The class holds the principal amount, annual interest rate, and term in years,
 * and provides methods to calculate key financial figures like monthly payment.
 */
class Loan {
private:
    /// The principal amount of the loan (long double for high precision).
    long double amount;
    /// The annual interest rate in percent (e.g., 5.0 for 5%).
    long double rate;
    /// The term of the loan in full years.
    int years;

public:
    /**
     * @brief Constructor for the Loan class.
     * @param a The principal amount of the loan.
     * @param r The annual interest rate (percentage).
     * @param y The term of the loan in years.
     */
    Loan(long double a, long double r, int y);

    /**
     * @brief Checks if the loan parameters are valid.
     * @return true if amount > 0, rate >= 0, and years > 0.
     */
    bool isValid() const;

    /**
     * @brief Calculates the Equal Monthly Installment (EMI).
     *
     * The calculation uses the standard amortization formula and handles the edge case
     * of extremely long tenures to prevent floating-point overflow. The result is
     * rounded to two decimal places.
     *
     * @return The monthly payment amount (EMI).
     */
    long double monthlyPayment() const;

    /**
     * @brief Calculates the total payment made over the lifetime of the loan.
     * @return The total principal and interest paid.
     */
    long double totalPayment() const;

    /**
     * @brief Calculates the total interest paid over the lifetime of the loan.
     * @return The total interest paid (Total Payment - Principal Amount).
     */
    long double totalInterest() const;
};

#endif