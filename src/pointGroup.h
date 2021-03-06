/* Copyright 2011-2014 Kyle Michel, Logan Ward, Christopher Wolverton
 *
 * Contact: Kyle Michel (kylemichel@gmail.com)
 *			Logan Ward (LoganWard2012@u.northwestern.edu)
 *
 *
 * This file is part of Mint.
 *
 * Mint is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Mint is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with Mint.  If not, see
 * <http://www.gnu.org/licenses/>.
 */



#ifndef POINTGROUP_H
#define POINTGROUP_H



#include "num.h"
#include "iso.h"
#include "symmetry.h"
#include "text.h"
#include "list.h"



// Class to store point group information
class PointGroup
{

	// variables
	bool _centric;
	int _number;
	int _order;
	int _laueGroup;
	CenteringType _centeringType;
	CrystalSystem _crystalSystem;
	Word _schoenflies;
	Word _hermannMauguinShort;
	Word _hermannMauguin;
	Matrix3D _redToConv;
	Matrix3D _unitToConv;
	OList<SymmetryOperation> _convSymmetry;
	
	// General functions
	void setByNumber(int number);
	void setProperties(int number, bool centric, int order, const char* schoe, const char* hmShort, const char* hm, \
		int laueGroup, CrystalSystem crystalSystem);
	
	// Helper functions to get point group from name
	static int getNumberFromName(const Word& name);
	static bool compareName(const Word& name, const char* schoe, const char* hmShort, const char* hmFull);
	
	// Helper functions to get point group of structure
	int getNumberFromOperations(const Symmetry& symmetry);
	void setRedToConv(const ISO& reducedCell, const Symmetry& symmetry);
	static double getAngle(const Vector3D& vec1, const Vector3D& vec2, const Basis& basis);
	void setConvSymmetry(const Symmetry& symmetry);
	
public:
	
	// Constructor
	PointGroup()						{}
	PointGroup(const PointGroup& copy)	{ *this = copy; }
	
	// Setup functions
	void clear();
	PointGroup& operator= (const PointGroup& rhs);
	
	// Set point group by name or symmetry operations
	bool set(const Word& name, bool quitIfNotFound = true);
	void set(const ISO& iso, double tol);
	
	// Print functions
	void print() const;
	static void printAll();
	
	// Static member functions
	static bool isPointGroup(const Word& name)	{ return (getNumberFromName(name) != 0); }
	static bool findTranslation(const OList<Vector3D >& centVecs, double val1, double val2, double val3);
	
	// Access functions
	bool centric() const									{ return _centric; }
	int number() const										{ return _number; }
	int order() const										{ return _order; }
	int laueGroup() const									{ return _laueGroup; }
	CenteringType centeringType() const						{ return _centeringType; }
	CrystalSystem crystalSystem() const						{ return _crystalSystem; }
	const Word& schoenflies() const							{ return _schoenflies; }
	const Word& hermannMauguinShort() const					{ return _hermannMauguinShort; }
	const Word& hermannMauguin() const						{ return _hermannMauguin; }
	const Matrix3D& redToConv() const						{ return _redToConv; }
	const Matrix3D& unitToConv() const						{ return _unitToConv; }
	const OList<SymmetryOperation>& convSymmetry() const	{ return _convSymmetry; }
};



#endif
