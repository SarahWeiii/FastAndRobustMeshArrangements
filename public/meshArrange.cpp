/*****************************************************************************************
 *              MIT License                                                              *
 *                                                                                       *
 * Copyright (c) 2020 Gianmarco Cherchi, Marco Livesu, Riccardo Scateni e Marco Attene   *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION     *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                *
 *                                                                                       *
 * Authors:                                                                              *
 *      Gianmarco Cherchi (g.cherchi@unica.it)                                           *
 *      https://people.unica.it/gianmarcocherchi/                                        *
 *                                                                                       *
 *      Marco Livesu (marco.livesu@ge.imati.cnr.it)                                      *
 *      http://pers.ge.imati.cnr.it/livesu/                                              *
 *                                                                                       *
 *      Riccardo Scateni (riccardo@unica.it)                                             *
 *      https://people.unica.it/riccardoscateni/                                         *
 *                                                                                       *
 *      Marco Attene (marco.attene@ge.imati.cnr.it)                                      *
 *      https://www.cnr.it/en/people/marco.attene/                                       *
 *                                                                                       *
 * ***************************************************************************************/

#ifdef _MSC_VER         // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0 // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX        // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif

#include <iostream>

#include "solve_intersections.h"
#include "meshArrange.h"

namespace meshArrange
{
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    Mesh intersectionRemoval(Mesh const &input)
    {
        std::vector<double> in_coords, out_coords;
        std::vector<uint> in_tris, out_tris;
        std::vector<genericPoint *> gen_points;
        point_arena arena;

        Mesh output;

        for (int i = 0; i < input.vertices.size(); i++)
        {
            in_coords.push_back(input.vertices[i][0]);
            in_coords.push_back(input.vertices[i][1]);
            in_coords.push_back(input.vertices[i][2]);
        }
        for (int i = 0; i < input.indices.size(); i++)
        {
            in_tris.push_back(input.indices[i][0]);
            in_tris.push_back(input.indices[i][1]);
            in_tris.push_back(input.indices[i][2]);
        }

        /*-------------------------------------------------------------------
         * There are 4 versions of the solveIntersections function. Please
         * refer to the solve_intersections.h file to see how to use them. */
        solveIntersections(in_coords, in_tris, arena, gen_points, out_tris);
        computeApproximateCoordinates(gen_points, out_coords);

        for (int i = 0; i < out_coords.size(); i += 3)
        {
            std::array<double, 3> vertex;
            vertex[0] = out_coords[i];
            vertex[1] = out_coords[i + 1];
            vertex[2] = out_coords[i + 2];
            output.vertices.push_back(vertex);
        }
        for (int i = 0; i < out_tris.size(); i += 3)
        {
            std::array<int, 3> triangle;
            triangle[0] = out_tris[i];
            triangle[1] = out_tris[i + 1];
            triangle[2] = out_tris[i + 2];
            output.indices.push_back(triangle);
        }

        return output;
    }

} // namespace meshArrange
