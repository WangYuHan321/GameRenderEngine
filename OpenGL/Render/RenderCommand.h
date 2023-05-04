#include<GLM/glm.hpp>
#include"Mesh/Material.h"
#include"Mesh/Mesh.h"

struct RenderCommand {
	glm::mat4 Transfrom;
	glm::mat4 prevTransform;
	Mesh* mesh;
	Material* material;
	glm::vec3 BoxMin;
	glm::vec3 BoxMax;
};