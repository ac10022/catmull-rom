#include "map.h"
#include <math.h>
#include <string.h>
#include <assert.h>

#define POINT_RAD           20

#define RAND_POINT          (Vector2){(float)((rand()%(WINDOW_WIDTH/2)) + WINDOW_WIDTH/4), (float)((rand()%(WINDOW_HEIGHT/2)) + WINDOW_HEIGHT/4)}

#define TRACK_1_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4), (float)(WINDOW_HEIGHT/4)}    
#define TRACK_2_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4 + WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/4)}    
#define TRACK_3_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4), (float)(WINDOW_HEIGHT/4 + WINDOW_HEIGHT/2)}    
#define TRACK_4_STARTPOS    (Vector2){(float)(WINDOW_WIDTH/4 + WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/4 + WINDOW_HEIGHT/2)}    

static Color track_colors[] = { RED, GREEN, YELLOW, BLUE };

float LinearlyInterpolate(float start, float end, float amount) {
    return start + amount * (end - start);
}

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

void MakeMap(void) {
    HitCircle* notes = (HitCircle*)calloc(969, sizeof(HitCircle));
    size_t i = 0;
	
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 3.309f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 3.513f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 3.717f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 3.717f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 4.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 4.533f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 4.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 4.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 5.145f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 5.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 5.349f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 5.962f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 6.166f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 6.166f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 6.574f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 6.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 6.982f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 6.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 7.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 7.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 7.798f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 8.206f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 8.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 8.615f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 8.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 9.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 9.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 9.431f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 9.839f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 10.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 10.247f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 10.247f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 10.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 10.655f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 10.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.064f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.268f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.676f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.88f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 11.88f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 12.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 12.288f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 12.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 12.696f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 12.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 12.9f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 13.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 13.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 13.513f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 13.513f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 13.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 14.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 14.329f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 14.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 14.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 14.737f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 14.941f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 15.145f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 15.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 15.349f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 15.757f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 15.962f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 15.962f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 16.37f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 16.574f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 16.778f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 16.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 16.982f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 17.186f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 17.39f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 17.594f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 17.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 17.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 18.002f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 18.206f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 18.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 18.411f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 18.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 18.819f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 19.023f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 19.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 19.227f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 19.431f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 19.635f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 19.839f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 20.043f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 20.043f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 20.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 20.655f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 20.86f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 20.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 21.064f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 21.268f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 21.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 22.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 22.9f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.309f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.513f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.717f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 23.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.125f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.329f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.737f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.941f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 24.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.349f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.553f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.757f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.757f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 25.962f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.166f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.37f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.574f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.574f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.778f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.982f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 26.982f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 27.186f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 27.39f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 27.39f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 27.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 27.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 27.798f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.002f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.206f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.411f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.615f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.819f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 28.819f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.023f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.023f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.227f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.431f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.635f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.839f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 29.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.247f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.247f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.451f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.655f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 30.86f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.064f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.064f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.268f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.472f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.88f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 31.88f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.084f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.288f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.696f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 32.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.104f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.309f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.513f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.513f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 33.921f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.125f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.329f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.533f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.737f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.737f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 34.941f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 35.145f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 35.553f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 35.553f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 35.962f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 35.962f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.37f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.37f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.574f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.778f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 36.982f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 37.186f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 37.186f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 37.39f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 37.594f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 37.594f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 37.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.002f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.002f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.206f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.411f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.819f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 38.819f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.023f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.227f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.635f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.635f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 39.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.247f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.451f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.451f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.655f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.86f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 40.86f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.268f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.268f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.676f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 41.88f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.084f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.288f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.492f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.696f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.9f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 42.9f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.104f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.309f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.513f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.717f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 43.921f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.125f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.329f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.533f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.737f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.941f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 44.941f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.553f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.757f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.757f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 45.962f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.166f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.37f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.574f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.574f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.982f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 46.982f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 47.186f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 47.39f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 47.39f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 47.594f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 47.798f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 48.002f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 48.206f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 48.411f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 48.615f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.023f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.023f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.227f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.431f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.635f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 49.839f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 50.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 50.247f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 50.247f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 50.451f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 50.655f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 50.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.064f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.268f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.472f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.676f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.88f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 51.88f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 52.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 52.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 52.492f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 52.696f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 52.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 52.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 53.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 53.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 53.513f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 53.513f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 53.717f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 53.921f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 54.125f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 54.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 54.329f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 54.533f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 54.737f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 54.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.145f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.349f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.553f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.757f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.962f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 55.962f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 56.166f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 56.37f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 56.574f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 56.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 56.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 56.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 57.186f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 57.39f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 57.594f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 57.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 57.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 58.002f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 58.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 58.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 58.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 58.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 58.819f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 59.023f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 59.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 59.227f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 59.431f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 59.635f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 59.839f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 60.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 60.043f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 60.247f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 60.247f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 60.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 61.064f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 61.676f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 61.88f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 62.084f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 62.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 62.288f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 62.492f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 62.696f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 62.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 63.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 63.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 63.513f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 63.717f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 63.921f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 64.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 64.329f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 64.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 64.737f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 64.941f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 65.145f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 65.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 65.553f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 65.757f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 65.962f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 66.166f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 66.37f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 66.574f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 66.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 66.982f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 67.186f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 67.39f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 67.594f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 67.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 68.002f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 68.206f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 68.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 68.615f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 68.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 68.819f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 69.023f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 69.227f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 69.431f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 69.635f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 69.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 70.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 70.247f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 70.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 70.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 70.86f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 71.064f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 71.268f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 71.472f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 71.676f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 71.88f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 72.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 72.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 72.492f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 72.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 72.9f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.104f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.309f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.717f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 73.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 74.125f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 74.125f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 74.533f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 74.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 74.737f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 74.737f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.145f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.349f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.553f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.757f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 75.962f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 76.37f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 76.574f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 76.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 77.186f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 77.39f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 77.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 77.798f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 77.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.002f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.002f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.206f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.615f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.819f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 78.819f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.023f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.227f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.227f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.431f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.635f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.635f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 79.839f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.043f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.247f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.451f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.451f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 80.86f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.064f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.268f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.268f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.472f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.676f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 81.88f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.084f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.492f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.492f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.696f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.9f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 82.9f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.104f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.309f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.309f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.513f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.717f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.717f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 83.921f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.125f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.533f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.737f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 84.941f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.145f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.349f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.553f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.757f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.757f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 85.962f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 86.166f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 86.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 86.37f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 86.574f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 86.574f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 86.982f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 87.39f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 87.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 87.798f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.002f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.206f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.615f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 88.819f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.023f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.023f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.227f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.431f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.635f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.839f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 89.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.247f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.247f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.451f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.655f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.655f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 90.86f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.064f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.268f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.472f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.472f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.676f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.88f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 91.88f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.288f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.696f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 92.9f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.104f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.104f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.513f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.513f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 93.921f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.125f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.125f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.329f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.329f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.533f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.533f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.737f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.737f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 94.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.145f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.349f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.553f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.553f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.757f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.962f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 95.962f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.166f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.37f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.37f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.574f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.778f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 96.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 97.186f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 97.186f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 97.39f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 97.594f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 97.594f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 97.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.002f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.002f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.615f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.819f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 98.819f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.023f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.227f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.431f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.635f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.635f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 99.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.043f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.247f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.655f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.655f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.86f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 100.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 101.268f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 101.472f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 101.676f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 101.676f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 101.88f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.084f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.492f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.492f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.9f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 102.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.104f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.309f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.513f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.717f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.717f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 103.921f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.125f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.329f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.533f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.737f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.941f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 104.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.553f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.757f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.757f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 105.962f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.166f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.37f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.574f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.574f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.982f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 106.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 107.186f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 107.186f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 107.39f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 107.39f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 107.594f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 107.798f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.002f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.206f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.615f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 108.819f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.023f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.023f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.227f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.431f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.431f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.635f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.839f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 109.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.247f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.247f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.655f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 110.86f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.064f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.064f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.268f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.472f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.88f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 111.88f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.084f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.288f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.696f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.696f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 112.9f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 113.104f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 113.309f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 113.717f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 113.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 113.921f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 113.921f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 116.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 117.594f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 117.594f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 117.798f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.002f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.002f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.206f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.411f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.615f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.819f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 118.819f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.023f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.227f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.227f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.431f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.635f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.635f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 119.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.247f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.451f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.451f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 120.86f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.268f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.268f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.472f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.676f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 121.88f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.084f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.084f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.492f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.696f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.9f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 122.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.104f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.309f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.309f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.513f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.513f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.717f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 123.921f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.125f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.125f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.737f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.941f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 124.941f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.553f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.757f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.757f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 125.962f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.166f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.166f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.37f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.574f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.574f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.982f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 126.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 127.186f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 127.39f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 127.39f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 127.594f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 127.798f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 127.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.002f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.206f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.411f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.615f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.615f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 128.819f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.023f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.023f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.227f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.635f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.635f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.839f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 129.839f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 130.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 130.043f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 130.247f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 130.451f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 130.655f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.064f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.064f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.268f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.472f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.676f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.88f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 131.88f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.084f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.288f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.288f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.696f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 132.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.104f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.104f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.309f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.513f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.513f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.717f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 133.921f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.125f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.329f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.737f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.737f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 134.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.145f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.145f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.553f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.553f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.757f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.962f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 135.962f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.37f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.37f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.574f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.574f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.778f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.778f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.982f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 136.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 137.186f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 137.186f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 137.39f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 137.594f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 137.594f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 137.798f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.002f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.002f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.411f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.411f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.615f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.819f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 138.819f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.023f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.227f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.227f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.431f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.635f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.635f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 139.839f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.043f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.043f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.247f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.451f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.86f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 140.86f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.064f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.268f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.268f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.472f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.676f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 141.88f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.084f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.084f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.288f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.492f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.492f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.696f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.9f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 142.9f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 143.309f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 143.309f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 143.513f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 143.717f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 143.717f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 144.125f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 144.533f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 144.533f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 144.941f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 145.145f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 145.349f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 145.349f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 145.553f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 145.962f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.166f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.166f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.37f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.574f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.778f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.982f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 146.982f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 147.39f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 147.798f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 147.798f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 148.206f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 148.411f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 148.615f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 148.615f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 148.819f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 149.227f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 149.431f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 149.431f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 149.635f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 149.839f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.043f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.247f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.247f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.451f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.655f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.655f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 150.86f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.064f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.064f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.268f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.472f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.472f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.676f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.88f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 151.88f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.084f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.288f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.288f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.492f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.696f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.696f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 152.9f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.104f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.104f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.309f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.513f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.513f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.717f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.921f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 153.921f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.125f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.329f, .track = 2 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.329f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.533f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.737f, .track = 1 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.737f, .track = 3 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.941f, .track = 0 };
	notes[i++] = (HitCircle){ .pos = RAND_POINT, .timestamp = 154.941f, .track = 2 };
		
    AddNotesToMap("map1.dat", notes, 969);
    free(notes);
}

