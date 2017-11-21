#include <cmath>
#include "error.hpp"
#include "matvec.hpp"

namespace util
{
  namespace math
  {

    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
    //vec2 methods

    vec2::vec2()
    { data[X] = data[Y] = 0.0; }

    vec2::vec2(const double x, const double y)
    { data[X] = x; data[Y] = y; }

    vec2::vec2(const double d)
    { data[X] = data[Y] = d; }

    vec2::vec2(const double v[2])
    { data[X] = v[X]; data[Y] = v[Y]; }

    vec2::vec2(const vec2& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; }

    //User to prevent divide by zero
    vec2::vec2(const vec3& v)
    { data[X] = v.data[X]/v.data[Z]; data[Y] = v.data[Y]/v.data[Z]; }

    vec2::vec2(const vec3& v, int dropAxis)
    {
      switch(dropAxis)
	{
	case X: data[X] = v.data[Y]; data[Y] = v.data[Z]; break;
	case Y: data[X] = v.data[X]; data[Y] = v.data[Z]; break;
	default: data[X] = v.data[X]; data[Y] = v.data[Y]; break;
	}
    }

    vec2::~vec2()
    { }

    vec2& vec2::operator = (const vec2& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; return *this; }

    vec2& vec2::operator += (const vec2& v)
    { data[X] += v.data[X]; data[Y] += v.data[Y]; return *this; }
    
    vec2& vec2::operator -= (const vec2& v)
    { data[X] -= v.data[X]; data[Y] -= v.data[Y]; return *this; }
    
    vec2& vec2::operator *= (const double d)
    { data[X] *= d; data[Y] *= d; return *this; }
    
    vec2& vec2::operator /= (const double d )
    { double d_inv = 1.0/d; data[X] *= d_inv; data[Y] *= d_inv; return *this; }
    
    double& vec2::operator [] (int index)
    {
      if ((index < X) || (index > Y))
	throw util::common::fatal_error("vec2::operator [] : Index out of bounds");
      return data[index];
    }

    double vec2::operator [] (int index) const
    {
      if ((index < X) || (index > Y))
	throw util::common::fatal_error("vec2::operator [] : Index out of bounds");
      return data[index];
    }

    double vec2::length(void) const
    { return sqrt(length2()); }

    double vec2::length2(void) const
    { return ((data[X]*data[X])+(data[Y]*data[Y])); }

    //User to avoid divide by zero
    vec2& vec2::normalize(void)
    { *this /= length(); return *this; }

    vec2& vec2::map( double (*fn)(double) )
    { data[X] = (*fn)(data[X]); data[Y] = (*fn)(data[Y]); return *this; }

    void vec2::set(double x, double y)
    { data[X] = x; data[Y] = y; }

    void vec2::print(FILE *file, std::string name)
    {
      fprintf( file, "%s: <%f, %f>\n", name.c_str(), data[X], data[Y] );
    }

    vec2 operator - (const vec2& v)
    { return vec2(-v.data[X],-v.data[Y]); }

    vec2 operator + (const vec2& v1, const vec2& v2)
    { return vec2(v1.data[X] + v2.data[X], v1.data[Y] + v2.data[Y]); }

    vec2 operator - (const vec2& v1, const vec2& v2)
    { return vec2(v1.data[X] - v2.data[X], v1.data[Y] - v2.data[Y]); }

    vec2 operator * (const vec2& v, const double d)
    { return vec2(d * v.data[X], d * v.data[Y]); }

    vec2 operator * (const double d, const vec2& v)
    { return vec2(d * v.data[X], d * v.data[Y]); }

    double operator * (const vec2& v1, const vec2& v2)
    { return ((v1.data[X] * v2.data[X]) + (v1.data[Y] * v2.data[Y])); }

    vec2 operator / (const vec2& v, const double d)
    { double d_inv = 1.0/d; return vec2(v.data[X] * d_inv, v.data[Y] * d_inv); }

    vec3 operator ^ (const vec2& v1, const vec2& v2)
    { return vec3(0.0, 0.0, v1.data[X] * v2.data[Y] - v2.data[X] * v1.data[Y]); }

    bool operator == (const vec2& v1, const vec2& v2)
    { return ((v1.data[X] == v2.data[X]) && (v1.data[Y] == v2.data[Y])); }
    
    bool operator != (const vec2& v1, const vec2& v2)
    { return (!(v1 == v2)); }

    void swap(vec2& v1, vec2& v2)
    { vec2 temp(v1); v1 = v2; v2 = temp; }
    
    vec2 min(const vec2& v1, const vec2& v2)
    { return vec2(MIN(v1.data[X], v2.data[X]), MIN(v1.data[Y], v2.data[Y])); }
    
    vec2 max(const vec2& v1, const vec2& v2)
    { return vec2(MAX(v1.data[X], v2.data[X]), MAX(v1.data[Y], v2.data[Y])); }
    
    vec2 prod(const vec2& v1, const vec2& v2)
    { return vec2(v1.data[X] * v2.data[X], v1.data[Y] * v2.data[Y]); }


    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
    // vec3 methods

    vec3::vec3()
    { data[X] = data[Y] = data[Z] = 0.0; }

    vec3::vec3(const double x, const double y, const double z)
    { data[X] = x; data[Y] = y; data[Z] = z; }

    vec3::vec3(const double d)
    { data[X] = data[Y] = data[Z] = d; }

    vec3::vec3(const double v[3])
    { data[X] = v[X]; data[Y] = v[Y]; data[Z] = v[Z]; }

    vec3::vec3(const vec3& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; }

    vec3::vec3(const vec2& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = 1.0; }

    vec3::vec3(const vec2& v, double d)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = d; }

    //User to prevent divide by zero
    vec3::vec3(const vec4& v)
    { data[X] = v.data[X]/v.data[W]; data[Y] = v.data[Y]/v.data[W]; data[Z] = v.data[Z]/v.data[W]; }

