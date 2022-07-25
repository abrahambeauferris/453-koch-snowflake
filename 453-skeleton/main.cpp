#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Geometry.h"
#include "GLDebug.h"
#include "Log.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <math.h>
#include "Window.h"


int depth = 0;
int isDifferent = 0;
int isSTriangle = 0;
int isNSquare = 0;
int isKoch = 0;
int isDCurve = 1;
int shouldSwitch = 0;
const float pi = 3.1415926535897;

// EXAMPLE CALLBACKS
class MyCallbacks : public CallbackInterface {

public:
	MyCallbacks(ShaderProgram& shader) : shader(shader) {}

	virtual void keyCallback(int key, int scancode, int action, int mods) {
		if (action == GLFW_REPEAT || action == GLFW_PRESS) {
			if (key == GLFW_KEY_R) {
				shader.recompile();
			}
			if (key == GLFW_KEY_UP && depth < 6) {
				depth++;
				std::cout << "depth= "<<depth<<"\n";
				isDifferent = 1;
			}
			if (key == GLFW_KEY_DOWN && depth > 0) {
				depth--;
				isDifferent = 1;
			}
			if (key == GLFW_KEY_1 && !isSTriangle) {
				isSTriangle = 1;
				isNSquare = 0;
				isKoch = 0;
				isDCurve = 0;
				shouldSwitch = 1;

			}
			if (key == GLFW_KEY_2 && !isNSquare) {
				isSTriangle = 0;
				isNSquare = 1;
				isKoch = 0;
				isDCurve = 0;
				shouldSwitch = 1;

			}
			if (key == GLFW_KEY_3 && !isKoch) {
				isSTriangle = 0;
				isNSquare = 0;
				isKoch = 1;
				isDCurve = 0;
				shouldSwitch = 1;

			}
			if (key == GLFW_KEY_4 && !isDCurve) {
				isSTriangle = 0;
				isNSquare = 0;
				isKoch = 0;
				isDCurve = 1;
				shouldSwitch = 1;

			}
		}
	}

private:
	ShaderProgram& shader;
};

// END EXAMPLES

void S_triangle(CPU_Geometry& cpuGeom, glm::vec3 A, glm::vec3 B, glm::vec3 C, int depth) {
	// triangle subdivision for Serpinsky
	glm::vec3 D, E, F;
	if (depth > 0) {
		D = 0.5f * A + 0.5f * B;
		E = 0.5f * B + 0.5f * C;
		F = 0.5f * C + 0.5f * A;
		S_triangle(cpuGeom, D, B, E, depth - 1);
		S_triangle(cpuGeom, A, D, F, depth - 1);
		S_triangle(cpuGeom, F, E, C, depth - 1);
	}
	else {
		
		cpuGeom.verts.push_back(glm::vec3(A));
		cpuGeom.verts.push_back(glm::vec3(B));
		cpuGeom.verts.push_back(glm::vec3(C));

		float col1 = (float)rand() / RAND_MAX;
		float col2 = (float)rand() / RAND_MAX;
		float col3 = (float)rand() / RAND_MAX;
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	}
}

