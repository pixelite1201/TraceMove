#include "error.hpp"

namespace util
{
  namespace common
  {
    void error::propogate_error(error const *e)
    {
      throw;
    }

    void error::absorb_error(error const *e)
    {
      std::cerr << *e << std::endl; 
      delete e;
    }

    void error::halt_on_error(error const *e)
    {
      std::cerr << *e << std::endl; 
      delete e;
      exit(-1);
    }

    void error::handle_error(error const *e)
    {
      // show the plain-text information
      std::cerr << *e << std::endl; 

      if(dynamic_cast<warning_error const *>(e))
        {
	  // Process a message or a warning
	  e->process();              
	  delete e;
        }
      else
	// Pass on other types of Exceptions
	throw;
    }
  }
}
