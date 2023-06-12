/**
 * Name: Parisa Nawar
 * NetID: pxn210032
 */

import java.util.Scanner;
import java.util.*;
import java.io.*;
import java.lang.Math;

public class Main
{

  public static void main(String[]args) throws IOException
  {
    Scanner input = new Scanner(System.in);

    String fileName = input.nextLine();

    File file = new File(fileName);

    String[] results = battingRecord(file); // The records are parsed into an array so each stat can access individual data
    
    BufferedWriter bufferWriter = new BufferedWriter(new FileWriter(file, true));
    bufferWriter.close();
    
    // Each calculation is passed onto individual arrays as numbers achieved.
    String[] DN = displayName(file);
    int[] AB = atBat(results, hits (results), outs (results), strikeouts (results));
    double[] BA = battingAverage(results, hits (results), AB);
    double[] OBP = oBasePercent(results, hits (results), walks (results), hitsBPitch (results), plateApps (results));
    int[] H = hits(results);
    int[] BB = walks(results);
    int[] HBP = hitsBPitch(results);
    int[] K = strikeouts(results);
    
    for (int t = 0; t < results.length; t++) // Loops to print the stats for each player, also formats the text
    {
    	System.out.println (DN[t]);
	    System.out.printf ("BA: %.3f", BA[t]);
	    System.out.println ();
    	System.out.printf ("OB%%: %.3f", OBP[t]);
	    System.out.println ();
    	System.out.println ("H: " + H[t]);
    	System.out.println ("BB: " + BB[t]);
    	System.out.println ("K: " + K[t]);
    	System.out.println ("HBP: " + HBP[t]);
    	System.out.println ();
    }

    // Find leaders of each stat
    System.out.println("LEAGUE LEADERS");
    
    // Batting Average leaders 
    System.out.print("BA: ");
    int[] leadBA = findLeadersIndexes(BA);
    System.out.print(DN[leadBA[0]]);
    
    for(int i = 1; i < leadBA.length; i++) // Format and print out names of highest batting averages
    {
        System.out.print(", " + DN[leadBA[i]]);
    } 
    System.out.printf(" %.3f\r\n", BA[leadBA[0]]); // Format and print the highest batting average
    
    // On Base Percentage leaders
    System.out.print("OB%: "); 
    int[] leadOBP = findLeadersIndexes(OBP);
    System.out.print(DN[leadOBP[0]]);
    
    for(int i = 1; i < leadOBP.length; i++) // Format and print out names of highest on base percentage
    {
        System.out.print(", " + DN[leadOBP[i]]);
    }
    System.out.printf(" %.3f\r\n", OBP[leadOBP[0]]); // Format and print the highest on base percentage
    
    // Hits leaders
    System.out.print("H: ");
    int[] leadH = findLeadersIndexes(H);
    System.out.print(DN[leadH[0]]);
    
    for(int i = 1; i < leadH.length; i++) // Format and print out names of highest hits
    {
        System.out.print(", " + DN[leadH[i]]);
    }
    System.out.println(" " + H[leadH[0]]); // Format and print the highest hit
    
    // Walks leaders
    System.out.print("BB: ");
    int[] leadBB = findLeadersIndexes(BB);
    System.out.print(DN[leadBB[0]]);
    
    for(int i = 1; i < leadBB.length; i++) // Format and print out names of highest walks
    {
        System.out.print(", " + DN[leadBB[i]]);
    }
    System.out.println(" " + BB[leadBB[0]]); // Format and print out highest walk
    
    // Strikeouts leaders
    System.out.print("K: ");
    int[] leadK = findLeadersIndexesK(K);
    System.out.print(DN[leadK[0]]);
    
    for(int i = 1; i < leadK.length; i++) // Format and print out names of lowest strikeouts
    {
        System.out.print(", " + DN[leadK[i]]);
    }
    System.out.println(" " + K[leadK[0]]); // Format and print out lowest strikeout
    
    // Hit By Pitch leaders
    System.out.print("HBP: ");
    int[] leadHBP = findLeadersIndexes(HBP);
    System.out.print(DN[leadHBP[0]]);
    
    for(int i = 1; i < leadHBP.length; i++) // Format and print out names of highest hit by pitches
    {
        System.out.print(", " + DN[leadHBP[i]]);
    }
    System.out.print(" " + HBP[leadHBP[0]]); // Format and print out highest hit by pitch
  }
  
