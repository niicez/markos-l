#include <iostream>

#include "overlay.h"
#include "entities.h"
#include "types.h"
#include "rendering.h"
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

	this->window = glfwCreateWindow(1280, 720, "My Overlay", NULL, NULL);
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
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ListEntity listEntity = Entities::getEntities(this->processHandle, this->memory);

	for (Test entity : listEntity) {

		glLineWidth(5.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(entity.screenPosition.x, entity.screenPosition.y);
		glEnd();

		glLineWidth(2.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(entity.screenPosition.x, entity.screenPosition.y);
		glEnd();

		Rendering::DrawBox(entity.tester.x, entity.tester.y, entity.tester.w, entity.tester.h);
	}

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