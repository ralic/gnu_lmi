// Main file for automated testing of wx interface.
//
// Copyright (C) 2014 Gregory W. Chicares.
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

// $Id$

#ifdef __BORLANDC__
#   include "pchfile.hpp"
#   pragma hdrstop
#endif

#include "test_tools.hpp"

#include "skeleton.hpp"

#include "fenv_guard.hpp"
#include "fenv_lmi.hpp"
#include "handle_exceptions.hpp"
#include "main_common.hpp"
#include "msw_workarounds.hpp"
#include "path_utility.hpp"

#include <wx/defs.h>

class SkeletonTest;
DECLARE_APP(SkeletonTest)

class application_test
{
  public:
    static void test()
        {
        }
};

// Application to drive the tests
class SkeletonTest : public Skeleton
{
  public:
    SkeletonTest() {}
    virtual bool OnInit();

  private:
    void RunTheTests();
};

IMPLEMENT_APP_NO_MAIN(SkeletonTest)
IMPLEMENT_WX_THEME_SUPPORT

bool SkeletonTest::OnInit()
{
    if(!Skeleton::OnInit())
        return false;

    // Run the tests at idle time, when the main loop is running, in order to
    // do it in as realistic conditions as possible.
    CallAfter(&SkeletonTest::RunTheTests);

    return true;
}

void SkeletonTest::RunTheTests()
{
    application_test::test();
    ExitMainLoop();
}

int test_main(int argc, char* argv[])
{
    initialize_application();
    initialize_filesystem();
#ifdef LMI_MSW
    MswDllPreloader::instance().PreloadDesignatedDlls();
#endif
    return wxEntry(argc, argv);
}
