#ifndef SP1000GAPI_TYPES_H
#define SP1000GAPI_TYPES_H

#include <stdint.h>
#include "ihwapi_common_types.h"


#if defined(GENERATE_API_WIN)
#define SCANA_API __declspec(dllexport)
#elif defined(GENERATE_API_UNIX)
#define SCANA_API __attribute__((visibility("default")))
#elif defined(GENERATE_API_MAC)
#include "ftd2xxUNIX.h"
#include "WinTypes.h"
#define SCANA_API __attribute__((visibility("default")))
#elif defined(OS_WIN)
#define SCANA_API __declspec(dllimport)
#else
#define SCANA_API
#endif

#define API_VER_MAJ 1
#define API_VER_MIN 0
#define API_VER_PAT 0

#define SP1054G

#ifdef SP1018G
#define SP1000G_GROUPS_COUNT (1)
#define SP1000G_CHANNELS_COUNT (18)
#define SP1000G_TRIG_ENGINES_COUNT (2)
#define SP1000G_THRESHOLDS_COUNT (2)
#define SP1000G_MAX_TRIG_STEPS_COUNT (256)
#define SP1000G_OCI_CLOCK_COUNT (2)
#endif

#ifdef SP1036G
#define SP1000G_GROUPS_COUNT (2)
#define SP1000G_CHANNELS_COUNT (36)
#define SP1000G_TRIG_ENGINES_COUNT (2)
#define SP1000G_THRESHOLDS_COUNT (4)
#define SP1000G_MAX_TRIG_STEPS_COUNT (256)
#define SP1000G_OCI_CLOCK_COUNT (2)
#endif

#ifdef SP1054G
#define SP1000G_GROUPS_COUNT (3)
#define SP1000G_CHANNELS_COUNT (54)
#define SP1000G_TRIG_ENGINES_COUNT (2)
#define SP1000G_THRESHOLDS_COUNT (6)
#define SP1000G_MAX_TRIG_STEPS_COUNT (256)
#define SP1000G_OCI_CLOCK_COUNT (2)
#endif


// enum sp1000ggapi_firmware_t
// {
//     SP1000GAPI_FW_FPGA = 0,
//     SP1000GAPI_FW_MCU = 1,
//     SP1000GAPI_RECOVERY_FW_MCU = 2,
// };

enum sp1000gapi_model_t
{
    sp1018g = 1018,
    sp1036g = 1036,
    sp1054g = 1054,
};

enum sp1000gapi_pull_t
{
    SP1000GAPI_PULL_DOWN = 0,
    SP1000GAPI_PULL_UP = 1,
};

enum sp1000gapi_io_type_t
{
    SP1000GAPI_IO_IN = 0,
    SP1000GAPI_IO_PP = 1,
    SP1000GAPI_IO_OD = 2
};

enum sp1000gapi_state_clk_mode_t
{
    SCLK_DISABLE = 0,
    SCLK_RISING = 1,  ///< Rising edge
    SCLK_FALLING = 2, ///< Falling edge
    SCLK_DUAL = 3,    ///< Dual edge (any rising or falling edge)
};

enum sp1000gapi_state_clk_source_t
{
    SCLK_CH9 = 0,
    SCLK_CH18 = 1,
};

enum sp1000gapi_timebase_clk_t
{
    TIMEBASE_INTERNAL = 3,
    TIMEBASE_EXTERNAL = 2,
};

/**
 * @brief The sp1000ggapi_trigger_type_t enum lists the different kind of trigger supported by the API
 */
enum sp1000gapi_trigger_type_t
{
    SP1000GAPI_TRG_NOTRIG = 99,
    SP1000GAPI_TRG_RISING = 1, //don't change this enum value
    SP1000GAPI_TRG_FALLING = 0, //don't change this enum value
    SP1000GAPI_TRG_CHANGE = 3,
    SP1000GAPI_TRG_EXT_RISING = 0x1F, //don't change this enum value
    SP1000GAPI_TRG_EXT_FALLING = 0x0F //don't change this enum value
};

#pragma pack(push, 4) //Ensure known packing on all platforms