void N_square(CPU_Geometry& cpuGeom, glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, glm::vec3 E, glm::vec3 F, glm::vec3 G, glm::vec3 H, int depth) {
	cpuGeom.verts.push_back(glm::vec3(A));
	cpuGeom.verts.push_back(glm::vec3(B));
	cpuGeom.verts.push_back(glm::vec3(B));
	cpuGeom.verts.push_back(glm::vec3(C));
	cpuGeom.verts.push_back(glm::vec3(C));
	cpuGeom.verts.push_back(glm::vec3(D));
	cpuGeom.verts.push_back(glm::vec3(D));
	cpuGeom.verts.push_back(glm::vec3(A));
	cpuGeom.verts.push_back(glm::vec3(E));
	cpuGeom.verts.push_back(glm::vec3(F));
	cpuGeom.verts.push_back(glm::vec3(F));
	cpuGeom.verts.push_back(glm::vec3(G));
	cpuGeom.verts.push_back(glm::vec3(G));
	cpuGeom.verts.push_back(glm::vec3(H));
	cpuGeom.verts.push_back(glm::vec3(H));
	cpuGeom.verts.push_back(glm::vec3(E));

	float col1 = (float)abs(sin(0));
	float col2 = (float)abs(cos(0));
	float col3 = (float)abs(tan(0));

	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
	cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));

	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));

	for(int i = 1; i<=depth; i++) {
		float scaler = pow(0.5, i);
		cpuGeom.verts.push_back(glm::vec3(A) * scaler);
		cpuGeom.verts.push_back(glm::vec3(B) * scaler);
		cpuGeom.verts.push_back(glm::vec3(B) * scaler);
		cpuGeom.verts.push_back(glm::vec3(C) * scaler);
		cpuGeom.verts.push_back(glm::vec3(C) * scaler);
		cpuGeom.verts.push_back(glm::vec3(D) * scaler);
		cpuGeom.verts.push_back(glm::vec3(D) * scaler);
		cpuGeom.verts.push_back(glm::vec3(A) * scaler);
		cpuGeom.verts.push_back(glm::vec3(E) * scaler);
		cpuGeom.verts.push_back(glm::vec3(F) * scaler);
		cpuGeom.verts.push_back(glm::vec3(F) * scaler);
		cpuGeom.verts.push_back(glm::vec3(G) * scaler);
		cpuGeom.verts.push_back(glm::vec3(G) * scaler);
		cpuGeom.verts.push_back(glm::vec3(H) * scaler);
		cpuGeom.verts.push_back(glm::vec3(H) * scaler);
		cpuGeom.verts.push_back(glm::vec3(E) * scaler);

		float col1 = (float)abs(sin(i * 10));
		float col2 = (float)abs(cos(i * 10));
		float col3 = (float)abs(tan(i * 10));

		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));
		cpuGeom.cols.push_back(glm::vec3(col1, col2, col3));

		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
		cpuGeom.cols.push_back(glm::vec3(col2, col3, col1));
	}
}


glm::vec3 getTriangleTip(CPU_Geometry& cpuGeom, glm::vec3 A, glm::vec3 B) {
	glm::vec3 C, D;

	C.z = 0.f;
	D.z = 0.f;

	C.x = B.x - A.x;
	C.y = B.y - A.y;

	D.x = C.x * cos(glm::radians(60.f)) - C.y * sin(glm::radians(60.f));
	D.y = C.x * sin(glm::radians(60.f)) + C.y * cos(glm::radians(60.f));

	D.x += A.x;
	D.y += A.y;

	return D;
}

glm::vec3 getInbetweenPoints(CPU_Geometry& cpuGeom, glm::vec3 A, glm::vec3 B, float scale) {
	return glm::vec3(A.x + (B.x - A.x) * scale, A.y + (B.y - A.y) * scale, 0.f);
}

void K_snowflake(CPU_Geometry& cpuGeom, glm::vec3 A, glm::vec3 B, int depth, float colour1, float colour2, float colour3) {
	if (depth > 0) {
		glm::vec3 C, D, E;
		C = getInbetweenPoints(cpuGeom, A, B, 1.0f / 3.0f);
		E = getInbetweenPoints(cpuGeom, A, B, 2.0f / 3.0f);
		D = getTriangleTip(cpuGeom, C, E);
		float col1 = (float)rand() / RAND_MAX;
		float col2 = (float)rand() / RAND_MAX;
		float col3 = (float)rand() / RAND_MAX;
		K_snowflake(cpuGeom, A, C, depth - 1, colour1, colour2, colour3);
		K_snowflake(cpuGeom, C, D, depth - 1, col1, col2, col3);
		K_snowflake(cpuGeom, D, E, depth - 1, col1, col2, col3);
		K_snowflake(cpuGeom, E, B, depth - 1, colour1, colour2, colour3);

	}
	else {
		cpuGeom.verts.push_back(glm::vec3(A));
		cpuGeom.verts.push_back(glm::vec3(B));
		cpuGeom.cols.push_back(glm::vec3(colour1, colour2, colour3));
		cpuGeom.cols.push_back(glm::vec3(colour1, colour2, colour3));
	}

}

void D_curve(CPU_Geometry& cpuGeom, float x, float y, float length, float angle, int depth, float colour1, float colour2, float colour3) {
	if (depth > 0) {
		D_curve(cpuGeom, x, y, length / sqrt(2), angle - pi / 4.0f, depth - 1, colour1, colour2, colour3);
		D_curve(cpuGeom, x + length * cos(angle), y + length * sin(angle), length / sqrt(2), angle + pi + pi / 4.0, depth - 1, colour1, colour2, colour3);
	} else {
		cpuGeom.verts.push_back(glm::vec3(x, y, 0));
		cpuGeom.verts.push_back(glm::vec3(x + length * cos(angle), y + length * sin(angle), 0));
		cpuGeom.cols.push_back(glm::vec3(colour1, colour2, colour3));
		cpuGeom.cols.push_back(glm::vec3(colour1, colour2, colour3));
	}
}

