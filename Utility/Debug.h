#ifndef DEBUG_H
#define DEBUG_H

#pragma warning (disable : 4996) //fopen
#include <stdio.h>
#include <string.h>
#define DEBUG_MDUMP(filename, mode, str) \
    do { \
        FILE *__file = fopen(filename, mode); \
        if (__file == NULL) { \
            char __err[256]; \
            snprintf(__err, sizeof(__err), "Error opening %s in DEBUG_MDUMP", filename); \
            perror(__err); \
        } else { \
            fprintf(__file, "%s\n", str); \
            fclose(__file); \
        } \
    } while(0)

#define DEBUG_MDUMPF(filename, mode, ...) \
    do { \
        FILE *__file = fopen(filename, mode); \
        if (__file == NULL) { \
            char __err[256]; \
            snprintf(__err, sizeof(__err), "Error opening %s in DEBUG_MDUMPF", filename); \
            perror(__err); \
        } else { \
            fprintf(__file, __VA_ARGS__); \
            fclose(__file); \
        } \
    } while(0)

#define DEBUG_ADUMP(filename, str) DEBUG_MDUMP(filename, "a", str)
#define DEBUG_ADUMPF(filename, ...) DEBUG_MDUMPF(filename, "a", __VA_ARGS__)
#define DEBUG_WDUMP(filename, str) DEBUG_MDUMP(filename, "w", str)
#define DEBUG_WDUMPF(filename, ...) DEBUG_MDUMPF(filename, "w", __VA_ARGS__)

#define DEBUG_CLRDUMP(filename) \
    do { \
        FILE *__file = fopen(filename, "w"); \
        if (__file == NULL) { \
            char __err[256]; \
            snprintf(__err, sizeof(__err), "Error opening %s in DEBUG_CLRDUMP", filename); \
            perror(__err); \
        } else { \
            fclose(__file); \
        } \
    } while(0)

#define DEBUG_READ(filename, buf, bufSize) \
    do{ \
        FILE *__file = fopen(filename, "r"); \
        if (__file == NULL) { \
            char __err[256]; \
            snprintf(__err, sizeof(__err), "Error opening %s in DEBUG_READ", filename); \
            perror(__err); \
        } else { \
            if (fgets(buf, bufSize, __file) != NULL) { \
                size_t readLen = strlen(buf); \
                if (readLen > 0 && buf[readLen-1] == '\n') {\
                    buf[readLen-1] = '\0'; \
                } \
            } \
            else { \
                char __err[256]; \
                snprintf(__err, sizeof(__err), "Error reading %s in DEBUG_READ", filename); \
                perror(__err); \
            } \
            fclose(__file); \
        } \
    } while(0)

#define DEBUG_READ_BUF_SIZE 1024
#define DEBUG_READ_BUF(filename) \
    char DEBUG_READ_BUF_[DEBUG_READ_BUF_SIZE] = ""; \
    DEBUG_READ(filename, DEBUG_READ_BUF_, DEBUG_READ_BUF_SIZE)

#define DEBUG_RENAME_APPEND(file, newApn) \
    do { \
        const char *__fileName = (file); \
        FILE *__f = fopen(__fileName, "r"); \
        if (__f) { \
            fclose(__f); \
            char __newFileName[256]; \
            const char *__dot = strrchr(__fileName, '.'); \
            if (__dot) { \
                size_t __nameLen = __dot - __fileName; \
                snprintf(__newFileName, __nameLen + 1, "%s", __fileName); \
                snprintf(__newFileName + __nameLen, sizeof(__newFileName) - __nameLen, "%s.%s", newApn, __dot + 1); \
            } else { \
                snprintf(__newFileName, sizeof(__newFileName), "%s%s", __fileName, newApn); \
            } \
            remove(__newFileName); \
            if (rename(__fileName, __newFileName) != 0) { \
                char __err[256]; \
                snprintf(__err, sizeof(__err), "Error renaming %s in DEBUG_RENAME_APPEND", __newFileName); \
                perror(__err); \
            } \
        } \
    } while(0)

#define DEBUG_PUSH_BUF_INIT(size) \
    char DEBUG_PUSH_BUF_[size] = ""; \
	size_t DEBUG_PUSH_BUF_POS_ = 0; \
	const size_t DEBUG_PUSH_BUF_CAP_ = size;

#define DEBUG_PUSH_BUF_STR(str) \
    do { \
        size_t __len = strlen(str); \
        if (DEBUG_PUSH_BUF_POS_ + __len < DEBUG_PUSH_BUF_CAP_) { \
	        memcpy(DEBUG_PUSH_BUF_ + DEBUG_PUSH_BUF_POS_, str, __len); \
		    DEBUG_PUSH_BUF_POS_ += __len; \
		    DEBUG_PUSH_BUF_[DEBUG_PUSH_BUF_POS_] = '\0'; \
	    } else { \
		    fprintf(stderr, "DEBUG_PUSH_BUF_STR: Buffer overflow prevented\n"); \
	    } \
	} while(0)

#define DEBUG_PUSH_BUF_INT(num) \
    do { \
        char __intStr[32]; \
        int __intLen = snprintf(__intStr, sizeof(__intStr), "%d", (num)); \
        if (__intLen < 0 || (size_t)__intLen >= sizeof(__intStr)) { \
            fprintf(stderr, "DEBUG_PUSH_BUF_INT: Integer formatting failed or truncated\n"); \
        } \
        if (DEBUG_PUSH_BUF_POS_ + (size_t)__intLen < DEBUG_PUSH_BUF_CAP_) { \
            memcpy(DEBUG_PUSH_BUF_ + DEBUG_PUSH_BUF_POS_, __intStr, __intLen); \
            DEBUG_PUSH_BUF_POS_ += (size_t)__intLen; \
            DEBUG_PUSH_BUF_[DEBUG_PUSH_BUF_POS_] = '\0'; \
        } else { \
            fprintf(stderr, "DEBUG_PUSH_BUF_INT: Buffer overflow prevented\n"); \
        } \
    } while(0)

#ifdef __cplusplus
#include <mutex>
#define DEBUG_LOCK_MUTEX(mtx, ...) \
    do { \
        mtx.lock(); \
        __VA_ARGS__; \
        mtx.unlock(); \
	} while (0)

#define DEBUG_MUTEX_DECLARE() \
    inline std::mutex DEBUG_MUTEX_

#define DEBUG_LOCK(...) DEBUG_LOCK_MUTEX(DEBUG_MUTEX_, __VA_ARGS__)
#elif defined(_POSIX_THREADS) && (_POSIX_THREADS > 0)
#define DEBUG_LOCK_MUTEX(mtx, ...) \
    do { \
        pthread_mutex_lock(&(mtx)); \
        __VA_ARGS__; \
        pthread_mutex_unlock(&(mtx)); \
	} while (0)
	
#define DEBUG_MUTEX_DECLARE() \
    extern pthread_mutex_t DEBUG_MUTEX_

#define DEBUG_MUTEX_DEFINE() \
    pthread_mutex_t DEBUG_MUTEX_ = PTHREAD_MUTEX_INITIALIZER

#define DEBUG_LOCK(...) DEBUG_LOCK_MUTEX(DEBUG_MUTEX_, __VA_ARGS__)
#else
#define DEBUG_LOCK_MUTEX(mtx, ...) \
    do { \
        __VA_ARGS__; \
	} while (0)

#define DEBUG_MUTEX_DECLARE() \
    extern int DEBUG_MUTEX_

#define DEBUG_MUTEX_DEFINE() \
    int DEBUG_MUTEX_ = 0

#define DEBUG_LOCK(...) DEBUG_LOCK_MUTEX(DEBUG_MUTEX_, __VA_ARGS__)
#endif

