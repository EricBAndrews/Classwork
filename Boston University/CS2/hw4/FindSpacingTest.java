package hw4;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Set;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

public class FindSpacingTest {
	
	public static int finalFSPoints = 0;

	
	@BeforeClass
	public static void setUp() throws IOException {
		// Create an empty file
		String fileName = "hw4" + File.separatorChar + "Empty.txt";
		File file = new File(fileName);
		FileWriter writer = new FileWriter(file);
		writer.close();
	}

	// remove duplicates from the array;
	private String[] removeDuplicates(String[] inputArray) {
		Set<String> set = new HashSet<String>(Arrays.asList(inputArray));
		String[] array = set.toArray(new String[set.size()]);
		return array;
	}

	// find extra sentences in the result
	public int findExtras(String[] result, String[] expectedResult) {
		int extraCount = 0;
		Set<String> set = new HashSet<String>(Arrays.asList(expectedResult));
		for (String w : result) {
			if (!set.contains(w))
				extraCount++;
		}
		return extraCount;
	}

	public static String[] readExpectedOutput(String dictionaryFileName) {
		Scanner fileScanner;

		// Open the dictionary file
		try {
			fileScanner = new Scanner(new File(dictionaryFileName));
		} catch (IOException e) {
			System.err.println("Unable to open dictionary file. " + e.getMessage());
			System.err.println("Currently in directory " + System.getProperty("user.dir"));
			return null;
		}

		// read the dictionary file
		LinkedList<String> prelimDict = new LinkedList<String>();
		while (fileScanner.hasNextLine()) {
			prelimDict.add(fileScanner.nextLine().toLowerCase());
		}
		String[] dict = prelimDict.toArray(new String[0]);
		fileScanner.close();
		return dict;
	}

	// find the missing sentences in the result
	public int findMissing(String[] result, String[] expectedResult) {
		int missingCount = 0;
		Set<String> set = new HashSet<String>(Arrays.asList(result));
		for (String w : expectedResult) {
			if (!set.contains(w))
				missingCount++;
		}
		return missingCount;
	}

	@Test(timeout=1000)
	public void testFindSpacing1() {

		String dictionaryFileName = "hw3" + File.separatorChar + "dictionary.txt";
		String[] dict = HW4IO.readDictionary(dictionaryFileName);

		String testStr = "becausetodayuseat";

		String[] result = FindSpacing.space(dict, testStr);
		String[] expectedResult = { "be cause to day us eat ", "be cause to day use at ", "be cause today us eat ",
				"be cause today use at ", "because to day us eat ", "because to day use at ", "because today us eat ",
				"because today use at" };
		
		if (result.length == expectedResult.length) {
			for (int i = 0; i < result.length; i++) {
				result[i] = result[i].trim();
				expectedResult[i] = expectedResult[i].trim();
			}
		}

		Arrays.sort(result);
		Arrays.sort(expectedResult);

		boolean success = Arrays.equals(result, expectedResult);

		if (success) {
			finalFSPoints += 10;
		} else System.out.println("MARK DEDUCTION: FindSpacing fails on \"becausetodayuseat\"!\n-10");
		assertEquals("FindSpacing executed on String 1", true, success);
	}

	@Test(timeout=1000)
	public void testFindSpacing2() {

		String dictionaryFileName = "hw3" + File.separatorChar + "dictionary.txt";
		String[] dict = HW4IO.readDictionary(dictionaryFileName);
		String expectedOutFileName = "hw4" + File.separatorChar + "expectedoutput.txt";
		String[] expectedResult = readExpectedOutput(expectedOutFileName);

		String testStr = "iforgetfactoreverythingseason";

		String[] result = FindSpacing.space(dict, testStr);

		if (result.length == expectedResult.length) {
			for (int i = 0; i < result.length; i++) {
				result[i] = result[i].trim();
				expectedResult[i] = expectedResult[i].trim();
			}
		}

		Arrays.sort(result);
		Arrays.sort(expectedResult);
		
		boolean success = Arrays.equals(result, expectedResult);
		
		//System.out.println(Arrays.toString(result));
		//System.out.println(Arrays.toString(expectedResult));

		if (success) {
			finalFSPoints += 10;
		} else System.out.println("MARK DEDUCTION: FindSpacing fails on \"iforgetfactoreverythingseason\"!\n-10");
		assertEquals("FindSpacing executed on String 2", true, success);
	}