int main() {
	Log::debug("Starting main");

	// WINDOW
	glfwInit();
	Window window(800, 800, "CPSC 453"); // can set callbacks at construction if desired

	GLDebug::enable();

	// SHADERS
	ShaderProgram shader("shaders/test.vert", "shaders/test.frag");

	// CALLBACKS
	window.setCallbacks(std::make_shared<MyCallbacks>(shader)); // can also update callbacks to new ones

	// GEOMETRY
	CPU_Geometry cpuGeom;
	GPU_Geometry gpuGeom;

	// vertices
	if(isSTriangle) S_triangle(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.5f, 0.f), depth);
	if(isNSquare) N_square(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, -0.5f, 0.f),
		glm::vec3(0.5f, 0.f, 0.f), glm::vec3(0.f, 0.5f, 0.f), glm::vec3(-0.5f, 0.f, 0.f), depth);
	if (isKoch) {
		K_snowflake(cpuGeom, glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(-0.5f, -0.5f, 0.f), depth, 0.2f, 0.4f, 0.6f);
		K_snowflake(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.366f, 0.f), depth, 0.2f, 0.4f, 0.6f);
		K_snowflake(cpuGeom, glm::vec3(0.f, 0.366f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), depth, 0.2f, 0.4f, 0.6f);
	}
	if (isDCurve) D_curve(cpuGeom, 0.f, 0.f, 0.5f, 0.0f, depth, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

	gpuGeom.setVerts(cpuGeom.verts);
	gpuGeom.setCols(cpuGeom.cols);

	// RENDER LOOP
	while (!window.shouldClose()) {
		glfwPollEvents();
		if (isDifferent) {
			isDifferent = 0;
			cpuGeom.verts.clear();
			cpuGeom.cols.clear();
			if (isSTriangle) S_triangle(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.5f, 0.f), depth);
			if (isNSquare) N_square(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, -0.5f, 0.f), glm::vec3(0.5f, 0.f, 0.f), glm::vec3(0.f, 0.5f, 0.f), glm::vec3(-0.5f, 0.f, 0.f), depth);
			if (isKoch) {
				K_snowflake(cpuGeom, glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(-0.5f, -0.5f, 0.f), depth, 0.2f, 0.4f, 0.6f);
				K_snowflake(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.366f, 0.f), depth, 0.2f, 0.4f, 0.6f);
				K_snowflake(cpuGeom, glm::vec3(0.f, 0.366f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), depth, 0.2f, 0.4f, 0.6f);
			}
			if (isDCurve) D_curve(cpuGeom, 0.f, 0.f, 0.5f, 0.0f, depth, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			gpuGeom.setVerts(cpuGeom.verts);
			gpuGeom.setCols(cpuGeom.cols);
		}
		if (shouldSwitch) {
			shouldSwitch = 0;
			cpuGeom.verts.clear();
			cpuGeom.cols.clear();
			if (isSTriangle) S_triangle(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.5f, 0.f), depth);
			if (isNSquare) N_square(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.5f, 0.5f, 0.f), glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, -0.5f, 0.f), glm::vec3(0.5f, 0.f, 0.f), glm::vec3(0.f, 0.5f, 0.f), glm::vec3(-0.5f, 0.f, 0.f), depth);
			if (isKoch) {
				K_snowflake(cpuGeom, glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(-0.5f, -0.5f, 0.f), depth, 0.2f, 0.4f, 0.6f);
				K_snowflake(cpuGeom, glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.366f, 0.f), depth, 0.2f, 0.4f, 0.6f);
				K_snowflake(cpuGeom, glm::vec3(0.f, 0.366f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), depth, 0.2f, 0.4f, 0.6f);
			}
			if (isDCurve) D_curve(cpuGeom, 0.f, 0.f, 0.5f, 0.0f, depth, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
			gpuGeom.setVerts(cpuGeom.verts);
			gpuGeom.setCols(cpuGeom.cols);
		}
		shader.use();
		gpuGeom.bind();

		glEnable(GL_FRAMEBUFFER_SRGB);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(isSTriangle) glDrawArrays(GL_TRIANGLES, 0, GLsizei(cpuGeom.verts.size()));
		if(isNSquare||isKoch||isDCurve) glDrawArrays(GL_LINES, 0, GLsizei(cpuGeom.verts.size()));
		glDisable(GL_FRAMEBUFFER_SRGB); // disable sRGB for things like imgui

		window.swapBuffers();
	}

	glfwTerminate();
	return 0;
}
