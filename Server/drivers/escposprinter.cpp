#include <iostream>
using namespace std;

#include "escposprinter.h"
#include "escposcommands.h"

ESCPOSPrinter::ESCPOSPrinter()
{
    this->timeout = 1000;
}

ESCPOSPrinter::~ESCPOSPrinter()
{
}

unsigned ESCPOSPrinter::init()
{
    cout << "ESCPOSPrinter::init" << endl;

    unsigned result = transport->open();
    if(result == OK)
    {
        unsigned len = INITLENGTH;
        result = transport->write(HW_INIT, len, this->timeout);
    }
    return result;
}

unsigned ESCPOSPrinter::printRawText(QString text)
{
    cout << "ESCPOSPrinter::printRawText: " << text.toStdString().c_str() << endl;

    unsigned textSize = text.length();
    unsigned result = transport->write((unsigned char*)text.toStdString().c_str(), textSize, this->timeout);
    return result;
}

unsigned ESCPOSPrinter::cutPaper(bool fullCut)
{
    cout << "ESCPOSPrinter::cutPaper: " << fullCut << endl;

    unsigned result = OK;
    unsigned len = PAPERCUTLENGTH;

    if(fullCut)
    {
        result = transport->write(PAPER_FULL_CUT, len, this->timeout);
    }
    else
    {
        result = transport->write(PAPER_PART_CUT, len, this->timeout);
    }
    return result;
}

unsigned ESCPOSPrinter::sendPulseToCashDrawer(unsigned pin)
{
    cout << "ESCPOSPrinter::sendPulseToCashDrawer: " << pin << endl;

    unsigned result = OK;
    unsigned len = CASHDRAWERLENGTH;

    switch (pin)
    {
    case 2:
        result = transport->write(CD_KICK_2, len, this->timeout);
        break;
    case 5:
        result = transport->write(CD_KICK_5, len, this->timeout);
        break;
    default:
        return errPrinterUndefineCashDrawerPin;
        break;
    }
    return result;
}

unsigned ESCPOSPrinter::setTextProperties(unsigned align, unsigned font,
                                          unsigned type, unsigned width,
                                          unsigned height)
{
    cout << "ESCPOSPrinter::setTextProperties: " << align <<
         ":"<<font <<":"<<type <<":"<<width <<":"<<height<< endl;

    unsigned result = OK;
    unsigned len = TEXTFORMATLENGTH;

    switch (align)
    {
    case 0: //center
        result = transport->write(TXT_ALIGN_CT, len, this->timeout);
        break;
    case 1: //right
        result = transport->write(TXT_ALIGN_RT, len, this->timeout);
        break;
    case 2: //left
        result = transport->write(TXT_ALIGN_LT, len, this->timeout);
        break;
    default:
        return errPrinterUndefineAlign;
        break;
    }

    if(result != OK)
        return result;

    if(font == 0) // A
    {
        result = transport->write(TXT_FONT_A, len, this->timeout);
    }
    else if(font == 1) // B
    {
        result = transport->write(TXT_FONT_B, len, this->timeout);
    }
    else
    {
        return errPrinterUndefineFont;
    }

    if(result != OK)
        return result;

    switch (type)
    {
    case 0: //B
        result = transport->write(TXT_BOLD_ON, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_UNDERL_OFF, len, this->timeout);
        break;
    case 1: //U
        result = transport->write(TXT_BOLD_OFF, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_UNDERL_ON, len, this->timeout);
        break;
    case 2: //U2
        result = transport->write(TXT_BOLD_OFF, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_UNDERL2_ON, len, this->timeout);
        break;
    case 3: //BU
        result = transport->write(TXT_BOLD_ON, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_UNDERL_ON, len, this->timeout);
        break;
    case 4: //BU2
        result = transport->write(TXT_BOLD_ON, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_UNDERL2_ON, len, this->timeout);
        break;
    case 5: //Normal
        result = transport->write(TXT_BOLD_OFF, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_UNDERL_OFF, len, this->timeout);
        break;
    default:
        return errPrinterUndefineType;
        break;
    }

    if(result != OK)
        return result;

    if(width == 2 && height != 2)
    {
        result = transport->write(TXT_NORMAL, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_2WIDTH, len, this->timeout);
    }
    else if(height == 2 && width != 2)
    {
        result = transport->write(TXT_NORMAL, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_2HEIGHT, len, this->timeout);
    }
    else if(height == 2 && width == 2)
    {
        result = transport->write(TXT_2WIDTH, len, this->timeout);
        if(result != OK)
            return result;
        result = transport->write(TXT_2HEIGHT, len, this->timeout);
    }
    else
    {
        result = transport->write(TXT_NORMAL, len, this->timeout);
    }
    return result;
}