  /**
   * Function findLeadersIndexes takes an integer stat array, loops and sorts it from highest to lowest in a list,
   * converts the list into an array, loops the sorted list to compare to the original array 
   * to find the original indexes of the leaders.
   */
  public static int[] findLeadersIndexes(int[] stats)
  {
    List<Integer> leaderIndex = new ArrayList<Integer>();
    List<Integer> leaderStat = new ArrayList<Integer>();
    
    int lead = stats[0];
    
    for(int i = 0; i < stats.length; i++) // sorts the stats from highest to lowest
    {
        if(stats[i] >= stats[0])
        {
            leaderStat.add(0, stats[i]);
        }
    }
    
    int[] listStats = leaderStat.stream().mapToInt(Integer::intValue).toArray(); // converts the sorted list into an array
    

    for(int j = 0; j < stats.length; j++) // compares original array to create list with original indexes
    {
        if(listStats[0] == stats[j])
        {
            leaderIndex.add(j);
        }
    }
        
    int[] listIndex = leaderIndex.stream().mapToInt(Integer::intValue).toArray(); // turns the index list into array
    
    return listIndex;
  }
  
  /**
   * Function findLeadersIndexesK takes the strikeout array, loops and sorts it from lowest to highest in a list,
   * converts the list into an array, loops the sorted list to compare to the original array 
   * to find the original indexes of the leaders.
   */
  public static int[] findLeadersIndexesK(int[] stats)
  {
    List<Integer> leaderIndex = new ArrayList<Integer>();
    List<Integer> leaderStat = new ArrayList<Integer>();
    
    int lead = stats[0];
    
    for(int i = 0; i < stats.length; i++) // sorts the stats from lowest to highest
    {
        if(stats[i] <= stats[0])
        {
            leaderStat.add(0, stats[i]);
        }
    }
    
    int[] listStats = leaderStat.stream().mapToInt(Integer::intValue).toArray(); // converts the sorted list into an array
    

    for(int j = 0; j < stats.length; j++) // compares original array to create list with original indexes
    {
        if(listStats[0] == stats[j])
        {
            leaderIndex.add(j);
        }
    }
        
    int[] listIndex = leaderIndex.stream().mapToInt(Integer::intValue).toArray(); // turns the index list into array
    
    return listIndex;
  }
  
  /**
   * Function findLeadersIndexes takes a double array, loops and sorts it from highest to lowest in a list,
   * converts the list into an array, loops the sorted list to compare to the original array 
   * to find the original indexes of the leaders.
   */
  public static int[] findLeadersIndexes(double[] stats)
  {
    List<Integer> leaderIndex = new ArrayList<Integer>();
    List<Double> leaderStat = new ArrayList<Double>();
    
    double lead = stats[0];
    
    for(int i = 0; i < stats.length; i++) // sorts the stats from highest to lowest
    {
        if(stats[i] >= stats[0])
        {
            leaderStat.add(0, stats[i]);
        }
    }
    
    double[] listStats = leaderStat.stream().mapToDouble(Double::doubleValue).toArray(); // converts the sorted list into an array
    

    for(int j = 0; j < stats.length; j++) // compares original array to create list with original indexes
    {
        if(listStats[0] == stats[j])
        {
            leaderIndex.add(j);
        }
    }
        
    int[] listIndex = leaderIndex.stream().mapToInt(Integer::intValue).toArray(); // turns the index list into array
    
    return listIndex; 
  } 
  
  /**
   * Function displayName takes the first word of each line in the file, and puts it
   * into a string array with the names with the order they were at.
   */
  public static String[] displayName(File f) throws FileNotFoundException
  {
    String name;

    Scanner inputFile = new Scanner(f);

    List<String>listOfNames = new ArrayList<String>();

    while(inputFile.hasNext()) // takes the name from each line while skipping over the scores
    {
	    name = inputFile.next();
    	inputFile.nextLine();
    	listOfNames.add(name);
    }

    String[] listNames = listOfNames.toArray(new String[0]);

    return listNames;
  }
  
  /**
   * Function battingRecord parses the scores from the original file so that 
   * they can be used for calculations.
   */
  public static String[] battingRecord(File f) throws FileNotFoundException
  {
    String record;

    Scanner inputFile = new Scanner(f);

    List<String> listOfRecords = new ArrayList<String>();

    while(inputFile.hasNext()) // takes the scores and puts them into the same indexes as the names
    {
        inputFile.next();
	    record = inputFile.nextLine();
	    listOfRecords.add(record);
    }

    String[] listRecords = listOfRecords.toArray(new String[0]);

    return listRecords;
    
  }
  
