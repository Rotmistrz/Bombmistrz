#include "Window.h"

Window::Window(uint __dBits, uint __sBits, uint __aaLevel)
: depthBits(__dBits), stencilBits(__sBits), antialiasingLevel(__aaLevel) {
	settings.depthBits = depthBits;
	settings.stencilBits = stencilBits;
	settings.antialiasingLevel = antialiasingLevel;
}

Window::~Window() {
}
