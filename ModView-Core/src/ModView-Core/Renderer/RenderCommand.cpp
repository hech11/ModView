#include "mvpch.h"
#include "RenderCommand.h"

#include <GLAD/include/glad.h>


namespace MV {


	void RenderCommand::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void RenderCommand::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vao) {
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), vao->GetIndexBuffer()->GetType(), nullptr);
	}
	void RenderCommand::DrawArray(int count) {
		glDrawArrays(GL_TRIANGLES, 0, count);
	}


}