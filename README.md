![Posjs](docs/images/posjs_logo.png)

Posjs is a web based POS (Point of Sale) container and hardware bridge. 
In this version we use Apache Cordova platform to allow building of native 
mobile applications using HTML, CSS and JavaScript. 

We use a tcp socket cordova plugin to extend javascript environment with objects. 
That objects are used to access hardware-specific features like printing and 
scan text codes with HID USB devices.

![Posjs](docs/images/deploy.png)

See [LICENSE](LICENSE).

## Building

### Requirements

* Linux based OS with 64-bit or 32-bit architecture. 
* C++ toolchain.
* libusb-0.1-4.
* [Git](http://git-scm.com/).
* [Qt5.3.0](http://qt-project.org/downloads).

### Server

1. Open your command prompt and download the latest [posjs](https://github.com/Zimtronic/posjs2).

 ```sh
  git clone https://github.com/Zimtronic/posjs2.git
  cd posjs
  ```
  
2. Execute `qmake` to create Makefile. 
3. Execute `make` to compile.
4. Execute `sudo ./server` to run the posjs browser app. Don't forget to prefix with `sudo`. 

### Android SDK
