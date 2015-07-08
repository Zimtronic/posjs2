#ifndef ERRORS_H
#define ERRORS_H

   /**
    * @brief Error codes definitions
    *
    *
    * @author tony
    * @date 18-10-2014
    */

const unsigned OK = 0;

/**
 * @brief USB errors
 */
const unsigned errUSBOpen = 1;
const unsigned errUSBConfig = 2;
const unsigned errUSBDeviceNotFound = 3;
const unsigned errUSBClose = 4;
const unsigned errUSBClaimInterface = 5;
const unsigned errUSBWrite = 6;
const unsigned errUSBRead = 7;
const unsigned errUSBIsClose = 8;
const unsigned errUSBTimeout = 9;

/**
 * @brief Printer errors
 */
const unsigned errPrinterUndefineFeedControl = 10;
const unsigned errPrinterUndefineCashDrawerPin = 11;
const unsigned errPrinterUndefineAlign = 12;
const unsigned errPrinterUndefineFont = 13;
const unsigned errPrinterUndefineType = 14;

const unsigned errBarcodeSize = 15;
const unsigned errBarcodeType = 16;
const unsigned errBarcodeFont = 17;
const unsigned errBarcodeTextPos = 18;

/**
 * @brief Error codes information.
 */
static const char *errorsString[] =
{
    "OK",
    "Error opening USB port",
    "Error USB config",
    "Error USB device not found",
    "Error closing USB port",
    "Error USB claim interface",
    "Error USB write",
    "Error USB read",
    "Error USB is close",
    "Error USB read timeout",
    "Error printer undefine feed control",
    "Error printer undefine cash drawer pin",
    "Error printer undefine align",
    "Error printer undefine font",
    "Error printer undefine type",
    "Error Barcode Size",
    "Error Barcode Type",
    "Error Barcode Font",
    "Error Barcode Text Position"
};

#endif // ERRORS_H