#ifdef __cplusplus
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <format>
#include <bitset>
#include <cstdint>
#include <cstring>
#if defined(QT_VERSION)
#include <QString>
#include <QTextStream>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <qlogging.h>
#include <QVector>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QWidget>
#include <QDockWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDateTime>
#endif
#define stringify(name)#name
namespace Debug
{
	class RedirectCout
	{
		inline static std::once_flag m_onceFlag;
		inline static std::streambuf* m_coutBuf = nullptr;
		inline static const std::ofstream m_nullStream = std::ofstream("/dev/null");
		inline static std::ofstream m_ofstream;
		static void backup()
		{
			if (!m_coutBuf)
				m_coutBuf = std::cout.rdbuf();
		}
	public:
		static void toCout()
		{
			if (m_coutBuf && m_coutBuf != std::cout.rdbuf())
				std::cout.rdbuf(m_coutBuf);
		}
		static void toFile(const std::string& file)
		{
			std::call_once(m_onceFlag, backup);
			m_ofstream.clear();
			m_ofstream.close();
			m_ofstream.open(file);
			std::cout.rdbuf(m_ofstream.rdbuf());
		}
		static void toNullSink()
		{
			std::call_once(m_onceFlag, backup);
			std::cout.rdbuf(m_nullStream.rdbuf());
		}
	};
	typedef std::map<int, const char*> EnumNameMap;
	typedef std::vector<const char*> EnumNameVec;
	enum class Splitter
	{
		Comma = 0,
		NewLine = 1,
	};

	template<typename V>
	inline std::string toStrT(const V& v)
	{
		using D = std::decay_t<V>;
		if constexpr (std::is_same_v<D, std::string>)
			return v;
		else if constexpr (std::is_convertible_v<V, std::string_view>)
			return std::string(std::string_view(v));
		else if constexpr (std::is_arithmetic_v<V>)
			return std::to_string(v);
#if defined(QT_VERSION)
		else if constexpr (std::is_same_v<D, QByteArray>)
			return std::string(v.constData(), v.size());
		else if constexpr (std::is_same_v<D, QString>)
			return v.toStdString();
		else
		{
			QString s;
			QDebug dbg(&s);
			dbg.noquote();
			dbg << v;
			return s.toStdString();
		}
#else
		else if constexpr (std::is_pointer_v<D> && std::is_same_v<std::remove_pointer_t<D>, std::type_info>)
		{
			const std::type_info* ti = v;
			if (!ti) return "nullptr";
			std::ostringstream oss;
			oss << ti->name();
			return oss.str();
		}
		else
		{
			std::ostringstream oss;
			oss << v;
			return v.str();
		}
#endif
	}

	template<class T, class U = T>
	class Print2D
	{
	public:
		Print2D() {}
		~Print2D() {}

