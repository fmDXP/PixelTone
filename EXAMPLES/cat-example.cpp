#include <iostream>
#include "PixelTone.h"
#include "miniaudio.h"
#include "stb_image.h"
#include "stb_image_write.h"

int main() {
    // Initialize audio engine
    pxtone::init();

    // --- IMAGE EXAMPLE ---
    std::cout << "Loading image..." << std::endl;
    pxtone::Image img = pxtone::loadImage("cat.png");

    if (img.data.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
    } else {
        std::cout << "Image loaded! "
                  << "Width: " << img.width
                  << ", Height: " << img.height
                  << ", Channels: " << img.channels << std::endl;

        // Flip horizontally
        pxtone::Image flippedH = pxtone::flipHorizontal(img);
        pxtone::saveImage("cat_flippedH.png", flippedH);

        // Flip vertically
        pxtone::Image flippedV = pxtone::flipVertical(img);
        pxtone::saveImage("cat_flippedV.png", flippedV);

        // Resize image
        pxtone::Image resized = pxtone::resizeImage(img, img.width / 2, img.height / 2);
        pxtone::saveImage("cat_resized.png", resized);

        std::cout << "Image manipulations done, saved flipped and resized images." << std::endl;
    }

    // --- AUDIO EXAMPLE ---
    std::cout << "Playing sound with fade-in..." << std::endl;
    pxtone::playSoundFadeIn("meow.wav", 2.0f); // 2-second fade-in

    // Wait some time while sound plays
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Fading out audio..." << std::endl;
    pxtone::fadeOutAsync(2.0f); // 2-second fade-out

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Shutdown audio engine
    pxtone::quit();

    std::cout << "Done!" << std::endl;
    return 0;
}
