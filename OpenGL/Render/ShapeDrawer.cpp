#include "ShapeDrawer.h"

#include "../../Render/Mesh/Mesh.h"
#include "../../Render/ForwardRenderer.h"
#include "../../Render/Resource/Loader/ShaderLoader.h"

ShapeDrawer::ShapeDrawer(BaseRenderer& p_renderer):
	m_renderer(&p_renderer)
{
	std::vector<glm::vec3> pos;
	pos.push_back(glm::vec3(0.0f));
	pos.push_back(glm::vec3(0.0f));

	std::vector<glm::vec2> uv;
	uv.push_back(glm::vec2(0.0f));
	uv.push_back(glm::vec2(0.0f));

	std::vector<glm::vec3> normal;
	normal.push_back(glm::vec3(0.0f));
	normal.push_back(glm::vec3(0.0f));

	std::vector<glm::vec3> tangent;
	tangent.push_back(glm::vec3(0.0f));
	tangent.push_back(glm::vec3(0.0f));

	std::vector<glm::vec3> bitTangent;
	bitTangent.push_back(glm::vec3(0.0f));
	bitTangent.push_back(glm::vec3(0.0f));

	std::vector<uint32> index;
	index.push_back(0);
	index.push_back(1);

	m_lineMesh = new Mesh(pos, uv, normal, tangent, bitTangent, index);
	m_lineMesh->Finalize();

	std::string vertexShader = R"(
#version 430 core

uniform vec3 start;
uniform vec3 end;
uniform mat4 viewProjection;

void main()
{
	vec3 position = gl_VertexID == 0 ? start : end;
    gl_Position = viewProjection * vec4(position, 1.0);
}

)";

	std::string fragmentShader = R"(
#version 430 core

uniform vec3 color;

out vec4 FRAGMENT_COLOR;

void main()
{
	FRAGMENT_COLOR = vec4(color, 1.0);
}
)";

	m_lineShader = ShaderLoader::getInstance()->CreateFromSource("Line Shader", vertexShader, fragmentShader);

	vertexShader = R"(
#version 430 core

uniform vec3 start;
uniform vec3 end;
uniform mat4 viewProjection;

out vec3 fragPos;

void main()
{
	vec3 position = gl_VertexID == 0  ? start : end;
	fragPos = position;
	gl_Position = viewProjection * vec4(position, 1.0);
}
)";

	fragmentShader = R"(
#version 430 core

uniform vec3 color;
uniform vec3 viewPos;
uniform float linear;
uniform float quadratic;
uniform float fadeThreshold;

out vec4 FRAGMENT_COLOR;

in vec3 fragPos;

float AlphaFromAttenuation()
{
	vec3 fakeViewPos = viewPos;
	fakeViewPos.y = 0;

    const float distanceToLight = max(max(length(viewPos - fragPos) - fadeThreshold, 0) - viewPos.y, 0);
    const float attenuation = (linear * distanceToLight + quadratic * (distanceToLight * distanceToLight));
    return 1.0 / attenuation;
}

void main()
{
	FRAGMENT_COLOR = vec4(color, AlphaFromAttenuation());
}

)";
	

	m_gridShader = ShaderLoader::getInstance()->CreateFromSource("Grid Shader", vertexShader, fragmentShader);
}
ShapeDrawer::~ShapeDrawer()
{
	ShaderLoader::getInstance()->Destroy(m_gridShader);
}


void ShapeDrawer::SetViewProjection(Matrix4 p_mat4)
{
	m_lineShader->activeShader();
	m_lineShader->SetMatrix("viewProjection", p_mat4);
	m_lineShader->inactiveShader();

	m_gridShader->activeShader();
	m_gridShader->SetMatrix("viewProjection", p_mat4);
	m_gridShader->inactiveShader();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("[%f]", p_mat4[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void ShapeDrawer::DrawLine(Vector3 p_start, Vector3 p_end, Color3 p_color, float p_lineWidth)
{
	m_lineShader->activeShader();

	m_lineShader->SetVector("start", p_start);
	m_lineShader->SetVector("end", p_end);

	m_lineShader->SetVector("color", p_color);

	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationModel(GL_LINE);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationLineWidth(p_lineWidth);
	dynamic_cast<ForwardRenderer*>(m_renderer)->Draw(*m_lineMesh, EPrimitiveMode::LINES, 1);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationLineWidth(1.0f);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationModel(GL_FILL);

	m_lineShader->inactiveShader();
}

void ShapeDrawer::DrawGrid(Vector3 p_viewPos, Color3& p_color, uint32 p_gridSize, float p_linear, float p_quadratic, float p_fadeThreshold, float p_lineWidth)
{
	m_gridShader->activeShader();
	m_gridShader->SetVector("color", p_color);
	m_gridShader->SetVector("viewPos", p_viewPos);
	m_gridShader->SetFloat("linear", p_linear);
	m_gridShader->SetFloat("quadratic", p_quadratic);
	m_gridShader->SetFloat("fadeThreshold", p_fadeThreshold);

	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationModel(GL_LINE);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationLineWidth(p_lineWidth);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetCapability(GL_BLEND, true);

	for (int32_t i = -p_gridSize + 1; i < p_gridSize; ++i)
	{
		m_gridShader->SetVector("start", Vector3(-(float)p_gridSize + std::floor(p_viewPos.x), 0.f, (float)i + std::floor(p_viewPos.z)));
		m_gridShader->SetVector("end", Vector3((float)p_gridSize + std::floor(p_viewPos.x), 0.f, (float)i + std::floor(p_viewPos.z)));
		dynamic_cast<ForwardRenderer*>(m_renderer)->Draw(*m_lineMesh, EPrimitiveMode::LINES, 1);

		m_gridShader->SetVector("start", Vector3((float)i + std::floor(p_viewPos.x), 0.f, -(float)p_gridSize + std::floor(p_viewPos.z)));
		m_gridShader->SetVector("end", Vector3((float)i + std::floor(p_viewPos.x), 0.f, (float)p_gridSize + std::floor(p_viewPos.z)));
		dynamic_cast<ForwardRenderer*>(m_renderer)->Draw(*m_lineMesh, EPrimitiveMode::LINES, 1);
	}

	dynamic_cast<ForwardRenderer*>(m_renderer)->SetCapability(GL_BLEND, false);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationLineWidth(1.0f);
	dynamic_cast<ForwardRenderer*>(m_renderer)->SetRasterizationModel(GL_FILL);
	m_gridShader->inactiveShader();
}