// 6522056 zy22056 Xiangjun Peng

// All neccessary parts are imported in next following lines.

import java.util.Scanner;
import java.io.*;
import java.util.Arrays;

// Define the DataSample class and methods.

class DataSample {

  // All required variables.

  private int label;
  private int numOfAttributes;
  private double[] attributes;

  // Constructor for DataSample.

  public DataSample(int lb, double[] atr) {

    this.label = lb;

    this.numOfAttributes = atr.length; 

    this.attributes = atr;

  }

  // A method to set a new label with the input lb.

  public void setLabel(int lb) {

    this.label = lb;

    return;

  }

  // A method to get the corresponding DataSample's label.

  public int getLabel() {

    return this.label;
  
  }

  // A method to get the number of the attributes.

  public int getnumOfAttributes() {
 
    return this.numOfAttributes;

  }

  // A method to get all Attributes.

  public double[] getAttributes() {

    return this.attributes;

  }

  // A method to get the i-th attribute.

  public double getAttributes(int i) {

    return this.attributes[i];

  }

  // A method to calculate all other DataSamples' distances from this DataSample dat.
  // By applying the Euclidean distance in this period. 

  public double distance(DataSample dat) {

    double dist = 0, term = 0;

    for (int i = 0; i < dat.getnumOfAttributes(); i++) {

      term = this.attributes[i] - dat.attributes[i];

      dist += Math.pow(term, 2);

    }

    dist = Math.pow(dist, 0.5);

    return dist;

  }

}

// Define the DataSet class.

class DataSet {

  private DataSample[] dataArray;

  // Constructor for DataSet.

  public DataSet(String filename){

    BufferedReader scan = null;
    int size = this.getDataSetSize(filename);

    try {

        scan = new BufferedReader(new FileReader(filename));

        this.dataArray = new DataSample[size];

        String temp = null;
 
        for (int i = 0; i < size; i++) {
 
          temp = scan.readLine();

          if (!(temp.equals(""))) {
          // Avoid blank lines, no matter they are between in the file or in the end.

            String[] Element = temp.split(",");

            if (Element.length != 14) {

              throw new Exception();

            }  

            int lb = Integer.parseInt(Element[0]);

            double[] arAt = new double[13];

            for (int j = 0; j < 13; j++) {
  
              arAt[j] = Double.parseDouble(Element[j+1]);

            }

            this.dataArray[i] = new DataSample(lb,arAt);

          } else {

            i--;
            // Adjust the numbers for the iteration to record information.
           
          }  
  
        } 

        scan.close();

      } catch (Exception ex) { 

        // Here, exception will be catched instead of just IO exceptions,
        // which could catch the exceptions caused by wrong number of attributes
        // and the corresponding values could not be transfered with the standard
        // functions. And they all be treated as "doesn't qualify with the appropriate
        // formats".

        System.out.println(filename + " doesn't qualify with the appropriate formats.");

        if (scan !=  null) {

          try {

            scan.close();

          } catch (IOException ey) {

          }

        }

        System.exit(0);

      } finally {

       if (scan != null ) {

         try {

           scan.close();

         } catch (IOException e) {
           
         }

       }

      }

  }

  // A method to check the size of file named with "filename".

  public int getDataSetSize(String filename) {

    int counter = 0;

    Scanner scan = null;

    try {

       File newfile = new File(filename);

       try {
 
         if (!newfile.exists()) 

            throw new Exception();
     
       } catch (Exception ex) {

          System.out.println(filename + " doesn't exist. ");

          System.exit(0);
 
       }

       scan = new Scanner(newfile);

       while (scan.hasNextLine() == true) {

         String temp = scan.nextLine();
        
         if (!(temp.equals(""))) 
          
           counter++;

       }


     } catch (IOException ex) {

       System.out.println(filename + " couldn't be accessed.");

       if (scan != null) {

         scan.close();

       }      

     }  finally {

       if (scan != null ) {

           scan.close();

       } 

     }
 
   return counter;
 
  }

  // A method to get all means according to different attributes.

