#include "display.hpp"

psDisplay::psDisplay(int width, int height, const char *title) {

	handle = NULL;
	m_width = width;
	m_height = height;
	m_title = title;
}

psDisplay::~psDisplay() {

	dispose();
}

void psDisplay::setWidth(int width) {

	if (handle && m_width != width) {
		m_width = width;
		glfwSetWindowSize(handle, m_width, m_height);
	}

}

void psDisplay::setHeight(int height) {

	if (handle && m_height != height) {
		m_height = height;
		glfwSetWindowSize(handle, m_width, m_height);
	}

}

#pragma warning(push)
#pragma warning(disable : 26812)

psStateDefinition psDisplay::initContext() {

	printf("%s\n", "Initializing GLFW...");
	if (!glfwInit())
		return INIT_MISMATCH;

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	handle = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!handle) {
		dispose();
		return WINDOW_CREATION_FAIL;
	}

	auto _framesizecallback = [](GLFWwindow * window, int width, int height) {

		auto inst = (psDisplay *)glfwGetWindowUserPointer(window);
		inst->m_width = width;
		inst->m_height = height;
		glViewport(0, 0, inst->m_width, inst->m_height);
	};
	auto _keycallback = [](GLFWwindow *window, int key, int scancode, int action, int mods) {

		auto inst = (psDisplay *)glfwGetWindowUserPointer(window);
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			inst->close();

	};
	glfwSetWindowUserPointer(handle, this);
	glfwSetFramebufferSizeCallback(handle, _framesizecallback);
	glfwSetKeyCallback(handle, _keycallback);
	const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(handle, (vidmode->width - 640) / 2, (vidmode->height - 480) / 2);
	glfwMakeContextCurrent(handle);

	printf("%s\n", "Initializing GLEW...");
	GLenum st = glewInit();
	if (st) {
		printf("%s\n", glewGetErrorString(st));
		return INIT_MISMATCH;
	}

	glfwSwapInterval(1);
	glfwShowWindow(handle);

	return SUCCESS;
}

#pragma warning(pop)