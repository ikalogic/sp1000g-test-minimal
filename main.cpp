

#include "iostream"
#include "sp1000gapi.h"
#include <chrono>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <string.h>
#include <iostream>

void msleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


void assert_err(ihwapi_err_code_t e)
{
    if (e != ihwapi_err_code_t::IHWAPI_OK)
    {
        std::cout << "Error thrown by API " << uint32_t(e) << std::endl;
        throw std::runtime_error("unhandled error");
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "SP1018G API Test" << std::endl;

    ihwapi_err_code_t e;
    sp1000gapi_handle h = nullptr;

    e = sp1000gapi_create_new_handle(&h, sp1000gapi_model_t::sp1054g);
    assert_err(e);

    e = sp1000gapi_create_device_list(h);
    assert_err(e);

    e = sp1000gapi_device_open_first(h);
    assert_err(e);

    std::cout << "Device open and ready\n"
              << std::endl;

    sp1000gapi_settings_t settings;
    memset(&settings, 0, sizeof(settings));
    settings.s_clk = 250e6;
    settings.vcc_gen_mv[0] = 3000;
    settings.vcc_gen_mv[1] = 3000;
    settings.ext_trig_50r = false;
    settings.timebase_src = sp1000gapi_timebase_clk_t::TIMEBASE_INTERNAL;
    settings.state_clk_mode = sp1000gapi_state_clk_mode_t::SCLK_DISABLE;
    settings.state_clk_src = sp1000gapi_state_clk_source_t::SCLK_CH9;
    settings.sampling_depth = 10e6;                           // 50e6;
    settings.post_trig_depth = settings.sampling_depth * 0.9; // 5000e6; //float(settings.sampling_depth)*0.1f;
    settings.thresh_capture_mv[0] = 1000;
    settings.thresh_capture_mv[1] = 1000;
    settings.ext_in_threshold_mv = 1000;
    settings.ext_trig_out_polarity = true; // rising

    for (int ch = 0; ch < SP1000G_CHANNELS_COUNT; ch++)
    {
        settings.io_type[ch] = SP1000GAPI_IO_IN;
        settings.io_pull[ch] = SP1000GAPI_PULL_DOWN;
    }

    sp1000gapi_trigger_description_t trig_a, trig_b;
    trig_a.type = sp1000gapi_trigger_type_t::SP1000GAPI_TRG_NOTRIG;
    trig_a.channel = -1;
    trig_b.type = sp1000gapi_trigger_type_t::SP1000GAPI_TRG_NOTRIG;
    trig_b.channel = -1;

    e = sp1000gapi_get_last_error(h);
    e = sp1000gapi_launch_new_capture_simple_trigger(h, trig_a, trig_b, settings);
    e = sp1000gapi_get_last_error(h);
    assert_err(e);

    bool cfg_done = false;
    while (cfg_done == false)
    {
        e = sp1000gapi_get_config_done_flag(h, &cfg_done);
        assert_err(e);
        msleep(10);
    }
    std::cout << "cfg done!\n"
              << std::endl;

    bool trg_flag = false;
    while (trg_flag == false)
    {
        std::cout << "Waiting for trigger" << std::endl;
        e = sp1000gapi_get_triggered_flag(h, &trg_flag);
        assert_err(e);
        msleep(100);
    }

    std::cout << "Trigged, ready for data!" << std::endl;

    int64_t total = 0;
    int64_t pre = 0;
    int64_t post = 0;

    while (post < settings.post_trig_depth)
    {
        e = sp1000gapi_get_available_samples(h, &total, &post);
        assert_err(e);
        msleep(100);

        std::cout << "retrieved transitions, pre-trig: " << pre / 1000 << +"K, post-trig:" << post / 1000 << "K" << std::endl;
    }

    e = sp1000gapi_get_last_error(h);
    assert_err(e);

    e = sp1000gapi_request_abort(h);
    assert_err(e);

    bool ready = false;
    while (!ready)
    {
        std::cout << "Waiting for abort\n"
                  << std::endl;
        msleep(100);
        e = sp1000gapi_get_ready_flag(h, &ready);
        assert_err(e);
    }

    e = sp1000gapi_free(h);
    assert_err(e);
    std::cout << "device freed\n"
              << std::endl;

    return 0;
}
