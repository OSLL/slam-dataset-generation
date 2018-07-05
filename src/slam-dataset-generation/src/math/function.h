#ifndef MATH_FUNCTION
#define MATH_FUNCTION

#include <memory>
#include <type_traits>

#include "misc/misc.h"

namespace math
{
	template <typename FunctionClass>
	class Function
	{
	public:
		Function makeFunction(Args ... args)
			: function_(std::move(std::make_unique<FunctionClass>(args)))
		{ }

		typedef std::result_of<(*function_)(Args ...)> return_t;

		return_t operator()(Args ... args)
		{
			return (*function_)(args);
		}

		template <int n = 1>
		return_t derivative(Args ... args)
		{
			return (*function_).derivative<n>(args);
		}

	private:
		std::unique_ptr<FunctionClass> function_;
	};
}

#endif
