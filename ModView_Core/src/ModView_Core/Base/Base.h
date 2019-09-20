#pragma once

#include <memory>


#if defined(MV_PLATFORM_WIN32) || defined(MV_PLATFORM_WIN64)
#else
#error ModView only supports Windows!
#endif



#ifdef MV_DEBUG
	#define ENABLE_MV_ASSERTS
#endif

#ifdef ENABLE_MV_ASSERTS
	#define MV_Assert(x) if(!(x)) { __debugbreak(); }
#else
	#define MV_Assert(x)
#endif



#define BIT(x) (x << 1);
#define MV_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1);


namespace MV {

	template <typename T>
	using Scoped = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using WeakRef = std::weak_ptr<T>;

}