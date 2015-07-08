#ifndef ITRANSPORT_H
#define ITRANSPORT_H

   /**
    * @class ITransport
    * @brief Transport interface
    *
    * @author tony
    * @date 17-10-2014
    */

class ITransport
{
public:
    /**
     * @brief Open connection with device. Return an error code
     */
    virtual unsigned open() = 0;

    /**
     * @brief Close connection. Return an error code
     */
    virtual unsigned close() = 0;

    /**
     * @brief Try to read bufferSize bytes from the current interface.
     * The read bytes are storage in buffer. This function is synchronous,
     * wait timeOut ms for result
     */
    virtual unsigned read(unsigned char* buffer, unsigned &bufferSize,
                          unsigned timeOut) = 0;

    /**
     * @brief Try to write bufferSize bytes from the current interface,
     * bufferSize store bytes really written
     */
    virtual unsigned write(unsigned char* buffer, unsigned &bufferSize,
                           unsigned timeOut) = 0;
};

#endif // ITRANSPORT_H
