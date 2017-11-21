/*!
  \file matvec.hpp
  \brief This file contains 3 vector and 2 matrix class definitions
  The vector classes are vec2, vec3 & vec4. The matrix classes are mat33 & mat44.

  All standard arithmetic operations are defined. '*' is used for the dot product of two vectors
  and two matrices. '^' is used for the cross product of two vectors. 
  
  Additional functions include length(), normalize(), homogenize for vectors, and print(), set(),
  map() for all classes.

  There are the transpose() & inverse for matrices, but note that they do not actually change the 
  matrix. 

  When multiplied with a matrix, a vector is treated as a row vector if it precedes the matrix (v*M),
  and as a column vector if it follows the matrix (M*v).

  Matrices are stored in row-major form.

  A vector of one dimension (2d, 3d, or 4d) can be cast to a vector of a higher or lower dimension.
  If casting to a higher dimension, the new component is set by default to 1.0, unless a value is
  specified:
     vec3 a(1.0, 2.0, 3.0 );
     vec4 b( a, 4.0 );       // now b == {1.0, 2.0, 3.0, 4.0};
  When casting to a lower dimension, the vector is homogenized in the lower dimension.  
  E.g., if a 4d {X,Y,Z,W} is cast to 3d, the resulting vector is {X/W, Y/W, Z/W}.
  It is up to the user to ensure the fourth component is not zero before casting.

  Authors: Jean-Francois Doue (Graphics Gems IV), Paul Rademacher
  Revised: Parag Chaudhuri
*/

#ifndef _MATVEC_HPP_
#define _MATVEC_HPP_

#include <cstdio>
#include <string>

//@{
//! Define PI if not present
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//@}

//@{
//! Define 2*PI if not present
#ifndef M_2_PI
#define M_2_PI 6.28318530717958647692
#endif
//@}

//@{
//! Min macro
#ifndef MIN
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#endif
//@}
//@{
//! Max macro
#ifndef MAX
#define MAX(A,B) ((A) > (B) ? (A) : (B))
#endif
//@}

//@{
//! Degrees to radians conversion macro
#ifndef DEG2RAD
#define DEG2RAD(x) ((x)/180.0*M_PI)
#endif
//@}

//@{
//! Radians to degrees macro
#ifndef RAD2DEG
#define RAD2DEG(x) ((x)/M_PI*180.0)
#endif
//@}

//@{
//! Clamp a vlue between bounds macro
#ifndef CLAMP
#define CLAMP(x,lo,hi)  {if ((x) < (lo)) {(x)=(lo);} else if((x) > (hi)) {(x)=(hi);}}
#endif
//@}

namespace util
{
  //! The namespace containing all the math classes in libUtil
  namespace math
  {

    //! The X,Y,Z,W coordinates    
    enum {X,Y,Z,W};

    //! This is used for comparison amongst floating pt. values
    const double EPSILON = 1e-6;
    
    class vec2;
    class vec3;
    class vec4;
    class mat33;
    class mat44;

    /*!
      \class vec2
      \brief This is a general 2D vector class
    */
    class vec2
    {
    protected:
      //!The two data components of the vector
      double data[2];

    public:
      //@{
      //! Constructor
      vec2();
      vec2(const double x, const double y);
      vec2(const double d);
      vec2(const double v[2]);
      vec2(const vec2& v);
      //@}

      //! Downcasting from a 3D vector to 2D
      vec2(const vec3& v);

      //! Downcasting from a 3D vector to 2D, dropping the `dropAxis' component
      vec2(const vec3& v, int dropAxis);
      
      //! Destructor
      ~vec2();

      //@{
      //! Overloaded assignment operators
      vec2& operator = (const vec2& v); 
      vec2& operator += (const vec2& v); 
      vec2& operator -= (const vec2& v); 
      vec2& operator *= (const double d); 
      vec2& operator /= (const double d); 
      //@}

