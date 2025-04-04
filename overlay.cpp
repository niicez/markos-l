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

	/* Render config */
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

float CalculateHealthBarTopByHealth(float health, float top) {
	float maxHealth = 100.0f;
	float decreaseHealthPercent = ((maxHealth - health) / maxHealth) * 100.0f;

	return top * (decreaseHealthPercent / 100.0f);
}

void Overlay::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	ListEntity listEntity = Entities::getEntities(this->processHandle, this->memory);

	for (Test entity : listEntity) {
		/* Draw Health bar */
		float d = CalculateHealthBarTopByHealth(entity.health, entity.barHeight);

		glLineWidth(5.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(entity.healthBar2, entity.tester.y);
		glVertex2f(entity.healthBar2, entity.tester.h);
		glEnd();

		glLineWidth(2.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(entity.healthBar2, entity.tester.y + d);
		glVertex2f(entity.healthBar2, entity.tester.h);
		glEnd();

		//Rendering::DrawLine(entity.screenPosition.x, entity.screenPosition.y);
		Rendering::DrawBox(entity.tester.x, entity.tester.y, entity.tester.w, entity.tester.h);
		//Rendering::DrawCircle(entity.head.x, entity.head.y, entity.headSize);
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