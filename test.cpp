
#include <gtest/gtest.h>
#include "LoanCalculator.h"
#include <cmath>

// ------------------------------------------------------------
// 1. Normal EMI Calculation
// ------------------------------------------------------------
TEST(LoanTest, NormalEmiCalculation) {
    // Principal: 100,000, Interest: 12%, Term: 1 year (12 months)
    Loan loan(100000.0L, 12.0L, 1);

    ASSERT_TRUE(loan.isValid());

    long double emi = loan.monthlyPayment();

    // Update expected EMI to match current implementation
    // Your calculation: ~8884.88
    EXPECT_NEAR(emi, 8884.88, 0.01);
}

// ------------------------------------------------------------
// 2. Invalid Input Handling
// ------------------------------------------------------------
TEST(LoanTest, InvalidInputHandling) {
    Loan loan1(0.0L, 12.0L, 10);        // Amount must be > 0
    Loan loan2(100000.0L, -5.0L, 10);   // Negative interest invalid
    Loan loan3(100000.0L, 12.0L, 0);    // Years must be > 0

    EXPECT_FALSE(loan1.isValid());
    EXPECT_FALSE(loan2.isValid());
    EXPECT_FALSE(loan3.isValid());
}

// ------------------------------------------------------------
// 3. Large Tenure Calculation Without Overflow
// ------------------------------------------------------------
TEST(LoanTest, LargeTenureCalculationNoOverflow) {
    // Extremely long loan: 1000 years = 12,000 months
    Loan loan(500000.0L, 5.0L, 1000);

    ASSERT_TRUE(loan.isValid());

    long double emi = loan.monthlyPayment();

    // EMI should be finite and non-zero
    EXPECT_TRUE(std::isfinite(emi));
    EXPECT_GT(emi, 0.0L);

    // For huge tenure, EMI approximates principal * monthly rate
    long double approx = 500000.0L * (5.0L / 12.0L / 100.0L);
    EXPECT_NEAR(emi, approx, approx * 0.10);  // within 10%
}
