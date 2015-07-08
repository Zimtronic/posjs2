#ifndef ESCPOSPRINTER_H
#define ESCPOSPRINTER_H

#include <QObject>
#include <QtWidgets>
#include <QBitArray>
#include <QBitmap>
#include <QImage>
#include <QRgb>

#include "iticketprinter.h"
#include "errors.h"

   /**
    * @class ESCPOSPrinter
    * @brief ITicketPrinter implementation
    *
    * This class has methods to print tickets using thermal
    * printers that use the ESC/POS  protocol over USB
    *
    * @author tony
    * @date 18-10-2014
    */

class BitmapData;

class ESCPOSPrinter : public QObject, public ITicketPrinter
{
    Q_OBJECT

public:
    /**
     * @brief Class builder
     */
    ESCPOSPrinter();

    /**
     * @brief Class destroyer
     */
    virtual ~ESCPOSPrinter();

    /**
     * @brief Try to open USB port and send the init
     * command to the printer
     *
     * @see ITicketPrinter.init
     */
    Q_INVOKABLE unsigned init();

    /**
     * @see ITicketPrinter.printRawText
     */
    Q_INVOKABLE unsigned printRawText(QString text);


    /**
     * @see ITicketPrinter.cutPaper
     */
    Q_INVOKABLE unsigned cutPaper(bool fullCut);

    /**
     * @param pin
     * 2, 5
     *
     * @see ITicketPrinter.sendPulseToCashDrawer
     */
    Q_INVOKABLE unsigned sendPulseToCashDrawer(unsigned pin);

    /**
     * Possible values
     *
     * @param align
     * 0->center, 1->right, 2->left
     *
     * @param font
     * 0->A, 1->B
     *
     * @param type
     * 0->B, 1->U, 2->U2, 3->BU, 4->BU2, 5->Normal
     *
     * @param width
     * 1->Normal width, 2->Double width
     *
     * @param height
     * 1->Normal heigth, 2->Double heigth
     *
     * @see ITicketPrinter.setTextProperties
     */
    Q_INVOKABLE unsigned setTextProperties(unsigned align, unsigned font,
                                           unsigned type, unsigned width,
                                           unsigned height);

    /**
     * @param crl
     * 0->LF, 1->FF, 2->CR, 3->HT, 4->VT
     *
     * @see ITicketPrinter.feedControl
     */
    Q_INVOKABLE unsigned feedControl(unsigned crl);

    /**
     * @param pathImage
     * absolute or relative path
     *
     * @param rightTab
     * tab numbers from the left border of paper
     *
     * @param sizeScale
     * 0 <= sizeScale <= 10
     *
     *
     * @see ITicketPrinter.printImage
     */
    Q_INVOKABLE unsigned printImage(QString pathImage, unsigned rightTab,
                                    unsigned sizeScale);


    /**
     * @brief Encode and print barcode
     *
     * @param code
     * String to be encoded in the barcode
     * Different barcodes have different requirements on the length
     * of data that can be encoded
     * @param type
     * Specify the type of barcode
     * 65 = UPC-A
     * 66 = UPC-E
     * 67 = JAN13(EAN)
     * 68 = JAN8(EAN)
     * 69 = CODE39
     * 70 = ITF
     * 71 = CODABAR
     * 72 = CODE93
     * 73 = CODE128
     * @param height
     * height of the barcode in points (1 <= n <= 255)
     * @param width
     * width of module (2 <= n <=6)
     * Barcode will not print if this value is too large
     * @param font
     * Set font of HRI characters
     * 0 = font A
     * 1 = font B
     * @param pos
     * set position of HRI characters
     * 0 = not printed
     * 1 = Above barcode
     * 2 = Below barcode
     * 3 = Both above and below barcode
     *
     * @see ITicketPrinter.printBarcode
     */
    Q_INVOKABLE unsigned printBarcode(QString code, unsigned type,
                                      unsigned width, unsigned height,
                                      unsigned pos, unsigned font);

    /**
     * @brief Return error codes information
     *
     * @param code
     * String to be encoded in the qrcode
     *
     * @param errCorrect
     * 48 <= errCorrect <= 51
     *
     * @param moduleSize
     * 1 <= moduleSize <= 16
     *
     * @see ITicketPrinter.printQRCode
     */
    Q_INVOKABLE unsigned printQRCode(QString code, unsigned errCorrect,
                                     unsigned moduleSize);

    /**
     * @brief Return error codes information
     */
    Q_INVOKABLE QString getErrorString(unsigned errorCode);


    Q_INVOKABLE unsigned getTimeout() const;
    Q_INVOKABLE void setTimeout(const unsigned &value);

private:
    BitmapData getBitmap(QString pathImage, unsigned sizeScale);

    unsigned timeout; /**<Read and write operations timeout */
};

class BitmapData
{
public:
    QBitArray Dots;
    int Height;
    int Width;
};

#endif // ESCPOSPRINTER_H
