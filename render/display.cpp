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
	glfwWindowHint(GLFW_SAMPLES, 4);
	handle = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (!handle) {
		dispose();
		return WINDOW_CREATION_FAIL;
	}

	auto _framesizecallback = [](GLFWwindow * window, int width, int height) {

		auto inst = (psDisplay *)glfwGetWindowUserPointer(window);
		if (inst->m_isfullscreen) {
			inst->m_width = width;
			inst->m_height = height;
		}

		glViewport(0, 0, width, height);
	};
	auto _keycallback = [](GLFWwindow *window, int key, int scancode, int action, int mods) {

		auto inst = (psDisplay *)glfwGetWindowUserPointer(window);
		if (action == GLFW_RELEASE) {
			switch (key) {
			case GLFW_KEY_ESCAPE:
				inst->close();
				break;

			case GLFW_KEY_F11:
				GLFWmonitor *monitor;
				monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode *vidmode;
				vidmode = glfwGetVideoMode(monitor);
				if (inst->m_isfullscreen)
					glfwSetWindowMonitor(window, NULL, (vidmode->width - inst->m_width) / 2, (vidmode->height - inst->m_height) / 2, inst->m_width, inst->m_height, 0);

				else
					glfwSetWindowMonitor(window, monitor, 0, 0, vidmode->width, vidmode->height, 0);

				inst->m_isfullscreen = !inst->m_isfullscreen;

			default:
				break;

			}

		}

	};
	auto _cursorposcallback = [](GLFWwindow *window, double x, double y) {

		auto inst = (psDisplay *)glfwGetWindowUserPointer(window);
		glfwSetCursorPos(window, 0.f, 0.f);
		inst->cursor.posX = fmod(inst->cursor.posX + (float)x * 0.001f, pi<float>() * 2.f);
		inst->cursor.posY = clamp(inst->cursor.posY + (float)y * 0.001f, -pi<float>() * 0.5f, pi<float>() * 0.5f);
	};
	glfwSetWindowUserPointer(handle, this);
	glfwSetFramebufferSizeCallback(handle, _framesizecallback);
	glfwSetKeyCallback(handle, _keycallback);
	glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//if (glfwRawMouseMotionSupported())
	//	glfwSetInputMode(handle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(handle, _cursorposcallback);
	const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(handle, (vidmode->width - m_width) / 2, (vidmode->height - m_height) / 2);
	glfwMakeContextCurrent(handle);
	printf("%s\n", "Initializing GLEW...");
	GLenum st = glewInit();
	if (st != GLEW_OK) {
		printf("%s\n", glewGetErrorString(st));
		return INIT_MISMATCH;
	}

	glfwSwapInterval(1);
	glfwShowWindow(handle);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	return SUCCESS;
}

#pragma warning(pop)