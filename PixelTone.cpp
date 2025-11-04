#include "pch.h"
#include "PixelTone.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace pxtone
{
    static ma_engine engine;


    // -- INIT --

    void initAudio()
    {
        ma_engine_init(nullptr, &engine);
    }

    void init()
    {
        initAudio();
    }


    // -- SHUTDOWN --

    void shutdownAudio()
    {
        ma_engine_uninit(&engine);
    }

    void quit()
    {
        shutdownAudio();
    }


    // -- IMAGE --

    Image loadImage(const std::string& path)
    {
        Image img{};
        unsigned char* data = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, 0);
        if (!data)
        {
            std::cerr << "[PixelTone] Error while loading image: " << path << std::endl;
            return img;
        }

        const size_t size = img.width * img.height * img.channels;
        img.data.assign(data, data + size);
        stbi_image_free(data);
        return img;
    }

    bool saveImage(const std::string& path, const Image& img) 
    {
        const int success = stbi_write_png(path.c_str(), img.width, img.height, img.channels, img.data.data(), img.width * img.channels);
        return success != 0;
    }

    Image flipHorizontal(const Image& img)
    {
        Image out = img;
        for (int y = 0; y < img.height; ++y)
        {
            for (int x = 0; x < img.width / 2; ++x)
            {
                for (int c = 0; c < img.channels; ++c)
                {
                    std::swap(out.data[(y * img.width + x) * img.channels + c],
                        out.data[(y * img.width + (img.width - 1 - x)) * img.channels + c]);
                }
            }
        }

        return out;
    }

    Image flipVertical(const Image& img)
    {
        Image out = img;
        for (int y = 0; y < img.height / 2; ++y)
        {
            for (int x = 0; x < img.width; ++x)
            {
                for (int c = 0; c < img.channels; ++c)
                {
                    std::swap(out.data[(y * img.width + x) * img.channels + c],
                        out.data[((img.height - 1 - y) * img.width + x) * img.channels + c]);
                }
            }
        }
        return out;
    }

    Image resizeImage(const Image& img, int newWidth, int newHeight) // Nearest-Neighbor
    {
        Image out;
        out.width = newWidth;
        out.height = newHeight;
        out.channels = img.channels;
        out.data.resize(newWidth * newHeight * img.channels);

        for (int y = 0; y < newHeight; ++y)
        {
            for (int x = 0; x < newWidth; ++x)
            {
                int srcX = x * img.width / newWidth;
                int srcY = y * img.height / newHeight;
                for (int c = 0; c < img.channels; ++c)
                {
                    out.data[(y * newWidth + x) * img.channels + c] =
                        img.data[(srcY * img.width + srcX) * img.channels + c];
                }
            }
        }
        return out;
    }


    // -- AUDIO --

    void playSound(const std::string& path)
    {
        ma_engine_play_sound(&engine, path.c_str(), nullptr);
    }

    void setVolume(float volume) // 0.0 = mute, 1.0 = normal
    {
        ma_engine_set_volume(&engine, volume);
    }

    void fadeIn(float durationSec, float targetVolume = 1.0f)
    {
        const int steps = 50;
        float stepVolume = targetVolume / steps;
        float stepTime = durationSec / steps;

        ma_engine_set_volume(&engine, 0.0f);
        for (int i = 0; i < steps; ++i)
        {
            float vol = stepVolume * (i + 1);
            ma_engine_set_volume(&engine, vol);
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(stepTime * 1000)));
        }
    }

    void fadeOut(float durationSec)
    {
        const int steps = 50;
        float currentVolume = 1.0f;  // Assume max vol at start
        float stepVolume = currentVolume / steps;
        float stepTime = durationSec / steps;

        for (int i = 0; i < steps; ++i)
        {
            float vol = currentVolume - stepVolume * (i + 1);
            ma_engine_set_volume(&engine, vol);
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(stepTime * 1000)));
        }
    }

    void fadeInAsync(float durationSec, float targetVolume = 1.0f)
    {
        std::thread([durationSec, targetVolume]() {
            fadeIn(durationSec, targetVolume);
            }).detach();
    }

    void fadeOutAsync(float durationSec)
    {
        std::thread([durationSec]() {
            fadeOut(durationSec);
            }).detach();
    }

    void playSoundFadeIn(const std::string& path, float durationSec)
    {
        playSound(path);
        fadeInAsync(durationSec);
    }

}