		void operator()(const std::vector<std::vector<T>>& vv, bool columnXrowY = true, bool tab = false)
		{
			if (vv.empty())
				return;
			if (columnXrowY)//[columnX][rowY]
			{
				std::ostringstream oss;
				oss << "[cX][rY]" << std::endl;
				int maxColumnSize = vv[0].size();//can vary
				int maxRowSize = vv.size();//should be fixed
				for (int columnX = 0; columnX < maxRowSize; ++columnX)
				{
					int columnSize = vv[columnX].size();

					if (maxColumnSize < columnSize)
						maxColumnSize = columnSize;
				}

				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
					{
						int columnSize = vv[columnX].size();
						if (columnX == 0)
						{
							if (tab)
								oss << "Row#" << rowY << "	=	";
							else
								oss << "Row#" << rowY << "	= ";
						}

						if (rowY < columnSize)
						{
							oss << vv[columnX][rowY];
						}
						else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}

						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
			else//[rowY][columnX]
			{
				std::ostringstream oss;
				oss << "[rY][cX]" << std::endl;
				int maxColumnSize = vv.size();//should be fixed
				int maxRowSize = vv[0].size();//can vary
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (maxRowSize < rowSize)
						maxRowSize = rowSize;
				}
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (tab)
						oss << "Row#" << rowY << "	=	";
					else
						oss << "Row#" << rowY << "	= ";
					for (int columnX = 0; columnX < maxRowSize; ++columnX)
					{
						if (columnX < rowSize)
							oss << vv[rowY][columnX];
						else
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}
						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
		}
		void operator()(const std::deque<std::vector<T>>& vv, bool columnXrowY = true, bool tab = false)
		{
			if (vv.empty())
				return;
			if (columnXrowY)//[columnX][rowY]
			{
				std::ostringstream oss;
				oss << "[cX][rY]" << std::endl;
				int maxColumnSize = vv[0].size();//can vary
				int maxRowSize = vv.size();//should be fixed
				for (int columnX = 0; columnX < maxRowSize; ++columnX)
				{
					int columnSize = vv[columnX].size();

					if (maxColumnSize < columnSize)
						maxColumnSize = columnSize;
				}

				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
					{
						int columnSize = vv[columnX].size();
						if (columnX == 0)
						{
							if (tab)
								oss << "Row#" << rowY << "	=	";
							else
								oss << "Row#" << rowY << "	= ";
						}

						if (rowY < columnSize)
						{
							oss << vv[columnX][rowY];
						}
						else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}

						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
			else//[rowY][columnX]
			{
				std::ostringstream oss;
				oss << "[rY][cX]" << std::endl;
				int maxColumnSize = vv.size();//should be fixed
				int maxRowSize = vv[0].size();//can vary
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (maxRowSize < rowSize)
						maxRowSize = rowSize;
				}
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (tab)
						oss << "Row#" << rowY << "	=	";
					else
						oss << "Row#" << rowY << "	= ";
					for (int columnX = 0; columnX < maxRowSize; ++columnX)
					{
						if (columnX < rowSize)
							oss << vv[rowY][columnX];
						else
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}
						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
		}
		void operator()(const std::vector<std::string>& vv, bool columnXrowY = true, bool tab = false)//no template parameter
		{
			if (vv.empty())
				return;
			if (columnXrowY)//[columnX][rowY]
			{
				std::ostringstream oss;
				oss << "[cX][rY]" << std::endl;
				int maxColumnSize = vv[0].size();//can vary
				int maxRowSize = vv.size();//should be fixed
				for (int columnX = 0; columnX < maxRowSize; ++columnX)
				{
					int columnSize = vv[columnX].size();

					if (maxColumnSize < columnSize)
						maxColumnSize = columnSize;
				}

				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
					{
						int columnSize = vv[columnX].size();
						if (columnX == 0)
						{
							if (tab)
								oss << "Row#" << rowY << "	=	";
							else
								oss << "Row#" << rowY << "	= ";
						}

						if (rowY < columnSize)
						{
							oss << vv[columnX][rowY];
						}
						else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}

						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
			else//[rowY][columnX]
			{
				std::ostringstream oss;
				oss << "[rY][cX]" << std::endl;
				int maxColumnSize = vv.size();//should be fixed
				int maxRowSize = vv[0].size();//can vary
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (maxRowSize < rowSize)
						maxRowSize = rowSize;
				}
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (tab)
						oss << "Row#" << rowY << "	=	";
					else
						oss << "Row#" << rowY << "	= ";
					for (int columnX = 0; columnX < maxRowSize; ++columnX)
					{
						if (columnX < rowSize)
							oss << vv[rowY][columnX];
						else
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}
						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
		}
		void operator()(const std::vector<std::stack<T>>& vs, bool columnXrowY = true, bool tab = false, bool topToBottom = false)
		{
			std::vector<std::vector<int>> copy;
			int N = vs.size();
			for (int i = 0; i < N; ++i)
			{
				copy.push_back(std::vector<int>());
				std::stack<int> s = vs[i];
				if (!topToBottom)
				{
					std::stack<int> rev;
					while (!s.empty())
						rev.push(s.top()), s.pop();
					rev.swap(s);
				}
				while (!s.empty())
				{
					copy.back().push_back(s.top());
					s.pop();
				}
			}
			this->operator()(copy, columnXrowY, tab);
		}
		void operator()(const std::unordered_map<T, std::unordered_map<T, U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::unordered_map<T, U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::unordered_map<T, U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << "[" << j->first << "," << j->second << "]";
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::unordered_map<T, std::map<T, U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::map<T, U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::map<T, U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << "[" << j->first << "," << j->second << "]";
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::unordered_map<T, std::unordered_set<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::unordered_set<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::unordered_set<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::unordered_map<T, std::multiset<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::multiset<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::multiset<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::unordered_map<T, std::set<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::set<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::set<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::unordered_map<T, std::stack<U>>& m, bool topToBottom = false)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::stack<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				std::stack<U> copy(i->second);
				if (!topToBottom)
				{
					std::stack<T> rev;
					while (!copy.empty())
						rev.push(copy.top()), copy.pop();
					rev.swap(copy);
				}
				while (!copy.empty())
				{
					oss << copy.top();
					copy.pop();
					if (!copy.empty())
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::map<T, std::map<T, U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::map<T, std::map<T, U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::map<T, U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << "[" << j->first << "," << j->second << "]";
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::map<T, std::unordered_map<T, U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::map<T, std::unordered_map<T, U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::unordered_map<T, U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << "[" << j->first << "," << j->second << "]";
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::map<T, std::vector<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::map<T, std::vector<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::vector<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::map<T, std::unordered_set<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::map<T, std::unordered_set<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::unordered_set<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::map<T, std::set<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::map<T, std::set<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::set<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::unordered_map<T, std::vector<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::unordered_map<T, std::vector<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::vector<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}

		void operator()(const std::vector<std::vector<std::pair<T, U>>>& vv, bool columnXrowY = true, bool tab = false)
		{
			if (vv.empty())
				return;
			if (columnXrowY)//[columnX][rowY]
			{
				std::ostringstream oss;
				oss << "[cX][rY]" << std::endl;
				int maxColumnSize = vv[0].size();//can vary
				int maxRowSize = vv.size();//should be fixed
				for (int columnX = 0; columnX < maxRowSize; ++columnX)
				{
					int columnSize = vv[columnX].size();

					if (maxColumnSize < columnSize)
						maxColumnSize = columnSize;
				}

				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
					{
						int columnSize = vv[columnX].size();
						if (columnX == 0)
						{
							if (tab)
								oss << "Row#" << rowY << "	=	";
							else
								oss << "Row#" << rowY << "	= ";
						}

						if (rowY < columnSize)
						{
							oss << "[" << vv[columnX][rowY].first << "," << vv[columnX][rowY].second << "]";
						}
						else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}

						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
			else//[rowY][columnX]
			{
				std::ostringstream oss;
				oss << "[rY][cX]" << std::endl;
				int maxColumnSize = vv.size();//should be fixed
				int maxRowSize = vv[0].size();//can vary
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (maxRowSize < rowSize)
						maxRowSize = rowSize;
				}
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vv[rowY].size();
					if (tab)
						oss << "Row#" << rowY << "	=	";
					else
						oss << "Row#" << rowY << "	= ";
					for (int columnX = 0; columnX < maxRowSize; ++columnX)
					{
						if (columnX < rowSize)
						{
							oss << "[" << vv[rowY][columnX].first << "," << vv[rowY][columnX].second << "]";
						}
						else
						{
							if (tab)
								oss << "	";
							else
								oss << " ";
						}
						if (columnX != maxRowSize - 1)
						{
							if (tab)
								oss << ",	";
							else
								oss << ", ";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
		}
		void operator()(const std::vector<std::pair<std::pair<T, T>, std::vector<U>>>& vv)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::vector<std::pair<std::pair<T, T>, std::vector<U>>>::const_iterator i = vv.cbegin(); i != vv.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= [" << i->first.first << "," << i->first.second << "]: ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::vector<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::vector<std::pair<T, std::vector<U>>>& vv)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::vector<std::pair<T, std::vector<U>>>::const_iterator i = vv.cbegin(); i != vv.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::vector<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::vector<std::pair<T, std::unordered_set<U>>>& vv)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::vector<std::pair<T, std::unordered_set<U>>>::const_iterator i = vv.cbegin(); i != vv.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::unordered_set<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::vector<std::pair<T, std::unordered_map<T, U>>>& vv)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::vector<std::pair<T, std::unordered_map<T, U>>>::const_iterator i = vv.cbegin(); i != vv.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::unordered_map<T, U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << "[" << j->first << "," << j->second << "]";
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::vector<std::pair<T, std::set<U>>>& vv)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::vector<std::pair<T, std::set<U>>>::const_iterator i = vv.cbegin(); i != vv.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::set<U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << *j;
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
		void operator()(const std::vector<std::pair<T, std::map<T, U>>>& vv)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::vector<std::pair<T, std::map<T, U>>>::const_iterator i = vv.cbegin(); i != vv.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (typename std::map<T, U>::const_iterator j = i->second.cbegin(); j != i->second.cend(); ++j)
				{
					oss << "[" << j->first << "," << j->second << "]";
					if (++cnt != M)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
	};

	class Print2D_
	{
	public:
		std::string operator()(const std::vector<std::vector<std::string>>& vv, bool columnXrowY,
			const std::vector<std::string>& rowItem, const std::vector<std::string>& colItem,
			bool hideEmptyRow, bool hideEmptyCol, int uniformMinCellWidth4)
		{
			if (vv.empty()) return "";
			int cellWidth = 0;
			if (uniformMinCellWidth4 >= 4)
			{
				int maxCellWidth = 1;
				for (int rowY = 0; rowY < vv.size(); ++rowY)
					for (int colX = 0; colX < vv[rowY].size(); ++colX)
						maxCellWidth = std::max(maxCellWidth, (int)vv[rowY][colX].size());
				cellWidth = std::max(uniformMinCellWidth4, maxCellWidth);
			}

			//use [colX,rowY] to represent actual matrix indices including row/col headers. so use vv[colX-1][rowY-1], rowItem[rowY-1], colItem[colX-1]

			std::ostringstream oss;
			if (columnXrowY)//[columnX][rowY]
			{
				int maxColumnSize = rowItem.size();//can vary (vertical size)
				int maxRowSize = std::max(vv.size(), colItem.size()) + 1;//should be fixed (horizontal size)
				for (int colX = 1; colX < maxRowSize; ++colX)
					if (colX - 1 < vv.size())
						maxColumnSize = std::max(maxColumnSize, (int)vv[colX - 1].size());
				maxColumnSize += 1;

				//calculate emptyColArr
				std::vector<int> emptyColArr(maxRowSize, 1);
				if (hideEmptyCol)
				{
					//1. check 1st column: rowItem
					emptyColArr[0] = 0;
					//2. check the rest columns
					for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
						for (int rowY = 1; rowY < maxColumnSize; ++rowY)
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								emptyColArr[colX] &= (vv[colX - 1][rowY - 1].empty() ? 1 : 0);
				}

				//calculate emptyRowArr
				std::vector<int> emptyRowArr(maxColumnSize, 1);
				if (hideEmptyRow)
				{
					//1. check 1st row: colItem
					emptyRowArr[0] = 0;
					//2. check the rest rows
					for (int rowY = 1; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
						for (int colX = 1; colX < maxRowSize; ++colX)
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								emptyRowArr[rowY] &= (vv[colX - 1][rowY - 1].empty() ? 1 : 0);
				}

				//calculate colWidthArr
				std::vector<int> colWidthArr(maxRowSize, cellWidth);//the width of each column
				if (cellWidth == 0)//calculate and use non-uniform cell widths
				{
					//1. check 1st column: rowItem
					colWidthArr[0] = std::format("{}", "Row#").size();
					for (int rowY = 1; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
					{
						if (hideEmptyRow && emptyRowArr[rowY])
							continue;
						if (rowY - 1 < rowItem.size())
							colWidthArr[0] = std::max(colWidthArr[0], (int)rowItem[rowY - 1].size());
						else
							colWidthArr[0] = std::max(colWidthArr[0], (int)std::format("{}", "Row#").size() + (int)std::format("{}", rowY).size());
					}
					//2. check the rest columns
					for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
					{
						colWidthArr[colX] = 4;//cell minimum width is 4
						if (hideEmptyCol && emptyColArr[colX])
							continue;
						//1. check 1st row: colItem
						if (colX - 1 < colItem.size())
							colWidthArr[colX] = std::max(colWidthArr[colX], (int)colItem[colX - 1].size());
						else
							colWidthArr[colX] = std::max(colWidthArr[colX], (int)std::format("{}", "Col#").size() + (int)std::format("{}", colX).size());
						//2. check the rest of colX
						for (int rowY = 1; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
						{
							if (hideEmptyRow && emptyRowArr[rowY])
								continue;
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								colWidthArr[colX] = std::max(colWidthArr[colX], (int)vv[colX - 1][rowY - 1].size());
						}
					}
				}

				//print matrix
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					if (rowY == 0)//1. print the 1st row: colItem
					{
						oss << std::vformat("{:>" + std::format("{}", colWidthArr[0] + std::format("{}", "| ").size()) + "}", std::make_format_args("| "));
						for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
						{
							if (hideEmptyCol && emptyColArr[colX])
								continue;
							if (colX - 1 < colItem.size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}",
									std::make_format_args(colItem[colX - 1].substr(0, std::min((int)colItem[colX - 1].size(), colWidthArr[colX]))));
							else if (colWidthArr[colX] - std::format("{}", "Col#").size() >= std::format("{}", colX).size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX] - std::format("{}", colX).size()) + "}{}",
									std::make_format_args("Col#", colX));
							else
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args("Col#"));
							if (colX != maxRowSize - 1 &&
								(!hideEmptyCol || !std::accumulate(emptyColArr.cbegin() + colX + 1, emptyColArr.cend(), 1, std::bit_and<int>())))
								oss << "| ";
						}
					}
					else if (hideEmptyRow && emptyRowArr[rowY])
						continue;
					else//2. print the rest rows
					{
						//1. print the 1st column: rowItem
						if (rowY - 1 < rowItem.size())
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[0]) + "}| ",
								std::make_format_args(rowItem[rowY - 1].substr(0, std::min((int)rowItem[rowY - 1].size(), colWidthArr[0]))));
						else if (colWidthArr[0] - std::format("{}", "Row#").size() >= std::format("{}", rowY).size())
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[0] - std::format("{}", rowY).size()) + "}{}| ",
								std::make_format_args("Row#", rowY));
						else
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[0]) + "}| ", std::make_format_args("Row#"));
						//2. print the rest columns or rowY
						for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
						{
							if (hideEmptyCol && emptyColArr[colX])
								continue;
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}",
									std::make_format_args(vv[colX - 1][rowY - 1].substr(0, std::min((int)vv[colX - 1][rowY - 1].size(), colWidthArr[colX]))));
							else
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args("NA"));
							if (colX != maxRowSize - 1 &&
								(!hideEmptyCol || !std::accumulate(emptyColArr.cbegin() + colX + 1, emptyColArr.cend(), 1, std::bit_and<int>())))
								oss << "| ";
						}
					}
					if (rowY == 0)
					{
						//print horizontal line
						oss << std::endl;
						for (int colX = 0; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
						{
							if (hideEmptyCol && emptyColArr[colX])
								continue;
							if (colX == 0)
								oss << std::vformat("{:->" + std::format("{}", colWidthArr[colX] + 1) + "}", std::make_format_args("+"));
							else if (colX != maxRowSize - 1 &&
								(!hideEmptyCol || !std::accumulate(emptyColArr.cbegin() + colX + 1, emptyColArr.cend(), 1, std::bit_and<int>())))
								oss << std::vformat("{:->" + std::format("{}", colWidthArr[colX] + 2) + "}", std::make_format_args("+"));
							else
								oss << std::vformat("{:->" + std::format("{}", colWidthArr[colX] + 1) + "}", std::make_format_args("-"));
						}
					}

					oss << std::endl;
				}
			}
			else//[rowY][columnX]
			{

			}
			return oss.str();
		}
	};