      //! Overloaded indexing operator
      double& operator [] (int index);

      //! Overloaded indexing operator
      double operator [] (int index) const;

      //! Returns length of the vector
      double length(void) const;
      
      //! Returns squared length of the vector
      double length2(void) const;

      //! Normalizes the vector
      vec2& normalize(void);

      //! Maps the function to every component of the vector
      vec2& map( double (*fn)(double) );

      //! Sets the value of the vector
      void set(double x, double y); 

      //! Prints the vector into a file
      void print(FILE *file, std::string name);


      //! Overloaded unary negation
      friend vec2 operator - (const vec2& v); 

      //! Overloaded addition
      friend vec2 operator + (const vec2& v1, const vec2& v2); 

      //! Overloaded subtraction
      friend vec2 operator - (const vec2& v1, const vec2& v2); 

      //! Overloaded multiplication (vector & constant)
      friend vec2 operator * (const vec2& v, const double d);

      //! Overloaded multiplication (constant & vector)
      friend vec2 operator * (const double d, const vec2& v);

      //! Overloaded multiplication (dot product)
      friend double operator * (const vec2& v1, const vec2& v2);

      //! Oveloaded division (vector & constant)
      friend vec2 operator / (const vec2& v, const double d);	

      //! Vector cross product
      friend vec3 operator ^ (const vec2& v1, const vec2& v2);

      //! Vector equality
      friend bool operator == (const vec2& v1, const vec2& v2);

      //! Vector inequality
      friend bool operator != (const vec2& v1, const vec2& v2);


      //! Swap vectors v1 and v2
      friend void swap(vec2& v1, vec2& v2);

      //! Minimum of vectors v1 & v2
      friend vec2 min(const vec2& v1, const vec2& v2);	

      //! Maximum of vectors v1 & v2
      friend vec2 max(const vec2& v1, const vec2& v2);	

      //! Term by term product
      friend vec2 prod(const vec2& v1, const vec2& v2);


      //! Friend class
      friend class vec3;
    };

    //-----------------------------------------------------------------------------
    /*!
      \class vec3
      \brief This is a general 3D vector class
    */
    class vec3
    {
    protected:
      double data[3];
      
    public:
      //@{
      //! Constructor
      vec3();
      vec3(const double x, const double y, const double z);
      vec3(const double d);
      vec3(const double v[3]);
      vec3(const vec3& v);
      //@}

      //@{
      //! Casting from a 2D vector to 3D
      vec3(const vec2& v);
      vec3(const vec2& v, double d);
      //@}

      //! Downcasting from a 4D vector to 3D
      vec3(const vec4& v);

      //! Downcasting from a 4D vector to 3D, dropping the `dropAxis' component
      vec3(const vec4& v, int dropAxis);

      //! Destructor
      ~vec3();

      //@{
      //! Overloaded assignment operators
      vec3& operator = (const vec3& v); 
      vec3& operator += (const vec3& v); 
      vec3& operator -= (const vec3& v); 
      vec3& operator *= (const double d); 
      vec3& operator /= (const double d); 
      //@}

      //! Overloaded indexing operator
      double& operator [] (int index);

      //! Overloaded indexing operator
      double operator [] (int index) const;

      //! Returns length of the vector
      double length(void) const;

      //! Returns squared length of the vector
      double length2(void) const;

      //! Normalizes the vector
      vec3& normalize(void);

      //! Homogenizes the vector
      vec3& homogenize(void);

      //! Maps the function to every component of the vector
      vec3& map( double (*fn)(double) );

      //! Sets the value of the vector
      void  set(double x, double y, double z); 

      //! Print the vector to a file
      void  print(FILE *file, std::string name);      


      //! Overloaded unary negation
      friend vec3 operator - (const vec3& v); 

      //! Overloaded addition
      friend vec3 operator + (const vec3& v1, const vec3& v2); 

      //! Overloaded subtraction
      friend vec3 operator - (const vec3& v1, const vec3& v2); 

