#ifndef LINUXUSBHID_H
#define LINUXUSBHID_H

#include "linuxusb.h"

    /**
     * @class LinuxUSBHid
     * @brief ITransport implementation
     *
     * This class lets read data from USB HID devices,
     * for this purpose used the libusb library
     *
     * @author tony
     * @date 18-10-2014
     */

class LinuxUSBHid : public LinuxUSB
{
public:
    /**
     * @brief Class builder
     */
    LinuxUSBHid();

    /**
     * @see LinuxUSB.open
     */
    unsigned open();

    /**
     * @see LinuxUSB.read
     */
    unsigned read(unsigned char* buffer, unsigned &bufferSize,
                  unsigned timeOut);
};

#endif // LINUXUSBHID_H
