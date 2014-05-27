nrf51-ble-app-lbs
==================

This is the accompanying code for the application note nAN-36: "Creating Bluetooth Low Energy Applications Using nRF51822", but modified to show data throughput. It was originally an implemtation of a simple application that shows a custom service with two characteristics; one for a button and one for a LED. In this variant, the button characteristic have however been changed to a data characteristic. When BUTTON_1 is pressed, it will start sending 20 byte notifications as fast as possible, until the button is pressed a second time.

Requirements
------------
- nRF51 SDK version 5.2.0
- S110 SoftDevice version 6.0.0
- nRF51822 Evaluation Kit version 2.1.0 or later

The project may need modifications to work with other versions or other boards. 

To compile it, clone the repository in the nrf51822/Board/pca10001/s110/ folder.

About this project
------------------
This application is one of several applications that has been built by the support team at Nordic Semiconductor, as a demo of some particular feature or use case. It has not necessarily been thoroughly tested, so there might be unknown issues. It is hence provided as-is, without any warranty. 

However, in the hope that it still may be useful also for others than the ones we initially wrote it for, we've chosen to distribute it here on GitHub. 

The application is built to be used with the official nRF51 SDK, that can be downloaded from https://www.nordicsemi.no, provided you have a product key for one of our kits.

Please post any questions about this project on https://devzone.nordicsemi.com.
