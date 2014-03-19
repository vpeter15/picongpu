/**
 * Copyright 2014 Richard Pausch
 *
 * This file is part of PIConGPU. 
 * 
 * PIConGPU is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * 
 * PIConGPU is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with PIConGPU.  
 * If not, see <http://www.gnu.org/licenses/>. 
 */ 

#pragma once

namespace picongpu
{

  /* several window functions behind namespaces: */


  namespace radWindowFunctionRectangle
  {
    struct radWindowFunction
    {
      HDINLINE float_X operator()(const float_X position_x, const float_X L_x) const
      {
	/* 1D Window function according to the rectangle window:
	 *
	 * f(x) = {1.0        : (-L_x/2 <= x <= +L_x/2 )
	 *        {0.0        : in any other case
	 * with x being position_x - L_x/2
	 *
	 * @param position_x = 1D position
	 * @param L_x        = length of the simulated area
	 *                     assuming that the simulation ranges
	 *                     from 0 to L_x in the choosen dimension
	 * @returns weighting factor to reduce ringing effects due to
         *          sharp spacial boundaries
	 */
	return float_X(math::abs(position_x- L_x)<=float_X(0.5*L_x));
      }
    };
  } /* end namespace: radWindowFunctionRectangle */
  


  namespace radWindowFunctionTriangle
  {
    struct radWindowFunction
    {
      HDINLINE float_X operator()(const float_X position_x, const float_X L_x) const
      {
	/* 1D Window function according to the triangle window:
	 *
	 * f(x) = {1+2x/L_x : (-L_x/2 <= x <= 0      )
	 *        {1-2x/L_x : (0      <= x <= +L_x/2 )
	 *        {0.0      : in any other case
	 * with x being position_x - L_x/2
	 *
	 * @param position_x = 1D position
	 * @param L_x        = length of the simulated area
	 *                     assuming that the simulation ranges
	 *                     from 0 to L_x in the choosen dimension
	 * @returns weighting factor to reduce ringing effects due to
         *          sharp spacial boundaries
	 */
	float_X x = position_x - 0.5*L_x;
	return float_X(math::abs(x)<=float_X(0.5*L_x))*(float_X(1.0)-float_X(2.0/L_x) * math::abs(x) );
      }
    };
  } /* end namespace: radWindowFunctionTriangle */



}  /* end namespace: picongpu */