struct sp1000gapi_trigger_description_t
{
    /**
     * @brief type is the type of trigger (e.g. falling edge, rising edge or logic change).
     */
    sp1000gapi_trigger_type_t type;
    /**
     * @brief channel set to the number of the channel concerned by the trigger,
     * or -1 if you wish to target all channels. (-1 is only valid for Logic Change
     * type of trigger)
     * @note channel is a 0 based index, i.e. first channel is 0.
     */
    int8_t channel;
};

/**
 * @brief The spx_settings_t struct exposes the options that need to be configured by the user via
 * various GUI options.
 */
struct sp1000gapi_settings_t
{
    /**
     * @brief Total number of samples requested by the user
     */
    int64_t sampling_depth;

    /**
     * @brief Total number of samples after the trigger
     */
    int64_t post_trig_depth;

    /**
     * @brief Sampling clock expressed in HZ
     */
    uint32_t s_clk;

    /**
     * @brief Trigger clock expressed in HZ
     */
    uint32_t t_clk[SP1000G_TRIG_ENGINES_COUNT]; //Should used need to adjust this in API?

    /**
     * @brief An array of thresholds expressed in mv
     * @warning this is not the target VCC, but the threshold
     */
    uint16_t thresh_capture_mv[SP1000G_THRESHOLDS_COUNT];

    /**
     * @brief An array of target VCC expressed in mv
     * @warning this is not the thredhold, but the target VCC!
     */
    uint16_t vcc_gen_mv[SP1000G_THRESHOLDS_COUNT];

    sp1000gapi_io_type_t io_type[SP1000G_CHANNELS_COUNT];
    sp1000gapi_pull_t io_pull[SP1000G_CHANNELS_COUNT];

    /**
     * @brief enable and config the use of external (AKA State mode)
     */
    sp1000gapi_state_clk_mode_t state_clk_mode;

    /**
     * @brief Select the channel to use for state clock
     */
    sp1000gapi_state_clk_source_t state_clk_src;

    sp1000gapi_timebase_clk_t timebase_src;

    /**
     * @brief activate the 50R input resistor on Ext. Trig input
     */
    bool ext_trig_50r;


    uint16_t ext_in_threshold_mv;

    bool ext_trig_out_polarity;

    //This is automatically set when starting a new capture (deduced from trigger configuration)
    // /**
    //  * @brief ext_trig_in_polarity selects the active edge for the external trigger
    //  * false: Faling edge
    //  * true: Rising edge
    //  */
    // bool ext_trig_in_polarity[SP1000G_TRIG_ENGINES_COUNT];

    // /**
    //  * @brief enable (and use) Ext Trig In as trigger source
    //  */
    // bool ext_trig_in[SP1018G_TRIG_ENGINES_COUNT];

    /**
     * @brief 2 bits describing the operation of the dual trigger engine
     * @details the 2 LSB bits describe the operation of the dual trigger engine
     * as the following:
     * - 00: Trig 0 or Trig 1 (any of the two trigger engines will cause the trigger to be valid)
     * - 01: Trig 0 then Trig 1 (Trig 1 is only enabled after Trig 1 occures)
     * - 10: Trig 1 then Trig 0 (Trig 0 is only enabled after Trig 0 occures)
     * - 11: Trig 0 and Trig 1, in any order.
     */
    uint8_t trig_order;

    //OCI part
    bool oci_clk_out_enable[SP1000G_GROUPS_COUNT][SP1000G_OCI_CLOCK_COUNT];
    uint64_t oci_clk_out_freq[SP1000G_GROUPS_COUNT][SP1000G_OCI_CLOCK_COUNT];
};

/**
 * @brief The sp1000gapi_trs_t struct describes an SP1000G transition on a given channel
 * @details SP1000G API provides captured samples in minimal structures called "transition".
 * During a transition, one or more chanel's logic level change. This structure describes this
 * transition.
 */
struct sp1000gapi_trs_t
{
    uint8_t value; //Line value
    /**
     * @brief delta_samples Number of samples since the previous transition
     */
    uint64_t sampple_index; //index of the same associated with that transition
};


#pragma pack(pop)

#endif // SP1018GAPI_TYPES_H
