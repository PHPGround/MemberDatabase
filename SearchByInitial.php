<!--
    SearchByInitial.php
    * Example use of Member Database library
    * Could be used as a template for a alphabetical search page
-->
<html>
<head>
<title>&lt;Your Organization Here&gt; - Member Directory</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>
<body>
<h3>&lt;Organization&gt; Member Directory</h3>
<?php
    $init = $_GET["init"];
    if (isSet($init))
    {
        include ("Member.inc");
        include ("MemberDb.inc");
        include ("DeeDubUtils.inc");

        $theDb = new cMemberDb;

        $theList = array();

        $theDb->SelectByInitial($init, $theList);

        print("<p>Members by Initial $init</p>");
        print("<table>");

        for ($i=0; $i<sizeof($theList); $i++)
        {
            $theMember = $theList[$i];

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

        } // end for each member with initial
        print("</table>");

    } // end if initial given
    else
    {
        print("<p>No initial specified</p>");
    }
?> 
</body>
</html>

