#include "IpIpoptApplication.hpp"

#include "IpoptAdapter.hpp"

//use HiOp's Example4 - mixed dense-sparse QP
#include "nlpMDSForm_ex4.hpp"

#include <iostream>

using namespace Ipopt;

// Example of how to use IpoptAdapter to solve HiOP-specified problems with Ipopt

int main(int    argv, char** argc)
{
  //instantiate a HiOp problem 
  Ex4 hiopNlp(12);
  //create 

  // Create a new instance of the Ipopt nlp
  //  (use a SmartPtr, not raw)
  SmartPtr<TNLP> mynlp = new hiopMDS2IpoptTNLP(&hiopNlp);
  
  // Create a new instance of IpoptApplication
  //  (use a SmartPtr, not raw)
  // We are using the factory, since this allows us to compile this
  // example with an Ipopt Windows DLL
  SmartPtr<IpoptApplication> app = IpoptApplicationFactory();

  // Change some options
  // Note: The following choices are only examples, they might not be
  //       suitable for your optimization problem.
  app->Options()->SetNumericValue("tol", 1e-7);
  app->Options()->SetStringValue("mu_strategy", "adaptive");
  app->Options()->SetStringValue("output_file", "ipopt.out");
  
  // Initialize the IpoptApplication and process the options
  ApplicationReturnStatus status;
  status = app->Initialize();
  if( status != Solve_Succeeded ) {
      std::cout << std::endl << std::endl << "*** Error during initialization!" << std::endl;
      return (int) status;
    }
  
  // Ask Ipopt to solve the problem
   status = app->OptimizeTNLP(mynlp);
   
   if( status == Solve_Succeeded ) {
     std::cout << std::endl << std::endl << "*** The problem solved!" << std::endl;
   } else  {
     std::cout << std::endl << std::endl << "*** The problem FAILED!" << std::endl;
   }
   
   // As the SmartPtrs go out of scope, the reference count
   // will be decremented and the objects will automatically
   // be deleted.
   
   return (int) status;
}