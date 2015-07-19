#ifndef POSDRIVERINTERFACE_H
#define POSDRIVERINTERFACE_H

#include <QtCore/QObject>
#include <QString>

class GenericHIDScanner;
class ESCPOSPrinter;

class  POSDriverInterface
{
public:
    POSDriverInterface() {}

    virtual ESCPOSPrinter *getESCPOSPrinterInstance() = 0;
    virtual GenericHIDScanner *getBarcodeScannerInstance() = 0;
    virtual GenericHIDScanner *getMagneticScannerInstance() = 0;

    virtual void processESCPOSPrinterASCIICommand(QString command) = 0;
};

#define POSDriverInterface_iid "com.zimtronic.posdriverinterface.01"

Q_DECLARE_INTERFACE(POSDriverInterface, POSDriverInterface_iid)

#endif // POSDRIVERINTERFACE_H
