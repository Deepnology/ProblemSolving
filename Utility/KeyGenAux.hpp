#ifndef _KEY_GEN_AUX_HPP_
#define _KEY_GEN_AUX_HPP_

#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <iomanip>
#include <codecvt>


class KeyGenAux
{
public:
	inline KeyGenAux(){}
	inline ~KeyGenAux(){}

	inline std::string UIntToHexStr(unsigned int n, bool upper_case = true, bool pad0s = true);//pad 0s toward 8 digits (0-F)
	inline void UIntToHexStr(unsigned int n, char * s, bool upper_case = true, bool pad0s = true);//pad 0s toward 8 digits (0-F)
	inline int UIntHexDigits(unsigned int n);
	inline std::string UCharToBinStr(unsigned char c);
	inline std::string UIntToBinStr(unsigned int c);
	inline std::string UIntToBinStrTrunc(unsigned int c);
	inline std::string UInt64ToBinStr(unsigned long long int c);
	inline std::string StrToHexStr(const std::string & s, bool upper_case = true);
	inline std::vector<unsigned long int> StrToUIntArray(const std::string & s);
	inline std::vector<unsigned int> HexStrToUIntArray(const std::string & s);
	inline std::vector<unsigned char> HexStrToUCharArray(const std::string & s);
	inline unsigned int HexStrToUInt(const std::string & s);
	inline unsigned char HexStrToUChar(const std::string & s);
	inline unsigned int FoldedSum(const unsigned int s, const unsigned int bits);//bits can be 8, 16


};


std::string KeyGenAux::UIntToHexStr(unsigned int n, bool upper_case, bool pad0s)
{
	//method 1:
	//std::ostringstream oss;
	//oss << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << i;

	//method 2:
	char s[2*sizeof(int)+1];//2digit*4bytes+1=9
	this->UIntToHexStr(n, s, upper_case, pad0s);
	return s;
}
void KeyGenAux::UIntToHexStr(unsigned int n, char * s, bool upper_case, bool pad0s)
{
	/*http://codereview.stackexchange.com/questions/30579/how-can-this-integer-to-hex-string-code-be-improved*/
	static const char hex_lookup_upper[] = "0123456789ABCDEF";
	static const char hex_lookup_lower[] = "0123456789abcdef";
	int len = this->UIntHexDigits(n);
	//std::cout << "hex digits = " << len << std::endl;
	if (pad0s)
	{
		for (int i = 0; i < 32/4 - len; ++i)//8 hex digits
			*s++ = '0';
		//after filling in 0s, s points to the (32/4-len)th position (which hasn't been filled in 0)
	}
	else
	{
		if (len & 1)//odd digits
			*s++ = '0';
		//after filling in 0, s points to the 2nd position (which hasn't been filled in 0)
	}
    s[len] = '\0';//fill in \0 in the next right position of the last digit
    for (--len; len >= 0; n >>= 4, --len) 
	{
        s[len] = upper_case ? hex_lookup_upper[n & 0xf] : hex_lookup_lower[n & 0xf];
    }
}
int KeyGenAux::UIntHexDigits(unsigned int n)
{
    if (!n) return 1;
    int ret = 0;
    for (; n; n >>= 4)
        ++ret;
    return ret;
}
std::string KeyGenAux::UCharToBinStr(unsigned char c)
{
	static char bin[CHAR_BIT + 1] = {0};
	for (int i = CHAR_BIT - 1; i >= 0; --i)
	{
		bin[i] = (c % 2) + '0';
		c /= 2;
	}
	return bin;
}
std::string KeyGenAux::UIntToBinStr(unsigned int c)
{
	static char bin[32 + 1] = {0};
	for (int i = 32 - 1; i >= 0; --i)
	{
		bin[i] = (c % 2) + '0';
		c /= 2;
	}
	return bin;
}
std::string KeyGenAux::UIntToBinStrTrunc(unsigned int c)
{
	static char bin[32 + 1] = { 0 };
	int first1 = 0;
	for (int i = 32 - 1; i >= 0; --i)
	{
		bin[i] = (c % 2) + '0';
		if ((c % 2) == 1)
			first1 = 31 - i;
		c /= 2;
	}
	std::string bin2;
	for (int i = first1; i >= 0; --i)
		bin2 += bin[31 - i];
	//std::cout << first1 << std::endl;
	return bin2;
}
std::string KeyGenAux::UInt64ToBinStr(unsigned long long int c)
{
	static char bin[64 + 1] = {0};
	for (int i = 64 - 1; i >= 0; --i)
	{
		bin[i] = (c % 2) + '0';
		c /= 2;
	}
	return bin;
}
std::string KeyGenAux::StrToHexStr(const std::string & s, bool upper_case)
{
    std::ostringstream oss;
    for (std::string::size_type i = 0; i < s.length(); ++i)
        oss << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];
    return oss.str();
}
std::vector<unsigned long int> KeyGenAux::StrToUIntArray(const std::string & s)
{
	std::vector<unsigned long int> v;
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		v.push_back(static_cast<unsigned long int>(s.at(i)));
		//std::cout << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << v[i] << std::endl;
	}
	return v;
}
std::vector<unsigned int> KeyGenAux::HexStrToUIntArray(const std::string & s)
{
	std::vector<unsigned int> r;
	std::istringstream iss(s);
	unsigned int c;
	while (iss >> std::hex >> c)
	{
		r.push_back(c);
	}
	return r;
}
std::vector<unsigned char> KeyGenAux::HexStrToUCharArray(const std::string & s)
{
	std::vector<unsigned char> r;
	std::istringstream iss(s);
	unsigned int c;
	while (iss >> std::hex >> c)
	{
		r.push_back(c);
	}
	return r;
}
inline unsigned int KeyGenAux::HexStrToUInt(const std::string & s)
{
	return strtoul(s.c_str(), NULL, 16);
}
inline unsigned char KeyGenAux::HexStrToUChar(const std::string & s)
{
	unsigned int r = strtoul(s.c_str(), NULL, 16);
	return static_cast<unsigned char>(r);
}
unsigned int KeyGenAux::FoldedSum(const unsigned int s, const unsigned int bits)
{
	unsigned int sum = s;
	//std::cout << "before folding sum: " << sum << std::endl;
	unsigned int filter = 0xFFFFFFFF;
	filter = filter >> (32 - bits);//used to make unwanted bits 0
	//std::cout << "filter = " << filter << std::endl;
	while (sum >> bits)
		sum = (sum & filter) + (sum >> bits);
	//std::cout << "after folding sum: " << sum << std::endl;
	return sum;
}




#endif