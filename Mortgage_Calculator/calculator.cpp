#include "calculator.h"
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
calculator::calculator()
    : totalAmount(1000000), interestRate(4.75), loanPeriod(25),
      totalAmount_CM(500000), totalAmount_PF(500000), interestRate_CM(3.75),
      interestRate_PF(3.75), loanPeriod_2(25), repaymentMethod(FIXED_PAYMENT), loanType(SINGLE)
{
}
// @param: i -> specifies which schedule to return.
//
//                     case 0  returns result for general method
//                     case 1  returns result for commercial part
//                     case 2  returns result for housing provident part
double calculator::paymentInFirstMonth_fixedPayment(int i)
{
    double loanPriodByMonth, paymentInFirstMonth,
        Cur_loanPeriod, Cur_interestRate, Cur_homePrice;
    switch (i)
    {
    case 0:
        Cur_interestRate = this->interestRate;
        Cur_homePrice = this->totalAmount;
        Cur_loanPeriod = this->loanPeriod;
        break;
    case 1:
        Cur_interestRate = this->interestRate_CM;
        Cur_homePrice = this->totalAmount_CM;
        Cur_loanPeriod = this->loanPeriod_2;
        break;
    case 2:
        Cur_interestRate = this->interestRate_PF;
        Cur_homePrice = this->totalAmount_PF;
        Cur_loanPeriod = this->loanPeriod_2;
        break;
    default:
        return -1;
        break;
    }
    loanPriodByMonth = Cur_loanPeriod * 12;
    double monthlyInterestRate = Cur_interestRate / 12 / 100;
    paymentInFirstMonth = Cur_homePrice * monthlyInterestRate *
                          pow(1 + monthlyInterestRate, loanPriodByMonth) /
                          (pow(1 + monthlyInterestRate, loanPriodByMonth) - 1);
    return paymentInFirstMonth;
}
// @param: i -> specifies which schedule to return.
//
//                     case 0  returns result for general method
//                     case 1  returns result for commercial part
//                     case 2  returns result for housing provident part
//                     case 3  returns decrease value in each month for general method
//                     case 4  returns decrease value in each month for commercial part
//                     case 5  returns decrease value in each month for housing provident part
double calculator::paymentInFirstMonth_fixedBasis(int i)
{
    double loanPriodByMonth, paymentInFirstMonth,
        Cur_loanPeriod, Cur_interestRate, Cur_homePrice;
    switch (i)
    {
    case 0:
        Cur_interestRate = this->interestRate;
        Cur_homePrice = this->totalAmount;
        Cur_loanPeriod = this->loanPeriod;
        break;
    case 1:
        Cur_interestRate = this->interestRate_CM;
        Cur_homePrice = this->totalAmount_CM;
        Cur_loanPeriod = this->loanPeriod_2;
        break;
    case 2:
        Cur_interestRate = this->interestRate_PF;
        Cur_homePrice = this->totalAmount_PF;
        Cur_loanPeriod = this->loanPeriod_2;
        break;
    }
    loanPriodByMonth = Cur_loanPeriod * 12;
    double monthlyInterestRate = Cur_interestRate / 12 / 100;
    double monthlyprinciple = Cur_homePrice / loanPriodByMonth;
    if (i == 3 && loanType == SINGLE)
        return (totalAmount / (loanPeriod * 12)) * (interestRate / 12 / 100);
    if (i == 4 && loanType == MIXED)
        return ((totalAmount_CM / (loanPeriod_2 * 12)) * (interestRate_CM / 12 / 100));
    if (i == 5 && loanType == MIXED)
        return ((totalAmount_PF / (loanPeriod_2 * 12)) * (interestRate_PF / 12 / 100));
    double currentIntrest = Cur_homePrice * monthlyInterestRate;
    paymentInFirstMonth = monthlyprinciple + currentIntrest;
    return paymentInFirstMonth;
}

