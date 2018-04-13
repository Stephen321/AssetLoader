#include "Assets.h"
#include "Config.h"

namespace Assets {
	std::string path = "";
	SDL_Renderer* renderer = nullptr;

	// https://stackoverflow.com/questions/25529893/explicit-specialization-of-function-templates-causes-linker-error
	template<> SDL_Texture* load<SDL_Texture>(const char* file) {
		SDL_Texture* texture = IMG_LoadTexture(renderer, (ASSET_PATH + std::string(file)).c_str());
		if (texture == nullptr) {
			printf("Couldn't load texture: %s. Error: %s\n", std::string(path + file).c_str(), SDL_GetError());
		}
		return texture;
	}
}