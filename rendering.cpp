#include "rendering.h"

Vector2 Rendering::WorldToScreen(Vector3 worldPosition, ViewMatrix& viewMatrix) {
	Vector4 clipPosition = {};

	clipPosition.y = worldPosition.x * viewMatrix[0][1] + worldPosition.y * viewMatrix[1][1] + worldPosition.z * viewMatrix[2][1] + viewMatrix[3][1];
	clipPosition.x = worldPosition.x * viewMatrix[0][0] + worldPosition.y * viewMatrix[1][0] + worldPosition.z * viewMatrix[2][0] + viewMatrix[3][0];
	clipPosition.z = worldPosition.x * viewMatrix[0][2] + worldPosition.y * viewMatrix[1][2] + worldPosition.z * viewMatrix[2][2] + viewMatrix[3][2];
	clipPosition.w = worldPosition.x * viewMatrix[0][3] + worldPosition.y * viewMatrix[1][3] + worldPosition.z * viewMatrix[2][3] + viewMatrix[3][3];

	// Out of screen
	if (clipPosition.w < 0.1f) {
		return {-2.0f, -2.0f};
	}

	// Normalized Device Coodinates (NDC)
	Vector2 ndcPosition = {};
	ndcPosition.x = clipPosition.x / clipPosition.w;
	ndcPosition.y = clipPosition.y / clipPosition.w;

	return ndcPosition;
}

void Rendering::DrawBox(const EntityBox& entityBox) {
	glLineWidth(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(entityBox.right, entityBox.top);
	glVertex2f(entityBox.right, entityBox.bottom);
	glVertex2f(entityBox.left, entityBox.bottom);
	glVertex2f(entityBox.left, entityBox.top);
	glEnd();

	glLineWidth(2.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(entityBox.right, entityBox.top);
	glVertex2f(entityBox.right, entityBox.bottom);
	glVertex2f(entityBox.left, entityBox.bottom);
	glVertex2f(entityBox.left, entityBox.top);
	glEnd();
}

void Rendering::DrawSnapLine(float x, float y) {
	glLineWidth(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(x, y);
	glEnd();

	glLineWidth(2.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(x, y);
	glEnd();
}

void Rendering::DrawCircle(float cx, float cy, float radius) {
	glBegin(GL_LINE_LOOP);

	float segment = 360.0f;
	float aspectRatio = 720.0f / 1280;

	for (int i = 0; i < segment; i++) {
		float angle = 2.0f * 3.1415926f * i / segment;
		float x = radius * cosf(angle) * aspectRatio;
		float y = radius * sinf(angle);
		glVertex2f(cx + x, cy + y);
	}

	glEnd();
}

static float getDecreaseHealthBar(float health, float top) {
	float maxHealth = 100.0f;
	float decreaseHealthPercent = ((maxHealth - health) / maxHealth) * 100.0f;

	return top * (decreaseHealthPercent / 100.0f);
}

void Rendering::DrawHealthBar(const float& health, const HealthBar& healthBar, const EntityBox& entityBox) {
	float decreaseHealthBar = getDecreaseHealthBar(health, healthBar.height);

	glLineWidth(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(healthBar.left, entityBox.bottom);
	glVertex2f(healthBar.left, entityBox.top);
	glEnd();

	glLineWidth(2.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(healthBar.left, entityBox.bottom);
	glVertex2f(healthBar.left, entityBox.top + decreaseHealthBar);
	glEnd();
}