double calculator::refreshDisplay_line()
{
    switch (repaymentMethod)
    {
    case FIXED_PAYMENT:
        return paymentInFirstMonth_fixedPayment();
        break;
    case FIXED_BASIS:
        return paymentInFirstMonth_fixedBasis();
        break;
    }
    return 0;
}
double calculator::refreshDisplay_line2()
{
    double payment = 0;
    switch (repaymentMethod)
    {
    case FIXED_PAYMENT:
        payment = paymentInFirstMonth_fixedPayment(1) + paymentInFirstMonth_fixedPayment(2);
        break;
    case FIXED_BASIS:
        payment = paymentInFirstMonth_fixedBasis(1) + paymentInFirstMonth_fixedBasis(2);
        break;
    }
    return payment;
}

void calculator::calculateTableValue()
{
    schedule.clear();
    int loanPriodByMonth;
    double monthlyPayment, monthlyInterestRate, remainingPriciple;

    remainingPriciple = totalAmount;
    loanPriodByMonth = loanPeriod * 12;
    monthlyInterestRate = interestRate / 12 / 100;
    eachMonth cur;
    switch (repaymentMethod)
    {
    case FIXED_PAYMENT:

        if (loanType == SINGLE)
        {
            monthlyPayment = paymentInFirstMonth_fixedPayment(0);

            for (int i = 0; i < loanPriodByMonth; i++)
            {
                cur.total = monthlyPayment;
                cur.intrest = remainingPriciple * monthlyInterestRate;
                cur.principle = monthlyPayment - cur.intrest;
                remainingPriciple -= cur.principle;
                schedule.push_back(cur);
            }
        }
        else if (loanType == MIXED)
        {
            double monthlyPayment1, monthlyPayment2, monthlyInterestRate1, monthlyInterestRate2,
                remainingPriciple1, remainingPriciple2;
            int loanPriodByMonth2;
            monthlyPayment1 = paymentInFirstMonth_fixedPayment(1);
            monthlyPayment2 = paymentInFirstMonth_fixedPayment(2);
            remainingPriciple1 = totalAmount_CM;
            remainingPriciple2 = totalAmount_PF;
            monthlyInterestRate1 = interestRate_CM / 12 / 100;
            monthlyInterestRate2 = interestRate_PF / 12 / 100;
            loanPriodByMonth2 = this->loanPeriod_2 * 12;

            for (int i = 0; i < loanPriodByMonth2; i++)
            {
                cur.total = monthlyPayment1 + monthlyPayment2;
                cur.intrest = remainingPriciple1 * monthlyInterestRate1 + remainingPriciple2 * monthlyInterestRate2;
                cur.principle = cur.total - cur.intrest;
                remainingPriciple1 = remainingPriciple1 - (monthlyPayment1 - remainingPriciple1 * monthlyInterestRate1);
                remainingPriciple2 = remainingPriciple2 - (monthlyPayment2 - remainingPriciple2 * monthlyInterestRate2);
                schedule.push_back(cur);
            }
        }

        break;

    case FIXED_BASIS:

        if (loanType == SINGLE)
        {

            double monthlyprinciple = totalAmount / loanPriodByMonth;
            double currentIntrest = remainingPriciple * monthlyInterestRate;
            double monthlyReducedInterest = monthlyprinciple * monthlyInterestRate;
            for (int i = 0; i < loanPriodByMonth; i++)
            {
                cur.principle = monthlyprinciple;
                cur.intrest = currentIntrest;
                cur.total = cur.principle + cur.intrest;
                schedule.push_back(cur);
                currentIntrest -= monthlyReducedInterest;
            }
        }
        else if (loanType == MIXED)
        {
            double monthlyInterestRate1, monthlyInterestRate2,
                remainingPriciple1, remainingPriciple2;
            int loanPriodByMonth2 = loanPeriod_2 * 12;
            double monthlyprinciple1 = totalAmount_CM / loanPriodByMonth2;
            double monthlyprinciple2 = totalAmount_PF / loanPriodByMonth2;
            remainingPriciple1 = this->totalAmount_CM;
            remainingPriciple2 = this->totalAmount_PF;
            monthlyInterestRate1 = this->interestRate_CM / 12 / 100;
            monthlyInterestRate2 = this->interestRate_PF / 12 / 100;
            double currentIntrest1 = remainingPriciple1 * monthlyInterestRate1;
            double currentIntrest2 = remainingPriciple2 * monthlyInterestRate2;
            double monthlyReducedInterest1 = monthlyprinciple1 * monthlyInterestRate1;
            double monthlyReducedInterest2 = monthlyprinciple2 * monthlyInterestRate2;
            for (int i = 0; i < loanPriodByMonth2; i++)
            {
                cur.principle = monthlyprinciple1 + monthlyprinciple2;
                cur.intrest = currentIntrest1 + currentIntrest2;
                cur.total = cur.principle + cur.intrest;
                schedule.push_back(cur);
                currentIntrest1 -= monthlyReducedInterest1;
                currentIntrest2 -= monthlyReducedInterest2;
            }
        }

        break;
    }
}