  /**
   * Function atBat calculats the at bat by adding hits, outs, and strikeouts of each players
   * and puts each total into the array by the respective indexes of the players.
   */
  public static int[] atBat(String[]r, int[]hits, int[]outs, int[]strikeouts)
  {

    int[] listAtBat = new int[r.length];

    for (int i = 0; i < r.length; i++)
    {
        listAtBat[i] = hits[i] + outs[i] + strikeouts[i];
    }

    return listAtBat;
  }
  
  /**
   * Function battingAverage calculates the batting average by dividing hits by at bat,
   * and puts each calculation into the array by the respective indexes of the players.
   */
  public static double[] battingAverage(String[]r, int[]hits, int[]atBat)
  {
    double[] listBattingAverage = new double[r.length];

    for(int i = 0; i < r.length; i++)
    {
	    listBattingAverage[i] = (double) hits[i] / atBat[i];
    }

    return listBattingAverage;
  }
  
  /**
   * Function oBasePercent calculates the on base percent by adding hits, walks, and hits
   * by pitch, totals them and divides them by plate appearences, then puts 
   * each calculation into the array by the respective indexes of the players.
   */
  public static double[] oBasePercent(String[]r, int[]hits, int[]walks, int[]hitsBPitch, int[]plateApps)
  {
    double[] listOBasePercent = new double[r.length];

    for (int i = 0; i < r.length; i++)
    {
	    listOBasePercent[i] = (((double)hits[i]) + walks[i] + hitsBPitch[i]) / plateApps[i];
    }

    return listOBasePercent;
  }
  
  /**
   * Function plateApps calculates the number of times the player has appeared on
   * field by looping through each letter of the score and counting how many there are.
   */
  public static int[] plateApps(String[]r)
  {
    int apps = 0;

    int[] listApps = new int[r.length];

    for(int i = 0; i < r.length; i++)
    {
	    listApps[i] = r[i].length() - 1;
    }

    return listApps;
  }
  
  /**
   * function hits calculates the amount of hits per player by counting the 'H' of each player 
   * and putting into an array.
   */
  public static int[] hits(String[]r)
  {
    int h = 0;

    int[] listHits = new int[r.length];

    for (int i = 0; i < r.length; i++)
    {
	    h = 0;
	    for (int j = 0; j < r[i].length (); j++)
	    {
	        if (r[i].charAt (j) == 'H')
	        {
	            h++;
	        }
	    listHits[i] = h;
	    }
    }

    return listHits;
  }
  
  /**
   * function outs calculates the amount of outs per player by counting the 'O' of each player 
   * and putting into an array.
   */
  public static int[] outs(String[]r)
  {
    int o = 0;

    int[] listOuts = new int[r.length];

    for (int i = 0; i < r.length; i++)
    {
	    o = 0;
	    for (int j = 0; j < r[i].length (); j++)
	    {
	        if (r[i].charAt (j) == 'O')
	        {
	            o++;
	        }
	        
	        listOuts[i] = o;
	    }
    }

    return listOuts;
  }
  
  /**
   * function strikeouts calculates the amount of strikeouts per player by counting the 'K' of each player 
   * and putting into an array.
   */
  public static int[] strikeouts(String[]r)
  {
    int k = 0;

    int[] listStrikeouts = new int[r.length];

    for(int i = 0; i < r.length; i++)
    {
	    k = 0;
	    for (int j = 0; j < r[i].length (); j++)
	    {
	        if (r[i].charAt (j) == 'K')
	        {
	        	k++;
	        }
	        
	        listStrikeouts[i] = k;
	    }
    }

    return listStrikeouts;
  }
  
  /**
   * function walks calculates the amount of walks per player by counting the 'W' of each player 
   * and putting into an array.
   */
  public static int[] walks(String[]r)
  {
    int w = 0;

    int[] listWalks = new int[r.length];

    for(int i = 0; i < r.length; i++)
    {
	    w = 0;
	    for (int j = 0; j < r[i].length (); j++)
	    {
	        if (r[i].charAt (j) == 'W')
	        {
	        	w++;
	        }
	        
	        listWalks[i] = w;
	    }
    }

    return listWalks;
  }
  
  /**
   * function hitsBPitch calculates the amount of hits by pitch per player by counting the 'P' of each player 
   * and putting into an array.
   */
  public static int[] hitsBPitch(String[]r)
  {
    int p = 0;

    int[] listBPitch = new int[r.length];

    for(int i = 0; i < r.length; i++)
    {
	    p = 0;
	    for (int j = 0; j < r[i].length (); j++)
	    {
	        if (r[i].charAt (j) == 'P')
	        {
		        p++;
	        }
	        listBPitch[i] = p;
	    }
    }

    return listBPitch;
  }

}