      //! Overloaded multiplication (vector & constant)
      friend vec3 operator * (const vec3& v1, const double d);

      //! Overloaded multiplication (constant & vector)
      friend vec3 operator * (const double d, const vec3& v1);

      //! Overloaded multiplication (vector & matrix)
      friend vec3 operator * (const vec3& v, mat33& M);

      //! Overloaded multiplication (matrix & vector)
      friend vec3 operator * (mat33& M, const vec3& v);

      //! Overloaded multiplication (dot product)
      friend double operator * (const vec3& v1, const vec3& v2);

      //! Oveloaded division (vector & constant)
      friend vec3 operator / (const vec3& v, const double d);	

      //! Vector cross product
      friend vec3 operator ^ (const vec3& v1, const vec3& v2);

      //! Vector equality
      friend bool operator == (const vec3& v1, const vec3& v2);

      //! Vector inequality
      friend bool operator != (const vec3& v1, const vec3& v2);


      //! Swap vectors v1 and v2
      friend void swap(vec3& v1, vec3& v2);

      //! Minimum of vectors v1 & v2
      friend vec3 min(const vec3& v1, const vec3& v2);	

      //! Maximum of vectors v1 & v2
      friend vec3 max(const vec3& v1, const vec3& v2);	

      //! Term by term product
      friend vec3 prod(const vec3& v1, const vec3& v2);


      //@{
      //! Friend classes
      friend class vec2;
      friend class vec4;
      friend class mat33;
      //@}
    };

    //-----------------------------------------------------------------------------
    /*!
      \class vec4
      \brief This is a general 4D vector class
    */
    class vec4
    {
    protected:
      double data[4];

    public: 
      //@{
      //! Constructor
      vec4();
      vec4(const double x, const double y, const double z, const double w);
      vec4(const double d);
      vec4(const double v[4]);
      vec4(const vec4& v);
      //@}

      //@{
      //! Casting from a 3D vector to 4D
      vec4(const vec3& v);
      vec4(const vec3& v, double d);
      //@}

      //! Destructor
      ~vec4();

      //@{
      //! Overloaded assignment operators
      vec4& operator = (const vec4& v); 
      vec4& operator += (const vec4& v); 
      vec4& operator -= (const vec4& v); 
      vec4& operator *= (const double v); 
      vec4& operator /= (const double v); 
      //@}

      //! Overloaded indexing operator
      double& operator [] (int index);

      //! Overloaded indexing operator
      double operator [] (int index) const;

      //! Returns length of the vector
      double length(void) const;

      //! Returns squared length of the vector
      double length2(void) const;

      //! Normalizes the vector
      vec4& normalize(void);

      //! Homogenizes the vector
      vec4& homogenize(void);

      //! Maps the function to every component of the vector
      vec4& map( double (*fn)(double) );

      //! Sets the value of the vector
      void  set(double x, double y, double z, double w); 

      //! Print the vector to a file
      void  print(FILE *file, std::string name); 

      //! Returns a vector orthographic to the given vector
      vec4 get_ortho(void) const;

      //! Returns a orthographic bases including the given vector
      void get_ortho_frame(vec4& v1, vec4& v2);


      //! Overloaded unary negation
      friend vec4 operator - (const vec4& v); 

      //! Overloaded addition
      friend vec4 operator + (const vec4& v1, const vec4& v2); 

      //! Overloaded subtraction
      friend vec4 operator - (const vec4& v1, const vec4& v2); 

      //! Overloaded multiplication (vector & constant)
      friend vec4 operator * (const vec4& v, const double d);

      //! Overloaded multiplication (constant & vector)
      friend vec4 operator * (const double d, const vec4& v);

      //! Overloaded multiplication (vector & matrix)
      friend vec4 operator * (const vec4& v1, mat44& M);

      //! Overloaded multiplication (matrix & vector)
      friend vec4 operator * (mat44& M, const vec4& v1);

