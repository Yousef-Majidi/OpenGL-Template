#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rectangle.h"

Rectangle::Rectangle(glm::vec3 center, float size, glm::vec3 color) : m_originalCenter(center)
{
	m_center = m_originalCenter;
	m_transform = glm::mat4{ 1.0f };
	generateVertices(center, size, color);
	generateIndices();
	this->m_numVertices = getIndicesSize() / sizeof(unsigned int);
	generateBuffers();
}

Rectangle::~Rectangle()
{
	// TODO: figure this out later
	/*glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);*/
}

const GLuint Rectangle::getVAO() const
{
	return this->VAO;
}

const GLuint Rectangle::getEBO() const
{
	return this->EBO;
}

const GLuint Rectangle::getNumVertices() const
{
	return this->m_numVertices;
}

const glm::mat4 Rectangle::getTransform() const
{
	return this->m_transform;
}

const glm::vec3 Rectangle::getCenter() const
{
	return this->m_center;
}

void Rectangle::resetTransform()
{
	m_transform = glm::mat4(1.0f);
}

void Rectangle::resetPosition()
{
	moveTo(m_originalCenter);
	m_center = m_originalCenter;
}

void Rectangle::resetScale()
{
	if (m_currentScale != 1.0f)
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), -m_center);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / m_currentScale, 1.0f / m_currentScale, 1.0f));
		glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), m_center);
		m_transform = translateBack * scale * translate * m_transform;
		m_currentScale = 1.0f;
	}
}

void Rectangle::rotate(float angle)
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), -m_center);
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), m_center);
	m_transform = translateBack * rotate * translate * m_transform;
}

void Rectangle::scale(float scaleFactor)
{
	if (m_currentScale != scaleFactor)
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), -m_center);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));
		glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), m_center);
		m_transform = translateBack * scale * translate * m_transform;
		m_currentScale = scaleFactor;
	}
}

void Rectangle::moveTo(glm::vec3 newPosition)
{
	glm::vec3 translationVector = newPosition - m_center;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
	m_transform = translationMatrix * m_transform;
	m_center = newPosition;
}

const float Rectangle::getVerticesSize() const
{
	return m_vertices.size() * sizeof(float);
}

const unsigned int Rectangle::getIndicesSize() const
{
	return m_indices.size() * sizeof(unsigned int);
}

void Rectangle::generateVertices(glm::vec3 center, float size, glm::vec3 color)
{
	float halfSize = size / 2.0f;
	m_vertices =
	{
		center.x + halfSize, center.y + halfSize, center.z, color.r, color.g, color.b, // top right
		center.x - halfSize, center.y + halfSize, center.z, color.r, color.g, color.b, // top left
		center.x - halfSize, center.y - halfSize, center.z, color.r, color.g, color.b, // bottom left
		center.x + halfSize, center.y - halfSize, center.z, color.r, color.g, color.b // bottom right
	};
}

void Rectangle::generateIndices()
{
	m_indices = {
		0, 1, 2,  
		2, 3, 0   
	};
}

void Rectangle::generateBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, getVerticesSize(), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesSize(), m_indices.data(), GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