    vec3::vec3(const vec4& v, int dropAxis)
    {
      switch(dropAxis)
	{
	case X: data[X] = v.data[Y]; data[Y] = v.data[Z]; data[Z] = v.data[W]; break;
	case Y: data[X] = v.data[X]; data[Y] = v.data[Z]; data[Z] = v.data[W]; break;
	case Z: data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[W]; break;
	default: data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; break;
	}
    }

    vec3::~vec3()
    { }

    vec3& vec3::operator = (const vec3& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; return *this; }

    vec3& vec3::operator += (const vec3& v)
    { data[X] += v.data[X]; data[Y] += v.data[Y]; data[Z] += v.data[Z]; return *this; }
    
    vec3& vec3::operator -= (const vec3& v)
    { data[X] -= v.data[X]; data[Y] -= v.data[Y]; data[Z] -= v.data[Z]; return *this; }
    
    vec3& vec3::operator *= (const double d)
    { data[X] *= d; data[Y] *= d; data[Z] *= d; return *this; }
    
    vec3& vec3::operator /= (const double d )
    { double d_inv = 1.0/d; data[X] *= d_inv; data[Y] *= d_inv; data[Z] *= d_inv; return *this; }
    
    double& vec3::operator [] (int index)
    {
      if ((index < X) || (index > Z))
	throw util::common::fatal_error("vec3::operator [] : Index out of bounds");
      return data[index];
    }

    double vec3::operator [] (int index) const
    {
      if ((index < X) || (index > Z))
	throw util::common::fatal_error("vec3::operator [] : Index out of bounds");
      return data[index];
    }

    double vec3::length(void) const
    { return sqrt(length2()); }

    double vec3::length2(void) const
    { return ((data[X]*data[X]) + (data[Y]*data[Y]) + (data[Z]*data[Z])); }

    //User to avoid divide by zero
    vec3& vec3::normalize(void)
    { *this /= length(); return *this; }

    vec3& vec3::homogenize(void)
    { data[X] /= data[Z]; data[Y] /= data[Z]; data[Z] = 1.0; return *this; }

    vec3& vec3::map( double (*fn)(double) )
    { data[X] = (*fn)(data[X]); data[Y] = (*fn)(data[Y]); data[Z] = (*fn)(data[Z]); return *this; }

    void vec3::set(double x, double y, double z)
    { data[X] = x; data[Y] = y; data[Z] = z; }

    void  vec3::print(FILE *file, std::string name)
    {
      fprintf( file, "%s: <%f, %f, %f>\n", name.c_str(), data[X], data[Y], data[Z] );
    }

    vec3 operator - (const vec3& v)
    { return vec3(-v.data[X],-v.data[Y],-v.data[Z]); }

    vec3 operator + (const vec3& v1, const vec3& v2)
    { return vec3(v1.data[X] + v2.data[X], v1.data[Y] + v2.data[Y], v1.data[Z] + v2.data[Z]); }

    vec3 operator - (const vec3& v1, const vec3& v2)
    { return vec3(v1.data[X] - v2.data[X], v1.data[Y] - v2.data[Y], v1.data[Z] - v2.data[Z]); }

    vec3 operator * (const vec3& v, const double d)
    { return vec3(d * v.data[X], d * v.data[Y], d * v.data[Z]); }

    vec3 operator * (const double d, const vec3& v)
    { return vec3(d * v.data[X], d * v.data[Y], d * v.data[Z]); }
    
    vec3 operator * (const vec3& v, mat33& M)
    {
      double val1 = (v.data[X] * (M.row[X])[X]) + (v.data[Y] * (M.row[Y])[X]) + (v.data[Z] * (M.row[Z])[X]);
      double val2 = (v.data[X] * (M.row[X])[Y]) + (v.data[Y] * (M.row[Y])[Y]) + (v.data[Z] * (M.row[Z])[Y]);
      double val3 = (v.data[X] * (M.row[X])[Z]) + (v.data[Y] * (M.row[Y])[Z]) + (v.data[Z] * (M.row[Z])[Z]);
      return vec3(val1, val2, val3);
    }

    vec3 operator * (mat33& M, const vec3& v)
    {
      double val1 = (v.data[X] * (M.row[X])[X]) + (v.data[Y] * (M.row[X])[Y]) + (v.data[Z] * (M.row[X])[Z]);
      double val2 = (v.data[X] * (M.row[Y])[X]) + (v.data[Y] * (M.row[Y])[Y]) + (v.data[Z] * (M.row[Y])[Z]);
      double val3 = (v.data[X] * (M.row[Z])[X]) + (v.data[Y] * (M.row[Z])[Y]) + (v.data[Z] * (M.row[Z])[Z]);
      return vec3(val1, val2, val3);
    }

    double operator * (const vec3& v1, const vec3& v2)
    { return ((v1.data[X] * v2.data[X]) + (v1.data[Y] * v2.data[Y]) + (v1.data[Z] * v2.data[Z])); }

    vec3 operator / (const vec3& v, const double d)
    { double d_inv = 1.0/d; return vec3(v.data[X] * d_inv, v.data[Y] * d_inv, v.data[Z] * d_inv); }

    vec3 operator ^ (const vec3& v1, const vec3& v2)
    { return vec3(v1.data[Y]*v2.data[Z] - v1.data[Z]*v2.data[Y],
		  v1.data[Z]*v2.data[X] - v1.data[X]*v2.data[Z],
		  v1.data[X]*v2.data[Y] - v1.data[Y]*v2.data[X]); }

    bool operator == (const vec3& v1, const vec3& v2)
    { return ((v1.data[X] == v2.data[X]) && (v1.data[Y] == v2.data[Y]) && (v1.data[Z] == v2.data[Z])); }
    
    bool operator != (const vec3& v1, const vec3& v2)
    { return (!(v1 == v2)); }

    void swap(vec3& v1, vec3& v2)
    { vec3 temp(v1); v1 = v2; v2 = temp; }
    
