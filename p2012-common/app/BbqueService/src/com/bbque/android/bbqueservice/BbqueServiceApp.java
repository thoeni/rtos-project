package com.bbque.android.bbqueservice;

import android.app.Application;
import android.os.ServiceManager;
import android.util.Log;
import com.bbque.android.service.IBbqueService;

public class BbqueServiceApp extends Application {
  private static final String TAG = "BbqueServiceApp";
  private static final String REMOTE_SERVICE_NAME = IBbqueService.class.getName();
  private IBbqueServiceImpl serviceImpl;

  public void onCreate() {
    super.onCreate();
    this.serviceImpl = new IBbqueServiceImpl(this);
    ServiceManager.addService(REMOTE_SERVICE_NAME, this.serviceImpl);
    Log.d(TAG, "Registered [" + serviceImpl.getClass().getName() + "] as [" + REMOTE_SERVICE_NAME + "]");
  }

  public void onTerminate() {
    super.onTerminate();
    Log.d(TAG, "Terminated");
  }
}
