#ifndef DEBUG_H
#define DEBUG_H

#pragma warning (disable : 4996) //fopen
#include <stdio.h>
#define DEBUG_MDUMP(filename, mode, str) \
    do { \
        FILE *file = fopen(filename, mode); \
        if (file == NULL) { \
            perror("Error opening file"); \
        } else { \
            fprintf(file, "%s\n", str); \
            fclose(file); \
        } \
    } while(0)

#define DEBUG_MDUMPF(filename, mode, ...) \
    do { \
        FILE *file = fopen(filename, mode); \
        if (file == NULL) { \
            perror("Error opening file"); \
        } else { \
            fprintf(file, __VA_ARGS__); \
            fclose(file); \
        } \
    } while(0)

#define DEBUG_ADUMP(filename, str) DEBUG_MDUMP(filename, "a", str)
#define DEBUG_ADUMPF(filename, ...) DEBUG_MDUMPF(filename, "a", __VA_ARGS__)
#define DEBUG_WDUMP(filename, str) DEBUG_MDUMP(filename, "w", str)
#define DEBUG_WDUMPF(filename, ...) DEBUG_MDUMPF(filename, "w", __VA_ARGS__)

#define DEBUG_READ(filename, buf, bufSize) \
    do{ \
        FILE *file = fopen(filename, "r"); \
        if (file == NULL) { \
            perror("Error opening file"); \
        } else { \
            if (fgets(buf, bufSize, file) != NULL) { \
                size_t readLen = strlen(buf); \
                if (readLen > 0 && buf[readLen-1] == '\n') {\
                    buf[readLen-1] = '\0'; \
                } \
            } \
            else { \
                perror("Error reading from file"); \
            } \
            fclose(file); \
        } \
    }while(0)

#define DEBUG_READ_BUF_SIZE 1024
#define DEBUG_READ_BUF(filename) \
    char DEBUG_READ_BUF_[DEBUG_READ_BUF_SIZE] = ""; \
    DEBUG_READ(filename, DEBUG_READ_BUF_, DEBUG_READ_BUF_SIZE)

#ifdef __cplusplus
#include <iostream>
#include <sstream>
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
#if defined(QT_VERSION)
#include <QString>
#include <QVector>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QWidget>
#endif
#define stringify(name)#name
namespace Debug
{
	typedef std::map<int, const char*> EnumNameMap;
	typedef std::vector<const char*> EnumNameVec;
	enum class Splitter
	{
		Comma = 0,
		NewLine = 1,
	};
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
	};

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

	template<class T, class U = T>
	class ToStr1D
	{
	public:
		ToStr1D() {}
		~ToStr1D() {}
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
		std::string operator()(const std::deque<T>& q)
		{
			std::deque<T> copy(q);
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
		std::string operator()(const std::map<T, U>& m)
		{
			std::ostringstream oss;
			if (m.empty())
				return oss.str();
			for (typename std::map<T, U>::const_iterator i = m.cbegin(); i != m.cend(); ++i)
			{
				oss << "[" << i->first << "," << i->second << "]";
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
				oss << v[i];
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
				oss << v[i];
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
#endif
	};
#if defined(QT_VERSION)
	template<>
	class ToStr1D<QString>
	{
	public:
		ToStr1D() {}
		~ToStr1D() {}
		std::string operator()(const QVector<QString>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << v[i].toStdString();
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QVector<QPair<QPair<int, int>, QString>>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << "[(" << v[i].first.first << "," << v[i].first.second << ")," << v[i].second.toStdString() << "]";
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
		std::string operator()(const QList<QString>& v, Splitter s = Splitter::Comma)
		{
			std::ostringstream oss;
			int N = v.size();
			for (int i = 0; i < N; ++i)
			{
				oss << v[i].toStdString();
				if (i != N - 1)
					s == Splitter::Comma ? (oss << ", ") : (oss << std::endl);
			}
			return oss.str();
		}
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
