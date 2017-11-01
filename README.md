nrf51-ble-app-lbs
==================
(Draft update to v8.0)
This is the accompanying code for the application note nAN-36: "Creating Bluetooth Low Energy Applications Using nRF51822". It is an implemtation of a simple application that shows a custom service with two characteristics; one for a button and one for a LED. The button characteristic will send a notification with the button state when the button is pressed or released, while the LED characteristic can be used to control an on-board LED.

Requirements
------------
- nRF51 SDK version 8.0
- S110 SoftDevice version 8.0
- nRF51822 DK (PCA10028)

The project may need modifications to work with other versions or other boards. 

To compile it, clone the repository in the [SDK]/examples/ble_peripheral folder.

About this project
------------------
This application is one of several applications that has been built by the support team at Nordic Semiconductor, as a demo of some particular feature or use case. It has not necessarily been thoroughly tested, so there might be unknown issues. It is hence provided as-is, without any warranty. 

However, in the hope that it still may be useful also for others than the ones we initially wrote it for, we've chosen to distribute it here on GitHub. 

The application is built to be used with the official nRF51 SDK, that can be downloaded from https://www.nordicsemi.no, provided you have a product key for one of our kits.

Please post any questions about this project on https://devzone.nordicsemi.com.

How to get started
------------------
- Install [Keil MDK version 5](http://www2.keil.com/mdk5/)
- Download SDK version 8.0.0 zip(nRF51_SDK_8.0.0_5fc2c3a.zip) from [here](https://developer.nordicsemi.com/nRF51_SDK/nRF51_SDK_v8.x.x/).
- The zip version of the SDK requires the nRF51 MDK to be installed separately (msi installer is included in the zip)
- Unzip to C:\Keil_v5\ARM\Device\SDK8.0.0 (SDK8.0.0 folder must be created)
- Make sure you are on the [SDKv8.0 branch](https://github.com/NordicPlayground/nrf51-ble-app-lbs/tree/SDKv8.0) of this github example project, and download the zip file.
- Unzip it to C:\Keil_v5\ARM\Device\SDK8.0.0\examples\ble_peripheral
- Open ble_app_lbs.uvprojx in C:\Keil_v5\ARM\Device\SDK8.0.0\examples\ble_peripheral\nrf51-ble-app-lbs-master\arm and compile.
