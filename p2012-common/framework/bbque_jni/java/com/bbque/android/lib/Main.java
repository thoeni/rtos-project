package com.bbque.android.lib;

/** @hide */
public class Main {
  public static void main (String[] args) {
	try {
      int num_core = LibBbque.getNumCore();
      System.out.printf("Num core after getNumCore: %d\n", num_core);
    } catch (LibBbqueException e) {
	  System.err.println("Failed to getNumCore");
	  e.printStackTrace();
    }
  }
}
