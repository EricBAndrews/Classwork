package hw4;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

import org.junit.AfterClass;
import org.junit.Test;

public class BigMergeTest {
	
	public static int finalBMPoints = 0;
	
	@Test
	public void testBigMerge1() {
		
		int points = 10;

		int[][] test = {{1,3,5,6,7}};
		int[] expected = {1,3,5,6,7};
		int[] result = BigMerge.merge(test);

		boolean success = Arrays.equals(result, expected);

		if (success) {
			finalBMPoints += 10;
		} else System.out.println("MARK DEDUCTION: BigMerge fails on {{1,3,5,6,7}}!\ndeduct:10");
		assertEquals("BigMerge executed on Test1", true, success);
	}
	
	@Test(timeout=1000)
	public void testBigMerge2() {

		int[][] test = {};
		int[] expected = {};
		int[] result = BigMerge.merge(test);

		boolean success = Arrays.equals(result, expected);

		if (success) {
			finalBMPoints += 6;
		} else System.out.println("MARK DEDUCTION: BigMerge fails on {}!\ndeduct:6");
		assertEquals("BigMerge executed on Test2", true, success);
	}
	
	@Test(timeout=1000)
	public void testBigMerge3() {

		int[][] test = {{0,5,10,15,20},{1,6,11},{12},{3,8,13,18,23,28}};
		int[] expected = {0,1,3,5,6,8,10,11,12,13,15,18,20,23,28};
		int[] result = BigMerge.merge(test);

		boolean success = Arrays.equals(result, expected);

		if (success) {
			finalBMPoints += 6;
		} else System.out.println("MARK DEDUCTION: BigMerge fails on {{0,5,10,15,20},{1,6,11},{12},{3,8,13,18,23,28}}!\ndeduct:6");
		assertEquals("BigMerge executed on Test3", true, success);
	}
	
	@Test(timeout=1000)
	public void testBigMerge4() {

		int[][] test = {{},{1,6,11},{12},{3,8,13,18,23,28}};
		int[] expected = {1,3,6,8,11,12,13,18,23,28};
		int[] result = BigMerge.merge(test);

		boolean success = Arrays.equals(result, expected);

		if (success) {
			finalBMPoints += 6;
		} else System.out.println("MARK DEDUCTION: BigMerge fails on {{},{1,6,11},{12},{3,8,13,18,23,28}}!\ndeduct:6");
		assertEquals("BigMerge executed on Test4", true, success);
	}
	
	@Test(timeout=1000)
	public void testBigMerge5() {

		int[][] test = {{0,1,5,6},{1},{0},{6},{2,Integer.MAX_VALUE}};
		int[] expected = {0, 0, 1, 1, 2, 5, 6, 6, Integer.MAX_VALUE};
		int[] result = BigMerge.merge(test);

		boolean success = Arrays.equals(result, expected);

		if (success) {
			finalBMPoints += 6;
		} System.out.println("MARK DEDUCTION: BigMerge fails on {{0,1,5,6},{1},{0},{6},{2, Integer.MAX_VALUE}}!\ndeduct:6");
		assertEquals("BigMerge executed on Test4", true, success);
	}
	
	@Test(timeout=1000)
	public void testBigMerge6() {

		int[][] test = {{Integer.MAX_VALUE},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11},{-1},{-11},{9},{21},{},{Integer.MIN_VALUE,-10,0,10,20,Integer.MAX_VALUE}};
		int[] expected = {Integer.MIN_VALUE, -11, -10, -1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 10, 11, 20, 21, Integer.MAX_VALUE, Integer.MAX_VALUE};
		int[] result = BigMerge.merge(test);

		boolean success = Arrays.equals(result, expected);

		if (success) {
			finalBMPoints += 6;
		} else System.out.println("MARK DEDUCTION: BigMerge fails on {{Integer.MAX_VALUE},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11},{-1},{-11},{9},{21},{},{Integer.MIN_VALUE,-10,0,10,20,Integer.MAX_VALUE}}!\n deduct:6");
		assertEquals("BigMerge executed on Test4", true, success);
	}
	
	public static int testArgMin() {
		
		int points = 0;
		
		int[][] test = {{Integer.MAX_VALUE},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11},{-1},{-11},{9},{21},{},{Integer.MIN_VALUE,-10,0,10,20,Integer.MAX_VALUE}};
		int[] testIndex = new int[test.length];
		boolean success = (BigMerge.argMin(test,testIndex) == 7);
		if (success) points += 4;
		
		test = new int[][]{{0,1,5,6},{1},{0},{6},{2,Integer.MAX_VALUE}};
		testIndex = new int[]{2,1,1,0,0};
		success = (BigMerge.argMin(test,testIndex) == 4 );
		if (success) points += 4;
		
		test = new int[][]{{1,3,5,6,7}};
		testIndex = new int[3];
		success = (BigMerge.argMin(test,testIndex) == 0 );
		if (success) points += 4;
		
		test = new int[][]{{},{1,6,11},{12},{3,8,13,18,23,28}};
		testIndex = new int[]{0,1,0,0};
		success = (BigMerge.argMin(test,testIndex) == 3);
		if (success) points += 4;
		
		test = new int[][]{{-10,-5,0,10,15,20},{-1,6,11},{-12},{-3,8,13,18,23,28}};;
		testIndex = new int[]{2,0,1,1};
		success = (BigMerge.argMin(test,testIndex) == 1);
		if (success) points += 4;
		
		return points;
	}
	
	@AfterClass
	public static void finalTest() throws IOException {

		if (finalBMPoints < 20) {
			System.out.println("Testing argMin in event of low score in Big Merge...");
			int argMinPoints = testArgMin();
			if (argMinPoints > finalBMPoints)
				finalBMPoints = argMinPoints;
		}
		String fileName = "hw4" + File.separatorChar + "points.txt";
		File file = new File(fileName);
		FileWriter writer = new FileWriter(file);
		System.out.println("\n\nFINAL SCORE FOR BigMerge:" + finalBMPoints + "\n");
		writer.write(""+finalBMPoints);
		writer.close();
		
	}

}
