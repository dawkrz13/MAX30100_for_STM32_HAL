#ifndef PULSE_DETECTOR_H
#define PULSE_DETECTOR_H

#define HR_BEAT_THRESHOLD  700
#define BPM_MIN            40
#define BPM_MAX            160
#define SECONDS_PER_MINUTE 60.0
#define NUM_SAMPLES        500

typedef enum
{
    STATE_IDLE,
    STATE_IN_PROGRESS,
    STATE_READY
} PULSE_DETECTOR_STATE;

typedef struct
{
    uint32_t bpm;
    size_t idx;
    uint16_t previous_sample;
    uint16_t is_algo_running;
    uint16_t sample_counter;
    uint16_t ir_buffer[NUM_SAMPLES];
    PULSE_DETECTOR_STATE state;
} PULSE_DETECTOR;

static inline void reset_detector(PULSE_DETECTOR* pd)
{
    pd->bpm = 0;
    pd->idx = 0;
    pd->previous_sample = 0;
    pd->is_algo_running = 0;
    pd->sample_counter  = 0;
    pd->state = STATE_IDLE;
}

void measure_heart_rate(PULSE_DETECTOR* pd, uint16_t current_sample);

#endif