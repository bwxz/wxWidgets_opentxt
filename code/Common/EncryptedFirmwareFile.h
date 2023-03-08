/*
 * © Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097 
 * U.S.A. All rights reserved. The copyright of the content of this file 
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of 
 * this file must not be copied or disclosed unless authorised in 
 * writing by Semtech.  
 *
 * $Workfile: EncryptedFirmwareFile.h $
 * $Revision: 1 $
 * $Date: 25/07/07 13:41 $
 */
 
/**
 * \file EncryptedFirmwareFile.h
 * Defines a class the represents an encrypted firmware file.
 */

#include "General.h"
#include "TEAFunctions.h"
#include <fstream>

/**
 * Random byte offsets, used for hiding the encryption key
 * within a firmware buffer.
 */
#define ENCRYPTION_KEY_OFFSET_BYTE_0    0x384
#define ENCRYPTION_KEY_OFFSET_BYTE_1    0x192
#define ENCRYPTION_KEY_OFFSET_BYTE_2    0x896
#define ENCRYPTION_KEY_OFFSET_BYTE_3    0x573
#define ENCRYPTION_KEY_OFFSET_BYTE_4    0x125
#define ENCRYPTION_KEY_OFFSET_BYTE_5    0x783
#define ENCRYPTION_KEY_OFFSET_BYTE_6    0x493
#define ENCRYPTION_KEY_OFFSET_BYTE_7    0x966
#define ENCRYPTION_KEY_OFFSET_BYTE_8    0x690
#define ENCRYPTION_KEY_OFFSET_BYTE_9    0x706
#define ENCRYPTION_KEY_OFFSET_BYTE_10   0x430
#define ENCRYPTION_KEY_OFFSET_BYTE_11   0x812
#define ENCRYPTION_KEY_OFFSET_BYTE_12   0x107
#define ENCRYPTION_KEY_OFFSET_BYTE_13   0x586
#define ENCRYPTION_KEY_OFFSET_BYTE_14   0x203
#define ENCRYPTION_KEY_OFFSET_BYTE_15   0x666


/**
 * Default encryption key.
 * This is temporary until I find the time to
 * hide the key in the encrypted file.
 */
#define DEFAULT_ENCRYPTION_KEY_WORD_0 0xABCDEF99
#define DEFAULT_ENCRYPTION_KEY_WORD_1 0x12345678
#define DEFAULT_ENCRYPTION_KEY_WORD_2 0x5a5a5a5a
#define DEFAULT_ENCRYPTION_KEY_WORD_3 0x01010101

using namespace std;

class EncryptedFirmwareFile
{
public:
    /**
     * Default constructor.
     */
    EncryptedFirmwareFile();

    /**
     * Constructor. Opens a firmware file with the given file name.
     * \param fileName          Name of the file to open.
     */
    EncryptedFirmwareFile(const char* fileName, ios_base::openmode mode);

    /**
     * Destructor.
     */
    ~EncryptedFirmwareFile();

    /**
     * Opens a firmware file in read/write/binary mode.
     * \param fileName          Name if the file to open.
     */
    bool Open(const char* fileName, ios_base::openmode mode);

    /**
     * Closes the firmware file.
     */
    void Close(void);

    /**
     * Checks if the file has been opened correctly.
     * \return      true if file is open, false otherwise.
     */
    bool IsOpen(void);

    /**
     * Encrypts the given buffer in bursts of 128 bytes and stores the
     * result in the opened file. This function will also store the
     * encryption key within the firmware buffer. The encryption key is
     * hidden in random byte offsets.
     * \param firmwareBuffer    Pointer to the firmware buffer.
     * \param encryptionKey     The TEA encryption key. Used for encrypting
     *                          the firmware data
	 * \param numSectors		Number of sectors in image file
     * \return                  true on success, false if the file is not open.
     */
    bool Encrypt(uint8* firmwareBuffer, const uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS], const uint8 numSectors);

    /**
     * Reads data from the opened file, decrypts it in burst of 128 bytes
     * and stores it into the given buffer. This function will also retrieve
     * the encryption key from the firmware buffer. The encryption key is
     * hidden in random byte offsets.
     * \param firmwareBuffer    Pointer to the firmware buffer.
     * \param encryptionKey     The TEA encryption key. Can be NULL or 0 if
     *                          note required.
     * \return                  true on success, false if the file is not open. 
     */
    bool Decrypt(uint8* firmwareBuffer, uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS]);


    /**
     * Reads data from the opened file, decrypts it in burst of 128 bytes
     * and stores it into the given buffer. This function will also retrieve
     * the encryption key from the firmware buffer. The encryption key is
     * hidden in random byte offsets.
     * \param firmwareBuffer    Pointer to the firmware buffer.
     * \param encryptionKey     The TEA encryption key. Can be NULL or 0 if
     *                          note required.
	 * \param numSectors		Number of sectors in image file
	 * \param startOffset		Where to start reading from (used for sfc files)
     * \return                  true on success, false if the file is not open. 
     */
    bool Decrypt(uint8* firmwareBuffer, uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS], const uint8 numSectors, uint32 startOffset);


private:
    /**
     * Assignment operator. Private to prevent assignment of EncryptedFirmwareFile
     * objects.
     */
	/* Change JHume: Add return type to appease VS2010 compiler */
    EncryptedFirmwareFile& EncryptedFirmwareFile::operator=(const EncryptedFirmwareFile& rhs);
    
    /**
     * Copy constructor. Private to prevent copy construction of EncryptedFirmwareFile
     * objects.
     */
    EncryptedFirmwareFile(const EncryptedFirmwareFile& obj);
    
    /**
     * Stores the TEA encryption key within the encrypted firmware file. This function 
     * will take a 128-bit encryption key and store it in random byte offsets within
     * sector 0 of the encrypted firmware file. Sector 0 is not used (but allocated
     * anyway) as it is reserved for the boot code and is therefore not uploaded 
     * to a ToPSync device.
     * \param encryptionKey     The encryption key to be hidden.
     */
    void StoreEncryptioKey(const uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS]);

    /**
     * Retrieves the TEA encryption key from the encrypted firmware buffer. This function 
     * will retrieve a 128-bit encryption key from the encrypted firmware file by reading
     * appropriate byte offsets. The encryption key is stored in random offsets in sector 0 
     * of the firmware buffer. Sector 0 is not used as it is reserved for the boot code and 
     * is therefore not uploaded to a ToPSync device.
     * \param encryptionKey     The encryption key to be hidden.
     */
    void RetrieveEncryptioKey(uint32 encryptionKey[ENCRYPTION_KEY_LENGTH_WORDS]);
    
    /**
     * The firmware file.
     */
    fstream mFirmwareFile;
};