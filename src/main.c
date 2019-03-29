#include <gb/gb.h>

#include "./assets/wanadev_logo_l.tileset.h"
#include "./assets/wanadev_logo_l.tilemap.h"

void main(void) {
    set_bkg_data(0, WANADEV_LOGO_TILESET_TILE_COUNT, WANADEV_LOGO_TILESET);
    set_bkg_tiles(0, 0, WANADEV_LOGO_TILEMAP_WIDTH, WANADEV_LOGO_TILEMAP_HEIGHT, WANADEV_LOGO_TILEMAP);
    SHOW_BKG;
}

