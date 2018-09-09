#ifndef _STRING_H
#define _STRING_H
#include <iostream>

/*
https://users.cs.fiu.edu/~weiss/dsaa_c++/code/mystring.h
https://users.cs.fiu.edu/~weiss/dsaa_c++/code/string.cpp

 */
class StringIndexOutOfBounds { };

class String
{
public:
    String( const char *cstring = "" );               // Constructor
    String( const String & str );                     // Copy constructor
    ~String( )                                        // Destructor
    { delete [ ] buffer; }

    const String & operator= ( const String & rhs );  // Copy
    const String & operator+=( const String & rhs );  // Append

    const char *c_str( ) const        // Return C-style string
    { return buffer; }
    int length( ) const               // Return string length
    { return strLength; }

    char   operator[]( int k ) const; // Accessor operator[]
    char & operator[]( int k );       // Mutator  operator[]

    enum { MAX_LENGTH = 1024 };  // Maximum length for input string

private:
    char *buffer;                  // storage for characters
    int strLength;                 // length of string (# of characters)
    int bufferLength;              // capacity of buffer
};

std::ostream & operator<<( std::ostream & out, const String & str );    // Output
std::istream & operator>>( std::istream & in, String & str );           // Input
std::istream & getline( std::istream & in, String & str );              // Read line

bool operator==( const String & lhs, const String & rhs );    // Compare ==
bool operator!=( const String & lhs, const String & rhs );    // Compare !=
bool operator< ( const String & lhs, const String & rhs );    // Compare <
bool operator<=( const String & lhs, const String & rhs );    // Compare <=
bool operator> ( const String & lhs, const String & rhs );    // Compare >
bool operator>=( const String & lhs, const String & rhs );    // Compare >=


String::String( const char * cstring )
{
    if( cstring == NULL )
        cstring = "";
    strLength = strlen( cstring );
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    strcpy( buffer, cstring );
}

String::String( const String & str )
{
    strLength = str.length( );
    bufferLength = strLength + 1;
    buffer = new char[ bufferLength ];
    strcpy( buffer,str.buffer );
}

const String & String::operator=( const String & rhs )
{
    if( this != &rhs )
    {
        if( bufferLength < rhs.length( ) + 1 )
        {
            delete [ ] buffer;
            bufferLength = rhs.length( ) + 1;
            buffer = new char[ bufferLength ];
        }
        strLength = rhs.length( );
        strcpy( buffer, rhs.buffer );
    }
    return *this;
}

const String & String::operator+=( const String & rhs )
{
    if( this == &rhs )
    {
        String copy( rhs );
        return *this += copy;
    }

    int newLength = length( ) + rhs.length( );
    if( newLength >= bufferLength )
    {
        bufferLength = 2 * ( newLength + 1 );

        char *oldBuffer = buffer;
        buffer = new char[ bufferLength ];
        strcpy( buffer, oldBuffer );
        delete [ ] oldBuffer;
    }

    strcpy( buffer + length( ), rhs.buffer );
    strLength = newLength;
    return *this;
}

char & String::operator[ ]( int k )
{
    if( k < 0 || k >= strLength )
        throw StringIndexOutOfBounds( );
    return buffer[ k ];
}

char String::operator[ ]( int k ) const
{
    if( k < 0 || k >= strLength )
        throw StringIndexOutOfBounds( );
    return buffer[ k ];
}

std::ostream & operator<<( std::ostream & out, const String & str )
{
    return out << str.c_str();
}

std::istream & operator>>( std::istream & in, String & str )
{
    char buf[ String::MAX_LENGTH + 1 ];
    in >> buf;
    if( !in.fail( ) )
        str = buf;
    return in;
}

std::istream & getline( std::istream & in, String & str )
{
    char buf[ String::MAX_LENGTH + 1 ];
    in.getline( buf, String::MAX_LENGTH );
    if( !in.fail( ) )
        str = buf;
    return in;
}

bool operator==( const String & lhs, const String & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) == 0;
}

bool operator!=( const String & lhs, const String & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) != 0;
}

bool operator<( const String & lhs, const String & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) < 0;
}

bool operator<=( const String & lhs, const String & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) <= 0;
}

bool operator>( const String & lhs, const String & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) > 0;
}

bool operator>=( const String & lhs, const String & rhs )
{
    return strcmp( lhs.c_str( ), rhs.c_str( ) ) >= 0;
}
#endif
