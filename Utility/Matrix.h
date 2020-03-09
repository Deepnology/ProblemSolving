#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <sstream>
#include <boost/function.hpp>
#include <string>
#include <map>


template <class T>
class matrix 
{
public:
	//1D: rows = 1
	matrix(unsigned int columns) : m_columns(columns), m_data(columns * 1) 
	{
		if (columns == 0)
		{
			std::cout << "***** Columns should be equal to or greater than one !! *****" << std::endl;
			throw;
		}
	}//1D

	/*basic member functions to implement a 2D matrix by vector*/
	matrix(unsigned int rows, unsigned int columns) : m_columns(columns), m_data(columns * rows) 
	{
		if (rows == 0 || columns == 0)
		{
			std::cout << "***** Rows and columns should be equal to or greater than one !! *****" << std::endl;
			throw;
		}
	}
	T & operator()(unsigned int row, unsigned int column)
	{
		if (row * m_columns + column >= m_data.size())
			std::cout << "******* Matrix Index Out Of Bound: (" << row << "," << column << ") out of ([0-" << m_data.size()/m_columns - 1 << "],[0-" << m_columns - 1 << "]) *******" << std::endl;
		return m_data[row * m_columns + column];
	}

	/*more member functions*/
	unsigned int get_columns() const
	{
		return m_columns;
	}
	unsigned int get_rows() const
	{
		return m_data.size() / m_columns;
	}
	unsigned int resize_new_rows(unsigned int row_number)//return last row index
	{
		unsigned int old_row_number = m_data.size() / m_columns;//old_row_number should be at least one!!
		m_data.resize((old_row_number + row_number) * m_columns);
		return old_row_number + row_number - 1;
	}
	void update_row(unsigned int row_index, const std::vector<T> & row)
	{
		if ((row_index + 1) - this->get_rows() > 0)
			this->reserve_new_rows((row_index + 1) - this->get_rows());
		for (unsigned int i = 0; i < m_columns; ++i)
		{
			m_data[row_index * m_columns + i] = row[i];
		}
	}
	unsigned int update_last_row(const std::vector<T> & row)//return last row index
	{
		unsigned int last_row_index = this->get_rows() - 1;
		for (unsigned int i = 0; i < m_columns; ++i)
		{
			m_data[last_row_index * m_columns + i] = row[i];
		}
		return last_row_index;
	}
	unsigned int append_new_row(const std::vector<T> & row)//return last row index
	{
		unsigned int new_row_index = this->resize_new_rows(1);
		for (unsigned int i = 0; i < m_columns; ++i)
		{
			m_data[new_row_index * m_columns + i] = row[i];
		}
		return new_row_index;
	}
	void swap(matrix<T> & m)
	{
		unsigned int tmp_columns = m_columns;
		m_columns = m.m_columns;
		m.m_columns = tmp_columns;
		m_data.swap(m.m_data);
	}
	void reserve_rows(unsigned int row)//reserve the capacity of m_data. the size is unchanged.
	{
		m_data.reserve(row * m_columns);
	}
	std::vector<std::map<std::string,std::string> > for_each_row(
		const boost::function<std::map<std::string,std::string>(std::vector<T> & row,unsigned int row_begin_index,unsigned int row_end_index,unsigned int index_increment,std::map<std::string,std::string> & args)> f//passed by value
		, std::map<std::string,std::string> & args//passed by ref
		)
	{
		std::vector<std::map<std::string,std::string> > r_vec;
		for (unsigned int i = 0; i < this->get_rows(); ++i)
		{
			std::map<std::string,std::string> result = f(m_data, i*m_columns, i*m_columns+(m_columns-1), 1, args);//f(vector, row_begin_index, row_end_index)
			r_vec.push_back(result);
		}
		return r_vec;
	}
	std::vector<std::map<std::string,std::string> > for_each_column(
		const boost::function<std::map<std::string,std::string>(std::vector<T> & column,unsigned int row_begin_index,unsigned int row_end_index,unsigned int index_increment,std::map<std::string,std::string> & args)> f//passed by value
		, std::map<std::string,std::string> & args//passed by ref
		)
	{
		std::vector<std::map<std::string,std::string> > r_vec;
		for (unsigned int i = 0; i < this->get_columns(); ++i)
		{
			std::map<std::string,std::string> result = f(m_data, i, i+(this->get_rows()-1)*m_columns, m_columns, args);//f(vector, row_begin_index, row_end_index)
			r_vec.push_back(result);
		}
		return r_vec;
	}
	void print()
	{
		std::ostringstream oss;
		unsigned int currentRow = 0;
		unsigned int currentColumn = 0;
		for (std::vector<T>::iterator i = m_data.begin(); i != m_data.end(); ++i)
		{
			if (currentColumn == 0)//1st element in a row
				oss << "Row_#" << currentRow << "	= ";
			oss << *i;
			
			if (currentColumn != m_columns - 1)
			{
				oss << ", ";
				++currentColumn;
			}
			else//last element in a row
			{
				if (i != m_data.end() - 1)
				{
					oss << "\n";
					currentColumn = 0;
					++currentRow;
				}
			}
		}
		std::cout << oss.str() << std::endl;
		std::cout << currentRow << " " << currentColumn << std::endl;
	}
private:
	unsigned int m_columns;//length of 1D row
	std::vector<T> m_data;
};

/*
sample code:
std::map<std::string,std::string> f_row(std::vector<unsigned int> & row, unsigned int beginIndex, unsigned int endIndex, unsigned int indexIncrement, std::map<std::string,std::string> & args)
{
	std::map<std::string,std::string> r;
	for (unsigned int i = beginIndex; i <= endIndex; i += indexIncrement)
	{
		//perform row element operation with args on row[i]
	}
	return r;
}
matrix<unsigned int> table(1);
boost::function<std::map<std::string,std::string>(std::vector<unsigned int> &,unsigned int,unsigned int,unsigned int,std::map<std::string,std::string>)> f = boost::bind<std::map<std::string,std::string> >(f_row,_1,_2,_3,_4,_5);
std::map<std::string,std::string> args;
std::vector<std::map<std::string,std::string> > r = table.for_each_row(f,args);
*/


template<class T, unsigned int size>
class matrix3 
{
private:
    T data[size][size][size];
    friend class proxy;
    friend class proxy2;

    class proxy
	{
    public:
        proxy(matrix3 &m, unsigned int i1, unsigned int i2) 
            : m_(m), index1_(i1), index2_(i2) 
        {}
        T &operator[](unsigned int index3)
		{ 
            return m_.data[index1_][index2_][index3];
        }
	private:
        matrix3 &m_;
        unsigned int index1_, index2_;
    };

    class proxy2 
	{
    public:
        proxy2(matrix3 &m, unsigned int d) : m_(m), index_(d) { }
        proxy operator[](unsigned int index2) 
		{ 
            return proxy(m_, index_, index2);
        }
	private:
        matrix3 &m_;
        unsigned int index_;
    };

public:
    proxy2 operator[](unsigned int index) 
	{
        return proxy2(*this, index);
    }
};


/*
multidimensional vector array proxy class
http://stackoverflow.com/questions/2216017/dynamical-two-dimension-array-according-to-input
*/

#endif