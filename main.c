#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

#include "map.h"
#include "raylib.h"

void WindowSetup(void) {
    srand(time(NULL));
    SetConfigFlags(
        FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI
    );
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bezier");
}

int main(void) {
    WindowSetup();

    InitAudioDevice();
    Sound s = LoadSound("audio.mp3");
    SetSoundVolume(s, 0.1f);

    HitCircle* circles = (HitCircle*)calloc(MAX_MAP_LENGTH, sizeof(HitCircle));
    MapSetup(MAX_MAP_LENGTH, circles);

    Track* tracks = (Track*)calloc(4, sizeof(Track));
    TrackSetup(tracks, circles, MAX_MAP_LENGTH);
    PlaySound(s);

    while (!WindowShouldClose()) {
        float song_time = GetTime();

        UpdateTrackPositions(tracks, song_time);

        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawText(TextFormat("%f\n", song_time), 10, 10, 20, WHITE);
        RenderTracks(tracks, song_time);

        EndDrawing();
    }

    UnloadSound(s);
    CloseAudioDevice();

    free(circles);
    free(tracks);
    CloseWindow();
}