#include "ModView_Core.h"
#include "ImGui/imgui.h"


#include "ModView_Core/Renderer/Buffer.h"
#include "ModView_Core/Renderer/VertexArray.h"
#include "ModView_Core/Renderer/Shader.h"
#include "ModView_Core/Renderer/RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>

class ApplicationLayer : public MV::Layer {

	public :
		ApplicationLayer() : Layer("Application Layer") { }

		void OnAttach() override {
			shader = MV::Shader::Create("assets/shaders/basic.shader");
			shader->Bind();

			float vertex[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			};


			vao = MV::VertexArray::Create();
			vao->Bind();

			vbo = MV::VertexBuffer::Create();
			vbo->Bind();
			vbo->Resize(sizeof(vertex));
			vbo->UploadData(vertex);
			MV::BufferLayout layout = { 
				{ "aPos", MV::BufferLayoutTypes::Float3 }, {"aTexture", MV::BufferLayoutTypes::Float2} };
			vbo->SetLayout(layout);


			vao->AddVertexBuffer(vbo);

	
			proj = glm::mat4(1.0f);
			view = glm::mat4(1.0f);
			model = glm::mat4(1.0f);

			proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
			view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
			model = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), 45.0f, {1.0f, 0.0f, 2.0f});

			shader->UploadUniform4f("u_Color", { 0.5f, 0.8f, 0.2f, 1.0f });
			shader->UploadUniformMat4("u_Model", model);
			shader->UploadUniformMat4("u_View", view);
			shader->UploadUniformMat4("u_Proj", proj);
		}
		void OnDetach() override {
		}

		void OnEvent(MV::Event& e) override {


		}
		void OnUpdate(MV::Timestep dt) override {
			view = glm::translate(glm::mat4(1.0f), camTranslate) * glm::rotate(glm::mat4(1.0f), glm::radians(camAngle), camRotation);
			shader->UploadUniformMat4("u_View", view);

			vao->Bind();
			MV::RenderCommand::DrawArray(36);

		}


		void OnImguiRender() override {
			ImGui::Begin("Sandbox test!");

			ImGui::SliderFloat3("Camera translate", &camTranslate.x, -50.0f, 50.0f);
			ImGui::SliderFloat3("Camera rotate", &camRotation.x, -50.0f, 50.0f);
			ImGui::SliderFloat("Camera angle", &camAngle, -50.0f, 50.0f);
			ImGui::End();
		}


	private :

		glm::mat4 proj = glm::mat4(1.0);
		glm::mat4 view = glm::mat4(1.0);
		glm::mat4 model = glm::mat4(1.0);

		MV::Ref<MV::Shader> shader;
		MV::Ref<MV::VertexArray> vao;
		MV::Ref<MV::VertexBuffer> vbo;

		glm::vec3 camTranslate = { 0.0f, 0.0f, 0.0f };
		glm::vec3 camRotation = { 0.0f, 0.0f, 0.0f };
		float camAngle = 0.0f;

		
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
