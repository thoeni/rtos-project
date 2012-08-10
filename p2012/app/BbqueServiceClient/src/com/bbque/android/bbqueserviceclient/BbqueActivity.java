package com.bbque.android.bbqueserviceclient;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.bbque.android.service.BbqueManager;

public class BbqueActivity extends Activity implements Runnable, View.OnClickListener {

  private TextView output;

  private Handler handler;

  private BbqueManager bbqueManager;

  public void onCreate(Bundle savedInstanceState) {
    this.bbqueManager = BbqueManager.getInstance();
    super.onCreate(savedInstanceState);
    super.setContentView(R.layout.log);
    this.output = (TextView)super.findViewById(R.id.output);
	 Button num_core_button = (Button)super.findViewById(R.id.num_core_button);
    num_core_button.setOnClickListener(this);
    Button more_core_button = (Button)super.findViewById(R.id.more_core_button);
    more_core_button.setOnClickListener(this);
    Button less_core_button = (Button)super.findViewById(R.id.less_core_button);
    less_core_button.setOnClickListener(this);
    Button free_core_button = (Button)super.findViewById(R.id.free_core_button);
    free_core_button.setOnClickListener(this);

/*	 Button more_core_button = (Button)super.findViewById(R.id.more_core_button);
    more_core_button.setOnClickListener(this);
*/
    this.handler = new Handler();
  }

  private void updateOutput() {
    this.output.setText(super.getString(R.string.bbque_message, this.bbqueManager.getNumCore()));
  }

  @Override
  public void onResume() {
    super.onResume();
    this.handler.post(this);
  }

  @Override
  public void onPause() {
    super.onPause();
    this.handler.removeCallbacks(this);
  }

/*  public void onClick(View view) {
    this.bbqueManager.getMoreCore();
    this.updateOutput();
  } */
  
  @Override
  public void onClick(View view) {
       switch(view.getId()) {
           case R.id.num_core_button:
           		this.bbqueManager.getNumCore();
           break;
           case R.id.more_core_button:
					this.bbqueManager.getMoreCore();
           break;
           case R.id.less_core_button:
           		this.bbqueManager.getLessCore();
           break;
           case R.id.free_core_button:
           		this.bbqueManager.freeCore();
           break;
       }
   }
   
  public void run() {
    this.updateOutput();
    this.handler.postDelayed(this, 1000);
  }
}