      //! Overloaded multiplication (dot product)
      friend double operator * (const vec4& v1, const vec4& v2);

      //! Oveloaded division (vector & constant)
      friend vec4 operator / (const vec4& v, const double d);	

      //! Vector equality
      friend bool operator == (const vec4& v1, const vec4& v2);

      //! Vector inequality
      friend bool operator != (const vec4& v1, const vec4& v2);


      //! Swap vectors v1 and v2
      friend void swap(vec4& v1, vec4& v2);

      //! Minimum of vectors v1 & v2
      friend vec4 min(const vec4& v1, const vec4& v2);	

      //! Maximum of vectors v1 & v2
      friend vec4 max(const vec4& v1, const vec4& v2);	

      //! Term by term product
      friend vec4 prod(const vec4& v1, const vec4& v2);


      //@{
      //! Friend classes
      friend class vec3;
      friend class mat44;
      //@}
    };

    //-----------------------------------------------------------------------------
    /*!
      \class mat33
      \brief This is a general 3x3 matrix class
    */
    class mat33
    {
    protected:
      vec3 row[3];


    public:
      //@{
      //! Constructor
      mat33();
      mat33(const vec3& v1, const vec3& v2, const vec3& v3);
      mat33(const double d);
      mat33(const mat33& m);
      mat33(const double a00, const double a01, const double a02,
	    const double a10, const double a11, const double a12,
	    const double a20, const double a21, const double a22);
      mat33(const double a[3][3]);

      //@}
      //! Destructor
      ~mat33();

      //@{
      //! Overloaded assignment operators
      mat33& operator = (const mat33& m);
      mat33& operator += (const mat33& m);
      mat33& operator -= (const mat33& m);
      mat33& operator *= (const double d);
      mat33& operator /= (const double d);
      //@}

      //! Overloaded [] operator
      vec3& operator [] (int index);

      //! Overloaded [] operator
      vec3 operator [] (int index) const;

      //! Returns the transpose of the matrix
      mat33 transpose(void);

      //! Returns the inverse of the matrix
      mat33 inverse(void);

      //! Maps the function to every element of the matrix
      mat33& map( double (*fn)(double) );

      //! Sets the value of the matrix
      void set(const vec3& v0, const vec3& v1, const vec3& v2);

      //! Sets the value of the matrix
      void set(double arr[3][3]);

      //! Print the matrix to a file
      void print( FILE *file, std::string name );

      //! Swap rows i and j
      void swap_rows(int i, int j);

      //! Swap columns i and j             
      void swap_cols(int i, int j);      

      
      //! Overloaded unary negation
      friend mat33 operator - (const mat33& m); 

      //! Overloaded addition
      friend mat33 operator + (const mat33& m1, const mat33& m2); 

      //! Overloaded subtraction
      friend mat33 operator - (const mat33& m1, const mat33& m2); 

      //! Overloaded multiplication (matrix & constant)
      friend mat33 operator * (const mat33& m, const double d);

      //! Overloaded multiplication (constant & matrix)
      friend mat33 operator * (const double d, const mat33& m);

      //! Overloaded multiplication (matrix & matrix)
      friend mat33 operator * (mat33 m1, mat33 m2);

      //! Oveloaded division (matrix & constant)
      friend mat33 operator / (const mat33& m, const double d);	

      //! Matrix equality
      friend bool operator == (const mat33& m1, const mat33& m2);

      //! Matrix inequality
      friend bool operator != (const mat33& m1, const mat33& m2);

      //! Swap matrices m1 and m2
      friend void swap(mat33& m1, mat33& m2);

      
      //! 2D identity matrix
      static mat33 identity2D(void);

      //! 2D rotation matrix (postmultiply column vector)
      static mat33 rotation2D(vec2& center, double theta);

      //! 2D translation matrix (postmultiply column vector)
      static mat33 translation2D(double tx, double ty);

