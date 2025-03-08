#include<iostream>
#include<cstring>
using namespace std;
//zad12 ispitni/kolokviumski eng
class InvestmentPlan {
private:
    char name[80];
    double sumInvesment;
    double shares;
    bool paymentDay; //true - current day payment, false - old payment
public:
    InvestmentPlan(const char *name = "", double sumInvestment = 0.0, double shares = 0.0, bool paymentDay = false) {
        strcpy(this->name, name);
        this->sumInvesment = sumInvestment;
        this->shares = shares;
        this->paymentDay = paymentDay;
    }

    const char *getName() {
        return name;
    }

    double getSumInvesment() {
        return sumInvesment;
    }

    double getShares() {
        return shares;
    }

    bool getPaymentDay() {
        return paymentDay;
    }

    void setName(const char *name) {
        strcpy(this->name, name);
    }

    void setSumInvesment(double sumInvesment) {
        this->sumInvesment = sumInvesment;
    }

    void setShares(double shares) {
        this->shares = shares;
    }

    void setPaymentDay(bool paymentDay) {
        this->paymentDay = paymentDay;
    }
};

class InvestmentFund {
private:
    char nameFund[50];
    InvestmentPlan *investmentPlans;
    int numInvestments;
    double priceShares;

public:
    InvestmentFund(const char *name = "", InvestmentPlan *investment = nullptr, int numInvestments = 0,
                   double priceShares = 0.0) {
        strcpy(this->nameFund, name);
        this->numInvestments = numInvestments;
        this->priceShares = priceShares;
        this->investmentPlans = new InvestmentPlan[numInvestments];
        for (int i = 0; i < numInvestments; i++) {
            investmentPlans[i] = investment[i];
        }
    }

    virtual double profit() const = 0;


    const char *getNameFund() const {
        return nameFund;
    }

    InvestmentPlan *getInvestmentPlans() const {
        return investmentPlans;
    }

    int getNumInvestments() const {
        return numInvestments;
    }

    double getPriceShares() const {
        return priceShares;
    }

    virtual ~InvestmentFund() {
        delete[] investmentPlans;
    }
};

class MoneyFund : public InvestmentFund {
private:
    static const double provisionYearly;

public:
    MoneyFund(const char *name = "", InvestmentPlan *investment = nullptr, int numInvestments = 0,
              double priceShares = 0.0) : InvestmentFund(name, investment, numInvestments, priceShares) {
    }

    double profit() const override {
        double totalSum = 0;
        for (int i = 0; i < getNumInvestments(); ++i) {
            totalSum += getInvestmentPlans()[i].getSumInvesment();
        }
        return (totalSum * provisionYearly / 100.0) / 365.0;
    }
};

class ActionFund : public InvestmentFund {
private:
    static const double provisionYearly;
    static const double provisionEntry;

public:
    ActionFund(const char *name = "", InvestmentPlan *investment = nullptr, int numInvestments = 0,
               double priceShares = 0.0) : InvestmentFund(name, investment, numInvestments, priceShares) {
    }

    double profit() const override {
        double totalSum = 0;
        double newPlansSum = 0;

        for (int i = 0; i < getNumInvestments(); i++) {
            double investment = getInvestmentPlans()[i].getSumInvesment();
            totalSum += investment;
            if (getInvestmentPlans()[i].getPaymentDay()) {
                newPlansSum += investment;
            }
        }

        return (totalSum * provisionYearly / 100.0) / 365.0 +
               (newPlansSum * provisionEntry / 100.0);
    }
};


const double MoneyFund::provisionYearly = 1.0;

const double ActionFund::provisionYearly = 1.5;
const double ActionFund::provisionEntry = 3.0;


double totalProfit(InvestmentFund **funds, int n) {
    double totalProfit = 0;
    for (int i = 0; i < n; i++) {
        totalProfit += funds[i]->profit();
    }
    return totalProfit;
}

int main() {
    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for (int j = 0; j < m; j++) {
            cin >> investitor >> plan >> brUdeli;
            if (j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if (i % 2) {
            fondovi[i] = new ActionFund(ime, ip, m, udel);
        } else {
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
