![Posjs](docs/images/posjs_logo.png)

Posjs is a web based POS(Point of Sale) container and hardware bridge. We use the Qt WebKit bridge 
mechanism to extend javascript environment with c++ objects. That objects are used 
to access hardware-specific features like printing and scan text codes with HID USB devices.

See [LICENSE](LICENSE).

## Building

### Requirements

* Linux based OS with 64-bit or 32-bit architecture. 
* C++ toolchain.
* libusb-0.1-4.
* [Git](http://git-scm.com/).
* [Qt5.3.0](http://qt-project.org/downloads).

### Build and run

1. Open your command prompt and download the latest [posjs](https://github.com/Zimtronic/posjs).

 ```sh
  git clone https://github.com/Zimtronic/posjs.git
  cd posjs
  ```
  
2. Execute `qmake` to create Makefile. 
3. Execute `make` to compile.
4. Execute `sudo ./posjsbrowser` to run the posjs browser app. Don't forget to prefix with `sudo`. 

## Supported devices

Theoretically we support any ESC/POS based printer and compatible cash drawers. ESC/POS protocol was designed by EPSON 
and is widely used by many other printer brands mainly on POS. Additionally, we support access
to USB HID barcode scanners and magnetic card readers.

Default devices:

* Printer EPSON TM-T20II
* Barcode scanner MJ_tech V3.00
* Magnetic card reader model MSR100 
* Cash drawers, as the cash drawers are connected to the printer all Epson compatible cash drawers should work. 

See [using other devices section](docs/supporteddevices.md).

## Developing a javascript app

The main idea of ​​this project is provide a platform with hardware access to developing your own POS application. 
Initially we export three objects to the javascript context: `ESCPOSPrinter`, `BarcodeScanner` and `MagneticScanner` 
(see [using other devices section](docs/supporteddevices.md) to change object names and add other devices). 
Then you can use this objects into the javascript code. 

* [Javascript API](docs/javascriptapi.md)
* [Using ESC/POS printers](docs/printer.md)
* [Using HSB HID scanners](docs/hid.md)