      //! 2D translation matrix (postmultiply column vector)
      static mat33 translation2D(vec2& v);

      //! 2D scaling matrix (postmultiply column vector)
      static mat33 scaling2D(vec2& v);


      //@{
      //! Necessary friend declarations
      friend vec3 operator * (const vec3& v, mat33& M);
      friend vec3 operator * (mat33& M, const vec3& v);
      //@}
    };

    //-----------------------------------------------------------------------------
    /*!
      \class mat44
      \brief This is a general 4x4 matrix class
    */
    class mat44
    {
    protected:
      vec4 row[4];


    public:
      //@{
      //! Constructor
      mat44();
      mat44(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);
      mat44(const double d);
      mat44(const mat44& m);
      mat44(const double a00, const double a01, const double a02, const double a03,
	    const double a10, const double a11, const double a12, const double a13,
	    const double a20, const double a21, const double a22, const double a23,
	    const double a30, const double a31, const double a32, const double a33);
      mat44(const double a[4][4]);
      //@}

      //! Destructor
      ~mat44();


      //@{
      //! Overloaded assignment operators
      mat44& operator = (const mat44& m);
      mat44& operator += (const mat44& m);
      mat44& operator -= (const mat44& m);
      mat44& operator *= (const double d);
      mat44& operator /= (const double d);
      //@}

      //! Overloaded [] operator
      vec4& operator [] (int index);

      //! Overloaded [] operator
      vec4 operator [] (int index) const;

      //! Returns the transpose of the matrix
      mat44 transpose(void);

      //! Returns the inverse of the matrix
      mat44 inverse(void);

      //! Maps the function to every element of the matrix
      mat44& map( double (*fn)(double) );

      //! Sets the value of the matrix
      void set(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3);

      //! Sets the value of the matrix
      void set(double arr[4][4]);

      //! Print the matrix to a file
      void print(FILE *file, std::string name);

      //! Swap rows i and j
      void swap_rows(int i, int j);

      //! Swap columns i and j             
      void swap_cols(int i, int j);
      

      //! Overloaded unary negation
      friend mat44 operator - (const mat44& m); 

      //! Overloaded addition
      friend mat44 operator + (const mat44& m1, const mat44& m2); 

      //! Overloaded subtraction
      friend mat44 operator - (const mat44& m1, const mat44& m2); 

      //! Overloaded multiplication (matrix & constant)
      friend mat44 operator * (const mat44& m1, const double d);

      //! Overloaded multiplication (constant & matrix)
      friend mat44 operator * (const double d, const mat44& m1);

      //! Overloaded multiplication (matrix & matrix)
      friend mat44 operator * (mat44& m1, mat44& m2);

      //! Oveloaded dimision (matrix & constant)
      friend mat44 operator / (const mat44& m1, const double d);	

      //! Matrix equality
      friend bool operator == (const mat44& m1, const mat44& m2);

      //! Matrix inequality
      friend bool operator != (const mat44& m1, const mat44& m2);

      //! Swap matrices m1 and m2
      friend void swap(mat44& m1, mat44& m2);

      
      //! 3D identity matrix
      static mat44 identity3D(void);

      //! 3D rotation matrix (postmultiply column vector)
      static mat44 rotation3D(vec3& axis, double theta);

      //! 3D translation matrix (postmultiply column vector)
      static mat44 translation3D(double tx, double ty, double tz);

      //! 3D translation matrix (postmultiply column vector)
      static mat44 translation3D(vec3& v);

      //! 3D scaling matrix (postmultiply column vector)
      static mat44 scaling3D(vec3& v);

      //! Perpective projection matrix (postmultiply column vector)
      static mat44 perspective3D(const double d);


      //@{
      //! Necessary friend declarations
      friend vec4 operator * (const vec4& v, mat44& M);
      friend vec4 operator * (mat44& M, const vec4& v);
      //@}
    };

    //-----------------------------------------------------------------------------
  }
}

#endif
