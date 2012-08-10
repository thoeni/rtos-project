package com.bbque.android.lib;

public class LibBbque {

  public native static int getNumCore() throws LibBbqueException;
  public native static int getMoreCore() throws LibBbqueException;
  public native static int getLessCore() throws LibBbqueException;
  public native static int freeCore() throws LibBbqueException;
  public native static int sendMessageToApp(String message) throws LibBbqueException;

  static {
     System.loadLibrary("bbque_jni");
  }
}

