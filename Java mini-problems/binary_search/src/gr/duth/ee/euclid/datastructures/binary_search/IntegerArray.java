package gr.duth.ee.euclid.datastructures.binary_search;

import java.io.Serializable;

/**
 * DO NOT MODIFY THIS FILE
 */
public class IntegerArray implements Serializable {
	private static final long serialVersionUID = 1L;
	
	private int accesses = 0;
	private int[] a;
	
	public IntegerArray(int[] original) {
		a = new int[original.length];
		for (int i = 0; i < original.length; i++) {
			a[i] = original[i];
		}
	}
	
	public IntegerArray(Integer[] original) {
		a = new int[original.length];
		for (int i = 0; i < original.length; i++) {
			a[i] = original[i];
		}
	}
	
	public int get(int index) {
		accesses++;
		return a[index];
	}
	
	public int length() {
		return a.length;
	}
	
	public int numberOfAccesses() {
		return accesses;
	}
}