unsigned ESCPOSPrinter::feedControl(unsigned crl)
{
    cout << "ESCPOSPrinter::feedControl: " << crl << endl;

    unsigned result = OK;
    unsigned len = FEEDCONTROLLENGTH;

    switch (crl)
    {
    case 0: //LF
        result = transport->write(CTL_LF, len, this->timeout);
        break;
    case 1: //FF
        result = transport->write(CTL_FF, len, this->timeout);
        break;
    case 2: //CR
        result = transport->write(CTL_CR, len, this->timeout);
        break;
    case 3: //HT
        result = transport->write(CTL_HT, len, this->timeout);
        break;
    case 4: //VT
        result = transport->write(CTL_VT, len, this->timeout);
        break;
    default:
        return errPrinterUndefineFeedControl;
        break;
    }
    return result;
}

unsigned ESCPOSPrinter::printImage(QString pathImage, unsigned rightTab,
                                   unsigned sizeScale)
{
    cout << "ESCPOSPrinter::printImage: " << pathImage.toStdString().c_str()
         <<":"<<rightTab<<":"<<sizeScale<< endl;

    BitmapData data = getBitmap(pathImage, sizeScale);
    QBitArray dots = data.Dots;

    union Mywidth
    {
        unsigned char byte[2];
        unsigned short widthshort;
    };

    Mywidth width;
    width.widthshort = data.Width;

    int offset = 0;
    unsigned cursor = 0;
    unsigned char buffer[22000];

    buffer[cursor++] = 0x1B;
    buffer[cursor++] = '@';

    buffer[cursor++] = 0x1B;
    buffer[cursor++] = '3';
    buffer[cursor++] = 24;

    while (offset < data.Height)
    {
        for (unsigned h = 0; h < rightTab; ++h)
        {
            buffer[cursor++] = 9;
        }

        buffer[cursor++] = 0x1B;
        buffer[cursor++] = '*';
        buffer[cursor++] = 33;
        buffer[cursor++] = width.byte[0];
        buffer[cursor++] = width.byte[1];

        for (int x = 0; x < data.Width; ++x)
        {
            for (int k = 0; k < 3; ++k)
            {
                char slice = 0;
                for (int b = 0; b < 8; ++b)
                {
                    int y = (((offset / 8) + k) * 8) + b;
                    int i = (y * data.Width) + x;
                    bool v = false;
                    if (i < dots.size())
                    {
                        v = dots[i];
                    }
                    slice |= (char)((v ? 1 : 0) << (7 - b));
                }
                buffer[cursor++] = slice;
            }
        }
        offset += 24;
        buffer[cursor++] = 0x0A;
    }
    buffer[cursor++] = 0x1B;
    buffer[cursor++] = '3';
    buffer[cursor++] = 30;

    unsigned result = transport->write(buffer, cursor, this->timeout);
    return result;
}

BitmapData ESCPOSPrinter::getBitmap(QString pathImage, unsigned sizeScale)
{
    QImage im(pathImage);
    im = im.convertToFormat(QImage::Format_Mono);

    if(im.width() > 480)
        im = im.scaledToWidth(480);
    if(im.height() > 480)
        im = im.scaledToHeight(480);

    QBitmap bitmap = QBitmap::fromImage(im, Qt::MonoOnly);

    int threshold = 127;
    int index = 0;

    if(sizeScale > 10)
        sizeScale = 10;

    double multiplier = 35*sizeScale;
    double scale = (double)(multiplier/(double)bitmap.width());
    int xheight = (int)(bitmap.height() * scale);
    int xwidth = (int)(bitmap.width() * scale);
    int dimensions = xwidth * xheight;
    QBitArray dots(dimensions);

    for (int y = 0; y < xheight; y++)
    {
        for (int x = 0; x < xwidth; x++)
        {
            double _x = (int)(x / scale);
            double _y = (int)(y / scale);
            QRgb color = bitmap.toImage().pixel(_x, _y);
            double luminance = (int)(qRed(color) * 0.3 + qGreen(color) * 0.59 +  qBlue(color) * 0.11);
            dots[index] = (luminance < threshold);
            index++;
        }
    }

    BitmapData data;
    data.Dots = dots;
    data.Height = (int)(bitmap.height()*scale);
    data.Width = (int)(bitmap.width()*scale);
    return data;
}

