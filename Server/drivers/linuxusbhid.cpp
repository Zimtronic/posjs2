#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "linuxusbhid.h"
#include "errors.h"
#include "hidtable.h"

using namespace std;
#include <iostream>

LinuxUSBHid::LinuxUSBHid()
{
    //Barcode scanner
    this->idProduct = 0x1010;
    this->idVendor = 0x05fe;

    //Magnetic card scanner
//    this->idProduct = 0x0001;
//    this->idVendor = 0x0801;
}

unsigned LinuxUSBHid::open()
{
    QMutexLocker locker(&mutex);

    this->isOpen = false;
    bool foundDevice = false;

    struct usb_bus *bus;
    struct usb_device *dev;
    struct usb_interface *iface;
    struct usb_interface_descriptor *desc;
    struct usb_endpoint_descriptor *ep;
    uint8_t buf[1024];
    int i, n, len, claimed;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for (bus = usb_get_busses(); bus; bus = bus->next)
    {
        for (dev = bus->devices; dev; dev = dev->next)
        {
            if (this->idVendor > 0 && dev->descriptor.idVendor != this->idVendor) continue;
            if (this->idProduct > 0 && dev->descriptor.idProduct != this->idProduct) continue;
            if (!dev->config) continue;
            if (dev->config->bNumInterfaces < 1) continue;

//            printf("device: vid=%04X, pic=%04X, with %d iface\n", dev->descriptor.idVendor, dev->descriptor.idProduct, dev->config->bNumInterfaces);

            iface = dev->config->interface;
            this->handle = NULL;
            claimed = 0;
            for (i=0; i<dev->config->bNumInterfaces && iface; i++, iface++)
            {
                desc = iface->altsetting;
                if (!desc) continue;

//                printf("  type %d, %d, %d\n", desc->bInterfaceClass, desc->bInterfaceSubClass, desc->bInterfaceProtocol);

                if (desc->bInterfaceClass != 3) continue;
                ep = desc->endpoint;
                this->inEndPoint = 0;
                this->outEndPoint = 0;
                for (n = 0; n < desc->bNumEndpoints; n++, ep++)
                {
                    if (ep->bEndpointAddress & 0x80)
                    {
                        if (!this->inEndPoint) this->inEndPoint = ep->bEndpointAddress & 0x7F;

//                        printf("    IN endpoint %d\n", this->inEndPoint);
                    }
                    else
                    {
                        if (!this->outEndPoint) this->outEndPoint = ep->bEndpointAddress;

//                        printf("    OUT endpoint %d\n", this->outEndPoint);
                    }
                }
                if (!this->inEndPoint) continue;
                if (!this->handle)
                {
                    this->handle = usb_open(dev);
                    if (!this->handle)
                    {
//                        printf("  unable to open device\n");
                        break;
                    }
                }
//                printf("  hid interface (generic)\n");
                if (usb_get_driver_np(this->handle, i, (char *)buf, sizeof(buf)) >= 0)
                {
//                    printf("  in use by driver \"%s\"\n", buf);
                    if (usb_detach_kernel_driver_np(this->handle, i) < 0)
                    {
//                        printf("  unable to detach from kernel\n");
                        continue;
                    }
                }
                if (usb_claim_interface(this->handle, i) < 0)
                {
//                    printf("  unable claim interface %d\n", i);
                    continue;
                }
                len = usb_control_msg(this->handle, 0x81, 6, 0x2200, i, (char *)buf, sizeof(buf), 250);

//                printf("  descriptor, len=%d\n", len);

                if (len < 2)
                {
                    usb_release_interface(this->handle, i);
                    continue;
                }
                foundDevice = true;
                claimed++;
            }
            if (this->handle && !claimed)
            {
                usb_close(this->handle);
            }
        }
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

unsigned LinuxUSBHid::read(unsigned char *buffer, unsigned &bufferSize,
                           unsigned timeOut)
{
    QMutexLocker locker(&mutex);

    if(this->isOpen)
    {
        int result = usb_interrupt_read(this->handle, this->inEndPoint, (char*)buffer, bufferSize, timeOut);
        if (result < 0)
        {
            if(result == -110)
                return errUSBTimeout;
            return errUSBRead;
        }
        bufferSize = result;
        return OK;
    }
    else
    {
        return errUSBIsClose;
    }
}
