// Premium tax.
//
// Copyright (C) 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011 Gregory W. Chicares.
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

#ifndef premium_tax_hpp
#define premium_tax_hpp

#include "config.hpp"

#include "mc_enum_type_enums.hpp" // mcenum_state
#include "obstruct_slicing.hpp"
#include "uncopyable_lmi.hpp"

class product_database;
class stratified_charges;

class premium_tax
  :        private lmi::uncopyable <premium_tax>
  ,virtual private obstruct_slicing<premium_tax>
{
  public:
    premium_tax
        (mcenum_state              premium_tax_state
        ,mcenum_state              state_of_domicile
        ,bool                      amortize_premium_load
        ,product_database   const& database
        ,stratified_charges const& strata
        );
    ~premium_tax();

    double levy_rate                          () const;
    double load_rate                          () const;
    double least_load_rate                    () const;
    double domiciliary_load_rate              () const;
    bool   PremiumTaxLoadIsTiered() const; ////
    bool   load_is_tiered_in_premium_tax_state() const;
    bool   load_is_tiered_in_state_of_domicile() const;
    bool   premium_tax_is_retaliatory         () const;

  private:
    void set_parameters
        (product_database   const&
        ,stratified_charges const&
        );
    void test_consistency() const;

    // Ctor value-arguments.
    mcenum_state premium_tax_state_;
    mcenum_state state_of_domicile_;
    bool         amortize_premium_load_;

    double levy_rate_;
    double load_rate_;
    double least_load_rate_;
    double domiciliary_load_rate_;
    bool   load_is_tiered_in_premium_tax_state_;
    bool   load_is_tiered_in_state_of_domicile_;
    bool   premium_tax_is_retaliatory_;
};

bool premium_tax_is_retaliatory
    (mcenum_state premium_tax_state
    ,mcenum_state state_of_domicile
    );

double lowest_premium_tax_load
    (mcenum_state              premium_tax_state
    ,mcenum_state              state_of_domicile
    ,bool                      amortize_premium_load
    ,product_database   const& db
    ,stratified_charges const& stratified
    );

inline double premium_tax::levy_rate() const
{
    return levy_rate_;
}

inline double premium_tax::load_rate() const
{
    return load_rate_;
}

inline double premium_tax::least_load_rate() const
{
    return least_load_rate_;
}

inline double premium_tax::domiciliary_load_rate() const
{
    return domiciliary_load_rate_;
}

//// Identical to the more-appropriately-named load_is_tiered_in_premium_tax_state().
inline bool premium_tax::PremiumTaxLoadIsTiered() const ////
{
    return load_is_tiered_in_premium_tax_state_;
}

inline bool premium_tax::load_is_tiered_in_premium_tax_state() const
{
    return load_is_tiered_in_premium_tax_state_;
}

inline bool premium_tax::load_is_tiered_in_state_of_domicile() const
{
    return load_is_tiered_in_state_of_domicile_;
}

inline bool premium_tax::premium_tax_is_retaliatory() const
{
    return premium_tax_is_retaliatory_;
}

#endif // premium_tax_hpp
