// Xiangjun Peng 6522056

import java.util.*;

class InsertionSort {

	public static void main(String[] args) {

		// Check the validiaty of input
		if (args.length != 1) {
			
			// Generate prompt information if the input size is correct
			System.out.println("Usage: java main n"+"\n"
					   +"n stands for the expected number to test");

		} else {
		
			try {

				int num = Integer.parseInt(args[0]);

				InsertSort example = new InsertSort(num);

				// Print the array before sorting
				example.ShowState();

				// Sort by insertion sort method
				example.Sort();

				// Print the array after sorting
				example.ShowState();
	
			} catch (NumberFormatException e) {

				// This exception aims to deal with the format of input
			
				System.out.println("Usage: java main n"+"\n"
						   +"n stands for the expected number to test\n");

				System.out.println("Please enter an integer");
			
			}

		}

	}

}