#if defined(QT_VERSION)
	template<class U>
	class Print2D<QString, U>
	{
	public:
		void operator()(const std::map<QString, QVector<U>>& m)
		{
			std::ostringstream oss;
			int count = 0;
			for (typename std::map<QString, QVector<U>>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "Row#" << count++ << "	= " << i->first.toStdString() << ": ";
				int M = i->second.size();
				int cnt = 0;
				for (int j = 0; j < M; ++j)
				{
					oss << i->second[j];
					if (j != M - 1)
						oss << ", ";
				}
				oss << std::endl;
			}
			std::cout << oss.str() << std::endl;
		}
	};
#endif

	//check also the UniqueBinarySearchTree.h
	template<class T>
	class Print3D
	{
	public:
		Print3D() {}
		~Print3D() {}

		void operator()(const std::vector<std::vector<std::vector<T>>>& vvv, bool colXrowYdepthZ = true)
		{
			if (vvv.empty())
				return;
			if (colXrowYdepthZ)
			{
				std::ostringstream oss;
				oss << "[cX][rY][dZ]" << std::endl;
				int maxColumnSize = vvv[0].size();//can vary
				int maxRowSize = vvv.size();//should be fixed
				int maxDepthSize = 0;
				for (int columnX = 0; columnX < maxRowSize; ++columnX)
				{
					int columnSize = vvv[columnX].size();

					if (maxColumnSize < columnSize)
						maxColumnSize = columnSize;

					for (int rowY = 0; rowY < columnSize; ++rowY)
					{
						int depthSize = vvv[columnX][rowY].size();

						if (maxDepthSize < depthSize)
							maxDepthSize = depthSize;
					}
				}

				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
					{
						int columnSize = vvv[columnX].size();
						if (columnX == 0)
						{
							oss << "Row#" << rowY << "	= ";
						}

						if (rowY < columnSize)
						{
							int depthSize = vvv[columnX][rowY].size();
							for (int depthZ = 0; depthZ < depthSize; ++depthZ)
							{
								oss << vvv[columnX][rowY][depthZ];
								if (depthZ != depthSize - 1)
									oss << ",";
							}
						}
						else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
						{
							oss << "	";
						}

						if (columnX != maxRowSize - 1)
						{
							oss << ".	";
						}
						else
						{
							oss << ".";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
			else//rowYcolXdepthZ
			{
				std::ostringstream oss;
				oss << "[rY][cX][dZ]" << std::endl;
				int maxColumnSize = vvv.size();//should be fixed
				int maxRowSize = vvv[0].size();//can vary
				int maxDepthSize = 0;
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vvv[rowY].size();
					if (maxRowSize < rowSize)
						maxRowSize = rowSize;

					for (int colX = 0; colX < rowSize; ++colX)
					{
						int depthSize = vvv[rowY][colX].size();

						if (maxDepthSize < depthSize)
							maxDepthSize = depthSize;
					}
				}
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vvv[rowY].size();
					oss << "Row#" << rowY << "	= ";
					for (int columnX = 0; columnX < maxRowSize; ++columnX)
					{
						if (columnX < rowSize)
						{
							int depthSize = vvv[rowY][columnX].size();
							for (int depthZ = 0; depthZ < maxDepthSize; ++depthZ)
							{
								if (depthZ < depthSize)
									oss << vvv[rowY][columnX][depthZ];
								else
									oss << " ";
								if (depthZ != maxDepthSize - 1)
									oss << ",";
							}
						}
						else
						{
							for (int depthZ = 0; depthZ < maxDepthSize; ++depthZ)
							{
								oss << " ";
								if (depthZ != maxDepthSize - 1)
									oss << ",";
							}
						}
						if (columnX != maxRowSize - 1)
						{
							oss << ".	";
						}
						else
						{
							oss << ".";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
		}
		void operator()(const std::vector<std::vector<std::vector<std::pair<T, T>>>>& vvv, bool colXrowYdepthZ = true)
		{
			if (vvv.empty())
				return;
			if (colXrowYdepthZ)
			{
				std::ostringstream oss;
				oss << "[cX][rY][dZ]" << std::endl;
				int maxColumnSize = vvv[0].size();//can vary
				int maxRowSize = vvv.size();//should be fixed
				int maxDepthSize = 0;
				for (int columnX = 0; columnX < maxRowSize; ++columnX)
				{
					int columnSize = vvv[columnX].size();

					if (maxColumnSize < columnSize)
						maxColumnSize = columnSize;

					for (int rowY = 0; rowY < columnSize; ++rowY)
					{
						int depthSize = vvv[columnX][rowY].size();

						if (maxDepthSize < depthSize)
							maxDepthSize = depthSize;
					}
				}

				for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					for (int columnX = 0; columnX < maxRowSize; ++columnX)//for each columnX (iterate horizontally)
					{
						int columnSize = vvv[columnX].size();
						if (columnX == 0)
						{
							oss << "Row#" << rowY << "	= ";
						}

						if (rowY < columnSize)
						{
							int depthSize = vvv[columnX][rowY].size();
							for (int depthZ = 0; depthZ < depthSize; ++depthZ)
							{
								oss << "[" << vvv[columnX][rowY][depthZ].first << "," << vvv[columnX][rowY][depthZ].second << "]";
								if (depthZ != depthSize - 1)
									oss << ",";
							}
						}
						else//(rowY > 0 && rowY < maxColumnSize) || (rowY == 0 && columnSize == 0)
						{
							oss << "	";
						}

						if (columnX != maxRowSize - 1)
						{
							oss << ".	";
						}
						else
						{
							oss << ".";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
			else//rowYcolXdepthZ
			{
				std::ostringstream oss;
				oss << "[rY][cX][dZ]" << std::endl;
				int maxColumnSize = vvv.size();//should be fixed
				int maxRowSize = vvv[0].size();//can vary
				int maxDepthSize = 0;
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vvv[rowY].size();
					if (maxRowSize < rowSize)
						maxRowSize = rowSize;

					for (int colX = 0; colX < rowSize; ++colX)
					{
						int depthSize = vvv[rowY][colX].size();

						if (maxDepthSize < depthSize)
							maxDepthSize = depthSize;
					}
				}
				for (int rowY = 0; rowY < maxColumnSize; ++rowY)
				{
					int rowSize = vvv[rowY].size();
					oss << "Row#" << rowY << "	= ";
					for (int columnX = 0; columnX < maxRowSize; ++columnX)
					{
						if (columnX < rowSize)
						{
							int depthSize = vvv[rowY][columnX].size();
							for (int depthZ = 0; depthZ < maxDepthSize; ++depthZ)
							{
								if (depthZ < depthSize)
									oss << "[" << vvv[rowY][columnX][depthZ].first << "," << vvv[rowY][columnX][depthZ].second << "]";
								else
									oss << "[ , ]";
								if (depthZ != maxDepthSize - 1)
									oss << ",";
							}
						}
						else
						{
							for (int depthZ = 0; depthZ < maxDepthSize; ++depthZ)
							{
								oss << "[ , ]";
								if (depthZ != maxDepthSize - 1)
									oss << ",";
							}
						}
						if (columnX != maxRowSize - 1)
						{
							oss << ".	";
						}
						else
						{
							oss << ".";
						}
					}
					oss << std::endl;
				}
				std::cout << oss.str() << std::endl;
			}
		}
	};

	class Print3D_
	{
	public:
		std::string operator()(const std::vector<std::vector<std::vector<std::string>>>& vv, bool columnXrowY,
			const std::vector<std::string>& rowItem, const std::vector<std::string>& colItem,
			bool hideEmptyRow, bool hideEmptyCol, int uniformMinCellWidth4, int uniformMinCellHeight1, bool useNilForEmpty)
		{
			if (vv.empty()) return "";
			int cellWidth = 0;
			if (uniformMinCellWidth4 >= 4)
			{
				int maxCellWidth = 1;
				for (int rowY = 0; rowY < vv.size(); ++rowY)
					for (int colX = 0; colX < vv[rowY].size(); ++colX)
						maxCellWidth = std::max(maxCellWidth, (int)vv[rowY][colX].size());
				cellWidth = std::max(uniformMinCellWidth4, maxCellWidth);
			}
			int cellHeight = 1;

			//use [colX,rowY] to represent actual matrix indices including row/col headers. so use vv[colX-1][rowY-1][], rowItem[rowY-1], colItem[colX-1]

			std::ostringstream oss;
			int maxColumnSize = 0;
			int maxRowSize = 0;
			if (columnXrowY)
			{
				maxColumnSize = rowItem.size();//can vary (vertical size)
				maxRowSize = std::max(vv.size(), colItem.size()) + 1;//should be fixed (horizontal size)
				for (int colX = 1; colX < maxRowSize; ++colX)
					if (colX - 1 < vv.size())
						maxColumnSize = std::max(maxColumnSize, (int)vv[colX - 1].size());
				maxColumnSize += 1;
			}
			else
			{
				maxRowSize = colItem.size();//can vary (horizontal size)
				maxColumnSize = std::max(vv.size(), rowItem.size()) + 1;//should be fixed (vertical size)
				for (int rowY = 1; rowY < maxColumnSize; ++rowY)
					if (rowY - 1 < vv.size())
						maxRowSize = std::max(maxRowSize, (int)vv[rowY - 1].size());
				maxRowSize += 1;
			}

			//calculate emptyColArr
			std::vector<int> emptyColArr(maxRowSize, 1);
			if (hideEmptyCol)
			{
				//1. check 1st column: rowItem
				emptyColArr[0] = 0;
				//2. check the rest columns
				for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
					for (int rowY = 1; rowY < maxColumnSize; ++rowY)
						if (columnXrowY)
						{
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								emptyColArr[colX] &= (vv[colX - 1][rowY - 1].empty() ? 1 : 0);
						}
						else
						{
							if (rowY - 1 < vv.size() && colX - 1 < vv[rowY - 1].size())
								emptyColArr[colX] &= (vv[rowY - 1][colX - 1].empty() ? 1 : 0);
						}
			}

			//calculate emptyRowArr
			std::vector<int> emptyRowArr(maxColumnSize, 1);
			if (hideEmptyRow)
			{
				//1. check 1st row: colItem
				emptyRowArr[0] = 0;
				//2. check the rest rows
				for (int rowY = 1; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
					for (int colX = 1; colX < maxRowSize; ++colX)
						if (columnXrowY)
						{
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								emptyRowArr[rowY] &= (vv[colX - 1][rowY - 1].empty() ? 1 : 0);
						}
						else
						{
							if (rowY - 1 < vv.size() && colX - 1 < vv[rowY - 1].size())
								emptyRowArr[rowY] &= vv[rowY - 1][colX - 1].empty() ? 1 : 0;
						}
			}

			//calculate colWidthArr
			std::vector<int> colWidthArr(maxRowSize, cellWidth);//the width of each column
			if (cellWidth == 0)//calculate and use non-uniform cell widths
			{
				//1. check 1st column: rowItem
				colWidthArr[0] = std::format("{}", "Row#").size();
				for (int rowY = 1; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
				{
					if (hideEmptyRow && emptyRowArr[rowY])
						continue;
					if (rowY - 1 < rowItem.size())
						colWidthArr[0] = std::max(colWidthArr[0], (int)rowItem[rowY - 1].size());
					else
						colWidthArr[0] = std::max(colWidthArr[0], (int)std::format("{}", "Row#").size() + (int)std::format("{}", rowY).size());
				}
				//2. check the rest columns
				for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
				{
					colWidthArr[colX] = 4;//cell minimum width is 4
					if (hideEmptyCol && emptyColArr[colX])
						continue;
					//1. check 1st row: colItem
					if (colX - 1 < colItem.size())
						colWidthArr[colX] = std::max(colWidthArr[colX], (int)colItem[colX - 1].size());
					else
						colWidthArr[colX] = std::max(colWidthArr[colX], (int)std::format("{}", "Col#").size() + (int)std::format("{}", colX).size());
					//2. check the rest rows of colX
					for (int rowY = 1; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
					{
						if (hideEmptyRow && emptyRowArr[rowY])
							continue;
						if (columnXrowY)
						{
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								for (int rowY2 = 0; rowY2 < vv[colX - 1][rowY - 1].size(); ++rowY2)
									colWidthArr[colX] = std::max(colWidthArr[colX], (int)vv[colX - 1][rowY - 1][rowY2].size());
						}
						else
						{
							if (rowY - 1 < vv.size() && colX - 1 < vv[rowY - 1].size())
								for (int rowY2 = 0; rowY2 < vv[rowY - 1][colX - 1].size(); ++rowY2)
									colWidthArr[colX] = std::max(colWidthArr[colX], (int)vv[rowY - 1][colX - 1][rowY2].size());
						}
					}
				}
			}

			//calculate rowHeightArr
			std::vector<int> rowHeightArr(maxColumnSize, cellHeight);
			if (cellHeight == 1)//calculate and use non-uniform cell heights
			{
				//1. check 1st row: colItem
				rowHeightArr[0] = 1;
				//2. check the rest rows
				for (int rowY = 1; rowY < maxColumnSize; ++rowY)
				{
					if (hideEmptyRow && emptyRowArr[rowY])
						continue;
					for (int colX = 1; colX < maxRowSize; ++colX)
					{
						if (hideEmptyCol && emptyColArr[colX])
							continue;
						if (columnXrowY)
						{
							if (colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								rowHeightArr[rowY] = std::max(rowHeightArr[rowY], (int)vv[colX - 1][rowY - 1].size());
						}
						else
						{
							if (rowY - 1 < vv.size() && colX - 1 < vv[rowY - 1].size())
								rowHeightArr[rowY] = std::max(rowHeightArr[rowY], (int)vv[rowY - 1][colX - 1].size());
						}
					}
				}
			}

			//print matrix
			for (int rowY = 0; rowY < maxColumnSize; ++rowY)//for each rowY (iterate vertically)
			{
				if (rowY == 0)//1. print the 1st row: colItem
				{
					oss << std::vformat("{:>" + std::format("{}", colWidthArr[0] + std::format("{}", "| ").size()) + "}", std::make_format_args("| "));
					for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
					{
						if (hideEmptyCol && emptyColArr[colX])
							continue;
						if (colX - 1 < colItem.size())
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}",
								std::make_format_args(colItem[colX - 1].substr(0, std::min((int)colItem[colX - 1].size(), colWidthArr[colX]))));
						else if (colWidthArr[colX] - std::format("{}", "Col#").size() >= std::format("{}", colX).size())
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX] - std::format("{}", colX).size()) + "}{}",
								std::make_format_args("Col#", colX));
						else
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args("Col#"));
						if (colX != maxRowSize - 1 &&
							(!hideEmptyCol || !std::accumulate(emptyColArr.cbegin() + colX + 1, emptyColArr.cend(), 1, std::bit_and<int>())))
							oss << "| ";
					}
				}
				else if (hideEmptyRow && emptyRowArr[rowY])
					continue;
				else//2. print the rest rows
				{
					for (int rowY2 = 0; rowY2 < rowHeightArr[rowY]; ++rowY2)
					{
						//1. print the 1st column: rowItem
						if (rowY2 != rowHeightArr[rowY] - 1)
						{
							oss << std::vformat("{:>" + std::format("{}", colWidthArr[0]) + "}| ", std::make_format_args(" "));
						}
						else
						{
							if (rowY - 1 < rowItem.size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[0]) + "}| ",
									std::make_format_args(rowItem[rowY - 1].substr(0, std::min((int)rowItem[rowY - 1].size(), colWidthArr[0]))));
							else if (colWidthArr[0] - std::format("{}", "Row#").size() >= std::format("{}", rowY).size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[0] - std::format("{}", rowY).size()) + "}{}| ",
									std::make_format_args("Row#", rowY));
							else
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[0]) + "}| ", std::make_format_args("Row#"));
						}
						//2. print the rest columns of rowY
						for (int colX = 1; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
						{
							if (hideEmptyCol && emptyColArr[colX])
								continue;
							int revIdx = rowHeightArr[rowY] - 1 - rowY2;
							if (columnXrowY && colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size() && revIdx < vv[colX - 1][rowY - 1].size())
							{
								int idx = vv[colX - 1][rowY - 1].size() - 1 - revIdx;
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}",
									std::make_format_args(vv[colX - 1][rowY - 1][idx].substr(0, std::min((int)vv[colX - 1][rowY - 1][idx].size(), colWidthArr[colX]))));
							}
							else if (!columnXrowY && rowY - 1 < vv.size() && colX - 1 < vv[rowY - 1].size() && revIdx < vv[rowY - 1][colX - 1].size())
							{
								int idx = vv[rowY - 1][colX - 1].size() - 1 - revIdx;
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}",
									std::make_format_args(vv[rowY - 1][colX - 1][idx].substr(0, std::min((int)vv[rowY - 1][colX - 1][idx].size(), colWidthArr[colX]))));
							}
							else if (columnXrowY && colX - 1 < vv.size() && rowY - 1 < vv[colX - 1].size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args((useNilForEmpty ? "nil" : " ")));
							else if (!columnXrowY && rowY - 1 < vv.size() && colX - 1 < vv[rowY - 1].size())
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args((useNilForEmpty ? "nil" : " ")));
							else if (rowY2 != rowHeightArr[rowY] - 1)
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args(" "));
							else
								oss << std::vformat("{:>" + std::format("{}", colWidthArr[colX]) + "}", std::make_format_args("NA"));
							if (colX != maxRowSize - 1 &&
								(!hideEmptyCol || !std::accumulate(emptyColArr.cbegin() + colX + 1, emptyColArr.cend(), 1, std::bit_and<int>())))
								oss << "| ";
						}
						if (rowY2 != rowHeightArr[rowY] - 1)
							oss << std::endl;
					}
				}
				if (rowY == 0 ||
					rowY != maxColumnSize - 1 && (!hideEmptyRow || !std::accumulate(emptyRowArr.cbegin() + rowY + 1, emptyRowArr.cend(), 1, std::bit_and<int>())))
				{
					//print horizontal line
					oss << std::endl;
					for (int colX = 0; colX < maxRowSize; ++colX)//for each colX (iterate horizontally)
					{
						if (hideEmptyCol && emptyColArr[colX])
							continue;
						if (colX == 0)
							oss << std::vformat("{:->" + std::format("{}", colWidthArr[colX] + 1) + "}", std::make_format_args("+"));
						else if (colX != maxRowSize - 1 &&
							(!hideEmptyCol || !std::accumulate(emptyColArr.cbegin() + colX + 1, emptyColArr.cend(), 1, std::bit_and<int>())))
							oss << std::vformat("{:->" + std::format("{}", colWidthArr[colX] + 2) + "}", std::make_format_args("+"));
						else
							oss << std::vformat("{:->" + std::format("{}", colWidthArr[colX] + 1) + "}", std::make_format_args("-"));
					}
				}

				oss << std::endl;
			}
			return oss.str();
		}
	};

	template<class T, class U = T>
	class ToStr1D
	{
	public:
		ToStr1D() {}
		~ToStr1D() {}
		std::string operator()(int argc, T* argv, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			for (int i = 0; i < argc; ++i)
			{
				oss << argv[i];
				if (i != argc - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const std::pair<T, U>& p)
		{
			std::ostringstream oss;
			oss << p.first << ", " << p.second;
			return oss.str();
		}
		std::string operator()(const std::vector<T>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << v[i];
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const std::vector<T>& v, int first, int last)
		{
			std::ostringstream oss;
			for (int i = first; i <= last; ++i)
			{
				oss << v[i];
				if (i != last)
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::list<T>& l)
		{
			std::ostringstream oss;
			for (typename std::list<T>::const_iterator i = l.cbegin(); i != l.cend(); ++i)
			{
				oss << *i;
				if (std::next(i) != l.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::list<std::pair<T, U>>& l)
		{
			std::ostringstream oss;
			for (typename std::list<std::pair<T, U>>::const_iterator i = l.cbegin(); i != l.cend(); ++i)
			{
				oss << "[" << i->first << "," << i->second << "]";
				if (std::next(i) != l.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(T A[], int n)
		{
			std::ostringstream oss;
			for (int i = 0; i < n; ++i)
			{
				oss << A[i];
				if (i != n - 1)
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(T A[], int first, int last)
		{
			std::ostringstream oss;
			for (int i = first; i <= last; ++i)
			{
				oss << A[i];
				if (i != last)
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::vector<T>>& vv)
		{
			std::ostringstream oss;
			for (typename std::vector<std::vector<T>>::const_iterator v = vv.cbegin(); v != vv.cend(); ++v)
			{
				oss << "[";
				for (typename std::vector<T>::const_iterator i = v->cbegin(); i != v->cend(); ++i)
				{
					oss << *i;
					if (std::next(i) != v->cend())
						oss << ",";
				}
				oss << "]";
				if (std::next(v) != vv.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<T, U>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<T, U>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[" << i->first << "," << i->second << "]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<T, U>>& v, int first, int last)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<T, U>>::const_iterator i = v.cbegin() + first; i != (v.cbegin() + last + 1); ++i)
			{
				oss << "[" << i->first << "," << i->second << "]";
				if (i != (v.cbegin() + last))
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<std::pair<T, T>, U>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<std::pair<T, T>, U>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[(" << i->first.first << "," << i->first.second << ")," << i->second << "]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<T, std::pair<U, U>>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<T, std::pair<U, U>>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[" << i->first << ",(" << i->second.first << "," << i->second.second << ")]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<std::pair<T, U>, std::pair<T, U>>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<std::pair<T, U>, std::pair<T, U>>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[(" << i->first.first << "," << i->first.second << "),(" << i->second.first << "," << i->second.second << ")]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::stack<T>& s, bool topToBottom = false)
		{
			std::stack<T> copy(s);
			if (!topToBottom)
			{
				std::stack<T> rev;
				while (!copy.empty())
					rev.push(copy.top()), copy.pop();
				rev.swap(copy);
			}
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << copy.top();
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::stack<std::pair<T, U>>& s, bool topToBottom = false)
		{
			std::stack<std::pair<T, U>> copy(s);
			if (!topToBottom)
			{
				std::stack<std::pair<T, U>> rev;
				while (!copy.empty())
					rev.push(copy.top()), copy.pop();
				rev.swap(copy);
			}
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << "[" << copy.top().first << "," << copy.top().second << "]";
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::queue<T>& q)
		{
			std::queue<T> copy(q);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << copy.front();
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::queue<std::pair<T, U>>& q)
		{
			std::queue<std::pair<T, U>> copy(q);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << "[" << copy.front().first << "," << copy.front().second << "]";
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::deque<T>& q, bool sort = false)
		{
			std::deque<T> copy(q);
			if (sort)
				std::stable_sort(copy.begin(), copy.end());
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << copy.front();
				copy.pop_front();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::deque<std::pair<T, U>>& q)
		{
			std::deque<std::pair<T, U>> copy(q);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << "[" << copy.front().first << "," << copy.front().second << "]";
				copy.pop_front();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::unordered_set<T>& s)
		{
			std::ostringstream oss;
			if (s.empty())
				return oss.str();
			for (typename std::unordered_set<T>::const_iterator i = s.cbegin(); i != s.cend(); ++i)
			{
				oss << *i;
				if (std::next(i) != s.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::set<T>& s)
		{
			std::ostringstream oss;
			if (s.empty())
				return oss.str();
			for (typename std::set<T>::const_iterator i = s.cbegin(); i != s.cend(); ++i)
			{
				oss << *i;
				if (std::next(i) != s.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::multiset<T>& s)
		{
			std::ostringstream oss;
			if (s.empty())
				return oss.str();
			for (typename std::multiset<T>::const_iterator i = s.cbegin(); i != s.cend(); ++i)
			{
				oss << *i;
				if (std::next(i) != s.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::multiset<std::pair<T, U>>& s)
		{
			std::ostringstream oss;
			if (s.empty())
				return oss.str();
			for (typename std::multiset<std::pair<T, U>>::const_iterator i = s.cbegin(); i != s.cend(); ++i)
			{
				oss << "[" << i->first << "," << i->second << "]";
				if (std::next(i) != s.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::unordered_map<T, U>& m)
		{
			std::ostringstream oss;
			if (m.empty())
				return oss.str();
			for (typename std::unordered_map<T, U>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "[" << i->first << "," << i->second << "]";
				if (std::next(i) != m.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::unordered_map<T, typename std::list<U>::iterator>& m, bool sort = false)
		{
			std::ostringstream oss;
			if (m.empty())
				return oss.str();
			if (!sort)
			{
				for (typename std::unordered_map<T, typename std::list<U>::iterator>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
				{
					oss << "[" << i->first << "," << *(i->second) << "]";
					if (std::next(i) != m.cend())
						oss << ", ";
				}
			}
			else
			{
				std::map<T, typename std::list<U>::iterator> sm;
				for (typename std::unordered_map<T, typename std::list<U>::iterator>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
					sm.insert({ i->first,i->second });
				for (typename std::map<T, typename std::list<U>::iterator>::const_iterator i = sm.cbegin(); i != sm.cend(); ++i)
				{
					oss << "[" << i->first << "," << *(i->second) << "]";
					if (std::next(i) != sm.cend())
						oss << ", ";
				}
			}
			return oss.str();
		}
		std::string operator()(const std::map<T, U>& m)
		{
			std::ostringstream oss;
			if (m.empty())
				return oss.str();
			for (typename std::map<T, U>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "[" << toStrT(i->first) << "," << toStrT(i->second) << "]";
				if (std::next(i) != m.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::priority_queue<T, std::vector<T>, std::greater<T>>& minHeap)
		{
			std::priority_queue<T, std::vector<T>, std::greater<T>> copy(minHeap);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << copy.top();
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::priority_queue<T, std::vector<T>, std::less<T>>& maxHeap)
		{
			std::priority_queue<T, std::vector<T>, std::less<T>> copy(maxHeap);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << copy.top();
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::priority_queue<std::pair<T, std::pair<U, U>>, std::vector<std::pair<T, std::pair<U, U>>>, std::greater<std::pair<T, std::pair<U, U>>>>& minHeap)
		{
			std::priority_queue<std::pair<T, std::pair<U, U>>, std::vector<std::pair<T, std::pair<U, U>>>, std::greater<std::pair<T, std::pair<U, U>>>> copy(minHeap);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << "[" << copy.top().first << ",(" << copy.top().second.first << "," << copy.top().second.second << ")]";
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::priority_queue<std::pair<T, std::pair<U, U>>, std::vector<std::pair<T, std::pair<U, U>>>, std::less<std::pair<T, std::pair<U, U>>>>& maxHeap)
		{
			std::priority_queue<std::pair<T, std::pair<U, U>>, std::vector<std::pair<T, std::pair<U, U>>>, std::less<std::pair<T, std::pair<U, U>>>> copy(maxHeap);
			std::ostringstream oss;
			while (!copy.empty())
			{
				oss << "[" << copy.top().first << ",(" << copy.top().second.first << "," << copy.top().second.second << ")]";
				copy.pop();
				if (!copy.empty())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<T>& v, const EnumNameVec& toEnumName, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				if ((int)v[i] >= 0 && (int)v[i] < (int)toEnumName.size())
					oss << toEnumName[(int)v[i]];
				else
					oss << "";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const std::vector<T>& v, const EnumNameMap& toEnumName, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				if (toEnumName.count((int)v[i]))
					oss << toEnumName.find((int)v[i])->second;
				else
					oss << "";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
#if defined(QT_VERSION)
		std::string operator()(const QVector<T>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << toStrT(v[i]);
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QVector<QPair<QPair<T, T>, U>>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << "[(" << toStrT(v[i].first.first) << "," << toStrT(v[i].first.second) << ")," << toStrT(v[i].second) << "]";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QVector<std::pair<T,T>>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << "[" << toStrT(v[i].first) << "," << toStrT(v[i].second) << "]";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QVector<T>& v, const EnumNameVec& toEnumName, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				if ((int)v[i] >= 0 && (int)v[i] < (int)toEnumName.size())
					oss << toEnumName[(int)v[i]];
				else
					oss << "";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QVector<T>& v, const EnumNameMap& toEnumName, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				if (toEnumName.count((int)v[i]))
					oss << toEnumName.find((int)v[i])->second;
				else
					oss << "";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QList<T>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << toStrT(v[i]);
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QList<T>& v, const std::function<std::string(const T&)> & f, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << f(v[i]);
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QSet<T>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			for (auto itr = v.constBegin(); itr != v.constEnd(); ++itr)
			{
				oss << toStrT(*itr);
				if (std::next(itr) != v.constEnd())
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		//usage: Debug::ToStr1D<int>().template operator()<1>(QMap<int,int>());
		template<int WhichBits = 3>
		std::string operator()(const QMap<T, U>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			for (auto itr = v.constBegin(); itr != v.constEnd(); ++itr)
			{
				oss << "[";
				if constexpr (WhichBits & 1) oss << toStrT(itr.key());
				oss << ",";
				if constexpr ((WhichBits >> 1) & 1) oss << toStrT(itr.value());
				oss << "]";
				if (std::next(itr) != v.constEnd())
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}

		//no dependencies to T and U ...
		std::string operator()(const QStringList& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			int i = 0;
			for (const auto& str : v)
			{
				oss << str.toStdString();
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
				++i;
			}
			return oss.str();
		}
		std::string operator()(const QRect& rec)
		{
			std::ostringstream oss;
			oss << "[left:" << rec.left() << ", right:" << rec.right() << ", top:" << rec.top() << ", bot:" << rec.bottom() << "]";
			return oss.str();
		}
#endif //QT_VERSION

	private:
		template<typename V>
		std::string toBinaryString(const V& number)
		{
			std::bitset<sizeof(V) * 8> bits(number);
			return bits.to_string();
		}
		template<typename V>
		std::string toHexString(const V& number)
		{
			std::ostringstream oss;
			oss << std::hex << std::showbase << number;
			return oss.str();
		}
	public:
		// Overloads for binary representation
		std::string operator()(const int& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const unsigned int& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const short& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const unsigned short& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const long& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const unsigned long& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const long long& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const unsigned long long& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const char& number)
		{
			return toBinaryString(static_cast<unsigned char>(number));
		}
		std::string operator()(const unsigned char& number)
		{
			return toBinaryString(number);
		}
		std::string operator()(const float& number)
		{
			uint32_t intRep;
			std::memcpy(&intRep, &number, sizeof(float));
			return toBinaryString(intRep);
		}
		std::string operator()(const double& number)
		{
			uint64_t intRep;
			std::memcpy(&intRep, &number, sizeof(double));
			return toBinaryString(intRep);
		}
		// Overloads for hexadecimal representation
		std::string toHex(const int& number)
		{
			return toHexString(number);
		}
		std::string toHex(const unsigned int& number)
		{
			return toHexString(number);
		}
		std::string toHex(const short& number)
		{
			return toHexString(number);
		}
		std::string toHex(const unsigned short& number)
		{
			return toHexString(number);
		}
		std::string toHex(const long& number)
		{
			return toHexString(number);
		}
		std::string toHex(const unsigned long& number)
		{
			return toHexString(number);
		}
		std::string toHex(const long long& number)
		{
			return toHexString(number);
		}
		std::string toHex(const unsigned long long& number)
		{
			return toHexString(number);
		}
		std::string toHex(const char& number)
		{
			return toHexString(static_cast<unsigned char>(number));
		}
		std::string toHex(const unsigned char& number)
		{
			return toHexString(number);
		}
		std::string toHex(const float& number)
		{
			uint32_t intRep;
			std::memcpy(&intRep, &number, sizeof(float));
			return toHexString(intRep);
		}
		std::string toHex(const double& number)
		{
			uint64_t intRep;
			std::memcpy(&intRep, &number, sizeof(double));
			return toHexString(intRep);
		}

	private:
		template<typename V>
		std::string toSetBitStringConcat(const V& number, const std::function<std::string(const V&)>& getSetBitString)
		{
			std::vector<std::string> res;
			unsigned int digit = 0;
			V cur = number;
			while (cur)
			{
				if (cur & 1u)
				{
					V num = (1 << digit);
					res.push_back(getSetBitString(num));
				}
				cur >>= 1;
				++digit;
			}
			std::ostringstream oss;
			for (int i = res.size() - 1; i >= 0; --i)
			{
				oss << res[i];
				if (i != 0)
					oss << "|";
			}
			return oss.str();
		}
	public:
		// Overloads for toSetBitStringConcat
		std::string operator()(const unsigned int& number, const std::function<std::string(const unsigned int&)>& getSetBitString)
		{
			return toSetBitStringConcat(number, getSetBitString);
		}
		std::string operator()(const int& number, const std::function<std::string(const int&)>& getSetBitString)
		{
			return toSetBitStringConcat(number, getSetBitString);
		}
		std::string operator()(const unsigned long& number, const std::function<std::string(const unsigned long&)>& getSetBitString)
		{
			return toSetBitStringConcat(number, getSetBitString);
		}
		std::string operator()(const long& number, const std::function<std::string(const long&)>& getSetBitString)
		{
			return toSetBitStringConcat(number, getSetBitString);
		}
		std::string operator()(const unsigned long long& number, const std::function<std::string(const unsigned long long&)>& getSetBitString)
		{
			return toSetBitStringConcat(number, getSetBitString);
		}
		std::string operator()(const long long& number, const std::function<std::string(const long long&)>& getSetBitString)
		{
			return toSetBitStringConcat(number, getSetBitString);
		}

	};
#if defined(QT_VERSION)
	template<>
	class ToStr1D<QMenuBar*>
	{
		static std::string toStr(QAction* act, int level)
		{
			const std::string indent(level * 2, ' ');
			std::ostringstream oss;
			if (act->isSeparator())
				oss << indent << "----";
			else
			{
				oss << indent << act->text().toStdString();
				if (!act->shortcut().isEmpty())
					oss << ", " << act->shortcut().toString(QKeySequence::NativeText).toStdString();
				for (auto& i : act->shortcuts())
				{
					if (!i.isEmpty())
						oss << ", " << i.toString(QKeySequence::NativeText).toStdString();
				}
			}
			return oss.str();
		}
		static void visitMenuRecur(QMenu* menu, int level, std::ostringstream& oss)
		{
			for (QAction* act : menu->actions())
			{
				oss << toStr(act, level + 1) << std::endl;
				if (!act->isSeparator())
				{
					if (QMenu* subMenu = act->menu())
						visitMenuRecur(subMenu, level + 1, oss);
				}
			}
		}
	public:
		std::string operator()(QMenuBar* mbar)
		{
			std::ostringstream oss;
			int level = 0;
			for (QAction* act : mbar->actions())
			{
				oss << toStr(act, level) << std::endl;
				if (!act->isSeparator())
				{
					if (QMenu* subMenu = act->menu())
						visitMenuRecur(subMenu, level + 1, oss);
				}
			}
			return oss.str();
		}
	};
	class QtUtil
	{
	public:
		static QRect mapToGlobalRect(QWidget* cur)
		{
			return QRect(cur->mapToGlobal(QPoint(0, 0)), cur->size());
		}
		static QRect mapToParentRect(QWidget* cur, QWidget* parent)
		{
			return QRect(cur->mapTo(parent, QPoint(0, 0)), cur->size());
		}
	private:
		// Since C++17, both "namespace-scope class inline static data member" and "namespace-scope inline variable" declared in header included by multiple TUs
		// have external linkage, i.e., every source file that includes this header will see its own definition, but ODR guarantees they all refer to the same object.
		// However, "namespace-scope inline static variable" declared in header included by multiple TUs have internal linkage.
		// Pre-C++17 work-around for external linkage:
		// 1. declare "extern variable" in header and define variable in source file.
		// 2. declare "inline function returning reference to local static variable" in header.
		inline static QString s_logFileName = QString();
		static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
		{
			QFile out(s_logFileName);
			if (out.open(QIODevice::Append | QIODevice::Text))
			{
				QTextStream ts(&out);
				ts.setCodec(QTextCodec::codecForName("UTF-8"));

				// simple timestamp + type header
				const char* typeStr = nullptr;
				switch (type) {
				case QtDebugMsg:    typeStr = "DEBUG";    break;
				case QtInfoMsg:     typeStr = "INFO";     break;
				case QtWarningMsg:  typeStr = "WARNING";  break;
				case QtCriticalMsg: typeStr = "CRITICAL"; break;
				case QtFatalMsg:    typeStr = "FATAL";    break;
				}

				ts << QDateTime::currentDateTime().toString(Qt::ISODate)
					<< " [" << typeStr << "] "
					<< msg
					<< "\n";
				ts.flush();
			}

			// keep Qt’s default behavior on fatal messages
			if (type == QtFatalMsg)
				abort();
		}
	public:
		static void redirectQDebug_(const QString& fileName)
		{
			if (fileName.isEmpty())
			{
				qInstallMessageHandler(nullptr);
			}
			else if (fileName != s_logFileName)
			{
				s_logFileName = fileName;
				qInstallMessageHandler(messageHandler);
			}
		}
		static void redirectQDebug(const std::string& fileName)
		{
			redirectQDebug_(QString::fromStdString(fileName));
		}
	};
#endif
	template<class T, class U, class V, class W = V>
	class ToStr1D_
	{
	public:
		ToStr1D_() {}
		~ToStr1D_() {}
		std::string operator()(const std::vector<std::pair<std::pair<T, U>, V>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<std::pair<T, U>, V>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[(" << i->first.first << "," << i->first.second << ")," << i->second << "]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<T, std::pair<U, V>>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<T, std::pair<U, V>>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[" << i->first << ",(" << i->second.first << "," << i->second.second << ")]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
		std::string operator()(const std::vector<std::pair<std::pair<T, U>, std::pair<V, W>>>& v)
		{
			std::ostringstream oss;
			for (typename std::vector<std::pair<std::pair<T, U>, std::pair<V, W>>>::const_iterator i = v.cbegin(); i != v.cend(); ++i)
			{
				oss << "[(" << i->first.first << "," << i->first.second << "),(" << i->second.first << "," << i->second.second << ")]";
				if (std::next(i) != v.cend())
					oss << ", ";
			}
			return oss.str();
		}
	};
}

#if __cplusplus < 201703L
namespace std
{
	int gcd(int a, int b)
	{
		while (b)
		{
			int tmp = b;
			b = a % b;
			a = tmp;
		}
		return a;
	}

}
#endif
#endif //#ifdef __cplusplus

#endif
