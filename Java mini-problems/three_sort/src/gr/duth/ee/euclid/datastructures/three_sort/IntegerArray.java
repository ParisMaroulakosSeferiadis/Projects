package gr.duth.ee.euclid.datastructures.three_sort;

import gr.duth.ee.euclid.datastructures.three_sort.IntegerArray;

import java.io.Serializable;

/**
 * DO NOT MODIFY THIS FILE
 */
public class IntegerArray implements Serializable {
	private static final long serialVersionUID = 1L;

	private int[] a;
	private int compares;
	private int swaps;

	public IntegerArray(int[] original) {
		a = new int[original.length];
		for (int i = 0; i < original.length; i++) {
			a[i] = original[i];
		}
		compares = 0;
		swaps = 0;
	}

	public IntegerArray(Integer[] original) {
		a = new int[original.length];
		for (int i = 0; i < original.length; i++) {
			a[i] = original[i];
		}
		compares = 0;
		swaps = 0;
	}

	public IntegerArray(IntegerArray a) {
		this(a.a);
		compares += a.length();
		swaps += a.length();
	}

	public boolean isSorted() {
		compares += a.length;
		swaps += a.length;
		for (int i = 0; i < a.length - 1; i++) {
			if (a[i] > a[i + 1]) {
				return false;
			}
		}
		return true;
	}

	public int length() {
		return a.length;
	}

	public int compare(int index, int with) {
		compares++;
		return Integer.compare(a[index], with);
	}

	public void swap(int index1, int index2) {
		swaps++;
		int tmp = a[index1];
		a[index1] = a[index2];
		a[index2] = tmp;
	}

	public int numberOfCompares() {
		return compares;
	}

	public int numberOfSwaps() {
		return swaps;
	}
}
