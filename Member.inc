<?php
///////////////////////////////////////////////////////////
// File: Member.inc
// Purpose: Define class cMember, a POD class for 
//          member attributes
// Revision History:
// Date      Pgmr Descr
//  3/30/02  ddw  Created
//  4/ 6/02  ddw  Added data items; changed some names
//  4/27/02  ddw  Made redundant inclusion protection
//                self-contained
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Class: cMember
// Description: 
//   A member (record) 
// Notes:
// - TO DO: prune the members down some when
//          we know for certain which data items
//          we need and which we don't
///////////////////////////////////////////////////////////

if (!IsSet($cMembertype))
{
    // set variable to prevent this file
    // being included more than once
    // 
    global $cMembertype;
    $cMembertype=true;

    class cMember
    {
        // (class) members correspond to each
        // field of the members table in the
        // database
        //
        var $memid;
        var $company;
        var $category;
        var $subcategory;
        var $status;
        var $address;
        var $address2;
        var $city;
        var $state;
        var $zip;
        var $phone;
        var $extn;
        var $fax;
        var $website;
        var $email;
        var $description;
        var $firstname;
        var $lastname;
        var $repphone;
        var $repextn;
        var $repfax;
        var $repemail;
    
        function Printself()
        {
            echo "<p>Member Data:<br>
                memid=$this->memid<br>
                member=$this->company<br>
                category=$this->category<br>
                subcategory=$this->subcategory<br>
                status=$this->status<br>
                address=$this->address<br>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                $this->address2<br>
                city, state zip=$this->city,
                $this->state &nbsp;
                $this->zip<br>
                phone=$this->phone ext $this->extn<br>
                fax=$this->fax<br>
                website=$this->website<br>
                email=$this->email<br>
                description=$this->description<br>
                contact: $this->firstname $this->lastname<br>
                phone: $this->repphone ext $this->repextn<br>
                fax: $this->repfax<br>
                email: $this->repemail<br>
                <p>";
        } // end Printself()

    } // end cMember class definition

} // end if not included before
?>
