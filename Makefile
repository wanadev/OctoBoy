PROG = GBVR
CC = ./gbdk-n/bin/gbdk-n-compile.sh -DDEBUG
LL = ./gbdk-n/bin/gbdk-n-link.sh
MR = ./gbdk-n/bin/gbdk-n-make-rom.sh
_OBJ_L = $(patsubst %.c,%.rel,$(wildcard src/*.c)) $(patsubst %.c,%.rel,$(wildcard src/*/*_l.*.c))
_OBJ_R = $(patsubst %.c,%.rel,$(wildcard src/*.c)) $(patsubst %.c,%.rel,$(wildcard src/*/*_r.*.c))

all: build

run: build
	mednafen $(PROG).gb

build: $(PROG)_L.gb $(PROG)_R.gb

$(PROG)_L.gb: $(_OBJ_L)
	$(LL) -o $(PROG)_L.ihx $^
	$(MR) $(PROG)_L.ihx $(PROG)_L.gb
	./maptosym/maptosym.py $(PROG)_L.map

$(PROG)_R.gb: $(_OBJ_R)
	$(LL) -o $(PROG)_R.ihx $^
	$(MR) $(PROG)_R.ihx $(PROG)_R.gb
	./maptosym/maptosym.py $(PROG)_R.map

src/%.rel: src/%.c
	$(CC) -o $@ -c $<

.PHONY: assets
assets: assets_left assets_right

assets_left:
	# Wanadev Logo
	img2gb tileset \
		--output-c-file=src/assets/wanadev_logo_l.tileset.c \
		--output-header-file=src/assets/wanadev_logo_l.tileset.h \
		--output-image=src/assets/wanadev_logo_l.tileset.png \
		--name WANADEV_LOGO_TILESET \
		--deduplicate \
		./assets/wanadev_logo_l.png
	img2gb tilemap \
		--output-c-file=src/assets/wanadev_logo_l.tilemap.c \
		--output-header-file=src/assets/wanadev_logo_l.tilemap.h \
		--name WANADEV_LOGO_TILEMAP \
		src/assets/wanadev_logo_l.tileset.png \
		./assets/wanadev_logo_l.png
	# Cube BG
	img2gb tileset \
		--output-c-file=src/assets/cube_bg_l.tileset.c \
		--output-header-file=src/assets/cube_bg_l.tileset.h \
		--output-image=src/assets/cube_bg_l.tileset.png \
		--name CUBE_BG_TILESET \
		--deduplicate \
		./assets/cube_bg_l.png
	img2gb tilemap \
		--output-c-file=src/assets/cube_bg_l.tilemap.c \
		--output-header-file=src/assets/cube_bg_l.tilemap.h \
		--name CUBE_BG_TILEMAP \
		src/assets/cube_bg_l.tileset.png \
		./assets/cube_bg_l.png
	# Cube anim
	img2gb tileset \
		--output-c-file=src/assets/cube_l.tileset.c \
		--output-header-file=src/assets/cube_l.tileset.h \
		--output-image=src/assets/cube_l.tileset.png \
		--name CUBE_TILESET \
		./assets/cube_l/cube_l_*.png

assets_right:
	img2gb tileset \
		--output-c-file=src/assets/wanadev_logo_r.tileset.c \
		--output-header-file=src/assets/wanadev_logo_r.tileset.h \
		--output-image=src/assets/wanadev_logo_r.tileset.png \
		--name WANADEV_LOGO_TILESET \
		--deduplicate \
		./assets/wanadev_logo_r.png
	img2gb tilemap \
		--output-c-file=src/assets/wanadev_logo_r.tilemap.c \
		--output-header-file=src/assets/wanadev_logo_r.tilemap.h \
		--name WANADEV_LOGO_TILEMAP \
		src/assets/wanadev_logo_r.tileset.png \
		./assets/wanadev_logo_r.png
	# Cube BG
	img2gb tileset \
		--output-c-file=src/assets/cube_bg_r.tileset.c \
		--output-header-file=src/assets/cube_bg_r.tileset.h \
		--output-image=src/assets/cube_bg_r.tileset.png \
		--name CUBE_BG_TILESET \
		--deduplicate \
		./assets/cube_bg_r.png
	img2gb tilemap \
		--output-c-file=src/assets/cube_bg_r.tilemap.c \
		--output-header-file=src/assets/cube_bg_r.tilemap.h \
		--name CUBE_BG_TILEMAP \
		src/assets/cube_bg_r.tileset.png \
		./assets/cube_bg_r.png
	# Cube anim
	img2gb tileset \
		--output-c-file=src/assets/cube_r.tileset.c \
		--output-header-file=src/assets/cube_r.tileset.h \
		--output-image=src/assets/cube_r.tileset.png \
		--name CUBE_TILESET \
		./assets/cube_r/cube_r_*.png

gbdk-n-lib:
	cd ./gbdk-n/ && make

clean:
	rm -rf src/*.rel
	rm -rf src/*.lst
	rm -rf src/*.sym
	rm -rf src/*.asm
	rm -rf src/*/*.rel
	rm -rf src/*/*.lst
	rm -rf src/*/*.sym
	rm -rf src/*/*.asm
	rm -rf $(PROG)_*.gb
	rm -rf $(PROG)_*.ihx
	rm -rf $(PROG)_*.map
	rm -rf $(PROG)_*.sym
	rm -rf $(PROG)_*.noi
	rm -rf $(PROG)_*.lk

clean_assets:
	rm -rf src/assets/*
