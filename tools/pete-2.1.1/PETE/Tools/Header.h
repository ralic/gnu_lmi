// -*- C++ -*-
//
// Copyright (C) 1998, 1999, 2000, 2002  Los Alamos National Laboratory,
// Copyright (C) 1998, 1999, 2000, 2002  CodeSourcery, LLC
//
// This file is part of FreePOOMA.
//
// FreePOOMA is free software; you can redistribute it and/or modify it
// under the terms of the Expat license.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the Expat
// license for more details.
//
// You should have received a copy of the Expat license along with
// FreePOOMA; see the file LICENSE.
//

#ifndef PETE_TOOLS_HEADER_H
#define PETE_TOOLS_HEADER_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::endl;

template<class OSTR>
void printHeader(OSTR& ostr,const string& includeGuard,
		 const vector<string>& files,
		 bool lanlBoilerplate,const string& prefix)
{
  string fileList = "";
  typename vector<string>::const_iterator i;
  for (i=files.begin(); i!=files.end(); ++i)
    {
      fileList += "// " + (*i) + "\n";
    }
  if (lanlBoilerplate)
    {
      ostr
	<< "// -*- C++ -*-" << endl
	<< "// ACL:license" << endl
	<< "// ACL:license" << endl
	<< endl;
    }
  if (includeGuard != string(""))
    {
      ostr
	<< "#ifndef " << includeGuard << endl
	<< "#define " << includeGuard << endl
	<< endl;
    }
  ostr
    << "///////////////////////////////////////////////////////////////////////////////"
    << endl
    << "//" << endl
    << "// WARNING: THIS FILE WAS GENERATED AUTOMATICALLY!" << endl
    << "// YOU SHOULD MODIFY THE INPUT FILES INSTEAD OF CHANGING THIS FILE DIRECTLY!"
    << endl
    << "//" << endl
    << "// THE FOLLOWING INPUT FILES WERE USED TO MAKE THIS FILE:" << endl
    << "//" << endl
    << fileList
    << "//" << endl
    << "///////////////////////////////////////////////////////////////////////////////"
    << endl
    << endl;

  if (prefix.size() != 0)
    ostr << prefix << endl << endl;
}

template<class OSTR>
void printFooter(OSTR& ostr,const string& includeGuard,
		 bool lanlBoilerplate,const string& suffix)
{
  ostr
    << endl;
  if (suffix.size() != 0)
    ostr << suffix << endl << endl;
  if (includeGuard != string(""))
    {
      ostr
	<< "#endif // " << includeGuard << endl
	<< endl;
    }
  if (lanlBoilerplate)
    {
      ostr
	<< "// ACL:rcsinfo" << endl
	<< "// ----------------------------------------------------------------------"
	<< endl
	<< "// $RCSfile: Header.h,v $   $Author: chicares $" << endl
	<< "// $Revision: 1.2 $   $Date: 2008-09-07 17:38:20 $" << endl
	<< "// ----------------------------------------------------------------------"
	<< endl
	<< "// ACL:rcsinfo" << endl;
    }
}

#endif // PETE_TOOLS_HEADER_H

// ACL:rcsinfo
// ----------------------------------------------------------------------
// $RCSfile: Header.h,v $   $Author: chicares $
// $Revision: 1.2 $   $Date: 2008-09-07 17:38:20 $
// ----------------------------------------------------------------------
// ACL:rcsinfo