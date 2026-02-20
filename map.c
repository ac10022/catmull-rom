#include "map.h"
#include <math.h>
#include <string.h>
#include <assert.h>

#define POINT_RAD           10

#define TRACK_1_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4), (float)(WINDOW_HEIGHT/4)}    
#define TRACK_2_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4 + WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/4)}    
#define TRACK_3_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4), (float)(WINDOW_HEIGHT/4 + WINDOW_HEIGHT/2)}    
#define TRACK_4_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4 + WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/4 + WINDOW_HEIGHT/2)}    

static Color track_colors[] = { RED, GREEN, YELLOW, BLUE };

void AddNoteToMap(FILE* open_file, HitCircle* note) {
    fwrite(note, sizeof(HitCircle), 1, open_file);
}

void AddNotesToMap(const char* out_file, HitCircle* notes, size_t count) {
    FILE* open_file = fopen(out_file, "wb");

    if (open_file == NULL) {
        TraceLog(LOG_ERROR, "Unable to open file %s", out_file);
        return;
    } 

    for (size_t i = 0; i < count; i++)
        AddNoteToMap(open_file, &notes[i]);

    fclose(open_file);
}

HitCircle* ReadMap(const char* in_file, size_t* count) {
    FILE* file = fopen(in_file, "rb");
    if (file == NULL) {
        TraceLog(LOG_ERROR, "Unable to open file %s", in_file);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    size_t num_notes = file_size / sizeof(HitCircle);
    *count = num_notes; 
    if (num_notes == 0) {
        fclose(file);
        return NULL;
    }

    HitCircle* notes = (HitCircle*)calloc(num_notes, sizeof(HitCircle));
    if (notes == NULL) {
        fclose(file);
        return NULL;
    }

    size_t result = fread(notes, sizeof(HitCircle), num_notes, file);
    if (result != num_notes) {
        free(notes);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return notes;
}

void CatmullRom(
    float t, Vector2* out, Vector2* p_k0, Vector2* p_k1, Vector2* p_k2, Vector2* p_k3
) {
    float t_squared = t * t;
    float t_cubed = t_squared * t;

    Vector2 m_k1 = {
        .x = (p_k2->x - p_k0->x) / 2.0f,
        .y = (p_k2->y - p_k0->y) / 2.0f
    };

    Vector2 m_k2 = {
        .x = (p_k3->x - p_k1->x) / 2.0f,
        .y = (p_k3->y - p_k1->y) / 2.0f
    };

    float a1 = 2.0f * t_cubed - 3.0f * t_squared + 1.0f;
    float a2 = t_cubed - 2.0f * t_squared + t;
    float a3 = -2.0f * t_cubed + 3.0f * t_squared;
    float a4 = t_cubed - t_squared;

    out->x = a1 * p_k1->x + a2 * m_k1.x + a3 * p_k2->x + a4 * m_k2.x;
    out->y = a1 * p_k1->y + a2 * m_k1.y + a3 * p_k2->y + a4 * m_k2.y;
}

void MapSetup(unsigned int map_length, HitCircle* circles) {
    size_t count = 0;
    HitCircle* map_notes = ReadMap("map1.dat", &count);

    assert(count <= map_length && "Too many entries in this map.");
    map_length = (count < map_length) ? count : map_length;
    
    for (size_t i = 0; i < map_length; i++)
    {
        circles[i] = map_notes[i];
    }

    for (size_t i = 0; i < map_length; i++)
    {
        printf("circle[%ld] => { time = %f, track = %u }\n", i, circles[i].timestamp, circles[i].track);
    }
    
    free(map_notes);
}

void TrackSetup(Track* tracks, HitCircle* circles, unsigned int map_length) {
    tracks[0].pos = TRACK_1_STARTPOS;
    tracks[1].pos = TRACK_2_STARTPOS;
    tracks[2].pos = TRACK_3_STARTPOS;
    tracks[3].pos = TRACK_4_STARTPOS;

    for (size_t i = 0; i < 4; i++)
    {
        tracks[i] = (Track) {
            .color = track_colors[i],
            .size = POINT_RAD,
            .num_oncoming_positions = 0,
            .track_index = 0
        };

        unsigned int cur_index = 0;
        for (size_t search_index = 0; search_index < map_length; search_index++) {
            if (circles[search_index].track == i) {
                tracks[i].oncoming_positions[cur_index] = circles[search_index].pos;
                tracks[i].oncoming_timestamps[cur_index] = circles[search_index].timestamp;
                cur_index++;
            }
        }
        tracks[i].num_oncoming_positions = cur_index;

        // bubble sort to ensure that the tracks oncoming circles are in order based on timestamp
        for (size_t j = 0; j < tracks[i].num_oncoming_positions - 1; j++) {
            for (size_t k = j + 1; k < tracks[i].num_oncoming_positions; k++) {
                if (tracks[i].oncoming_timestamps[j] > tracks[i].oncoming_timestamps[k]) {
                    Vector2 temp_pos = tracks[i].oncoming_positions[j];
                    tracks[i].oncoming_positions[j] = tracks[i].oncoming_positions[k];
                    tracks[i].oncoming_positions[k] = temp_pos;

                    float temp_time = tracks[i].oncoming_timestamps[j];
                    tracks[i].oncoming_timestamps[j] = tracks[i].oncoming_timestamps[k];
                    tracks[i].oncoming_timestamps[k] = temp_time;
                }
            }
        }
    }
}

void UpdateTrackPositions(Track* tracks, float song_time) {
    for (size_t i = 0; i < 4; i++) {
        Track* track = &tracks[i];

        if (track->num_oncoming_positions < 2) continue;

        unsigned int k = 0; // find current segment

        while (k + 1 < track->num_oncoming_positions &&
               track->oncoming_timestamps[k + 1] <= song_time) {
            k++;
        }

        unsigned int p0_index = (k == 0) ? k : k - 1; 
        unsigned int p1_index = k;
        unsigned int p2_index = k + 1;
        unsigned int p3_index = (k + 2 >= track->num_oncoming_positions) ? p2_index : k + 2;

        float t0 = track->oncoming_timestamps[p1_index];
        float t1 = track->oncoming_timestamps[p2_index];

        float duration = t1 - t0;
        float t = (duration > 0) ? (song_time - t0) / duration : 0.1f;

        CatmullRom(
            t, &track->pos,
            &track->oncoming_positions[p0_index],
            &track->oncoming_positions[p1_index],
            &track->oncoming_positions[p2_index],
            &track->oncoming_positions[p3_index]
        );
    }
}

void RenderTracks(Track* tracks, float song_time) {
    for (size_t i = 0; i < 4; i++) {
        Track* track = &tracks[i];

        if (track->num_oncoming_positions < 2) continue;

        unsigned int j = 0; // find current segment

        while (j < track->num_oncoming_positions &&
            track->oncoming_timestamps[j] <= song_time) {
                j++;
            }
            
        if (j >= track->num_oncoming_positions) continue;
            
        Vector2* oncoming_hitcircle = &track->oncoming_positions[j];
        float target_time = track->oncoming_timestamps[j];

        float time_remaining = target_time - song_time;

        float k = 2.0f;
        float radius_factor = exp(-k * time_remaining);

        radius_factor = (radius_factor < 0.01f) ? 0.01f : (radius_factor > 1.0f) ? 1.0f : radius_factor;

        radius_factor = 1.0f / radius_factor;

        DrawCircleLinesV(
            *oncoming_hitcircle,
            POINT_RAD * radius_factor,
            track->color
        );

        DrawCircleV(track->pos, track->size, track->color);
    }
}