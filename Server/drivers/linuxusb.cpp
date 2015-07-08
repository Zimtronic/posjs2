#include "linuxusb.h"
#include "errors.h"

#include <iostream>
using namespace std;

LinuxUSB::LinuxUSB()
{
    this->idProduct = 0x0e15;
    this->idVendor = 0x04b8;
    this->interface = 0;
    this->configuration = 1;
    this->inEndPoint = 0x82;
    this->outEndPoint = 0x01;
    this->isOpen = false;
}

LinuxUSB::~LinuxUSB()
{
    if(this->isOpen)
        close();
}

unsigned LinuxUSB::open()
{
    QMutexLocker locker(&mutex);

    this->isOpen = false;
    bool foundDevice = false;

    struct usb_bus *bus;
    struct usb_device *dev;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for (bus = usb_get_busses(); bus; bus = bus->next)
    {
//        cout << "Found bus: " << bus->dirname << endl;

        for (dev = bus->devices; dev; dev = dev->next)
        {
//            cout << "Found device with idVendor: "<< dev->descriptor.idVendor
//                 << " and idProduct: "<< dev->descriptor.idProduct << endl;

            if ((dev->descriptor.idProduct == this->idProduct) && (dev->descriptor.idVendor == this->idVendor))
            {
//                cout << "Device found -> open "<< endl;

                this->handle = usb_open(dev);
                if (!this->handle)
                {
                    return errUSBOpen;
                }

                usb_detach_kernel_driver_np(this->handle, this->interface);

//                cout << "Set configuration" << endl;

                if (usb_set_configuration(this->handle, this->configuration) < 0)
                {
                    return errUSBConfig;
                }
                foundDevice = true;
                break;
            }
        }
        if(foundDevice)
            break;
    }
    if(foundDevice)
    {
        this->isOpen = true;
        return OK;
    }
    else
    {
        return errUSBDeviceNotFound;
    }
}

unsigned LinuxUSB::close()
{
    QMutexLocker locker(&mutex);

    int result = OK;
    if(this->isOpen)
    {
        result = usb_close(this->handle);
    }
    this->isOpen = false;
    if(result >= 0)
        return OK;
    else
        return errUSBClose;
}

unsigned LinuxUSB::read(unsigned char *buffer, unsigned &bufferSize,
                        unsigned timeOut)
{
    QMutexLocker locker(&mutex);

    if(this->isOpen)
    {
        if (usb_claim_interface(this->handle, this->interface) < 0)
        {
            return errUSBClaimInterface;
        }
        else
        {
            int result = usb_bulk_read(this->handle, this->inEndPoint, (char*)buffer, bufferSize, timeOut);
            if (result < 0)
            {
                return errUSBRead;
            }

//            cout << "usb_bulk_read: " << result << "bytes read" << endl;

            usb_release_interface(this->handle, this->interface);
        }
        return OK;
    }
    else
    {
        return errUSBIsClose;
    }
}

unsigned LinuxUSB::write(unsigned char *buffer, unsigned &bufferSize,
                         unsigned timeOut)
{
    QMutexLocker locker(&mutex);

    if(this->isOpen)
    {
//        cout << "usb_claim_interface" << endl;

        if (usb_claim_interface(this->handle, this->interface) < 0)
        {
            return errUSBClaimInterface;
        }
        else
        {
            int result = usb_bulk_write(this->handle, this->outEndPoint, (const char*)buffer, bufferSize, timeOut);
            if (result < 0)
            {
                return errUSBWrite;
            }
            bufferSize = result;

//            cout << "usb_bulk_write: " << result << " bytes written" << endl;

            usb_release_interface(this->handle, this->interface);
        }
        return OK;
    }
    else
    {
        return errUSBIsClose;
    }
}

unsigned LinuxUSB::getIdProduct() const
{
    return idProduct;
}

void LinuxUSB::setIdProduct(const unsigned &value)
{
    idProduct = value;
}

unsigned LinuxUSB::getIdVendor() const
{
    return idVendor;
}

void LinuxUSB::setIdVendor(const unsigned &value)
{
    idVendor = value;
}

unsigned LinuxUSB::getInterface() const
{
    return interface;
}

void LinuxUSB::setInterface(const unsigned &value)
{
    interface = value;
}

unsigned LinuxUSB::getInEndPoint() const
{
    return inEndPoint;
}

void LinuxUSB::setInEndPoint(const unsigned &value)
{
    inEndPoint = value;
}

unsigned LinuxUSB::getOutEndPoint() const
{
    return outEndPoint;
}

void LinuxUSB::setOutEndPoint(const unsigned &value)
{
    outEndPoint = value;
}

unsigned LinuxUSB::getConfiguration() const
{
    return configuration;
}

void LinuxUSB::setConfiguration(const unsigned &value)
{
    configuration = value;
}

