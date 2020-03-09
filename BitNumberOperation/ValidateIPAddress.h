#ifndef _VALIDATE_IP_ADDRESS_H
#define _VALIDATE_IP_ADDRESS_H
#include "Debug.h"
/*
Leetcode: Validate IP Address
Write a function to check whether an input string is a valid IPv4 address or IPv6 address or neither.
IPv4 addresses are canonically represented in dot-decimal notation, which consists of four decimal numbers
, each ranging from 0 to 255, separated by dots ("."), e.g.,172.16.254.1;
Besides, leading zeros in the IPv4 is invalid.
For example, the address 172.16.254.01 is invalid.

IPv6 addresses are represented as eight groups of four hexadecimal digits, each group representing 16 bits.
The groups are separated by colons (":"). For example, the address 2001:0db8:85a3:0000:0000:8a2e:0370:7334 is a valid one.
Also, we could omit some leading zeros among four hexadecimal digits and some low-case characters in the address to upper-case ones
, so 2001:db8:85a3:0:0:8A2E:0370:7334 is also a valid IPv6 address(Omit leading zeros and using upper cases).
However, we don't replace a consecutive group of zero value with a single empty group using two consecutive colons (::) to pursue simplicity.
For example, 2001:0db8:85a3::8A2E:0370:7334 is an invalid IPv6 address.
Besides, extra leading zeros in the IPv6 is also invalid.
For example, the address 02001:0db8:85a3:0000:0000:8a2e:0370:7334 is invalid.

Note: You may assume there is no extra space or special characters in the input string.
Example 1:
Input: "172.16.254.1"
Output: "IPv4"
Explanation: This is a valid IPv4 address, return "IPv4".
Example 2:
Input: "2001:0db8:85a3:0:0:8A2E:0370:7334"
Output: "IPv6"
Explanation: This is a valid IPv6 address, return "IPv6".
Example 3:
Input: "256.256.256.256"
Output: "Neither"
Explanation: This is neither a IPv4 address nor a IPv6 address.
 */
class ValidateIPAddress
{
public:
    ValidateIPAddress(){}

    std::string Solve(std::string IP)
    {
        std::string res = BruteForce(IP);
        std::cout << "ValidateIPAddress for \"" << IP << "\": " << res << std::endl;
        return res;
    }

    std::string BruteForce(std::string IP)
    {
        std::istringstream iss(IP);
        std::string s;
        int count = 0;
        if (IP.find(':') == std::string::npos)//check IPv4
        {
            while (getline(iss, s, '.'))
            {
                ++count;
                if (count > 4 || s.empty() || (s.size() > 1 && s[0] == '0') || s.size() > 3) return "Neither";
                for (char c : s)
                    if (!isdigit(c)) return "Neither";
                int val = stoi(s);
                if (val < 0 || val > 255) return "Neither";
            }
            return (count == 4 && IP.back() != '.') ? "IPv4" : "Neither";
        }
        else//check IPv6
        {
            while (getline(iss, s, ':'))
            {
                ++count;
                if (count > 8 || s.empty() || s.size() > 4) return "Neither";
                for (char c : s)
                    if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F')) return "Neither";
            }
            return (count == 8 && IP.back() != ':') ? "IPv6" : "Neither";
        }
    }
};
/*
ValidateIPAddress for "172.16.254.1": IPv4
ValidateIPAddress for "2001:0db8:85a3:0:0:8A2E:0370:7334": IPv6
ValidateIPAddress for "256.256.256.256": Neither
 */
#endif