void CatmullRom(float t, Vector2* out, Vector2* p_k0, Vector2* p_k1, Vector2* p_k2, Vector2* p_k3) {
    float t_squared = t * t;
    float t_cubed = t_squared * t;

    Vector2 m_k1 = { .x = (p_k2->x - p_k0->x) / 2.0f, .y = (p_k2->y - p_k0->y) / 2.0f };
    Vector2 m_k2 = { .x = (p_k3->x - p_k1->x) / 2.0f, .y = (p_k3->y - p_k1->y) / 2.0f };

    float a1 = 2.0f * t_cubed - 3.0f * t_squared + 1.0f;
    float a2 = t_cubed - 2.0f * t_squared + t;
    float a3 = -2.0f * t_cubed + 3.0f * t_squared;
    float a4 = t_cubed - t_squared;

    out->x = a1 * p_k1->x + a2 * m_k1.x + a3 * p_k2->x + a4 * m_k2.x;
    out->y = a1 * p_k1->y + a2 * m_k1.y + a3 * p_k2->y + a4 * m_k2.y;
}

Vector2 GetSplinePositionAtTime(Track* track, float song_time) {
    if (track->num_oncoming_positions < 2) return track->pos;

    unsigned int k = 0;
    while (k + 1 < track->num_oncoming_positions &&
           track->oncoming_timestamps[k + 1] <= song_time) {
        k++;
    }

    unsigned int p0_index = (k == 0) ? k : k - 1; 
    unsigned int p1_index = k;
    unsigned int p2_index = k + 1;
    unsigned int p3_index = (k + 2 >= track->num_oncoming_positions) ? p2_index : k + 2;

    if (p2_index >= track->num_oncoming_positions) {
        return track->oncoming_positions[track->num_oncoming_positions - 1];
    }

    float t0 = track->oncoming_timestamps[p1_index];
    float t1 = track->oncoming_timestamps[p2_index];

    float duration = t1 - t0;
    float t = (duration > 0) ? (song_time - t0) / duration : 0.0f;

    Vector2 out;
    CatmullRom(t, &out, 
        &track->oncoming_positions[p0_index], 
        &track->oncoming_positions[p1_index], 
        &track->oncoming_positions[p2_index], 
        &track->oncoming_positions[p3_index]);
	
    return out;
}

