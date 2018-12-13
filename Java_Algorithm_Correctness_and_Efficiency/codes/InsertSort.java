// Xiangjun Peng 6522056

import java.util.*;
import java.io.*;

class InsertSort{

	int i,j;
	int[] target;

	
	// Constructor could generate num integers randomly
	public InsertSort(int num) {

		this.target = new int[num];

		Random random = new Random();
		
		for (i = 0; i < num; i++) {
		
			target[i] = random.nextInt();
		
		}

	}

	// Print the array
	public void ShowState() {

		for (i = 0; i < target.length; i++) 

			System.out.print(target[i]+" ");

		System.out.println();

	}

	// Sort by Insertion sorting
	public void Sort() {

		int ToCompare;
		
		try {
		
		// Prepare output, setting true allowed to output without destroying former data
		BufferedWriter out = new BufferedWriter(new FileWriter("out.csv", true));
		
		// Record the beginning time
		long begin = System.nanoTime();

		for (i = 0; i < target.length; i++) {

			ToCompare = target[i];

			j = i -1;

			while ( (j >= 0) && (target[j] > ToCompare)) {

				target[j+1] = target[j];
				
				j--;

			}

			target[j+1] = ToCompare;

		}
		
		// Record the end time.
		long end = System.nanoTime();

		// Output to out.csv
		out.write((end - begin)+",");
		
		out.close();

		} catch (Exception e) {
			
		}
	}
	
}
