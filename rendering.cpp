#include "rendering.h"

Vector2 Rendering::WorldToScreen(Vector3 worldPosition, ViewMatrix& viewMatrix) {
	Vector4 clipPosition;

	clipPosition.y = worldPosition.x * viewMatrix[0][1] + worldPosition.y * viewMatrix[1][1] + worldPosition.z * viewMatrix[2][1] + viewMatrix[3][1];
	clipPosition.x = worldPosition.x * viewMatrix[0][0] + worldPosition.y * viewMatrix[1][0] + worldPosition.z * viewMatrix[2][0] + viewMatrix[3][0];
	clipPosition.z = worldPosition.x * viewMatrix[0][2] + worldPosition.y * viewMatrix[1][2] + worldPosition.z * viewMatrix[2][2] + viewMatrix[3][2];
	clipPosition.w = worldPosition.x * viewMatrix[0][3] + worldPosition.y * viewMatrix[1][3] + worldPosition.z * viewMatrix[2][3] + viewMatrix[3][3];

	// Out of screen
	if (clipPosition.w < 0.1f) {
		return {-2.0f, -2.0f};
	}

	// Normalized Device Coodinates (NDC)
	Vector2 ndcPosition;
	ndcPosition.x = clipPosition.x / clipPosition.w;
	ndcPosition.y = clipPosition.y / clipPosition.w;
	//ndcPosition.z = clipPosition.z / clipPosition.w;

	return ndcPosition;
}

void Rendering::DrawBox(float x, float y, float w, float h) {
	/* Border of Box Line */
	glLineWidth(5.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(w, y);
	glVertex2f(w, h);
	glVertex2f(x, h);
	glVertex2f(x, y);
	glEnd();

	glLineWidth(2.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(w, y);
	glVertex2f(w, h);
	glVertex2f(x, h);
	glVertex2f(x, y);
	glEnd();
}