float CalculateDiscrepancy(Track* track, float song_time) {
    unsigned int k = 0;
    while (k + 1 < track->num_oncoming_positions &&
           track->oncoming_timestamps[k + 1] <= song_time) {
        k++;
    }

    if (k + 1 >= track->num_oncoming_positions) return 0.0f;

    float oncoming_hitnote1 = track->oncoming_timestamps[k + 1];
    float oncoming_hitnote2 = track->oncoming_timestamps[k];

    float discrepancy1 = oncoming_hitnote1 - song_time; // next
    float discrepancy2 = song_time - oncoming_hitnote2; // prev

    return (discrepancy1 > discrepancy2) ? discrepancy2 : discrepancy1;
}

#define KEY_TRACK1        KEY_A
#define KEY_TRACK2        KEY_S
#define KEY_TRACK3        KEY_K
#define KEY_TRACK4        KEY_L

void CheckForKeyPresses(Track* tracks, float song_time) {
    float discrepancy = 0.0f;
    if (IsKeyPressed(KEY_TRACK1)) {
        discrepancy = CalculateDiscrepancy(&tracks[0], song_time);
        printf("TRACK1 with %f discrepancy\n", discrepancy);
    }
    if (IsKeyPressed(KEY_TRACK2)) {
        discrepancy = CalculateDiscrepancy(&tracks[1], song_time);
        printf("TRACK2 with %f discrepancy\n", discrepancy);
    }
    if (IsKeyPressed(KEY_TRACK3)) {
        discrepancy = CalculateDiscrepancy(&tracks[2], song_time);
        printf("TRACK3 with %f discrepancy\n", discrepancy);
    }
    if (IsKeyPressed(KEY_TRACK4)) {
        discrepancy = CalculateDiscrepancy(&tracks[3], song_time);
        printf("TRACK4 with %f discrepancy\n", discrepancy);
    }
}

