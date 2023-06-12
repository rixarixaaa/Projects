package avalanche;
import java.text.*;

public class Debt implements Comparable<Debt> {
    String debtName;
    double interest;
    double owedMonthly;
    double totalOwed;
    //boolean isAnnual = true;
    //int perMonth = 12;
    
    public Debt() {
        this("Null", -1, -1, -1);
    }
    public Debt(String dname, double intrst, double monthly, double total) {
        debtName = dname;
        interest = intrst;
        owedMonthly = monthly;
        totalOwed = total;
        //isAnnual = annl;
        //perMonth = pmnth;
    }
//Getters----------------------------------------------------------------------------------------------------------
    public String getDebtName() {
        return debtName;
    }
    
    public double getInterest() {
        return interest;
    }
    
    public double getTotalOwed() {
       return owedMonthly;
    }
    
    public double getOwedMonthly() {
        return owedMonthly;
    }
    
 /*   public int getPerMonth() {
        return perMonth;
    }
    
    public boolean isAnnual() {
        return isAnnual;
    } */
    
    @Override
    public int compareTo(Debt o) {
        return Double.compare(interest, o.getInterest());
    }
    
    @Override
    public String toString() {
        NumberFormat threeZeros = new DecimalFormat("#0.000");
        NumberFormat twoZeros = new DecimalFormat("#0.00");
        return "Owed To: " + debtName + " Interest: " + threeZeros.format(interest) + "% Total Owed: " + twoZeros.format(totalOwed) + " Monthly Owed: " + twoZeros.format(owedMonthly);
    }
//Getters----------------------------------------------------------------------------------------------------------
//Setters----------------------------------------------------------------------------------------------------------
    public void setDebtName(String debtName) {
        this.debtName = debtName;
    }

    public void setInterest(double interest) {
        this.interest = interest;
    }

    public void setOwedMonthly(double owed) {
        this.owedMonthly = owed;
    }
    
    public void setTotalOwed(double total) {
        owedMonthly = total;
    }

 /*   public void setAnnual(boolean annual) {
        isAnnual = annual;
    }

    public void setPerMonth(int perMonth) {
        this.perMonth = perMonth;
    } */
//Setters----------------------------------------------------------------------------------------------------------
}