all:
	node makeResource.js > dialog.r
	rm -Rf build
	mkdir build
	cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=~/github/R68/toolchain/m68k-apple-macos/cmake/retro68.toolchain.cmake
	cd build && make


