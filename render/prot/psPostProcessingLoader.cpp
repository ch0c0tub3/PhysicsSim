#include "psPostProcessingLoader.h"

void psPostProcessingLoader::load(psDisplay *display) {

	m_display = display;
	m_memwidth = m_display->getSrcWidth();
	m_memheight = m_display->getSrcHeight();
	m_shader.create();
	m_shader.setupVertexShader(readfile_s("resource/post_vertex.glsl"));
	m_shader.setupFragmentShader(readfile_s("resource/post_fragment.glsl"));
	m_shader.link();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quads), &quads, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glBindVertexArray(0);

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_memwidth, m_memheight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
	glGenRenderbuffers(1, &m_rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_memwidth, m_memheight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboDepth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void psPostProcessingLoader::rescale() {

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_memwidth, m_memheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_memwidth, m_memheight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void psPostProcessingLoader::bind() {

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void psPostProcessingLoader::unbind() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void psPostProcessingLoader::process() {

	int width = m_display->getSrcWidth();
	int height = m_display->getSrcHeight();
	if (m_memwidth != width || m_memheight != height) {
		m_memwidth = width;
		m_memheight = height;
		rescale();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader.bind();
	glBindTexture(GL_TEXTURE_2D, m_texture);
	m_shader.setUniform("texture_loc", 0);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_shader.unbind();
}

void psPostProcessingLoader::dispose() {

	glDeleteRenderbuffers(1, &m_rboDepth);
	glDeleteTextures(1, &m_texture);
	glDeleteFramebuffers(1, &m_fbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	m_shader.dispose();
}