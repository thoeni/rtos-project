package com.bbque.android.bbqueservice;

import android.content.Context;
import android.content.pm.PackageManager;
import android.os.RemoteException;
import android.util.Log;
import com.bbque.android.service.IBbqueService;
import com.bbque.android.lib.LibBbque;

class IBbqueServiceImpl extends IBbqueService.Stub {
  private static final String TAG = "IBbqueServiceImpl";
  private final Context context;

  IBbqueServiceImpl(Context context) {
    this.context = context;
  }

  public int getNumCore() throws RemoteException {
    return LibBbque.getNumCore();
  }
  
  public int getMoreCore() throws RemoteException {
    return LibBbque.getMoreCore();
  }
  
  public int getLessCore() throws RemoteException {
    return LibBbque.getLessCore();
  }
  
  public int freeCore() throws RemoteException {
    return LibBbque.freeCore();
  }
  
  public int sendMessageToApp(String message) {
  	 return LibBbque.sendMessageToApp(message);
  }
}
