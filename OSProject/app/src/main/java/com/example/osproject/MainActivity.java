package com.example.osproject;

import android.bluetooth.BluetoothAdapter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public final String TAG = "Main";

    private Bluetooth bt;
    final String message_stop="0";
    final String message_forward="3";
    final String message_backward="4";
    final String message_left="1";
    final String message_right="2";
    //TextView textView_status;
    TextView text_view_message;
    Button move_forward;
    Button move_backword;
    Button move_left;
    Button move_right;
    Button stop;
    Button connect;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bt = new Bluetooth(this, mHandler);
        text_view_message=(TextView)findViewById(R.id.message);
        //textView_status=(TextView)findViewById(R.id.state);
        connect=(Button)findViewById(R.id.connect);
        move_forward = (Button) findViewById(R.id.forward);
        move_backword=(Button)findViewById(R.id.backward);
        move_left=(Button)findViewById(R.id.left);
        move_right=(Button)findViewById(R.id.right);
        stop=(Button)findViewById(R.id.stop);


        connect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connectService();
            }
        });
        move_forward.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bt.sendMessage(message_forward);
                text_view_message.setText("Forward");

            }
        });
        move_backword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bt.sendMessage(message_backward);
                text_view_message.setText("Backward");
            }
        });

        move_left.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bt.sendMessage(message_left);
                text_view_message.setText("Left");

            }
        });

        move_right.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bt.sendMessage(message_right);
                text_view_message.setText("Right");

            }
        });

        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                bt.sendMessage(message_stop);
                text_view_message.setText("Stop");

            }
        });

    }
    public void connectService() {
        try {
            //textView_status.setText("Connecting...");
            BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
            if (bluetoothAdapter.isEnabled()) {

                bt.start();
                bt.connectDevice("HC-05");

                Log.d(TAG, "Btservice started - listening");
                //textView_status.setText(String.valueOf(bt.getState()));
            } else {
                Log.w(TAG, "Btservice started - bluetooth is not enabled");
                //textView_status.setText("Bluetooth Not enabled");
            }
        } catch (Exception e) {
            Log.e(TAG, "Unable to start bt ", e);
            //textView_status.setText("Unable to connect " + e);
        }
    }


    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case Bluetooth.MESSAGE_STATE_CHANGE:
                    Log.d(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
                    break;
                case Bluetooth.MESSAGE_WRITE:
                    Log.d(TAG, "MESSAGE_WRITE ");
                    break;
                case Bluetooth.MESSAGE_READ:
                    Log.d(TAG, "MESSAGE_READ ");
                    break;
                case Bluetooth.MESSAGE_DEVICE_NAME:
                    Log.d(TAG, "MESSAGE_DEVICE_NAME "+msg);
                    break;
                case Bluetooth.MESSAGE_TOAST:
                    Log.d(TAG, "MESSAGE_TOAST "+msg);
                    break;
            }
        }
    };

    @Override
    protected void onStart()
    {
        super.onStart();
    }

}