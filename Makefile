all:
	if [ ! -d "build" ]; then mkdir build; fi
	cd build && cmake ..
	cd build && make

install: all
	cd build && make install

uninstall:
	if [ -f "build/install_manifest.txt" ]; then cd build && make uninstall; fi

clean:
	cd build && make clean

maintainer-clean:
	rm -rf build