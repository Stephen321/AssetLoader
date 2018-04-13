#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <functional>
#include <memory>
#include <unordered_map>
#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"

namespace Assets {
	extern SDL_Renderer* renderer; //TODO: how to not make this global...

	//Assets need to be stored in a central location.
	//what assets are there?
	//SDL_Texture*

	template<typename T> T* load(const char* file) { printf("Please only try loading a loadable type!"); }
	template<> SDL_Texture* load<SDL_Texture>(const char* file);

	struct AssetBase {};
	template<class T> 
	struct Asset : AssetBase{
		Asset() : data(nullptr) {};
		Asset(T* _data) : data(_data) {};
		//https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		friend void swap(Asset& first, Asset& second) {
			using std::swap;
			swap(first.data, second.data);
		}
		Asset(const T& other) {
			std::copy(other.data, sizeof(T*), data);
		}
		Asset& operator=(Asset other) {
			swap(*this, other);
			return *this;
		}
		Asset(Asset&& other)
			: Asset() {
			swap(*this, other);
		}
		T* data;		
	};
	
	template<class T>
	class Holder {
	public:
		void acquire(T id, std::unique_ptr<AssetBase> asset) {
			m_assets[id] = std::move(asset);
		}
		template<class T2>
		T2* get(T id) const{
			return (static_cast<Asset<T2>*>(m_assets.at(id).get()))->data;
		}
	private:
		std::unordered_map<T, std::unique_ptr<AssetBase>> m_assets;

	};

	template<class T>
	std::unique_ptr<AssetBase> loadFromFile(const char* file) {
		return std::make_unique<Asset<T>>(Asset<T>(load<T>(file))); //TODO: pointers..?
	}
}

#endif