int CompareHitCircles(const void* a, const void* b) {
    const HitCircle* circleA = (const HitCircle*)a;
    const HitCircle* circleB = (const HitCircle*)b;

    if (circleA->timestamp < circleB->timestamp) return -1;
    if (circleA->timestamp > circleB->timestamp) return 1;
    return 0;
}

void MapSetup(unsigned int map_length, HitCircle* circles) {
    size_t count = 0;
    HitCircle* map_notes = ReadMap("map1.dat", &count);

    assert(count <= map_length && "Too many entries in this map.");
    map_length = (count < map_length) ? count : map_length;
    
    for (size_t i = 0; i < map_length; i++) {
        circles[i] = map_notes[i];
    }
    
    free(map_notes);
}

void TrackSetup(Track* tracks, HitCircle* circles, unsigned int map_length) {
    tracks[0].pos = TRACK_1_STARTPOS;
    tracks[1].pos = TRACK_2_STARTPOS;
    tracks[2].pos = TRACK_3_STARTPOS;
    tracks[3].pos = TRACK_4_STARTPOS;

    qsort(circles, map_length, sizeof(HitCircle), CompareHitCircles);

    float total_duration = circles[map_length - 1].timestamp + SONG_END_BUFFER;
    unsigned int total_lookup_samples = (unsigned int)(total_duration * SAMPLES_PER_SECOND);

    for (size_t i = 0; i < 4; i++) {
        tracks[i] = (Track) {
            .color = track_colors[i],
            .size = POINT_RAD,
            .num_oncoming_positions = 0,
            .track_index = i,
            .current_render_index = 0,
            .total_samples = total_lookup_samples,
            .pathLUT = (Vector2*)malloc(total_lookup_samples * sizeof(Vector2))
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

		// form look-up table
        for (unsigned int s = 0; s < total_lookup_samples; s++) {
            float simTime = (float)s / SAMPLES_PER_SECOND;
            tracks[i].pathLUT[s] = GetSplinePositionAtTime(&tracks[i], simTime);
        }
    }
}

void UpdateTrackPositions(Track* tracks, float song_time, unsigned int frame_counter) {
    for (size_t i = 0; i < 4; i++) {
        Track* track = &tracks[i];
        if (track->num_oncoming_positions < 2) continue;

        float index_f = song_time * SAMPLES_PER_SECOND;
        unsigned int index = (unsigned int)index_f;
        
        // prevent out-of-bounds array access
        if (index >= track->total_samples - 1) {
            track->pos = track->pathLUT[track->total_samples - 1];
            continue;
        }

        float fraction = index_f - (float)index;
        Vector2 posA = track->pathLUT[index];
        Vector2 posB = track->pathLUT[index + 1];

        track->pos.x = LinearlyInterpolate(posA.x, posB.x, fraction);
        track->pos.y = LinearlyInterpolate(posA.y, posB.y, fraction);
    }
}

void RenderTracks(Track* tracks, float song_time) {
    for (size_t i = 0; i < 4; i++) {
        Track* track = &tracks[i];
        if (track->num_oncoming_positions < 2) continue;

		for (int g = TRAIL_GHOSTS; g > 0; g--) {
            float ghost_time = song_time - (g * TRAIL_TIME_STEP);
            if (ghost_time < 0) continue;

            float g_index_f = ghost_time * SAMPLES_PER_SECOND;
            unsigned int g_index = (unsigned int)g_index_f;

            if (g_index < track->total_samples - 1) {
                Vector2 posA = track->pathLUT[g_index];
                Vector2 posB = track->pathLUT[g_index + 1];
                float fraction = g_index_f - (float)g_index;

                Vector2 ghost_pos = {
                    LinearlyInterpolate(posA.x, posB.x, fraction),
                    LinearlyInterpolate(posA.y, posB.y, fraction)
                };

                float ghost_factor = 1.0f - ((float)g / (TRAIL_GHOSTS + 1));
                Color ghost_color = track->color;
                ghost_color.a = (unsigned char)(100.0f * ghost_factor);

                DrawCircleV(ghost_pos, track->size, ghost_color);
            }
        }

        unsigned int j = track->current_render_index; 

        while (j < track->num_oncoming_positions &&
            track->oncoming_timestamps[j] <= song_time) {
                j++;
            }

        track->current_render_index = j;
            
        if (j >= track->num_oncoming_positions) continue;
            
        Vector2* oncoming_hitcircle = &track->oncoming_positions[j];
        float target_time = track->oncoming_timestamps[j];

        float time_remaining = target_time - song_time;

        float k = 3.0f;
        float radius_factor = expf(-k * time_remaining);
        
        k = 1.0f;
        Color alpha_color = track->color;
        alpha_color.a = (unsigned char)(128.0f + radius_factor * 127.0f);

        radius_factor = (radius_factor < 0.01f) ? 0.01f : (radius_factor > 1.0f) ? 1.0f : radius_factor;
        radius_factor = 1.0f / radius_factor;

		if (radius_factor < 5.0f) {
			DrawCircleLinesV(
				*oncoming_hitcircle,
				POINT_RAD * radius_factor,
				alpha_color
			);
		}

        DrawCircleV(track->pos, track->size, alpha_color);
    }
}