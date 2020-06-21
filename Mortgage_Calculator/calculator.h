#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cmath>
#include <QVector>
#define FIXED_PAYMENT 1
#define FIXED_BASIS 0        // specifies repayment mentod, used in variable repaymentType
#define SINGLE 1
#define  MIXED 0  // specifies the input method to user interface, used in vriable loanType

struct eachMonth{
    double total;
    double intrest;
    double principle;
};//mounthly payment in structure
/*
//class calculator：
//____________________________________________________________________________________________________________
//    attributes                |                description
//____________________________________________________________________________________________________________
//    totalAmount	            |         Total amount of loan
//    interestRate	            |         Interest rate of loan
//    loanPeriod	            |         length of loan
//    totalAmount_CM            |  	     Commercial part of total amount for combined repayment method
//    totalAmount_PF	        |         Housing provident part of total amount for combined repayment method
//    interestRate_CM	        |         interest rate of Commercial part for combined repayment method
//    interestRate_PF	        |         interest rate of Housing provident part for combined repayment method
//    loanPeriod_2	            |         Length of loan for combined repayment method
//    repaymentMethod           |     	 Specifies current repayment method (fixed payment or fixed basis)
//    loanType	                |         Specifies current loan type (general or combined)
//______________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________
//    methods                                  description
//______________________________________________________________________________________________________________

//    paymentInFirstMonth_fixedPayment	  |         Returns payment in first month of fixed payment repayment method
//    paymentInFirstMonth_fixedBasis	  |         Returns payment in first month of fixed basis repayment method
//    setTotalAmount	                  |         Setter of total amount
//    setRepaymentMethod	              |         Setter of repaymentMethod
//    setloanType	                      |         Setter of loanType
//    setInterestRate	                  |         Setter of interestMate
//    setLoanPeriod	                      |         Setter of LoanPeriod
//    setInterestRate_CM	              |         Setter of interestRate_CM
//    setInterestRate_PF	              |         Setter of interestRate_PF
//    setHomePrice_CM	                  |         Setter of homePrice_CM
//    setHomePrice_PF	                  |         Setter of homePrice_PF
//    setLoanPeriod_2	                  |         Setter of loanPeriod_2
//    getLoantype	                      |         Getter of loanType
//    getRepaymentMethod	              |         Getter of repaymentMethod
//    getLoanPeriod	                      |         Getter of loanPeroiod
//    getLoanPeriod_2	                  |         Getter of loanPeriod_2
//    getProportion_interest1	          |         A method returns proportion of interest of general loan type
//    getProportion_interest2	          |         A method returns proportion of interest of combined loan type
//    getTableValue	                      |         A method returns schedule of i+1 th month
//    refreshDisplay_line	              |     	A method returns value of payment in first month or monthly payment
//    refreshDisplay_line2	              |     	A method returns value of payment in first month or monthly payment for combined loantype
*/
class calculator
{
private:

    double totalAmount;
    double interestRate;
    int loanPeriod;

    double totalAmount_CM;
    double totalAmount_PF;
    double interestRate_CM;
    double interestRate_PF;
    int loanPeriod_2;

    int repaymentMethod;
    int loanType;
    double paymentInFirstMonth_fixedPayment(int i=0);
    double paymentInFirstMonth_fixedBasis(int i=0);

    QVector <eachMonth> schedule;

public:
    calculator();
    void setTotalAmount(double Total);
    void setRepaymentMethod(int method);
    void setloanType(int type);
    void setInterestRate(double rate);
    void setLoanPeriod(int period);
    void setInterestRate_CM(double i);
    void setInterestRate_PF(double i);
    void setHomePrice_CM(double i);
    void setHomePrice_PF(double i);
    void setLoanPeriod_2(int i);

    int getLoantype();
    int getRepaymentMethod();
    int getLoanPeriod();
    int getLoanPeriod_2();

    double getProportion_interest1();
    double getProportion_interest2();
    eachMonth getTableValue(int i);
    void calculateTableValue();

    double refreshDisplay_line();
    double refreshDisplay_line2();
};

#endif // CALCULATOR_H
