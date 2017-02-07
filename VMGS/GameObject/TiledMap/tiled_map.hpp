//=============================================================================
// ■ tiled_map.hpp
//=============================================================================

#include <global.hpp>

#ifndef _INCLUDE_TILED_MAP_H
#define _INCLUDE_TILED_MAP_H

#include "../Cube/cube.hpp"

namespace VM76 {

	struct TileData {
		unsigned int tid;
		unsigned char data_flag;
	};

	class TiledMap {
	public:
		TileData* tiles;
		int width, length, height;
		glm::vec3 mount_point = glm::vec3(0.0);

	private:
		Cube* cinstance[16];

	public:
		int calcTileIndex(int x, int y, int z);
		int calcTileIndex(glm::vec3 pos);

		TiledMap(int x, int y, int z, glm::vec3 wp);
		void render();
		void generate_flat();
		void bake_tiles();
		void dispose();
	};
}

#endif