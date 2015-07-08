#ifndef LINUXUSB_H
#define LINUXUSB_H

#include <QMutex>
#include <QMutexLocker>

#include "itransport.h"
#include <usb.h>

   /**
    * @class LinuxUSB
    * @brief ITransport implementation
    *
    * This class lets read and write data using USB interface,
    * for this purpose used the libusb library
    *
    * @author tony
    * @date 18-10-2014
    */

class LinuxUSB : public ITransport
{
public:
    /**
     * @brief Class builder
     */
    LinuxUSB();

    /**
     * @brief Class destroyer
     */
    ~LinuxUSB();

    /**
     * @brief Initialize the libusb library, find busses and devices
     *
     * @see ITransport.open
     */
    unsigned open();

    /**
     * @brief Close usb interface and release the communication handler
     *
     * @see ITransport.close
     */
    unsigned close();

    /**
     * @brief Read bytes from usb port
     *
     * @see ITransport.read
     */
    unsigned read(unsigned char* buffer, unsigned &bufferSize,
                  unsigned timeOut);

    /**
     * @brief Write bytes to usb port
     *
     * @see ITransport.write
     */
    unsigned write(unsigned char* buffer, unsigned &bufferSize,
                   unsigned timeOut);

    unsigned getIdProduct() const;
    void setIdProduct(const unsigned &value);

    unsigned getIdVendor() const;
    void setIdVendor(const unsigned &value);

    unsigned getInterface() const;
    void setInterface(const unsigned &value);

    unsigned getInEndPoint() const;
    void setInEndPoint(const unsigned &value);

    unsigned getOutEndPoint() const;
    void setOutEndPoint(const unsigned &value);

    unsigned getConfiguration() const;
    void setConfiguration(const unsigned &value);

protected:
    unsigned idProduct; /**< USB product identification */
    unsigned idVendor; /**< USB vendor identification */
    unsigned interface; /**< USB interface number */
    unsigned configuration; /**< USB configuration number */
    int inEndPoint; /**< USB read endpoint */
    int outEndPoint; /**< USB write endpoint */

    struct usb_dev_handle *handle; /**< Connection handler */

    bool isOpen; /**< Connection state */

    QMutex mutex;
};

#endif // LINUXUSB_H
