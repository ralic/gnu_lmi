// xml document for MEC testing.
//
// Copyright (C) 2009 Gregory W. Chicares.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
//
// http://savannah.nongnu.org/projects/lmi
// email: <gchicares@sbcglobal.net>
// snail: Chicares, 186 Belle Woods Drive, Glastonbury CT 06033, USA

// $Id: mec_xml_document.cpp,v 1.1 2009-06-27 17:47:39 chicares Exp $

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif // __BORLANDC__

#include "mec_xml_document.hpp"

#include "assert_lmi.hpp"
#include "mec_input.hpp"
#include "xml_lmi.hpp"

#include <xmlwrapp/nodes_view.h>

#include <istream>
#include <ostream>

//============================================================================
mec_xml_document::mec_xml_document()
    :input_data_(new mec_input)
{
}

//============================================================================
mec_xml_document::mec_xml_document(mec_input const& z)
    :input_data_(new mec_input(z))
{
}

//============================================================================
mec_xml_document::~mec_xml_document()
{
}

//============================================================================
std::string mec_xml_document::xml_root_name() const
{
    return "mec_xml_document";
}

//============================================================================
void mec_xml_document::parse(xml::element const& root)
{
    xml::const_nodes_view const elements(root.elements());
    LMI_ASSERT(!elements.empty());
    xml::const_nodes_view::const_iterator i(elements.begin());
    *i >> *input_data_;
    // XMLWRAPP !! It would be better to have operator+(int) in the
    // iterator class, and to write this check above as
    //   LMI_ASSERT(elements.end() == 1 + i);
    LMI_ASSERT(elements.end() == ++i);
}

//============================================================================
void mec_xml_document::read(std::istream const& is)
{
    xml_lmi::dom_parser parser(is);
    parse(parser.root_node(xml_root_name()));
}

//============================================================================
void mec_xml_document::write(std::ostream& os)
{
    xml_lmi::xml_document document(xml_root_name());
    xml::element& root = document.root_node();
    root << *input_data_;
    os << document;
}
