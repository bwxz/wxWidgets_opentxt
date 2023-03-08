/**
  * \file TopSyncImpairmentFile.hpp
  * Declaration of TopSyncImpairmentFile class.
  */
#ifndef TOPSYNC_IMPAIRMENT_FILE_HPP
#define TOPSYNC_IMPAIRMENT_FILE_HPP

#include "General.h"
#include "Exception.hpp"
#include <string>
#include <fstream>

using namespace std;
using namespace Semtech;

namespace
{
    const uint16 RESPONSE_BUFFER_SIZE = 2000;
};

/**
  * Class representing a ToPSync impairment file service.  Reads in a sequence of 65535 delay values from a
  * user-specified text file (if the file contains less than 65535 entries, starts again from the beginning
  * of the file).  Delay values in the file are assumed to be floating point values in seconds, occurring after
  * user specified number <fieldNumber - 1> tab characters.
  * Provides the requesting (TimeServer Master) client with n delays starting at position p in the 65k sequence,
  * n and p specified in the client request.  Wraps around when n + p > 65k.
  */
class TopSyncImpairmentFile
{
public:
    /**
      * Class constructor.  Reads in a file of impairment data containing up to 65535 delay values.
      * If the file contains less than 65535 entries, starts again from the beginning
      * of the file.  Delay values in the file are assumed to be floating point values in seconds, occurring after
      * user specified number <fieldNumber - 1> tab characters.
      * \param fileName The name of the impairment data file.
      * \param fieldNumber The number of the impairment data column.
      */
    TopSyncImpairmentFile(const string& fileName = "", uint16 fieldNumber = 0);

    /**
      * Get a sequence of n delays starting at position p in the 65k sequence. Wraps around when n + p > 65k.
      * \param number The number of delays.
      * \param pos The position of the first delay in the sequence.
      * \param responseBuffer The buffer into which the impairments are written.
      */
    void getImpairments(uint16 number, uint32 pos, uint8 responseBuffer[]);

    /**
      *  Get the name of the impairment file.
      * \return The impairment file name.
      */
    const string& getFileName(void) const;

    /**
      *  Get the field number in the impairment file.
      * \return The field number.
      */
    uint16 getFieldNumber(void) const;

    /**
      *  Class destructor.
      */
    ~TopSyncImpairmentFile(void);

private:

    /**
      *  Read the next set of impairments from the file.
      */
    void readImpairments(double impairments[]);

    /**
      *  The name of the impairment file.
      */
    string mFileName;

    /**
      *  The impairment file stream.
      */
    ifstream mFile;

    /**
      * The number of the impairment data column.
      */
    uint16 mFieldNumber;

    /**
      * The impairments.
      */
    double* mImpairments1;

    /**
      * The next impairments.
      */
    double* mImpairments2;

    /**
      * Pointer to current impairments buffer.
      */
    double* mCurrent;

    /**
      * Pointer to current impairments buffer.
      */
    double* mNext;

    /**
      * The maximum number of impairments to read ahead.
      */
    uint16 mMaxImpairments;

    /**
      * The current read threshold at which a read ahead is commenced.
      */
    uint16 mReadThreshold;

    /**
      * Flag indicating whether threshold should be checked.
      */
    bool mThresholdFlag;
};

#endif
 