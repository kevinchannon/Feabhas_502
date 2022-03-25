#pragma once

namespace kjc
{

	class String
	{
	public:
		String(const wchar_t* s);
		~String();
		String(const String& other);

		const wchar_t* what() const;

	private:
		size_t _len;
		wchar_t* _s;
	};
}
