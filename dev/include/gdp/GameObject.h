#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "MeshRenderer.h"

namespace gdp
{
	class GameObject {
	public:
		glm::vec3 Position;
		glm::vec3 Scale;
		glm::quat Rotation;
		MeshRenderer Renderer;
	};
}