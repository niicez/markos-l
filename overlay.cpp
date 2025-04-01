#include <iostream>

#include "overlay.h"
#include "entities.h"
#include "types.h"
#include "memory.h"

using namespace std;

Overlay::Overlay(HANDLE processHandle, Memory memory) : processHandle(processHandle), memory(memory), window(nullptr) {}

Overlay::~Overlay() {
	if (this->window) {
		glfwDestroyWindow(this->window);
	}
	glfwTerminate();
}

int Overlay::Initialize() {
	if (!glfwInit()) {
		cerr << "Failed to initialize GLFW" << endl;
		return -1;
	}

	/* Overlay config */
	glfwWindowHint(GLFW_FLOATING, true);
	glfwWindowHint(GLFW_RESIZABLE, false);
	//glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, true);

	this->window = glfwCreateWindow(800, 800, "My Overlay", NULL, NULL);
	if (!this->window) {
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	return 0;
}


void Overlay::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);

	ListEntity listEntity = Entities::getEntities(this->processHandle, this->memory);
	for (Vector2 entity : listEntity) {
		glVertex2f(0.0f, -1.0f);
		glVertex2f(entity.x, entity.y);
	}

	glEnd();
}

int Overlay::Run() {
	if (this->Initialize() != 0) {
		return -1;
	}

	while (!glfwWindowShouldClose(this->window)) {

		this->Render();

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	return 0;
}