    vec3 min(const vec3& v1, const vec3& v2)
    { return vec3(MIN(v1.data[X], v2.data[X]), MIN(v1.data[Y], v2.data[Y]), MIN(v1.data[Z], v2.data[Z])); }
    
    vec3 max(const vec3& v1, const vec3& v2)
    { return vec3(MAX(v1.data[X], v2.data[X]), MAX(v1.data[Y], v2.data[Y]), MAX(v1.data[Z], v2.data[Z])); }
    
    vec3 prod(const vec3& v1, const vec3& v2)
    { return vec3(v1.data[X] * v2.data[X], v1.data[Y] * v2.data[Y], v1.data[Z] * v2.data[Z]); }
    
    
    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
    // vec4 methods

    vec4::vec4()
    { data[X] = data[Y] = data[Z] = data[W] = 0.0; }

    vec4::vec4(const double x, const double y, const double z, const double w)
    { data[X] = x; data[Y] = y; data[Z] = z; data[W] = w; }

    vec4::vec4(const double d)
    { data[X] = data[Y] = data[Z] = data[W] = d; }

    vec4::vec4(const double v[4])
    { data[X] = v[X]; data[Y] = v[Y]; data[Z] = v[Z]; data[W] = v[W]; }

    vec4::vec4(const vec4& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; data[W] = v.data[W]; }

    vec4::vec4(const vec3& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; data[W] = 1.0; }

