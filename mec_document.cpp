// Document class for MEC testing.
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

// $Id: mec_document.cpp,v 1.1 2009-06-27 17:47:39 chicares Exp $

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif

#include "mec_document.hpp"
#include "view_ex.tpp"

#include "alert.hpp"
#include "mec_view.hpp"
#include "miscellany.hpp"

#include <fstream>

IMPLEMENT_DYNAMIC_CLASS(mec_document, wxDocument)

mec_document::mec_document()
    :wxDocument()
{
}

mec_document::~mec_document()
{
}

mec_view& mec_document::PredominantView() const
{
    return ::PredominantView<mec_view>(*this);
}

wxHtmlWindow& mec_document::PredominantViewWindow() const
{
    return ::PredominantViewWindow<mec_view,wxHtmlWindow>
        (*this
        ,&mec_view::html_window_
        );
}

/// See the documentation for similar class IllustrationDocument.

bool mec_document::OnCreate(wxString const& filename, long int flags)
{
    if(wxDOC_NEW & flags)
        {
        ; // Do nothing.
        }
    else
        {
        std::ifstream ifs(filename.c_str());
        if(!ifs)
            {
            warning()
                << "Unable to read file '"
                << filename
                << "'."
                << LMI_FLUSH
                ;
            return false;
            }
        doc_.read(ifs);
        }

    return wxDocument::OnCreate(filename, flags);
}

#if !wxCHECK_VERSION(2,9,0)
/// See the documentation for similar class IllustrationDocument.

bool mec_document::OnNewDocument()
{
    Modify(true);
    SetDocumentSaved(false);

#if wxCHECK_VERSION(2,8,8)
    wxString const name = GetDocumentManager()->MakeNewDocumentName();
#else  // !wxCHECK_VERSION(2,8,8)
    wxString name;
    GetDocumentManager()->MakeDefaultName(name);
#endif // !wxCHECK_VERSION(2,8,8)
    SetTitle(name);
    SetFilename(name, true);

    return true;
}
#endif // !wxCHECK_VERSION(2,9,0)

/// See the documentation for similar class IllustrationDocument.

bool mec_document::DoOpenDocument(wxString const& filename)
{
    return true;
}

/// See the documentation for similar class IllustrationDocument.

bool mec_document::DoSaveDocument(wxString const& filename)
{
    std::ofstream ofs(filename.c_str(), ios_out_trunc_binary());
    doc_.write(ofs);
    if(!ofs)
        {
        warning() << "Unable to save '" << filename << "'." << LMI_FLUSH;
        return false;
        }

    status() << "Saved '" << filename << "'." << std::flush;
    return true;
}
