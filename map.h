#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define MAX_MAP_LENGTH          1024
#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       600

typedef struct {
    Vector2 pos;
    unsigned char track;
    float timestamp;
} HitCircle;

typedef struct {
    Vector2 pos;
    Color color;
    unsigned int size;
    Vector2 oncoming_positions[MAX_MAP_LENGTH];
    float oncoming_timestamps[MAX_MAP_LENGTH];
    unsigned int num_oncoming_positions;
    unsigned int track_index;
} Track;

void AddNoteToMap(FILE* open_file, HitCircle* note);
void AddNotesToMap(const char* out_file, HitCircle* notes, size_t count);
HitCircle* ReadMap(const char* in_file, size_t* count);
void CatmullRom(float t, Vector2* out, Vector2* p_k0, Vector2* p_k1, Vector2* p_k2, Vector2* p_k3);
void MapSetup(unsigned int map_length, HitCircle* circles);
void TrackSetup(Track* tracks, HitCircle* circles, unsigned int map_length);
void UpdateTrackPositions(Track* tracks, float song_time);
void RenderTracks(Track* tracks, float song_time);

#endif