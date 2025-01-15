/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agodeanu <agodeanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:24:30 by agodeanu          #+#    #+#             */
/*   Updated: 2025/01/16 01:20:13 by agodeanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>

// c++ default copy constructor looks like this:
// String(const String &other): m_Buffer(other.m_Buffer), m_Size(other.m_Size) {}
// or the same as
// String(const String &other) {memcpy(this, &other, sizeof(String));}

// Pass objects as const references to avoid unnecessary copying

// Remember that a static member of the class is shared across all instances of the class
// and remains constant

// Should one check for self-assignment?

class String
{
	private:
		char			*m_Buffer;
		unsigned int	m_Size;
	public:
		String(const char *string)
		{
			m_Size = strlen(string);
			m_Buffer = new char[m_Size + 1];
			memcpy(m_Buffer, string, m_Size + 1);
			m_Buffer[m_Size] = 0;
		}
		String(const String &other): m_Size(other.m_Size)
		{
			std::cout << "copied string\n";
			m_Buffer = new char[m_Size + 1];
			memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		}
		~String()
		{
			delete[] m_Buffer;
		}
	char	&operator[](unsigned int index)
	{
		return (m_Buffer[index]);
	}
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return (stream);
}

void	PrintString(const String& string)
{
	std::cout << string << std::endl;
}

int	main()
{
	String	string = "Alexandru";
	String	second = string;

	string[2] = 'z';
	// std::cout << string << std::endl;
	// std::cout << second << std::endl;
	PrintString(string);
	PrintString(second);
	return (0);
}
