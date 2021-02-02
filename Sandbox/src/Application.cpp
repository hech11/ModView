#include "ModView-Core.h"
#include "ImGui/imgui.h"


#include "ModView-Core/Renderer/API/Buffer.h"
#include "ModView-Core/Renderer/API/VertexArray.h"
#include "ModView-Core/Renderer/API/Shader.h"
#include "ModView-Core/Renderer/API/FrameBuffer.h"
#include "ModView-Core/Renderer/RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ModView-Core/Renderer/API/Texture.h"

#include "ModView-Core/Renderer/PerspectiveCamera.h"

class ApplicationLayer : public MV::Layer {

	public :
		ApplicationLayer() : Layer("Application Layer") { }

		void OnAttach() override {
			shader = MV::Shader::Create("assets/shaders/basic.shader");
			shader->Bind();

			float vertex[] = {
				
				// front
				-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
				 1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
				 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
				-1.0f,  1.0f, 1.0f, 0.0f, 1.0f,


				// right
				 1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
				 1.0f,  1.0f, -1.0f,  1.0f, 0.0f,
				 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
				 1.0f, -1.0f,  1.0f,  0.0f, 1.0f,

				// back
				-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
				 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
				 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
				-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,

				// left
				 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
				 -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
				 -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
				 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,


				// upper
				 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
				-1.0f, 1.0f,  1.0f, 1.0f, 0.0f,
				-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
				 1.0f, 1.0f, -1.0f, 0.0f, 1.0f,

				// bottom
				-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
				 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
				 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
				-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,

			};


			vao = MV::VertexArray::Create();
			vao->Bind();

			vbo = MV::VertexBuffer::Create();
			vbo->Bind();
			vbo->Resize(sizeof(vertex));
			vbo->UploadData(vertex);
			MV::BufferLayout layout = { 
				{ "aPos", MV::BufferLayoutTypes::Float3 },
				{ "aTexCoords", MV::BufferLayoutTypes::Float2 },

			};
			vbo->SetLayout(layout);



			unsigned char indices[] = {
				0, 1, 2, 0, 2, 3, //front
				4, 5, 6, 4, 6, 7, //right
				8, 9, 10, 8, 10, 11, //back
				12, 13, 14, 12, 14, 15, //left
				16, 17, 18, 16, 18, 19, //upper
				20, 21, 22, 20, 22, 23 
			};

			ibo = MV::IndexBuffer::Create(6 * 6, MV::IndexBuffer::BufferType::Char);
			ibo->Bind();
			ibo->UploadData(indices);


			vao->AddVertexBuffer(vbo);
			vao->AddIndexBuffer(ibo);

	
			proj = glm::mat4(1.0f);
			view = glm::mat4(1.0f);
			model = glm::mat4(1.0f);

			proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
			view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
			model = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), 0.0f, {1.0f, 1.0f, 1.0f});

			shader->UploadUniform4f("u_Color", { 0.5f, 0.8f, 0.2f, 1.0f });
			shader->UploadUniformMat4("u_Model", model);
			shader->UploadUniformMat4("u_View", view);
			shader->UploadUniformMat4("u_Proj", proj);



			framebuffer = MV::FrameBuffer::Create(960 / 2, 540 / 2);
			texture = MV::Texture::Create("assets/textures/test.png");


			texture->Bind();
			shader->UploadUniform1i("u_Texture", texture->GetSlot());

			Camera = std::make_shared<MV::PerspectiveCamera>(glm::perspective(40.0f, 16.0f / 9.0f, 0.1f, 1000.0f));

		}
		void OnDetach() override {
		}

		void OnEvent(MV::Event& e) override {
			Camera->OnEvent(e);

		}
		void OnUpdate(MV::Timestep dt) override {
			view = glm::translate(glm::mat4(1.0f), camTranslate) * glm::rotate(glm::mat4(1.0f), glm::radians(camAngle), camRotation);

			Camera->OnUpdate(dt);


			shader->UploadUniformMat4("u_View", Camera->GetViewMatrix());

			vao->Bind();

			if (m_RenderToFramebuffer) {
				framebuffer->Bind();
				MV::RenderCommand::Clear();
				MV::RenderCommand::DrawIndexed(vao);
				framebuffer->Unbind();
			}
			else {
				MV::RenderCommand::DrawIndexed(vao);
			}


		}


		void OnImguiRender() override {
			ImGui::Begin("Camera test!");

			ImGui::SliderFloat3("Camera translate", &camTranslate.x, -50.0f, 50.0f);
			ImGui::SliderFloat3("Camera rotate", &camRotation.x, -50.0f, 50.0f);
			ImGui::SliderFloat("Camera angle", &camAngle, -360.0f, 360.0f);
			ImGui::End();

			ImGui::Begin("framebuffer test!");
			if (ImGui::Button("Render to framebuffer")) {
				m_RenderToFramebuffer = !m_RenderToFramebuffer;
				if (!m_RenderToFramebuffer) {
					float width = MV::Application::GetApp().GetWindow()->GetWidth();
					float height = MV::Application::GetApp().GetWindow()->GetHeight();
					MV::RenderCommand::SetViewport(0, 0, width, height);
				}
			}



			ImGui::Image((ImTextureID)framebuffer->GetRendererID(), { 960 / 2, 540 / 2 }, { 0, 1 }, {1, 0});
			ImGui::End();
		}


	private :

		glm::mat4 proj = glm::mat4(1.0);
		glm::mat4 view = glm::mat4(1.0);
		glm::mat4 model = glm::mat4(1.0);

		MV::Ref<MV::Shader> shader;
		MV::Ref<MV::VertexArray> vao;
		MV::Ref<MV::VertexBuffer> vbo;
		MV::Ref<MV::IndexBuffer> ibo;
		MV::Ref<MV::Texture> texture;
		MV::Ref<MV::FrameBuffer> framebuffer;

		MV::Ref<MV::PerspectiveCamera> Camera;

		glm::vec3 camTranslate = { 0.0f, 0.0f, -8.0f };
		glm::vec3 camRotation = { 1.0f, 0.0f, 0.0f };
		float camAngle = 0.0f;

		bool m_RenderToFramebuffer = false;
		
};

class Sandbox : public MV::Application {


	public :

		Sandbox() {
			PushLayer(new ApplicationLayer);
		}
		~Sandbox() {}

};



MV::Application* MV::CreateApplication() {
	return new Sandbox();
}
