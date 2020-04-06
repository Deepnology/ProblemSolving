#ifndef ENCODE_DECODE_TINY_URL_H
#define ENCODE_DECODE_TINY_URL_H
#include "Debug.h"
/*
Leetcode: Encode and decode TinyURL
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.
Design the encode and decode methods for the TinyURL service.
There is no restriction on how your encode/decode algorithm should work.
You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
*/
class EncodeDecodeTinyURL
{
public:
	EncodeDecodeTinyURL() {}

	std::string map = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";//for base62
	std::unordered_map<std::string, std::string> keyURL;
	// Encodes a URL to a shortened URL.
	std::string encode(std::string longUrl)
	{
		auto curHash = std::hash<std::string>()(longUrl);
		std::string key;//transform curHash to base62
		while (curHash)
		{
			key = map[curHash % 62] + key;
			curHash /= 62;
		}

		keyURL.insert({ key, longUrl });
		std::string res = "http://tinyurl.com/" + key;

		std::cout << "EncodeDecodeTinyURL Encode for \"" << longUrl << "\": " << res << std::endl;
		return res;
	}

	// Decodes a shortened URL to its original URL.
	std::string decode(std::string shortUrl)
	{
		std::string key = shortUrl.substr(19);//remove "http://tinyurl.com/"

		std::cout << "EncodeDecodeTinyURL Decode for \"" << shortUrl << "\": " << keyURL[key] << std::endl;
		return keyURL[key];
	}
};
/*
EncodeDecodeTinyURL Encode for "https://leetcode.com/problems/design-tinyurl": http://tinyurl.com/buKmzk
EncodeDecodeTinyURL Decode for "http://tinyurl.com/buKmzk": https://leetcode.com/problems/design-tinyurl
*/
#endif
