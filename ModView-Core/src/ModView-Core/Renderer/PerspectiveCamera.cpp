#include "mvpch.h"
#include "PerspectiveCamera.h"

#include <corecrt_math_defines.h>

#include "ModView-Core/Base/Input.h"
#include <GLFW\include\GLFW\glfw3.h>


#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace MV {


	PerspectiveCamera::PerspectiveCamera(const glm::mat4& projectionMatrix)
		: m_Proj(projectionMatrix)
	{
		m_Rotation = { 90.0f, 0.0f, 0.0f };
		m_FocalPoint = glm::vec3(0.0f, 0.0f, 0.0f);

		m_Distance = glm::distance({ -5, 5, 5 }, m_FocalPoint);

		m_Yaw = 3.0f * (float)M_PI / 4.0f;
		m_Pitch = M_PI / 4.0f;


		m_Position = m_FocalPoint - GetForwardDirection() * m_Distance;
		auto orientation = GetOrientation();

		m_Rotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);

		m_RotationSpeed = 0.8f;
		

		m_ViewportWidth = 1280;
		m_ViewportHeight = 720;
	}

	void PerspectiveCamera::OnUpdate(const Timestep& ts)
	{
		const auto pos = Input::GetMousePosition();
		glm::vec2 mouse = { pos.first, pos.second };
		glm::vec2 delta = (mouse - m_PrevMousePos) * 0.003f;
		m_PrevMousePos = mouse;


		if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {


			float x = std::min(m_ViewportWidth / 1000.0f, 2.4f);
			float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

			float y = std::min(m_ViewportHeight / 1000.0f, 2.4f);
			float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;


			m_FocalPoint += -GetRightDirection() * delta.x * xFactor * m_Distance;
			m_FocalPoint += GetUpDirection() * delta.y * yFactor * m_Distance;

		} else if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
			MV_WARN("RIGHT MOUSE\n");



			float x = std::min(m_ViewportWidth / 1000.0f, 2.4f);
			float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

			float y = std::min(m_ViewportHeight / 1000.0f, 2.4f);
			float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

			float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
			m_Yaw += yawSign * delta.x * m_RotationSpeed;
			m_Pitch += delta.y * m_RotationSpeed;
		}
		else if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_3)) {



			float dist = m_Distance * 0.2f;
			dist = std::max(dist, 0.0f);
			m_ZoomSpeed = dist * dist;
			m_ZoomSpeed = std::min(m_ZoomSpeed, 100.0f);

			m_Distance -= delta.y * m_ZoomSpeed;
			if (m_Distance < 1.0f) {
				m_FocalPoint += GetForwardDirection();
				m_Distance = 1.0f;
			}

		}

		m_Position = m_FocalPoint - GetForwardDirection() * m_Distance;
		auto orientation = GetOrientation();

		m_Rotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);

	}

	void PerspectiveCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MV_BIND_EVENT_FUNC(PerspectiveCamera::OnMouseScroll));
	}

	glm::vec3 PerspectiveCamera::GetUpDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));

	}

	glm::vec3 PerspectiveCamera::GetRightDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 PerspectiveCamera::GetForwardDirection()
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat PerspectiveCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}


	bool PerspectiveCamera::OnMouseScroll(MouseScrolledEvent e) {
		float delta = e.GetYOffset() * 0.1f;


		float dist = m_Distance * 0.2f;
		dist = std::max(dist, 0.0f);
		m_ZoomSpeed = dist * dist;
		m_ZoomSpeed = std::min(m_ZoomSpeed, 100.0f);

		m_Distance -= delta * m_ZoomSpeed;
		if (m_Distance < 1.0f) {
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}

		m_Position = m_FocalPoint - GetForwardDirection() * m_Distance;
		auto orientation = GetOrientation();

		m_Rotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);

		return false;
	}

}