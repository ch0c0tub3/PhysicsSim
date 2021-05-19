#ifndef PS_DISPLAY_PROTOTYPE
#define PS_DISPLAY_PROTOTYPE

// Note for later: try to find a better alternative to this shit.
#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtx/transform.hpp"

using namespace glm;

enum psStateDefinition {

	SUCCESS = 0,
	INIT_MISMATCH = 1,
	WINDOW_CREATION_FAIL = 2
};

struct mouse_input {

	float posX = 0.f;
	float posY = 0.f;
	float pitch;
	float yaw;
};

class psDisplay {

protected:
	// Protected for safety reasons, like keeping things synchronized.
	GLFWwindow *handle;
	const char *m_title;
	int m_width;
	int m_height;
	struct mouse_input cursor;

public:

	psDisplay(int width, int height, const char *title);

	virtual ~psDisplay();

	const char *getTitle() {

		return m_title;
	}

	void setTitle(const char* title) {

		if (handle && title) {
			glfwSetWindowTitle(handle, title);
			m_title = title;
		}

	}

	int getWidth() {

		return m_width;
	}

	// Abstract, the impl class might not be resizable.
	virtual void setWidth(int width);

	int getHeight() {
		
		return m_height;
	}

	virtual void setHeight(int height);

	float getViewYaw() {

		return cursor.yaw;
	}

	float getViewPitch() {

		return cursor.pitch;
	}

	virtual psStateDefinition initContext();

	void refresh() {

		if (handle) {
			if (cursor.posX)
				cursor.yaw = cursor.posX * 0.001f;

			if (cursor.posY)
				cursor.pitch = cursor.posY * 0.001f;

			glfwSwapBuffers(handle);
			glfwPollEvents();
		}

	}

	void dispose() {

		if (handle)
			glfwDestroyWindow(handle);
		
		glfwTerminate();
	}

	bool isKeyPressed(int key) {

		return glfwGetKey(handle, key) == GLFW_PRESS;
	}

	int shouldClose() {

		// Still serious doubts.
		return handle ? glfwWindowShouldClose(handle) : 1;
	}

	void close() {

		if (handle)
			glfwSetWindowShouldClose(handle, GL_TRUE);

	}

};

#endif