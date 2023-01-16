#ifndef DEVICE_TYPE_H
#define DEVICE_TYPE_H

/**
 * @brief The ihwapi_err_code_t enum
 */
enum ihwapi_err_code_t //TODO: error codes have to match those of hw::exception
{
    IHWAPI_OK = 0, ///< All is OK
    IHWAPI_HW_ERRORS = 1000,
    IHWAPI_NOT_SUPPORTED, ///< Unsopported command by this device
    IHWAPI_DEVICE_NOT_OPEN, ///< Device is not open
    IHWAPI_DEVICE_NOT_FOUND, ///< Device not found
    IHWAPI_INVALID_SERIAL,
    IHWAPI_INVALID_CONFIG,
    IHWAPI_INVALID_ARGUMENT, ///< One or more invalid arguments were used when calling an API function
    IHWAPI_BUSY ,///< Device is busy
    IHWAPI_ABORTED,
    IHWAPI_POWER_FAILURE, //9
    IHWAPI_PLL_FAILURE, //10
    IHWAPI_FLUSH_TIMEOUT, //11
    IHWAPI_NOT_RESPONDING, //12
    IHWAPI_NO_DATA, //13
    IHWAPI_FIRMWARE_ERROR, ///< Firmware error (invalid version or corrupted image)
    IHWAPI_FIRM_UPDT_FAILED,
    IHWAPI_DATA_NOT_ALIGNED,
    IHWAPI_DEVICE_FORGED,
    IHWAPI_HARDWARE_FAULT = 1100,
    IHWAPI_UNKNOWN_ERROR = 1999,///< Unknown error
    IHWAPI_USB_ERRORS = 2000,
    IHWAPI_USB3_ERRORS = 3000,

    IHWAPI_NOT_IMPLEMENTED = 99998,
};

/**
 * @brief The device_descriptor_t struct defines any device detected by the API
 */
struct device_descriptor_t
{
    /**
     * @brief sn pointer to Null terminated string for the serial number
     */
    char* sn;
    /**
     * @brief desc pointer to Null terminated string for the descriptions of the device
     */
    char* desc;
};

#endif // DEVICE_TYPE_H
