#include <gb/gb.h>

#include "./palette.h"

#include "./assets/wanadev_logo_l.tileset.h"
#include "./assets/wanadev_logo_l.tilemap.h"

#define TRUE  1
#define FALSE 0

UINT8 FADE[] = {
    PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK,
    PALETTE_GRAY, PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK,
    PALETTE_SILVER, PALETTE_GRAY, PALETTE_BLACK, PALETTE_BLACK,
    PALETTE_WHITE, PALETTE_SILVER, PALETTE_GRAY, PALETTE_BLACK,
};

void fade_in() {
    UINT8 t;
    UINT8 step;

    for (step = 0 ; step < 4 ; step++) {
        for (t = 0 ; t < 6 ; t++) {
            wait_vbl_done();
        }
        palette_set_bgp(
                FADE[step * 4 + 0],
                FADE[step * 4 + 1],
                FADE[step * 4 + 2],
                FADE[step * 4 + 3]);
    }
}

void fade_out() {
    UINT8 t;
    UINT8 step;

    for (step = 4 ; step > 0 ; step--) {
        for (t = 0 ; t < 6 ; t++) {
            wait_vbl_done();
        }
        palette_set_bgp(
                FADE[(step - 1) * 4 + 0],
                FADE[(step - 1) * 4 + 1],
                FADE[(step - 1) * 4 + 2],
                FADE[(step - 1) * 4 + 3]);
    }
}

void sleep(UINT16 frames) {
    UINT16 t;
    for (t = 0 ; t < frames ; t++) {
        wait_vbl_done();
    }
}

void show_logo() {
    HIDE_BKG;
    set_bkg_data(0, WANADEV_LOGO_TILESET_TILE_COUNT, WANADEV_LOGO_TILESET);
    set_bkg_tiles(0, 0, WANADEV_LOGO_TILEMAP_WIDTH, WANADEV_LOGO_TILEMAP_HEIGHT, WANADEV_LOGO_TILEMAP);
    palette_set_bgp(PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK);
    SHOW_BKG;

    fade_in();
    sleep(120);  // 2s
    fade_out();
}

void show_cube() {
    // TODO
}

void main(void) {
    show_logo();
    show_cube();
}
