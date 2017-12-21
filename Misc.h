#ifndef _MISC_H
#define _MISC_H

struct Misc
{
	static double clamp ( double a, double min, double max ) 
	{
	   a = fsel( a - min , a, min );
	   return fsel( a - max, max, a );
	}
private:
	static double fsel( double a, double b, double c ) 
	{
	  return a >= 0 ? b : c; 
	}
};


#endif