  public double[] getMean(int label) {

    double sum = 0, counter  = 0;
    double[] Mean = new double[13];

    for (int i = 0; i < 13; i++) {

      counter = 0; sum = 0;

      for (int j = 0; j < this.dataArray.length; j++) {

        if (this.dataArray[j].getLabel() == label) {

          sum += this.dataArray[j].getAttributes(i);
         
          counter ++;

        }

      }

      Mean[i] = sum / counter;

    }

    return Mean;

  }  
 
  // A method to get all standard derivation values according to different attributes.

  public double[] getStd(int label) {

    double sum = 0, counter = 0;
    double[] Std = new double[13];
    double[] Mean = this.getMean(label);

    for (int i = 0; i < 13; i++) {
 
      counter = 0; sum = 0; 

      for (int j = 0; j < this.dataArray.length; j++) {

        if (this.dataArray[j].getLabel() == label) {

           sum += Math.pow(this.dataArray[j].getAttributes(i) - Mean[i], 2);

           counter ++;

        }
 
      }

      Std[i] = Math.pow(sum / (counter - 1), 0.5);

    }

    return Std;

  }

  // A method to get this DataSet.

  public DataSample[] getDataSet(){

    return dataArray;

  }

  // A method to get i-th DataSample in DataSet. 

  public DataSample getDataSample(int i){

    return dataArray[i];

  }
 
}

// Define DataClassification class which extends the DataSet class

class DataClassification extends DataSet {

  private DataSet newData;

  // Constructor for DataClassification
 
  public DataClassification(String trainfilename, String newdatafilename) {

    super(trainfilename);

    newData = new DataSet(newdatafilename);

  }

  // A method to get new DataSet.

  public DataSet getNewData() {

    return newData;

  }

  // A method to classify DataSample datasp into the class which
  // datasp should belong to. 
  // By apply the method "distance" in DataSample class,
  // the closest one reflects where datasp belongs to.

  public int nnClassification(DataSample datasp) {

    DataSample[] testData = this.getDataSet();
    double distance = datasp.distance(testData[0]);
    int label = testData[0].getLabel(); 

    for (int i = 1; i < testData.length; i++) {

      if (datasp.distance(testData[i]) < distance) {

        distance = datasp.distance(testData[i]);

        label = testData[i].getLabel();

      }

    }

    return label;

  }

}

// Define main class.

class main{

  public static void main(String[] args) {

    DataSet train = new DataSet("wine.txt");
    // Task 1 completed.

    String task2OutputString =
        "Mean of class 1: " + Arrays.toString(train.getMean(1)) + "\n"
      + "Std of class 1: " + Arrays.toString(train.getStd(1)) + "\n"
      + "Mean of class 2: " + Arrays.toString(train.getMean(2)) + "\n"
      + "Std of class 2: " + Arrays.toString(train.getStd(2)) + "\n"
      + "Mean of class 3: " + Arrays.toString(train.getMean(3)) + "\n"
      + "Std of class 3: " + Arrays.toString(train.getStd(3)) + "\n";
    try {
  
      BufferedWriter Task2 = new BufferedWriter(new FileWriter("task2Result.txt"));
   
      Task2.write(task2OutputString);
   
      Task2.close();
    
    } catch (IOException ex) {

    }
    // Task 2 completed.

    DataClassification newtest = new DataClassification("wine.txt","testwine.txt");
    // Task 3 completed.
  
    DataSet testSet = newtest.getNewData();
    int testSize = testSet.getDataSetSize("testwine.txt");
    String task4OutputString = "";

    for (int i = 0; i < testSize; i++) {

      int label = newtest.nnClassification(testSet.getDataSample(i));

      task4OutputString += "The " + Integer.toString(i+1) + "-th new sample belongs to class "
                           + Integer.toString(label) + "\n";
 
    }

    try {

      BufferedWriter Task4 = new BufferedWriter(new FileWriter("task4Result.txt"));

      Task4.write(task4OutputString);

      Task4.close();

    } catch (IOException ex) {

    } 
    // Task 4 completed.
    
  }

}
