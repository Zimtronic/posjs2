#ifndef GENERICHIDSCANNER_H
#define GENERICHIDSCANNER_H

#include <QThread>

#include "linuxusbhid.h"

    /**
     * @class GenericHIDScanner
     * @brief Thread to scan USB HID devices
     *
     * This class try to read ASCII packets from USB
     * HID devices
     *
     * @author tony
     * @date 28-10-2014
     */

class GenericHIDScanner : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Class builder
     */
    GenericHIDScanner();

    void run();

    /**
     * @brief Set USB product identification
     */
    Q_INVOKABLE void setIdProduct(const unsigned &value);

    /**
     * @brief Set USB vendor identification
     */
    Q_INVOKABLE void setIdVendor(const unsigned &value);

signals:
    /**
     * @brief This signal is emited when HID packet arrived
     */
    void packetRead(QString packet);

private:
    LinuxUSBHid * hid; /**<Linux USB HID transport pointer */
};

#endif // GENERICHIDSCANNER_H
