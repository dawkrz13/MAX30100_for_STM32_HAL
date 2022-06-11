#include "max30100_for_stm32_hal.h"
#include "pulse_detector.h"

#ifdef __cplusplus
extern "C"{
#endif

void measure_heart_rate(PULSE_DETECTOR* pd, uint16_t current_sample)
{
    uint8_t cond = (current_sample - pd->previous_sample > HR_PEAK_THRESHOLD) ? 1 : 0;
    if(cond && !pd->is_peak_detected)
    {
        pd->is_peak_detected = 1;
    }
    else if(cond && pd->is_peak_detected)
    {
        float num_seconds_between_peaks = pd->sample_counter / 100.0; // TODO: replace 100
        float bpm_f = (SECONDS_PER_MINUTE / num_seconds_between_peaks);
        if(bpm_f < BPM_MIN || bpm_f > BPM_MAX)
        {
            pd->sample_counter = 0;
            pd->is_data_ready = 0;
            pd->is_peak_detected = 0;
            return;
        }
        pd->bpm = (uint16_t)bpm_f;
        pd->sample_counter = 0;
        pd->is_data_ready = 1;
    }

    if(pd->is_peak_detected)
    {
        pd->sample_counter++;
    }

    pd->previous_sample = current_sample;
}

#ifdef __cplusplus
}
#endif