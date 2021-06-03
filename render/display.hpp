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
};

class psDisplay {

protected:
	// Protected for safety reasons, like keeping things synchronized.
	GLFWwindow *handle;
	const char *m_title;
	int m_width;
	int m_height;
	struct mouse_input cursor;
	bool m_isfullscreen;

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

		return cursor.posX;
	}

	float getViewPitch() {

		return cursor.posY;
	}

	int getSrcWidth() const {

		int width, height;
		if (handle)
			glfwGetWindowSize(handle, &width, &height);

		return width;
	}

	int getSrcHeight() const {

		int width, height;
		if (handle)
			glfwGetWindowSize(handle, &width, &height);

		return height;
	}

	virtual psStateDefinition initContext();

	void refresh() {

		if (handle) {
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

	bool isKeyReleased(int key) {

		return glfwGetKey(handle, key) == GLFW_RELEASE;
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