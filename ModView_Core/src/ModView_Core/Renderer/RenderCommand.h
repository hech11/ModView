#pragma once

#include <glm.hpp>
#include "VertexArray.h"

namespace MV {

	class RenderCommand {

		public :
			

			static void SetClearColor(const glm::vec4& color);
			static void Clear();

			static void DrawIndexed(const Ref<VertexArray>& vao);

	};

}