	@Test(timeout=1000)
	public void testFindSpacing3() {

		String dictionaryFileName = "hw3" + File.separatorChar + "dictionary.txt";
		String[] dict = HW4IO.readDictionary(dictionaryFileName);

		String testStr = "djfhskdjfh";
		String[] expectedResult = {};
		String[] result = FindSpacing.space(dict, testStr);
		
		Arrays.sort(result);
		Arrays.sort(expectedResult);
		boolean success = Arrays.equals(result, expectedResult);

		if (success) {
			finalFSPoints += 5;
		} else System.out.println("MARK DEDUCTION: FindSpacing fails on \"djfhskdjfh\"\n-5");
		assertEquals("FindSpacing executed on String 3", true, success);
	}

	@Test(timeout=1000)
	public void testFindSpacing4() {

		String dictionaryFileName = "hw3" + File.separatorChar + "dictionary.txt";
		String[] dict = HW4IO.readDictionary(dictionaryFileName);

		String testStr = "i";
		String[] expectedResult = { "i" };
		String[] result = FindSpacing.space(dict, testStr);
		
		if (result.length == expectedResult.length) {
			for (int i = 0; i < result.length; i++) {
				result[i] = result[i].trim();
				expectedResult[i] = expectedResult[i].trim();
			}
		}
		
		Arrays.sort(result);
		Arrays.sort(expectedResult);
		
		//System.out.println(Arrays.toString(result));
		//System.out.println(Arrays.toString(expectedResult));
		
		boolean success = Arrays.equals(result, expectedResult);

		if (success) {
			finalFSPoints += 5;
		} else System.out.println("MARK DEDUCTION: FindSpacing fails on \"i\"\n-5");
		assertEquals("FindSpacing executed on String 4", true, success);
	}
	
	@Test(timeout=1000)
	public void testFindSpacing5() {

		String dictionaryFileName = "hw3" + File.separatorChar + "dictionary.txt";
		String[] dict = HW4IO.readDictionary(dictionaryFileName);

		String testStr = "";
		String[] expectedResult = {""};
		String[] result = FindSpacing.space(dict, testStr);

		boolean success = Arrays.equals(result, expectedResult);

		if (success) {
			finalFSPoints += 5;
		} else System.out.println("MARK DEDUCTION: FindSpacing fails on empty string\n-5");
		assertEquals("FindSpacing executed on String 4", true, success);
	}

	@Test(timeout=1000)
	public void testFindSpacingEmptyDict() throws IOException {
		try {
			setUp();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		String dictionaryFileName = "hw4" + File.separatorChar + "Empty.txt";
		String[] dict = HW4IO.readDictionary(dictionaryFileName);
		String testStr = "test";
		String[] result = FindSpacing.space(dict, testStr);

		String[] expectedResult = {};
		boolean success = Arrays.equals(result, expectedResult);

		if (success) {
			finalFSPoints += 5;
		} else System.out.println("MARK DEDUCTION: FindSpacing fails on \"empty dictionary\"\n-5");
		assertEquals("FindSpacing executed on empty dictionary", true, success);
		
	}

	@AfterClass
	public static void closeSetUp() throws IOException {
		String fileName = "hw4" + File.separatorChar + "Empty.txt";
		File file = new File(fileName);
		file.delete();
		String fileName2 = "hw4" + File.separatorChar + "points.txt";
		File file2 = new File(fileName2);
		FileWriter writer = new FileWriter(file2,true);
		System.out.println("\n\nFINAL SCORE FOR FindSpacing: "+finalFSPoints+"\n");
		writer.write("\n"+finalFSPoints);
		writer.close();
	}

}