unsigned ESCPOSPrinter::printBarcode(QString code, unsigned type,
                                     unsigned width, unsigned height,
                                     unsigned pos, unsigned font)
{
    cout << "ESCPOSPrinter::printBarcode: " << code.toStdString().c_str() << endl;

    if(pos > 3)
        return errBarcodeTextPos;
    if(width < 2 || width > 6 || height < 1 || height > 255)
        return errBarcodeSize;
    if(type < 65 || type > 73)
        return errBarcodeType;

    unsigned index = 0;
    unsigned char cmd[32];
    cmd[index++] = 0x1D;
    cmd[index++] = 'H';
    cmd[index++] = pos; //0=no print, 1=above, 2=below, 3=above & below

    //GS f = set barcode characters
    cmd[index++] = 0x1D;
    cmd[index++] = 'f';
    cmd[index++] = font;

    //GS h = sets barcode height
    cmd[index++] = 0x1D;
    cmd[index++] = 'h';
    cmd[index++] = height;

    //GS w = sets barcode width
    cmd[index++] = 0x1D;
    cmd[index++] = 'w';
    cmd[index++] = width;//module = 1-6

    //GS k
    cmd[index++] = 0x1D;
    cmd[index++] = 'k';
    cmd[index++] = type; //m = barcode type 0-6
    cmd[index++] = code.length();

    unsigned result;
    result = transport->write(cmd, index, this->timeout);
    if(result != OK)
        return result;

    //Print Code
    unsigned codeSize = code.length();
    result = transport->write((unsigned char*)code.toStdString().c_str(), codeSize, this->timeout);
    if(result != OK)
        return result;

    unsigned char zero[] = {0x0};
    unsigned l = 1;
    result = transport->write(zero, l, this->timeout);
    return result;
}

unsigned ESCPOSPrinter::printQRCode(QString code, unsigned errCorrect,
                                    unsigned moduleSize)
{
    cout << "ESCPOSPrinter::printQRCode: " << code.toStdString().c_str() << endl;

    unsigned index = 0;
    unsigned char cmd[32];

    //save data function 80
    cmd[index++] = 0x1D;
    cmd[index++] = '(';
    cmd[index++] = 'k';//adjust height of barcode
    cmd[index++] = code.length()+3;
    cmd[index++] = 0;
    cmd[index++] = 49;
    cmd[index++] = 80;
    cmd[index++] = 48;

    unsigned result;
    result = transport->write(cmd, index, this->timeout);
    if(result != OK)
        return result;

    //Print Code
    unsigned codeSize = code.length();
    result = transport->write((unsigned char*)code.toStdString().c_str(), codeSize, this->timeout);
    if(result != OK)
        return result;

    index = 0;

    //error correction function 69
    cmd[index++] = 0x1D;
    cmd[index++] = '(';
    cmd[index++] = 'k';
    cmd[index++] = 3;
    cmd[index++] = 0;
    cmd[index++] = 49;
    cmd[index++] = 69;
    cmd[index++] = errCorrect; //48<= n <= 51

    //size function 67
    cmd[index++] = 0x1D;
    cmd[index++] = '(';
    cmd[index++] = 'k';
    cmd[index++] = 3;
    cmd[index++] = 0;
    cmd[index++] = 49;
    cmd[index++] = 67;
    cmd[index++] = moduleSize; //1<= n <= 16

    //print function 81
    cmd[index++] = 0x1D;
    cmd[index++] = '(';
    cmd[index++] = 'k';
    cmd[index++] = 3;
    cmd[index++] = 0;
    cmd[index++] = 49;
    cmd[index++] = 81;
    cmd[index++] = 48;

    result = transport->write(cmd, index, this->timeout);
    return result;
}

unsigned ESCPOSPrinter::getTimeout() const
{
    return timeout;
}

void ESCPOSPrinter::setTimeout(const unsigned &value)
{
    timeout = value;
}

QString ESCPOSPrinter::getErrorString(unsigned errorCode)
{
    if(errorCode > errPrinterUndefineType)
    {
        return QString("Undefine error code");
    }
    else
    {
        return QString(errorsString[errorCode]);
    }
}

