#include "mvpch.h"
#include "RenderCommand.h"

#include <glad.h>

namespace MV {


	void RenderCommand::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void RenderCommand::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vao) {
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), vao->GetIndexBuffer()->GetType(), nullptr);
	}

}