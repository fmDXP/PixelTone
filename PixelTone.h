#pragma once
#include <string>
#include <vector>

namespace pxtone
{
	// -- INIT / SHUTDOWN --

	void initAudio();
	void init();

	void shutdownAudio();
	void quit();


	// -- IMAGE --

	struct Image
	{
		int width, height, channels;
		std::vector<unsigned char> data;
	};

	Image loadImage(const std::string& filepath);
	bool saveImage(const std::string& filepath, const Image& image);
	Image flipHorizontal(const Image& img);
	Image flipVertical(const Image& img);
	Image resizeImage(const Image& img, int newWidth, int newHeight);	// Nearest-Neighbor


	// -- AUDIO --

	void playSound(const std::string& path);
	void setVolume(float volume);
	void fadeIn(float durationSec, float targetVolume);
	void fadeOut(float durationSec);
	void fadeInAsync(float durationSec, float targetVolume);
	void fadeOutAsync(float durationSec);
	void playSoundFadeIn(const std::string& path, float durationSec);
}