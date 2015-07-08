#include "generichidscanner.h"
#include "errors.h"
#include "hidtable.h"

using namespace std;
#include <iostream>

GenericHIDScanner::GenericHIDScanner()
{
    hid = new LinuxUSBHid();
}

void GenericHIDScanner::setIdProduct(const unsigned &value)
{
    hid->setIdProduct(value);
}

void GenericHIDScanner::setIdVendor(const unsigned &value)
{
    hid->setIdVendor(value);
}

void GenericHIDScanner::run()
{
    unsigned bufferSize, ctrol, packetIndex;
    unsigned char buf[16], packet[256];

    unsigned result = errUSBIsClose;

    while (1)
    {
        bufferSize = 8;
        packetIndex = 0;
        memset(packet, 0, 256);

        if(result != OK && result != errUSBTimeout)
        {
            hid->close();
            result = hid->open();
            cout << "close open " <<result<< endl;
            if(result != OK)
            {
                sleep(10);
            }
        }

        do
        {
            result = hid->read(buf, bufferSize, 100);
            if(result == OK)
            {
                if(buf[2])
                {
                    if(buf[0] == 0x02)
                        ctrol = 1;
                    else
                        ctrol = 0;

                    packet[packetIndex++] = hidTable[(int)buf[2]][ctrol];
                }
//                cout << packet[packetIndex-1] << endl;
            }
        } while(result == OK);

        if(packetIndex)
            emit packetRead(QString((const char*)packet));
    }
}
