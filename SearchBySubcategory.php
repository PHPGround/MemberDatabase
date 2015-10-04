<!--
    SearchBySubcategory.php
    * Example use of Member Database library
    * Could be used as a template for a subcategory search page
-->
<html>
<head>
<title>&lt;Your Organization Here&gt; - Member Business Directory</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>
<body>
<h3>&lt;Organization&gt; Member Directory</h3>
<?php
    $subcategory = $_GET["subcategory"];
    if(IsSet($subcategory))
    {
        if (!IsSet($cMembertype))
           include ("Member.inc");
        if (!IsSet($cMemberdbtype))
            include ("MemberDb.inc");
        include ("DeeDubUtils.inc");
        $theDb = new cMemberDb;

        $mbrlist = array();
        $theDb->SelectBySubcategory($subcategory, $mbrlist);

        print("<p>Members in the subcategory $subcategory:</p>");
        print("<table>");

        for ($i=0; $i<sizeof($mbrlist); $i++)
        {
            $theMember = $mbrlist[$i];

            // format phone numbers for display
            $displayPhone = formatPhone($theMember->phone, $PAREN_STYLE);
            $displayFax = formatPhone($theMember->fax, $PAREN_STYLE);

            print("<tr><td class=\"memberlabel\">Company:</td><td class=\"memberdata\">$theMember->company</td></tr>");
            print("<tr><td class=\"memberlabel\">Category:</td><td class=\"memberdata\">$theMember->category, $theMember->subcategory</td></tr>");
            print("<tr><td class=\"memberlabel\">Address:</td><td class=\"memberdata\">$theMember->address<br>$theMember->city, $theMember->state $theMember->zip</td></tr>");
            print("<tr><td class=\"memberlabel\">Contact:</td><td class=\"memberdata\">$theMember->firstname $theMember->lastname</td></tr>");
            print("<tr><td class=\"memberlabel\">Phone:</td><td class=\"memberdata\">$displayPhone Ext: $theMember->extn</td></tr>");
            print("<tr><td class=\"memberlabel\">Fax:</td><td class=\"memberdata\">$displayFax</td></tr>");
            print("<tr><td class=\"memberlabel\">Website:</td><td class=\"memberdata\"><a href=\"http://$theMember->website\" target=\"_blank\">$theMember->website</a></td></tr>");
            print("<tr><td class=\"memberlabel\">Email:</td><td class=\"memberdata\"><a href=\"mailto:$theMember->email\">$theMember->email</a></td></tr>");
            print("<tr><td class=\"memberlabel\">Description:</td><td class=\"memberdata\">$theMember->description</td></tr>");
            print("<tr><td colspan=\"2\">&nbsp;</td></tr>");
            print("<tr><td colspan=\"2\">&nbsp;</td></tr>");
        } // end for each member
        print("</table>");

    } // end if subcategory given
    else
    {
        print("<p>No Subcategory Selected</p>");
    }
?>
</body>
</html>