void calculator::setRepaymentMethod(int method)
{
    this->repaymentMethod = method;
}
void calculator::setloanType(int type)
{
    this->loanType = type;
}
void calculator::setInterestRate(double rate)
{
    this->interestRate = rate;
}
void calculator::setLoanPeriod(int period)
{
    this->loanPeriod = period;
}

void calculator::setInterestRate_CM(double i)
{
    this->interestRate_CM = i;
}
void calculator::setInterestRate_PF(double i)
{
    this->interestRate_PF = i;
}
void calculator::setHomePrice_CM(double i)
{
    this->totalAmount_CM = i;
}
void calculator::setHomePrice_PF(double i)
{
    this->totalAmount_PF = i;
}
void calculator::setLoanPeriod_2(int i)
{
    this->loanPeriod_2 = i;
}

void calculator::setTotalAmount(double homePrice)
{

    this->totalAmount = homePrice;
}

int calculator::getLoantype()
{
    return loanType;
}
int calculator::getRepaymentMethod()
{
    return this->repaymentMethod;
}

double calculator::getProportion_interest1()
{
    double ans = 0;
    switch (repaymentMethod)
    {
    case FIXED_PAYMENT:
        ans = paymentInFirstMonth_fixedPayment() * loanPeriod * 12 - totalAmount;
        break;
    case FIXED_BASIS:
        double a1 = paymentInFirstMonth_fixedBasis();
        double n = loanPeriod * 12;
        double d = -paymentInFirstMonth_fixedBasis(3);
        ans = n * (2 * a1 + (n - 1) * d) / 2;
        ans = ans - totalAmount;
        break;
    }
    ans = ans / (totalAmount + ans);
    return ans;
}
double calculator::getProportion_interest2()
{
    double ans1 = 0, ans2 = 0;
    switch (repaymentMethod)
    {
    case FIXED_PAYMENT:
        ans1 = paymentInFirstMonth_fixedPayment(1) * loanPeriod_2 * 12 - totalAmount_CM;
        ans2 = paymentInFirstMonth_fixedPayment(2) * loanPeriod_2 * 12 - totalAmount_PF;
        break;
    case FIXED_BASIS:
        double a1_1 = paymentInFirstMonth_fixedBasis(1);
        double a1_2 = paymentInFirstMonth_fixedBasis(2);
        double d1 = -paymentInFirstMonth_fixedBasis(4);
        double d2 = -paymentInFirstMonth_fixedBasis(5);
        double n = loanPeriod_2 * 12;
        ans1 = n * (2 * a1_1 + (n - 1) * d1) / 2;
        ans1 = ans1 - totalAmount_CM;
        ans2 = n * (2 * a1_2 + (n - 1) * d2) / 2;
        ans2 = ans2 - totalAmount_PF;
        break;
    }

    return ((ans1 + ans2) / (totalAmount_CM + totalAmount_PF + ans1 + ans2));
}
int calculator::getLoanPeriod()
{
    return this->loanPeriod;
}
int calculator::getLoanPeriod_2()
{
    return this->loanPeriod_2;
}

eachMonth calculator::getTableValue(int i)
{
    return this->schedule[i];
}
