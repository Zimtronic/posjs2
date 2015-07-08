#ifndef ITICKETPRINTER_H
#define ITICKETPRINTER_H

#include "itransport.h"

   /**
    * @class ITicketPrinter
    * @brief Tickets printer interface
    *
    *
    * @author tony
    * @date 17-10-2014
    */

class QString;

class ITicketPrinter
{
public:
    /**
     * @brief Initialize printer: hardware configuration and write the init command
     */
    virtual unsigned init() = 0;

    /**
     * @brief Lets print raw text
     */
    virtual unsigned printRawText(QString text) = 0;

    /**
     * @brief Cut full or partial paper
     */
    virtual unsigned cutPaper(bool fullCut) = 0;

    /**
     * @brief Lets access to cash drawer pins
     */
    virtual unsigned sendPulseToCashDrawer(unsigned pin) = 0;

    /**
     * @brief Lets format text
     */
    virtual unsigned setTextProperties(unsigned align, unsigned font,
                                       unsigned type, unsigned width,
                                       unsigned height) = 0;

    /**
     * @brief Send feed control sequences
     */
    virtual unsigned feedControl(unsigned crl) = 0;

    /**
     * @brief Print bitmap image given a path
     */
    virtual unsigned printImage(QString pathImage, unsigned rightTab,
                                unsigned sizeScale) = 0;

    /**
     * @brief Print barcode
     */
    virtual unsigned printBarcode(QString code, unsigned type,
                                  unsigned width, unsigned height,
                                  unsigned pos, unsigned font) = 0;

    /**
     * @brief Print QR Code
     */
    virtual unsigned printQRCode(QString code, unsigned errCorrect,
                                 unsigned moduleSize) = 0;

    ITransport *getTransport() const;
    void setTransport(ITransport *value);

protected:
    ITransport * transport; /**< Pointer to generic transport */
};

inline ITransport *ITicketPrinter::getTransport() const
{
    return transport;
}

inline void ITicketPrinter::setTransport(ITransport *value)
{
    transport = value;
}

#endif // ITICKETPRINTER_H
