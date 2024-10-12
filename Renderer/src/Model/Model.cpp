#include "Model.h"

glm::mat4 Model::GetModelMatrix()
{
	glm::mat4 trans = glm::mat4(1);
	trans = glm::translate(trans, this->position);

	// rotate z-x-y
	trans = glm::rotate(trans, rotation.z, glm::vec3(0, 0, 1));
	trans = glm::rotate(trans, rotation.x, glm::vec3(1, 0, 0));
	trans = glm::rotate(trans, rotation.y, glm::vec3(0, 1, 0));

	trans = glm::scale(trans, scale);

	return trans;
}

int Model::GetVertexArraySize()
{
	return vertices.size() * 3;
}

int Model::GetVertices(float result[])
{
	for (int i = 0, j = 0; i < vertices.size(); i++, j+=3) {
		result[j] = vertices[i].x;
		result[j + 1] = vertices[i].y;
		result[j + 2] = vertices[i].z;
	}
	return vertices.size() * 3;
}

Model::Model() {
	scale = glm::vec3(1, 1, 1);
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
}

Model::Model(std::vector<glm::vec3> vetices): Model()
{
	this->vertices = vertices;
}

Model::Model(float vertices[], int length) : Model()
{
	if (length % 3 != 0) {
		printf("[Error] length: %d\n", length);
		return;
	}
	for (int i = 0; i < length; i += 3) {
		this->vertices.emplace_back(glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]));
	}
}
