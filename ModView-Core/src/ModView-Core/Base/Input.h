#pragma once

#include <utility>


namespace MV {

	class Input {
		public :


			static bool IsKeyPressed(int keycode);
			static bool IsMouseButtonPressed(int button);

			static std::pair<int, int> GetMousePosition();

		private :


	};

}