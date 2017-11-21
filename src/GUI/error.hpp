/*!
  \file error.hpp
  \brief This file contains the error class definitions.
*/


#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>

 //! The namespace shared by all support classes that form libUtil
namespace util
{
  //! The namespace shared by error classes in libUtil
  namespace common
  {
    //! The general error class
    /*! This is a singleton class and hence an object of this
     *  class cannot be directly instantiated. Only one of its
     *  derived classes can be directly instantiated. The class
     *  consists of the error message, a virtual general error 
     *  processing method, and static error handlers.
     */     
    class error
    {
    protected:
      //! The error message
      std::string error_msg;
      //! Constructor
      error(char const *_error_msg):error_msg(_error_msg) { }

    public:
      //! Destructor
      virtual ~error() { }

      //! Error processing method. See derived classes for details
      virtual void process() const = 0;

      //! The overloaded string type casting operator 
      virtual operator std::string() const 
      {
	return error_msg;
      }

      /*! This error handler propogates the error to the next higher
       *  level in the program hierarchy.
       */
      static void propogate_error(error const *e);

      /*! This error handler absorbs the error and processes it as
       *  is declared in the processing method
       */
      static void absorb_error(error const *e);

      /*! This error handler causes the execution to halt,
       *  irrespective of the type of the error
       */
      static void halt_on_error(error const *e);

      /*! This error handler propogates warning_errors,
       * and halts on fatal errors.
       */
      static void handle_error(error const *e);

      //! The overloaded << operator
      friend std::ostream &operator<<(std::ostream &str, error const &e)
      {
	return str << e.operator std::string();
      }
    };

    //! The fatal error class
    /*! If such an error should occur the program execution should halt
     */
    class fatal_error : public error
    {
    public:
      //! Constructor
      fatal_error(char const *_error_msg):error(_error_msg) { }

      //! Error processing method
      void process() const
      {
	exit(1);
      }
    };

    //! The warning error class
    /*! If such an error will cause a warning to be issued to the user
     */
    class warning_error : public error
    {
    public:
      //! Constructor
      warning_error(char const *_error_msg):error(_error_msg) { }

      //! Error processing method
      void process() const
      {

      }
    };
  }
}

#endif
