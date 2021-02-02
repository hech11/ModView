#pragma once

#include <glm/glm.hpp>
#include "ModView-Core/Base/Timestep.h"
#include "ModView-Core/Event/Event.h"
#include <ModView-Core\Event\InputEvents.h>




namespace MV {

	class PerspectiveCamera {
		public :

			PerspectiveCamera(const glm::mat4& projectionMatrix);

			void SetViewportSize(uint32_t width, uint32_t height) { m_ViewportWidth = width; m_ViewportHeight = height; }

			void OnUpdate(const Timestep& ts);
			void OnEvent(Event& e);

			const glm::mat4& GetViewMatrix() const { return m_View; }

			glm::vec3 GetUpDirection();
			glm::vec3 GetRightDirection();
			glm::vec3 GetForwardDirection();

			const glm::vec3& GetPosition() const { return m_Position; }
			glm::quat GetOrientation() const;


			float GetPitch() const { return m_Pitch; }
			float GetYaw() const { return m_Yaw; }
		private :
			bool OnMouseScroll(MouseScrolledEvent e);
		private :
			glm::mat4 m_View, m_Proj;
			glm::vec3 m_Position, m_Rotation, m_FocalPoint;
			glm::vec2 m_PanSpeed;

			glm::vec2 m_PrevMousePos;

			float m_Pitch, m_Yaw;
			float m_Distance;
			float m_RotationSpeed, m_ZoomSpeed;

			uint32_t m_ViewportWidth, m_ViewportHeight;

	};

}
