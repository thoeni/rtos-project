package com.bbque.android.service;

import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;

public class BbqueManager {
  private static final String TAG = "BbqueManager";
  private static final String REMOTE_SERVICE_NAME = IBbqueService.class.getName();
  private final IBbqueService service;
  
  public static BbqueManager getInstance() {
    return new BbqueManager();
  }
    
  private BbqueManager() {
    Log.d(TAG, "Connecting to IBbqueService by name [" + REMOTE_SERVICE_NAME + "]");
    this.service = IBbqueService.Stub.asInterface(ServiceManager.getService(REMOTE_SERVICE_NAME));
    if (this.service == null) {
      throw new IllegalStateException("Failed to find IBbqueService by name [" + REMOTE_SERVICE_NAME + "]");
    }
  }   
    
  public int getNumCore() {
    try {
      return this.service.getNumCore();
    } catch (RemoteException e) {
      throw new RuntimeException("Failed to getNumCore", e);
    }
  }
  
  public int getMoreCore() {
    try {
      return this.service.getMoreCore();
    } catch (RemoteException e) {
      throw new RuntimeException("Failed to getMoreCore", e);
    }
  }
  
  public int getLessCore() {
    try {
      return this.service.getLessCore();
    } catch (RemoteException e) {
      throw new RuntimeException("Failed to getLessCore", e);
    }
  }
  
  public int freeCore() {
    try {
      return this.service.freeCore();
    } catch (RemoteException e) {
      throw new RuntimeException("Failed to freeCore", e);
    }
  }
  
  public int sendMessageToApp(String message) {
    try {
      return this.service.sendMessageToApp(message);
    } catch (RemoteException e) {
      throw new RuntimeException("Failed to sendMessageToApp("+message+")", e);
    }
  }
}
