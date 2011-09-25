default: bake

bake:
	mkdir -p build 
	cd build; cmake ..; make -j3

run:
	cd bin; ./NoisyHunter

go: bake run

gdb: bake
	cd bin; gdb ./NoisyHunter


clean:
	rm -r build
	rm -r doc
