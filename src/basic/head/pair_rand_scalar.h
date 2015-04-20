/*
 * This file is part of the SYMPLER package.
 * https://github.com/kauzlari/sympler
 *
 * Copyright 2002-2015, 
 * David Kauzlaric <david.kauzlaric@frias.uni-freiburg.de>,
 * and others authors stated in the AUTHORS file in the top-level 
 * source directory.
 *
 * SYMPLER is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SYMPLER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SYMPLER.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Please cite the research papers on SYMPLER in your own publications. 
 * Check out the PUBLICATIONS file in the top-level source directory.
 *
 * You are very welcome to contribute extensions to the code. Please do 
 * so by making a pull request on https://github.com/kauzlari/sympler
 * 
 */


#ifndef __PAIR_RAND_SCALAR_H_
#define __PAIR_RAND_SCALAR_H_

#include "pair_rand_arbitrary.h"

using namespace std;

/*! Module for calculation of a random scalar Symbol pairFactor*ranScalar stored per non-bonded pair of particles, where pairFactor is a scalar user-defined runtime-compiled expression and ranScalar is a Gaussian random number with zero mean and unit variance. Note that you can modify the mean and variance through a suitable pairFactor. */

class PairRandScalar : public PairRandArbitrary {

 protected:
  
  /*!
   * For copying an instance of this class
   */  
  virtual ValCalculatorPair* copyMySelf() {
    return new PairRandScalar(*this);
  }
  /*!
   * Initialise the property list
   */
  virtual void init();

 public:
  
  /*!
   * Old, usually not used constructor
   */
  PairRandScalar(string symbol);

  /*!
   * Constructor for Node hierarchy
   */
  PairRandScalar(/*Node*/Simulation* parent);
  
  /*!
   * Destructor//
   */
  virtual ~PairRandScalar();
    
  
  /*Compute the user defined expression for pair pD*/
#ifdef _OPENMP
  virtual void compute(Pairdist* dis, int threadNum) {
    // does the same as in serial mode at the moment; 
    // it writes into pairs, so should work
    compute(dis);
  }
#endif
  virtual void compute(Pairdist* dis) {
    if (dis->abs() < m_cutoff) {

      double& scalar =  dis->tag.doubleByOffset(m_slot);
      
      // compute the expression for the pair function
      m_function(&scalar, dis);

      // multiply Gaussian random number
      scalar *=  m_rng.normal(1);

    }    
  }
  
};

#endif 
