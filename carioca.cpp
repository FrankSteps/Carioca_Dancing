/*
    Carioca dancing
    Coloque qualquer música e veja como qualquer música combina com o vídeo

    Carioca dancing
    Play any song and see how it matches the video

    by Francisco Passos (Frank Steps)
*/

#include <iostream>
#include <string>
#include <vector>

namespace ray{
    #include <raylib.h>
}

int main(int argc, char* argv[]) {
    ray::InitWindow(224, 224, "Carioca dancing");
    ray::InitAudioDevice();

    const int frame_count = 2325;
    std::vector<ray::Texture> frames(frame_count);

    for (int i = 0; i < frame_count; i++) {
        frames[i] = ray::LoadTexture(("dancing/carioca_" + std::to_string(i) + ".png").c_str());
    }

    ray::Sound sound;
    if (argc > 1) {
        sound = ray::LoadSound(argv[1]);
        ray::PlaySound(sound);
    } else {
        return EXIT_FAILURE;
    }

    int current_frame = 0;
    float frame_timer = 0.0f;
    const float frame_duration = 1.0f / 60.0f;;

    while (!ray::WindowShouldClose()) { 
        frame_timer += ray::GetFrameTime();
        if (frame_timer >= frame_duration) {
            current_frame = (current_frame + 1) % frame_count;
            frame_timer = 0.0f;
        }
        ray::BeginDrawing();
        ray::ClearBackground(ray::RAYWHITE);
        ray::DrawTexture(frames[current_frame], 0, 0, ray::WHITE);
        ray::EndDrawing();
    }
    for(int i = 0; i < frame_count; i++){
        ray::UnloadTexture(frames[i]);
    }
    ray::UnloadSound(sound);
    ray::CloseAudioDevice();
    ray::CloseWindow();
    return EXIT_SUCCESS;
}