    vec4::vec4(const vec3& v, double d)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; data[W] = d; }

    vec4::~vec4()
    { }

    vec4& vec4::operator = (const vec4& v)
    { data[X] = v.data[X]; data[Y] = v.data[Y]; data[Z] = v.data[Z]; data[W] = v.data[W]; return *this; }

    vec4& vec4::operator += (const vec4& v)
    { data[X] += v.data[X]; data[Y] += v.data[Y]; data[Z] += v.data[Z]; data[W] += v.data[W]; return *this; }
    
    vec4& vec4::operator -= (const vec4& v)
    { data[X] -= v.data[X]; data[Y] -= v.data[Y]; data[Z] -= v.data[Z]; data[W] -= v.data[W]; return *this; }
    
    vec4& vec4::operator *= (const double d)
    { data[X] *= d; data[Y] *= d; data[Z] *= d; data[W] *= d; return *this; }
    
    vec4& vec4::operator /= (const double d )
    { double d_inv = 1.0/d; data[X] *= d_inv; data[Y] *= d_inv; data[Z] *= d_inv; data[W] *= d_inv; return *this; }
    
    double& vec4::operator [] (int index)
    {
      if ((index < X) || (index > W))
	throw util::common::fatal_error("vec4::operator [] : Index out of bounds");
      return data[index];
    }

    double vec4::operator [] (int index) const
    {
      if ((index < X) || (index > W))
	throw util::common::fatal_error("vec4::operator [] : Index out of bounds");
      return data[index];
    }

    double vec4::length(void) const
    { return sqrt(length2()); }

    double vec4::length2(void) const
    { return ((data[X]*data[X]) + (data[Y]*data[Y]) + (data[Z]*data[Z]) + (data[W]*data[W])); }

    //User to avoid divide by zero
    vec4& vec4::normalize(void)
    { *this /= length(); return *this; }

    vec4& vec4::homogenize(void)
    { data[X] /= data[W]; data[Y] /= data[W]; data[Z] /= data[W]; data[W] = 1.0; return *this; }

    vec4& vec4::map( double (*fn)(double) )
    { data[X] = (*fn)(data[X]); data[Y] = (*fn)(data[Y]); data[Z] = (*fn)(data[Z]); data[W] = (*fn)(data[W]); return *this; }

    void vec4::set(double x, double y, double z, double w)
    { data[X] = x; data[Y] = y; data[Z] = z; data[W] = w; }

    void vec4::print(FILE *file, std::string name)
    {
      fprintf( file, "%s: <%f, %f, %f, %f>\n", name.c_str(), data[X], data[Y], data[Z], data[W] );
    }

    vec4 vec4::get_ortho(void) const
    {
      vec4 v;
      if (( data[X] > 0.5 || data[X]<-0.5) || (data[Y] > 0.5 || data[Y]<-0.5 ))
	{ v = vec4(data[Y],-data[X],0.0,1.0 ); }
      else
	{ v = vec4( 0.0,data[Z],-data[Y],1.0); }
      v = v.normalize();
      return v;
    }
    
    void vec4::get_ortho_frame(vec4& v1, vec4& v2)
    {
      vec4 temp = vec4(1.0, 0.0, 0.0, 1.0);
      if ((*this) == temp) temp = vec4(0.0, 1.0, 0.0, 1.0);
      v2 = (*this)^(temp);
      v2 = v2.normalize();
      v1 = v2^(*this);
    }

    vec4 operator - (const vec4& v)
    { return vec4(-v.data[X], -v.data[Y], -v.data[Z], -v.data[W]); }

    vec4 operator + (const vec4& v1, const vec4& v2)
    { return vec4(v1.data[X] + v2.data[X], v1.data[Y] + v2.data[Y], v1.data[Z] + v2.data[Z], v1.data[W] + v2.data[W]); }

    vec4 operator - (const vec4& v1, const vec4& v2)
    { return vec4(v1.data[X] - v2.data[X], v1.data[Y] - v2.data[Y], v1.data[Z] - v2.data[Z], v1.data[W] - v2.data[W]); }

    vec4 operator * (const vec4& v, const double d)
    { return vec4(d * v.data[X], d * v.data[Y], d * v.data[Z], d * v.data[W]); }

    vec4 operator * (const double d, const vec4& v)
    { return vec4(d * v.data[X], d * v.data[Y], d * v.data[Z], d * v.data[W]); }
    
    vec4 operator * (const vec4& v, mat44& M)
    {
      double val1 = (v.data[X] * (M.row[X])[X]) + (v.data[Y] * (M.row[Y])[X]) + (v.data[Z] * (M.row[Z])[X]) + (v.data[W] * (M.row[W])[X]);
      double val2 = (v.data[X] * (M.row[X])[Y]) + (v.data[Y] * (M.row[Y])[Y]) + (v.data[Z] * (M.row[Z])[Y]) + (v.data[W] * (M.row[W])[Y]);
      double val3 = (v.data[X] * (M.row[X])[Z]) + (v.data[Y] * (M.row[Y])[Z]) + (v.data[Z] * (M.row[Z])[Z]) + (v.data[W] * (M.row[W])[Z]);
      double val4 = (v.data[X] * (M.row[X])[W]) + (v.data[Y] * (M.row[Y])[W]) + (v.data[Z] * (M.row[Z])[W]) + (v.data[W] * (M.row[W])[W]);
      return vec4(val1, val2, val3, val4);
    }

    vec4 operator * (mat44& M, const vec4& v)
    {
      double val1 = (v.data[X] * (M.row[X])[X]) + (v.data[Y] * (M.row[X])[Y]) + (v.data[Z] * (M.row[X])[Z]) + (v.data[W] * (M.row[X])[W]);
      double val2 = (v.data[X] * (M.row[Y])[X]) + (v.data[Y] * (M.row[Y])[Y]) + (v.data[Z] * (M.row[Y])[Z]) + (v.data[W] * (M.row[Y])[W]);
      double val3 = (v.data[X] * (M.row[Z])[X]) + (v.data[Y] * (M.row[Z])[Y]) + (v.data[Z] * (M.row[Z])[Z]) + (v.data[W] * (M.row[Z])[W]);
      double val4 = (v.data[X] * (M.row[W])[X]) + (v.data[Y] * (M.row[W])[Y]) + (v.data[Z] * (M.row[W])[Z]) + (v.data[W] * (M.row[W])[W]);
      return vec4(val1, val2, val3, val4);
    }

    double operator * (const vec4& v1, const vec4& v2)
    { return ((v1.data[X] * v2.data[X]) + (v1.data[Y] * v2.data[Y]) + (v1.data[Z] * v2.data[Z]) + (v1.data[W] * v2.data[W])); }

    vec4 operator / (const vec4& v, const double d)
    { double d_inv = 1.0/d; return vec4(v.data[X] * d_inv, v.data[Y] * d_inv, v.data[Z] * d_inv, v.data[W] * d_inv); }

    bool operator == (const vec4& v1, const vec4& v2)
    { return ((v1.data[X] == v2.data[X]) && (v1.data[Y] == v2.data[Y]) 
	      && (v1.data[Z] == v2.data[Z]) && (v1.data[W] == v2.data[W]) ); }
    
    bool operator != (const vec4& v1, const vec4& v2)
    { return (!(v1 == v2)); }

    void swap(vec4& v1, vec4& v2)
    { vec4 temp(v1); v1 = v2; v2 = temp; }
    
    vec4 min(const vec4& v1, const vec4& v2)
    { return vec4(MIN(v1.data[X], v2.data[X]), MIN(v1.data[Y], v2.data[Y]),
		  MIN(v1.data[Z], v2.data[Z]), MIN(v1.data[W], v2.data[W])); }
    
    vec4 max(const vec4& v1, const vec4& v2)
    { return vec4(MAX(v1.data[X], v2.data[X]), MAX(v1.data[Y], v2.data[Y]),
		  MAX(v1.data[Z], v2.data[Z]), MAX(v1.data[W], v2.data[W])); }
    
    vec4 prod(const vec4& v1, const vec4& v2)
    { return vec4(v1.data[X] * v2.data[X], v1.data[Y] * v2.data[Y], 
		  v1.data[Z] * v2.data[Z], v1.data[W] * v2.data[W]); }
    
    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
    // mat33 methods

    mat33::mat33()
    { *this = identity2D(); }

    mat33::mat33(const vec3& v1, const vec3& v2, const vec3& v3)
    { this->set(v1, v2, v3); }

    mat33::mat33(const double d)
    { row[X] = row[Y] = row[Z] = vec3(d); }

    mat33::mat33(const mat33& m)
    { row[X] = m.row[X]; row[Y] = m.row[Y]; row[Z] = m.row[Z]; }

    mat33::mat33(const double a00, const double a01, const double a02,
		 const double a10, const double a11, const double a12,
		 const double a20, const double a21, const double a22)
    {
      row[X][X] = a00; row[X][Y] = a01; row[X][Z] = a02;
      row[Y][X] = a10; row[Y][Y] = a11; row[Y][Z] = a12;
      row[Z][X] = a20; row[Z][Y] = a21; row[Z][Z] = a22;
    }

    mat33::mat33(const double a[3][3])
    {
      row[X][X] = a[X][X]; row[X][Y] = a[X][Y]; row[X][Z] = a[X][Z];
      row[Y][X] = a[Y][X]; row[Y][Y] = a[Y][Y]; row[Y][Z] = a[Y][Z];
      row[Z][X] = a[Z][X]; row[Z][Y] = a[Z][Y]; row[Z][Z] = a[Z][Z];
    }

    mat33::~mat33()
    { }

    mat33& mat33::operator = ( const mat33& m )
    { row[X] = m.row[X]; row[Y] = m.row[Y]; row[Z] = m.row[Z]; return *this; }

    mat33& mat33::operator += ( const mat33& m )
    { row[X] += m.row[X]; row[Y] += m.row[Y]; row[Z] += m.row[Z]; return *this; }

    mat33& mat33::operator -= ( const mat33& m )
    { row[X] -= m.row[X]; row[Y] -= m.row[Y]; row[Z] -= m.row[Z]; return *this; }

    mat33& mat33::operator *= ( const double d )
    { row[X] *= d; row[Y] *= d; row[Z] *= d; return *this; }

    mat33& mat33::operator /= ( const double d )
    { row[X] /= d; row[Y] /= d; row[Z] /= d; return *this; }

    vec3& mat33::operator [] (int index)
    {
      if ((index < X) || (index > Z))
	throw util::common::fatal_error("mat33::operator [] : Index out of bounds");
      return row[index];
    }

    vec3 mat33::operator [] (int index) const
    {
      if ((index < X) || (index > Z))
	throw util::common::fatal_error("mat33::operator [] : Index out of bounds");
      return row[index];
    }

    mat33 mat33::transpose(void)
    { return mat33(row[X][X], row[Y][X], row[Z][X],
		   row[X][Y], row[Y][Y], row[Z][Y],
		   row[X][Z], row[Y][Z], row[Z][Z]); }

    // Gauss-Jordan elimination with partial pivoting
    mat33 mat33::inverse(void)      
    {
      // As a evolves from original mat into identity
      // b evolves from identity into inverse(a)
      mat33 a(*this), b(identity2D());
      int i, j, i1;

      // Loop over cols of a from left to right, eliminating above and below diag
      for (j=0; j<3; j++) 
	{ 
	  // Find largest pivot in column j among rows j..2
	  i1 = j;
	  // Row with largest pivot candidate
	  for (i=j+1; i<3; i++)
	    if (fabs(a.row[i].data[j]) > fabs(a.row[i1].data[j]))
	      i1 = i;

	  // Swap rows i1 and j in a and b to put pivot on diagonal
	  swap(a.row[i1], a.row[j]);
	  swap(b.row[i1], b.row[j]);

	  // Scale row j to have a unit diagonal
	  if (fabs(a.row[j].data[j]) <= EPSILON)
	    throw util::common::fatal_error("mat33::inverse : Singular matrix, cannot invert");
	  b.row[j] /= a.row[j].data[j];
	  a.row[j] /= a.row[j].data[j];

	  // Eliminate off-diagonal elems in col j of a, doing identical ops to b
	  for (i=0; i<3; i++)
	    if (i != j) 
	      {
		b.row[i] -= a.row[i].data[j] * b.row[j];
		a.row[i] -= a.row[i].data[j] * a.row[j];
	      }
	}
      return b;
    }

    mat33& mat33::map( double (*fn)(double) )
    {
      row[X].map(fn); row[Y].map(fn); row[Z].map(fn); return *this;
    }

    void mat33::set(const vec3& v0, const vec3& v1, const vec3& v2)
    { row[X] = v0; row[Y] = v1; row[Z] = v2; }

    void mat33::set(double arr[3][3])
    { 
      row[X][X] = arr[X][X]; row[X][Y] = arr[X][Y]; row[X][Z] = arr[X][Z];
      row[Y][X] = arr[Y][X]; row[Y][Y] = arr[Y][Y]; row[Y][Z] = arr[Y][Z];
      row[Z][X] = arr[Z][X]; row[Z][Y] = arr[Z][Y]; row[Z][Z] = arr[Z][Z];
    }

    void mat33::print( FILE *file, std::string name )
    {
      int i, j;
      fprintf( file, "%s:\n", name.c_str() );
      for( i = 0; i < 3; i++ )
	{
	  fprintf( file, "   " );
	  for( j = 0; j < 3; j++ )
	    {
	      fprintf( file, "%f  ", row[i][j] );
	    }
	  fprintf( file, "\n" );
	}
    }
    
    void mat33::swap_rows(int i, int j)
    {
      vec4 t;
      t = row[i]; row[i] = row[j]; row[j] = t;
    }

    void mat33::swap_cols(int i, int j)
    {
      float t; int k;
      for(k=0; k<3; k++ )
	{
	  t = row[k][i];
	  row[k][i] = row[k][j];
	  row[k][j] = t;
	}
    }

    mat33 operator - (const mat33& m)
    { return mat33(-m.row[X], -m.row[Y], -m.row[Z]); }

    mat33 operator + (const mat33& m1, const mat33& m2)
    { return mat33(m1.row[X] + m2.row[X], m1.row[Y] + m2.row[Y], m1.row[Z] + m2.row[Z]); }

    mat33 operator - (const mat33& m1, const mat33& m2)
    { return mat33(m1.row[X] - m2.row[X], m1.row[Y] - m2.row[Y], m1.row[Z] - m2.row[Z]); }

    mat33 operator * (const mat33& m, const double d)
    { return mat33(m.row[X] * d, m.row[Y] * d,  m.row[Z] * d); }

    mat33 operator * (const double d, const mat33& m)
    { return mat33(m.row[X] * d, m.row[Y] * d,  m.row[Z] * d); }

    mat33 operator * (mat33 m1, mat33 m2)
    { 
      double c11 = (m1.row[X][X] * m2.row[X][X]) + (m1.row[X][Y] * m2.row[Y][X]) + (m1.row[X][Z] * m2.row[Z][X]);
      double c12 = (m1.row[X][X] * m2.row[X][Y]) + (m1.row[X][Y] * m2.row[Y][Y]) + (m1.row[X][Z] * m2.row[Z][Y]);
      double c13 = (m1.row[X][X] * m2.row[X][Z]) + (m1.row[X][Y] * m2.row[Y][Z]) + (m1.row[X][Z] * m2.row[Z][Z]);

      double c21 = (m1.row[Y][X] * m2.row[X][X]) + (m1.row[Y][Y] * m2.row[Y][X]) + (m1.row[Y][Z] * m2.row[Z][X]);
      double c22 = (m1.row[Y][X] * m2.row[X][Y]) + (m1.row[Y][Y] * m2.row[Y][Y]) + (m1.row[Y][Z] * m2.row[Z][Y]);
      double c23 = (m1.row[Y][X] * m2.row[X][Z]) + (m1.row[Y][Y] * m2.row[Y][Z]) + (m1.row[Y][Z] * m2.row[Z][Z]);

      double c31 = (m1.row[Z][X] * m2.row[X][X]) + (m1.row[Z][Y] * m2.row[Y][X]) + (m1.row[Z][Z] * m2.row[Z][X]);
      double c32 = (m1.row[Z][X] * m2.row[X][Y]) + (m1.row[Z][Y] * m2.row[Y][Y]) + (m1.row[Z][Z] * m2.row[Z][Y]);
      double c33 = (m1.row[Z][X] * m2.row[X][Z]) + (m1.row[Z][Y] * m2.row[Y][Z]) + (m1.row[Z][Z] * m2.row[Z][Z]);

      return mat33(c11, c12, c13,
		   c21, c22, c23,
		   c31, c32, c33);
    }

    mat33 operator / (const mat33& m, const double d)
    { return mat33(m.row[X] / d, m.row[Y] / d, m.row[Z] / d); }

    bool operator == (const mat33& m1, const mat33& m2)
    { return ((m1.row[X] == m2.row[X]) && (m1.row[Y] == m2.row[Y]) && (m1.row[Z] == m2.row[Z])); }

    bool operator != (const mat33& m1, const mat33& m2)
    { return !(m1 == m2); }

    void swap(mat33& m1, mat33& m2)
    { mat33 temp(m1); m1 = m2; m2 = temp; }

    mat33 mat33::identity2D(void)
    { return mat33(vec3(1.0, 0.0, 0.0),
		   vec3(0.0, 1.0, 0.0),
		   vec3(0.0, 0.0, 1.0)); }

    mat33 mat33::rotation2D(vec2& center, double theta)
    { 
      double thetaRad = theta * M_PI / 180.0;
      double c = cos(thetaRad);
      double s = sin(thetaRad);

      return mat33(vec3(c, -s, center[X] * (1.0-c) + center[Y] * s),
		   vec3(s, c, center[Y] * (1.0-c) - center[X] * s),
		   vec3(0.0, 0.0, 1.0));
    }

    mat33 mat33::translation2D(double tx, double ty)
    { return mat33(vec3(1.0, 0.0, tx),
		   vec3(0.0, 1.0, ty),
		   vec3(0.0, 0.0, 1.0)); }

    mat33 mat33::translation2D(vec2& v)
    { return mat33(vec3(1.0, 0.0, v[X]),
		   vec3(0.0, 1.0, v[Y]),
		   vec3(0.0, 0.0, 1.0)); }

    mat33 mat33::scaling2D(vec2& v)
    { return mat33(vec3(v[X], 0.0, 0.0),
		   vec3(0.0, v[Y], 0.0),
		   vec3(0.0, 0.0, 1.0)); }

    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
    // mat44 methods
  
    mat44::mat44()
    { *this = identity3D(); }

    mat44::mat44(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
    { this->set(v1, v2, v3, v4); }

    mat44::mat44(const double d)
    { row[X] = row[Y] = row[Z] = row[W] = vec4(d); }

    mat44::mat44(const mat44& m)
    { row[X] = m.row[X]; row[Y] = m.row[Y]; row[Z] = m.row[Z]; row[W] = m.row[W]; }

    mat44::mat44(const double a00, const double a01, const double a02, const double a03,
		 const double a10, const double a11, const double a12, const double a13,
		 const double a20, const double a21, const double a22, const double a23,
		 const double a30, const double a31, const double a32, const double a33)
    {
      row[X][X] = a00; row[X][Y] = a01; row[X][Z] = a02; row[X][W] = a03;
      row[Y][X] = a10; row[Y][Y] = a11; row[Y][Z] = a12; row[Y][W] = a13;
      row[Z][X] = a20; row[Z][Y] = a21; row[Z][Z] = a22; row[Z][W] = a23;
      row[W][X] = a30; row[W][Y] = a31; row[W][Z] = a32; row[W][W] = a33;
    }

    mat44::mat44(const double a[4][4])
    {
      row[X][X] = a[X][X]; row[X][Y] = a[X][Y]; row[X][Z] = a[X][Z]; row[X][W] = a[X][W]; 
      row[Y][X] = a[Y][X]; row[Y][Y] = a[Y][Y]; row[Y][Z] = a[Y][Z]; row[Y][W] = a[Y][W];
      row[Z][X] = a[Z][X]; row[Z][Y] = a[Z][Y]; row[Z][Z] = a[Z][Z]; row[Z][W] = a[Z][W];
      row[W][X] = a[W][X]; row[W][Y] = a[W][Y]; row[W][Z] = a[W][Z]; row[W][W] = a[W][W];
    }

    mat44::~mat44()
    { }
  
    mat44& mat44::operator = ( const mat44& m )
    { row[X] = m.row[X]; row[Y] = m.row[Y]; row[Z] = m.row[Z]; row[W] = m.row[W]; return *this; }

    mat44& mat44::operator += ( const mat44& m )
    { row[X] += m.row[X]; row[Y] += m.row[Y]; row[Z] += m.row[Z]; row[W] += m.row[W]; return *this; }

    mat44& mat44::operator -= ( const mat44& m )
    { row[X] -= m.row[X]; row[Y] -= m.row[Y]; row[Z] -= m.row[Z]; row[W] -= m.row[W]; return *this; }

    mat44& mat44::operator *= ( const double d )
    { row[X] *= d; row[Y] *= d; row[Z] *= d; row[W] *= d; return *this; }

    mat44& mat44::operator /= ( const double d )
    { row[X] /= d; row[Y] /= d; row[Z] /= d; row[W] /= d; return *this; }
  
    vec4& mat44::operator [] (int index)
    {
      if ((index < X) || (index > W))
	throw util::common::fatal_error("mat44::operator [] : Index out of bounds");
      return row[index];
    }

    vec4 mat44::operator [] (int index) const
    {
      if ((index < X) || (index > W))
	throw util::common::fatal_error("mat44::operator [] : Index out of bounds");
      return row[index];
    }
 
    mat44 mat44::transpose(void)
    { return mat44(row[X][X], row[Y][X], row[Z][X], row[W][X],
		   row[X][Y], row[Y][Y], row[Z][Y], row[W][Y],
		   row[X][Z], row[Y][Z], row[Z][Z], row[W][Z],
		   row[X][W], row[Y][W], row[Z][W], row[W][W]); }
    
    // Gauss-Jordan elimination with partial pivoting
    mat44 mat44::inverse(void)      
    {
      // As a evolves from original mat into identity
      // b evolves from identity into inverse(a)
      mat44 a(*this), b(identity3D());
      int i, j, i1;

      // Loop over cols of a from left to right, eliminating above and below diag
      for (j=0; j<4; j++) 
	{ 
	  // Find largest pivot in column j among rows j..2
	  i1 = j;
	  // Row with largest pivot candidate
	  for (i=j+1; i<4; i++)
	    if (fabs(a.row[i].data[j]) > fabs(a.row[i1].data[j]))
	      i1 = i;

	  // Swap rows i1 and j in a and b to put pivot on diagonal
	  swap(a.row[i1], a.row[j]);
	  swap(b.row[i1], b.row[j]);

	  // Scale row j to have a unit diagonal
	  if (a.row[j].data[j] == 0.0)
	    throw util::common::fatal_error("mat44::inverse : Singular matrix, cannot invert");
	  b.row[j] /= a.row[j].data[j];
	  a.row[j] /= a.row[j].data[j];

	  // Eliminate off-diagonal elems in col j of a, doing identical ops to b
	  for (i=0; i<4; i++)
	    if (i != j) 
	      {
		b.row[i] -= a.row[i].data[j] * b.row[j];
		a.row[i] -= a.row[i].data[j] * a.row[j];
	      }
	}
      return b;
    }
  
    mat44& mat44::map( double (*fn)(double) )
    {
      row[X].map(fn); row[Y].map(fn); row[Z].map(fn); row[W].map(fn); return *this;
    }

    void mat44::set(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3)
    { row[X] = v0; row[Y] = v1; row[Z] = v2; row[W] = v3; }

    void mat44::set(double arr[4][4])
    { 
      row[X][X] = arr[X][X]; row[X][Y] = arr[X][Y]; row[X][Z] = arr[X][Z]; row[X][W] = arr[X][W];
      row[Y][X] = arr[Y][X]; row[Y][Y] = arr[Y][Y]; row[Y][Z] = arr[Y][Z]; row[Y][W] = arr[Y][W];
      row[Z][X] = arr[Z][X]; row[Z][Y] = arr[Z][Y]; row[Z][Z] = arr[Z][Z]; row[Z][W] = arr[Z][W];
      row[W][X] = arr[W][X]; row[W][Y] = arr[W][Y]; row[W][Z] = arr[W][Z]; row[W][W] = arr[W][W];
    }

    void mat44::print( FILE *file, std::string name )
    {
      int i, j;
      fprintf( file, "%s:\n", name.c_str() );
      for( i = 0; i < 4; i++ )
	{
	  fprintf( file, "   " );
	  for( j = 0; j < 4; j++ )
	    {
	      fprintf( file, "%f  ", row[i][j] );
	    }
	  fprintf( file, "\n" );
	}
    }
    
    void mat44::swap_rows(int i, int j)
    {
      vec4 t;
      t = row[i]; row[i] = row[j]; row[j] = t;
    }

    void mat44::swap_cols(int i, int j)
    {
      float t; int k;
      for(k=0; k<4; k++ )
	{
	  t = row[k][i];
	  row[k][i] = row[k][j];
	  row[k][j] = t;
	}
    }

    mat44 operator - (const mat44& m)
    { return mat44(-m.row[X], -m.row[Y], -m.row[Z], -m.row[W]); }

    mat44 operator + (const mat44& m1, const mat44& m2)
    { return mat44(m1.row[X] + m2.row[X], m1.row[Y] + m2.row[Y], m1.row[Z] + m2.row[Z], m1.row[W] + m2.row[W]); }

    mat44 operator - (const mat44& m1, const mat44& m2)
    { return mat44(m1.row[X] - m2.row[X], m1.row[Y] - m2.row[Y], m1.row[Z] - m2.row[Z], m1.row[W] - m2.row[W]); }

    mat44 operator * (const mat44& m, const double d)
    { return mat44(m.row[X] * d, m.row[Y] * d, m.row[Z] * d, m.row[W] * d); }

    mat44 operator * (const double d, const mat44& m)
    { return mat44(m.row[X] * d, m.row[Y] * d, m.row[Z] * d, m.row[W] * d); }

    mat44 operator * (mat44& m1, mat44& m2)
    { 
      double c11 = (m1.row[X][X] * m2.row[X][X]) + (m1.row[X][Y] * m2.row[Y][X]) + (m1.row[X][Z] * m2.row[Z][X]) + (m1.row[X][W] * m2.row[W][X]);
      double c12 = (m1.row[X][X] * m2.row[X][Y]) + (m1.row[X][Y] * m2.row[Y][Y]) + (m1.row[X][Z] * m2.row[Z][Y]) + (m1.row[X][W] * m2.row[W][Y]);
      double c13 = (m1.row[X][X] * m2.row[X][Z]) + (m1.row[X][Y] * m2.row[Y][Z]) + (m1.row[X][Z] * m2.row[Z][Z]) + (m1.row[X][W] * m2.row[W][Z]);
      double c14 = (m1.row[X][X] * m2.row[X][W]) + (m1.row[X][Y] * m2.row[Y][W]) + (m1.row[X][Z] * m2.row[Z][W]) + (m1.row[X][W] * m2.row[W][W]);

      double c21 = (m1.row[Y][X] * m2.row[X][X]) + (m1.row[Y][Y] * m2.row[Y][X]) + (m1.row[Y][Z] * m2.row[Z][X]) + (m1.row[Y][W] * m2.row[W][X]);
      double c22 = (m1.row[Y][X] * m2.row[X][Y]) + (m1.row[Y][Y] * m2.row[Y][Y]) + (m1.row[Y][Z] * m2.row[Z][Y]) + (m1.row[Y][W] * m2.row[W][Y]);
      double c23 = (m1.row[Y][X] * m2.row[X][Z]) + (m1.row[Y][Y] * m2.row[Y][Z]) + (m1.row[Y][Z] * m2.row[Z][Z]) + (m1.row[Y][W] * m2.row[W][Z]);
      double c24 = (m1.row[Y][X] * m2.row[X][W]) + (m1.row[Y][Y] * m2.row[Y][W]) + (m1.row[Y][Z] * m2.row[Z][W]) + (m1.row[Y][W] * m2.row[W][W]);

      double c31 = (m1.row[Z][X] * m2.row[X][X]) + (m1.row[Z][Y] * m2.row[Y][X]) + (m1.row[Z][Z] * m2.row[Z][X]) + (m1.row[Z][W] * m2.row[W][X]);
      double c32 = (m1.row[Z][X] * m2.row[X][Y]) + (m1.row[Z][Y] * m2.row[Y][Y]) + (m1.row[Z][Z] * m2.row[Z][Y]) + (m1.row[Z][W] * m2.row[W][Y]);
      double c33 = (m1.row[Z][X] * m2.row[X][Z]) + (m1.row[Z][Y] * m2.row[Y][Z]) + (m1.row[Z][Z] * m2.row[Z][Z]) + (m1.row[Z][W] * m2.row[W][Z]);
      double c34 = (m1.row[Z][X] * m2.row[X][W]) + (m1.row[Z][Y] * m2.row[Y][W]) + (m1.row[Z][Z] * m2.row[Z][W]) + (m1.row[Z][W] * m2.row[W][W]);

      double c41 = (m1.row[W][X] * m2.row[X][X]) + (m1.row[W][Y] * m2.row[Y][X]) + (m1.row[W][Z] * m2.row[Z][X]) + (m1.row[W][W] * m2.row[W][X]);
      double c42 = (m1.row[W][X] * m2.row[X][Y]) + (m1.row[W][Y] * m2.row[Y][Y]) + (m1.row[W][Z] * m2.row[Z][Y]) + (m1.row[W][W] * m2.row[W][Y]);
      double c43 = (m1.row[W][X] * m2.row[X][Z]) + (m1.row[W][Y] * m2.row[Y][Z]) + (m1.row[W][Z] * m2.row[Z][Z]) + (m1.row[W][W] * m2.row[W][Z]);
      double c44 = (m1.row[W][X] * m2.row[X][W]) + (m1.row[W][Y] * m2.row[Y][W]) + (m1.row[W][Z] * m2.row[Z][W]) + (m1.row[W][W] * m2.row[W][W]);

      return mat44(c11, c12, c13, c14,
		   c21, c22, c23, c24,
		   c31, c32, c33, c34,
		   c41, c42, c43, c44);
    }

    mat44 operator / (const mat44& m, const double d)
    { return mat44(m.row[X] / d, m.row[Y] / d, m.row[Z] / d, m.row[W] / d); }

    bool operator == (const mat44& m1, const mat44& m2)
    { return ((m1.row[X] == m2.row[X]) && (m1.row[Y] == m2.row[Y]) 
	      && (m1.row[Z] == m2.row[Z]) && (m1.row[W] == m2.row[W])); }

    bool operator != (const mat44& m1, const mat44& m2)
    { return !(m1 == m2); }

    void swap(mat44& m1, mat44& m2)
    { mat44 temp(m1); m1 = m2; m2 = temp; }

    mat44 mat44::identity3D(void)
    { return mat44(vec4(1.0, 0.0, 0.0, 0.0),
		   vec4(0.0, 1.0, 0.0, 0.0),
		   vec4(0.0, 0.0, 1.0, 0.0),
		   vec4(0.0, 0.0, 0.0, 1.0)); }

    mat44 mat44::rotation3D(vec3& axis, double theta)
    {
      double thetaRad = theta * M_PI / 180.0;
      double c = cos(thetaRad);
      double s = sin(thetaRad);
      double t = 1.0 - c;

      axis.normalize();
      return mat44(vec4(t * axis[X] * axis[X] + c,
			t * axis[X] * axis[Y] - s * axis[Z],
			t * axis[X] * axis[Z] + s * axis[Y],
			0.0),
		   vec4(t * axis[X] * axis[Y] + s * axis[Z],
			t * axis[Y] * axis[Y] + c,
			t * axis[Y] * axis[Z] - s * axis[X],
			0.0),
		   vec4(t * axis[X] * axis[Z] - s * axis[Y],
			t * axis[Y] * axis[Z] + s * axis[X],
			t * axis[Z] * axis[Z] + c,
			0.0),
		   vec4(0.0, 0.0, 0.0, 1.0));
    }

    mat44 mat44::translation3D(double tx, double ty, double tz)
    { return mat44(vec4(1.0, 0.0, 0.0, tx),
		   vec4(0.0, 1.0, 0.0, ty),
		   vec4(0.0, 0.0, 1.0, tz),
		   vec4(0.0, 0.0, 0.0, 1.0)); }

    mat44 mat44::translation3D(vec3& v)
    { return mat44(vec4(1.0, 0.0, 0.0, v[X]),
		   vec4(0.0, 1.0, 0.0, v[Y]),
		   vec4(0.0, 0.0, 1.0, v[Z]),
		   vec4(0.0, 0.0, 0.0, 1.0)); }

    mat44 mat44::scaling3D(vec3& v)
    { return mat44(vec4(v[X], 0.0, 0.0, 0.0),
		   vec4(0.0, v[Y], 0.0, 0.0),
		   vec4(0.0, 0.0, v[Z], 0.0),
		   vec4(0.0, 0.0, 0.0, 1.0)); }
    
    mat44 mat44::perspective3D(const double d)
    {   return mat44(vec4(1.0, 0.0, 0.0, 0.0),
		    vec4(0.0, 1.0, 0.0, 0.0),
		    vec4(0.0, 0.0, 1.0, 0.0),
		    vec4(0.0, 0.0, 1.0/d, 0.0)); }

    //-----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
  }
}
