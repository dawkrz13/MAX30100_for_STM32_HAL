#ifndef PULSE_DETECTOR_H
#define PULSE_DETECTOR_H

#define HR_PEAK_THRESHOLD  700
#define BPM_MIN            40
#define BPM_MAX            160
#define SECONDS_PER_MINUTE 60.0
/*
typedef enum
{
    STATE_IDLE,
    STATE_READY
} PULSE_DETECTOR_STATE;
*/

typedef struct
{
    uint16_t bpm;
    uint16_t previous_sample;
    uint16_t sample_counter;
    uint16_t is_peak_detected;
    uint16_t is_data_ready;
} PULSE_DETECTOR;

void measure_heart_rate(PULSE_DETECTOR* pd, uint16_t current_sample);

#endif