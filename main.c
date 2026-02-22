#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

#include "map.h"
#include "raylib.h"

#define FALLBACK_FPS      60

void WindowSetup(void) {
    srand(time(NULL));
    SetConfigFlags(
        FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI
    );

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Catmull-Rom");

    int refresh_rate = GetMonitorRefreshRate(GetCurrentMonitor());

    if (refresh_rate > 0) {
        TraceLog(LOG_INFO, TextFormat("Detected refresh rate at %dFPS", refresh_rate));
    }
    else {
        TraceLog(LOG_WARNING, TextFormat("Could not detect monitor refresh rate, falling back to %dFPS", FALLBACK_FPS));
        refresh_rate = FALLBACK_FPS;
    }
    
    SetTargetFPS(refresh_rate * 2);

    //ToggleFullscreen();
}

int main(void) {
    WindowSetup();

    //MakeMap();

    InitAudioDevice();
    Music m = LoadMusicStream("audio.mp3");

    if (!IsMusicValid(m)) {
        TraceLog(LOG_ERROR, "Invalid music source; could not load properly");
    }

    HitCircle* circles = (HitCircle*)calloc(MAX_MAP_LENGTH, sizeof(HitCircle));
    MapSetup(MAX_MAP_LENGTH, circles);

    Track* tracks = (Track*)calloc(4, sizeof(Track));
    TrackSetup(tracks, circles, MAX_MAP_LENGTH);
    PlayMusicStream(m);
    
    if (!IsMusicStreamPlaying(m)) {
        TraceLog(LOG_ERROR, "Could not play music");
    }

    unsigned int frame_counter = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(m);
        float song_time = GetMusicTimePlayed(m);

        UpdateTrackPositions(tracks, song_time, frame_counter);
        CheckForKeyPresses(tracks, song_time);

        BeginDrawing();
        ClearBackground(BLACK);

        int fps = GetFPS();
        
        DrawText(TextFormat("%f\n", song_time), 10, 10, 20, WHITE);
        DrawText(TextFormat("%dFPS\n", fps), 10, 40, 20, WHITE);

        RenderTracks(tracks, song_time);

        EndDrawing();

        frame_counter++;
    }

    UnloadMusicStream(m);
    CloseAudioDevice();

    for (int i = 0; i < 4; i++) {
        if (tracks[i].pathLUT != NULL) {
            free(tracks[i].pathLUT);
        }
    }
    free(circles);
    free(tracks);

    CloseWindow();
}