package com.example.garden_app.bluetooth;

public interface ExtendedRunnable extends Runnable {
    void write(byte[] bytes);
    void cancel();
}
