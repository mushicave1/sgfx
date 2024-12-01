USE_GLFW ?= OFF

build: clean
	@echo "Building project..."	
	mkdir -p build
	cd build && cmake -S ../ -B. -DUSE_GLFW=${USE_GLFW} && make 

tests:
	@echo "Running tests..."
	./build/test/sgfx_test

clean:
	@echo "Removing build..."
	rm -rf build