package avalanche;
import java.sql.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;

public class Main {
   public static void main(String[] args) {
       ArrayList<Debt> allDebts = new ArrayList<>();

       Scanner in = new Scanner(System.in);
       System.out.println("Amount for bills: ");
       double amtForBills = in.nextDouble();

       //While there are debts
       while(in.hasNext()) {
           allDebts.add(getInput());
       }
       Collections.sort(allDebts); //sort lowest to highest
       Collections.reverse(allDebts); //set highest to lowest
       
       output(allDebts, amtForBills);


   }

   public static Debt getInput() {
       Scanner input = new Scanner(System.in);
       System.out.println("Name");
       String inputName = input.nextLine();
       System.out.println("interest");
       double interest = input.nextDouble();
       System.out.println("monthly");
       double monthlyAmmount = input.nextDouble();
       System.out.println("total");
       double totalAmmount = input.nextDouble();
       return new Debt(inputName, interest, monthlyAmmount, totalAmmount);
   }
   
   public static double getPayAmmount(ArrayList<Debt> allDebt, double totalToPay) {
	   for(int i = 0; i < allDebt.size(); i++)
		   totalToPay -= allDebt.get(i).getOwedMonthly();
		return totalToPay;
   }
   
   public static void output(ArrayList<Debt> allDebt, double totalToPay) {
	   double extraCash = getPayAmmount(allDebt, totalToPay);
	   for (int i = 0; i < allDebt.size(); i++) {
		   System.out.println(allDebt.get(i));
		   if(extraCash > 0) { //if there is extra money
			   if(i == 0)
				   System.out.println("Pay: " + (allDebt.get(i).getOwedMonthly() + extraCash));
			   else
				   System.out.println("Pay: " + allDebt.get(i).getOwedMonthly());
		   }
		   else if(extraCash < 0) { //not enough to pay debts
			   System.out.println("Error");
		   }
		   else { //perfect ammount to pay debts
			   System.out.println("Pay: " + allDebt.get(i).getOwedMonthly());
		   }
	}
   }