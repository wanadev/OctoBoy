#include <gb/gb.h>

#include "./palette.h"

#include "./assets/wanadev_logo_l.tileset.h"
#include "./assets/wanadev_logo_l.tilemap.h"
#include "./assets/cube_bg_l.tileset.h"
#include "./assets/cube_bg_l.tilemap.h"
#include "./assets/cube_l.tileset.h"

#define TRUE  1
#define FALSE 0

#define CUBE_WIDTH        6
#define CUBE_HEIGHT       6
#define CUBE_X            7
#define CUBE_Y            6
#define CUBE_TILE_COUNT  36
#define CUBE_FRAME_COUNT 30
#define CUBE_TILE_OFFSET 0xA0

UINT8 FADE[] = {
    PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK,
    PALETTE_GRAY, PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK,
    PALETTE_SILVER, PALETTE_GRAY, PALETTE_BLACK, PALETTE_BLACK,
    PALETTE_WHITE, PALETTE_SILVER, PALETTE_GRAY, PALETTE_BLACK,
};

UINT8 CUBE_MAP[] = {
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5,
    0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB,
    0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1,
    0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD,
    0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3,
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
    set_bkg_data(0, WANADEV_LOGO_TILESET_TILE_COUNT, WANADEV_LOGO_TILESET);
    set_bkg_tiles(0, 0, WANADEV_LOGO_TILEMAP_WIDTH, WANADEV_LOGO_TILEMAP_HEIGHT, WANADEV_LOGO_TILEMAP);

    fade_in();
    sleep(120);  // 2s
    fade_out();
}

void show_cube() {
    UINT8 i;

    set_bkg_data(0, CUBE_BG_TILESET_TILE_COUNT, CUBE_BG_TILESET);
    set_bkg_tiles(0, 0, CUBE_BG_TILEMAP_WIDTH, CUBE_BG_TILEMAP_HEIGHT, CUBE_BG_TILEMAP);

    set_bkg_data(CUBE_TILE_OFFSET, CUBE_TILE_COUNT, CUBE_TILESET);
    set_bkg_tiles(CUBE_X, CUBE_Y, CUBE_WIDTH, CUBE_HEIGHT, CUBE_MAP);

    fade_in();

    while (TRUE) {
        for (i = 0 ; i < CUBE_FRAME_COUNT ; i++) {
            set_bkg_data(CUBE_TILE_OFFSET, CUBE_TILE_COUNT, CUBE_TILESET + i * CUBE_TILE_COUNT * 16);
            wait_vbl_done();
        }
    }
}

void main(void) {
    palette_set_bgp(PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK, PALETTE_BLACK);
    SHOW_BKG;
    show_logo();
    show_cube();
}
