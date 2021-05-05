#ifndef PS_DISPLAY_PROTOTYPE
#define PS_DISPLAY_PROTOTYPE

// Note for later: try to find a better alternative to this shit.
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <iostream>

enum psStateDefinition {

	SUCCESS = 0,
	INIT_MISMATCH = 1,
	WINDOW_CREATION_FAIL = 2
};

class psDisplay {

protected:
	// Protected for safety reasons, like keeping things synchronized.
	GLFWwindow *handle;
	const char *m_title;
	int m_width;
	int m_height;

public:

	psDisplay(int width, int height, const char *title);

	virtual ~psDisplay();

	const char *getTitle() {

		return m_title;
	}

	void setTitle(const char* title) {

		if (handle && !_stricmp(m_title, title)) {
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