#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

enum VertexType
{
	VertexArray,
	IndiceArray
};

class Model {

public:
	glm::vec3 scale;
	glm::vec3 position;
	// rotate in x,y,z axis
	glm::vec3 rotation;
	std::vector<glm::vec3> vertices;
	

	glm::mat4 GetModelMatrix();
	int GetVertexArraySize();
	int GetVertices(float result[]);

	Model();
	Model(std::vector<glm::vec3>);
	Model(float vertex[], int length);

};