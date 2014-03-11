nrf51-ble-app-lbs
==================

This is the accompanying code for the application note nAN-36: "Creating Bluetooth Low Energy Applications Using nRF51822". It is an implemtation of a simple application that shows a custom service with two characteristics; one for a button and one for a LED. The button characteristic will send a notification on each toggle of a button, while the LED characteristic can be used to control an on-board LED. 

Writing to the LED characteristic will also result in the value being printed on the nRF6350 display. This does however not use the PPI, so the application will also try to read the state of the joystick on the nRF6350, when the button is pressed, and then send the JS status instead of the button status. This will trigger a HardFault with the default twi_hw_master.c, so this file has been modified to use the SHORTS available on second revision chips instead.


Requirements
------------
- nRF51 SDK version 5.1.0
- S110 SoftDevice version 6.0.0
- nRF51822 Development Kit version 2.1.0 or later
- nRF6350 display module, with the TWI interface hooked up to P0.24 (SCK) and P0.25 (SDA).

The project may need modifications to work with later versions or other boards. 

To compile it, clone the repository in the nrf51822/Board/pca10001/s110/ folder.

About this project
------------------
This application is one of several applications that has been built by the support team at Nordic Semiconductor, as a demo of some particular feature or use case. It has not necessarily been thoroughly tested, so there might be unknown issues. It is hence provided as-is, without any warranty. 

However, in the hope that it still may be useful also for others than the ones we initially wrote it for, we've chosen to distribute it here on GitHub. 

The application is built to be used with the official nRF51 SDK, that can be downloaded from https://www.nordicsemi.no, provided you have a product key for one of our kits.

Please post any questions about this project on https://devzone.nordicsemi.com.
