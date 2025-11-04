# PixelTone

PixelTone is a lightweight C++ library for image manipulation and audio playback. It uses [stb_image](https://github.com/nothings/stb) for images and [miniaudio](https://github.com/mackron/miniaudio) for audio.

## Features

> ⚠️ Warning: This library is in early development. Features may be incomplete and code may be unstable.

- Load and save images (PNG, JPG, etc.)
- Flip and resize images
- Play sounds with fade in/out support
- Simple initialization and shutdown of audio engine

## Installation

1. Go to the [releases](https://github.com/fmDXP/PixelTone/releases) tab.
2. Grab the archive for your OS and arch.
3. Extract it in your project.
4. And you're ready to go!

> ⚠️ Warning: Your OS may not be fully supported yet. Feel free to modify the code and contribute!

## Usage

```cpp
#include "PixelTone.h"
#include "miniaudio.h"
#include "sdb_image.h"
#include "sdb_image_write.h"

int main() {
    pxtone::init();

    // Load an image
    auto img = pxtone::loadImage("cat.png");

    // Play a sound
    pxtone::playSound("meow.wav");

    // Remember to put the assets in an accessible location for the executable. 

    pxtone::quit();
    return 0;
}
```

## Development

> ℹ️ Note: This project was developed using Visual Studio Insiders (early Visual Studio 2026). Only the source code is included. That means no `.sln` or project files, so it’s easier to access and compile.  
> It’s recommended to use Visual Studio (any recent version) to build and work with this project.


## License

This project is using an MIT License making this free to use and modify.

> This library bundles `stb_image`, `stb_image_write`, and `miniaudio`.  
> All are under Public Domain / MIT, so redistribution is allowed.


Made with love by fmdxp 💫
