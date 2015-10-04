<?php
///////////////////////////////////////////////////////////
// File: MemberDb.inc
// Purpose: Interact with membership database
// Revision History:
// Date      Pgmr Descr
//  3/30/02  ddw  Created
//  4/ 6/02  ddw  Added MySQL interface
//  4/27/02  ddw  Made redundant inclusion protection
//                self-contained
//  4/29/02  ddw  Categories, subcategories in 
//                separate tables
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Class: cMemberDb
// Description: 
//   A database of members 
// Notes:
// - Tables include Member, Category, Subcategory
///////////////////////////////////////////////////////////

if (!IsSet($cMemberdbtype))
{
    // set variable to prevent this file being 
    // included more than once
    //
    global $cMemberdbtype;
    $cMemberdbtype=true;

    // include class definition of collaborator
    //
    include ("Member.inc");

    class cMemberDb
    {
        var $dblink;
        var $result;
    
        ///////////////////////////////////////////////////
        // Function: Constructor
        // Description:
        //   Set server members; connect to database
        ///////////////////////////////////////////////////
        function cMemberDb()
        {
            // dbinfo.inc has the host, user, and password data;
            // it's outside the public_html area to be (slightly
            // more) safe from inadvertent disclosure through
            // the web server
            // 
            include("../dbinfo.inc");

            // connect to server and select database
            //
            $this->dblink = @mysql_connect($host, $user, $passwd);
            @mysql_select_db($dbname, $this->dblink) or die(mysql_error());
        }

    
        ///////////////////////////////////////////////////
        // Function: GetCategoryList
        // Description:
        //   Retrieve list of categories
        // Notes:
        // - Sorted alphabetically
        ///////////////////////////////////////////////////
        function GetCategoryList(&$catList)
        {
            $query = "SELECT name 
                      FROM categories 
                      ORDER BY name";
            $this->result = mysql_query($query, $this->dblink) or 
                      die("Can't select record<br>".mysql_error()."<br>");
            $i=0;
            while ($row = mysql_fetch_array($this->result))
            {
                if (strlen($row[0])>0)
                {
                    $catList[$i++] = $row[0];
                }
		else
		    print("<b>no category<br>");  // shouldn't ever print this
            }
        }
    
        
        ///////////////////////////////////////////////////
        // Function: GetSubcategoryList
        // Description:
        //   Retrieve list of subcategories
        // Notes:
        // - Sorted alphabetically
        ///////////////////////////////////////////////////
        function GetSubcategoryList($theCat, &$subList)
        {
            $cid = $this->GetCategoryId($theCat);

            $query = "SELECT name 
                      FROM subcategories 
                      WHERE cid = '$cid'
                      ORDER BY name";
            $this->result = mysql_query($query, $this->dblink) or 
		      die("Can't select subcategory<br>".mysql_error()."<br>");
            $i=0;
            while ($row = mysql_fetch_array($this->result))
            {
                if (strlen($row[0])>0)
               {
                     $subList[$i++] = $row[0];
               }
		else
		    print("<b>no subcategory<br>");  // shouldn't ever print this
            }
        }
    
        
        ///////////////////////////////////////////////////
        // Function: SelectByName
        // Description:
        //   Retrieve member records by business name
        ///////////////////////////////////////////////////
        function SelectByName($theName, &$mbrList)
        {
            $searchval = addslashes($theName);
            $query = "SELECT * 
                      FROM members 
                      WHERE company='$searchval'
                      ORDER BY company";
            $this->result = mysql_query($query, $this->dblink) or 
                      die("Can't select record<br>");
            $this->ParseRecords($mbrList);
        }
        
        ///////////////////////////////////////////////////
        // Function: SelectByInitial
        // Description:
        //   Retrieve member records by first character
        //   of business name
        // Notes:
        // - Treats "The " as insignificant except in
        //   searches for initial 'T'. For example,
        //   company named "The Widget Works" will
        //   show up in a search for 'W'.
        ///////////////////////////////////////////////////
        function SelectByInitial($theInit, &$mbrList)
        {
            $query = "SELECT * 
                      FROM members 
                      WHERE (company REGEXP '^$theInit.*') 
                         || (company REGEXP '^The $theInit.*')
                      ORDER BY company";
            $this->result = mysql_query($query, $this->dblink) or 
                      die("Can't select record<br>");
            $this->ParseRecords($mbrList);
        }
        
        ///////////////////////////////////////////////////
        // Function: SelectByCategory
        // Description:
        //   Retrieve member records by business category
        ///////////////////////////////////////////////////
        function SelectByCategory($theCat, &$mbrList)
        {
            $cid = $this->GetCategoryId($theCat);
            $query = "SELECT * 
                      FROM members 
                      WHERE category='$cid'
                      ORDER BY company";
            $this->result = mysql_query($query, $this->dblink) or 
                      die("Can't select record<br>");
            $this->ParseRecords($mbrList);
        }
        
        ///////////////////////////////////////////////////
        // Function: SelectBySubcategory
        // Description:
        //   Retrieve member records by business 
        //   subcategory
        ///////////////////////////////////////////////////
        function SelectBySubcategory($theSubcat, &$mbrList)
        {
            $sid = $this->GetSubcategoryId($theSubcat);
            $query = "SELECT * 
                      FROM members 
                      WHERE subcategory ='$sid'
                      ORDER BY company";
            $this->result = mysql_query($query, $this->dblink) or 
                      die("Can't select record<br>");
            $this->ParseRecords($mbrList);
        }
    
    
        ///////////////////////////////////////////////////
        // Function: ParseRecords
        // Description:
        //   Retrieve member data from database record(s) 
        // Notes:
        // - Depends on the order of fields in the
        //   database (and the DB schema, obviously)
        ///////////////////////////////////////////////////
        function ParseRecords(&$mbrList)
        {
            // TODO: Purge any records from the member list
            //

            $i=0;
            while ($row = mysql_fetch_array($this->result))
            {
                $theMember = new cMember;
                $theMember->memid       = $row[0];
                $theMember->company     = stripslashes($row[1]);
                $theMember->status      = $row[2];
                $theMember->address     = stripslashes($row[3]);
                $theMember->address2    = stripslashes($row[4]);
                $theMember->city        = stripslashes($row[5]);
                $theMember->state       = $row[6];
                $theMember->zip         = $row[7];
                $theMember->phone       = $row[8];
                $theMember->extn        = $row[9];
                $theMember->fax         = $row[10];
                $theMember->website     = $row[11];
                $theMember->email       = $row[12];
                $theMember->description = stripslashes($row[13]);
                $theMember->firstname   = stripslashes($row[14]);
                $theMember->lastname    = stripslashes($row[15]);
                $theMember->repphone    = $row[16];
                $theMember->repextn     = $row[17];
                $theMember->repfax      = $row[18];
                $theMember->repemail    = $row[19];
                $theMember->category    = $this->GetCategoryName($row[21]);
                $theMember->subcategory = 
		    $this->GetSubcategoryName($row[20]);
                $mbrList[$i++] = $theMember;
            }
        } // end ParseRecords()

        ///////////////////////////////////////////////////
        // Function: GetCategoryId
        // Description:
        //   Given category name, retrieve category ID
        // Notes:
        // - 
        ///////////////////////////////////////////////////
        function GetCategoryId($name)
        {
            $name = addslashes($name);
            $query = "SELECT id 
                      FROM categories
                      WHERE name = '$name'";
	    $result = mysql_query($query, $this->dblink) or
		      die("Can't select category<br>".mysql_error()."<br>");
            $row = mysql_fetch_array($result);
            $cid = $row[0];

            return $cid;
        }

        ///////////////////////////////////////////////////
        // Function: GetCategoryName
        // Description:
        //   Given category id, retrieve category name
        // Notes:
        // - 
        ///////////////////////////////////////////////////
        function GetCategoryName($id)
        {
            $query = "SELECT name 
                      FROM categories
                      WHERE id = '$id'";
	    $result = mysql_query($query, $this->dblink) or
		      die("Can't select category<br>".mysql_error()."<br>");
            $row = mysql_fetch_array($result);
            $name = stripslashes($row[0]);

            return($name);
        }

        ///////////////////////////////////////////////////
        // Function: GetSubcategoryId
        // Description:
        //   Given subcategory name, retrieve subcategory ID
        // Notes:
        // - 
        ///////////////////////////////////////////////////
        function GetSubcategoryId($name)
        {
            $theName = addslashes($name);
            $query = "SELECT id 
                      FROM subcategories
                      WHERE name = '$theName'";
	    $result = mysql_query($query, $this->dblink) or
		      die("Can't select category<br>".mysql_error()."<br>");
            $row = mysql_fetch_array($result);
            $sid = $row[0];
            return $sid;
        }

        ///////////////////////////////////////////////////
        // Function: GetSubcategoryName
        // Description:
        //   Given subcategory id, retrieve subcategory name
        // Notes:
        // - 
        ///////////////////////////////////////////////////
        function GetSubcategoryName($sid)
        {
            $query = "SELECT name 
                      FROM subcategories
                      WHERE id = '$sid'";
	    $result = mysql_query($query, $this->dblink) or
		      die("Can't select category<br>".mysql_error()."<br>");
            $row = mysql_fetch_array($result);
            $name = stripslashes($row[0]);

            return($name);
        }

    } // end cMemberDb class definition

} // end if not included before
?>
