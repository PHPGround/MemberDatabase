<html>
<head>
<title>&lt;Organization Name&gt; - Member Business Directory</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<meta http-equiv="Expires" content="0">
<META HTTP-EQUIV="Update" CONTENT="0">
<link rel="stylesheet" type="text/css" href="memberdb.css">

<script>
function LoadArrays()
{
    <?php
    include("MemberDb.inc");
    $theDb = new cMemberDb;
    $catlist = array();
    $catidx = 0;
    $subcatlist = array();
    $subcatidx = 0;

    $theDb->GetCategoryList($catlist);
    $clen = sizeof($catlist);
    echo("cats = [");
    for ($i=0; $i<$clen; $i++)
    {
        echo("\"$catlist[$i]\"");
        if ($i<($clen-1))    // index increments at start of loop
            echo(",");

        if ( IsSet($category) && $catlist[$i]==$category )
            $catidx=$i+1;
    }
    echo("];\n");

    echo("subcats = new Array($clen);");
    for ($i=0; $i<$clen; $i++)
    {
        echo("subcats[$i] = [");
        $subcatlist[$i] = array();
        $theDb->GetSubcategoryList($catlist[$i], $subcatlist[$i]);
        $slen = sizeof($subcatlist[$i]);
        for ($j=0; $j<$slen; $j++)
        {
            $scstr = $subcatlist[$i][$j];

            echo("\"$scstr\"");
            if ($j<$slen-1)
                echo(",");

            if ( IsSet($subcategory) && $scstr==$subcategory )
                $subcatidx=$j+1;
        }
        echo("];\n");
    }
    echo("StartMenus();");
    if (IsSet($category))
    {
        echo ("msg=\"category=\";alert(msg+\"$category\");\n");
        echo("var catidx=$catidx;\n");
    }
    else
    {
        echo("var catidx=0;\n");
    }
    if (IsSet($subcategory))
    {
        echo ("msg=\"subcategory=\";alert(msg+\"$subcategory\");\n");
        echo("var subcatidx=$subcatidx;\n");

    }
    else
    {
        echo("var subcatidx=0;\n");
    }

    ?>

}

function StartMenus()
{
    frm = document.categoryForm;
    frm.category.length=cats.length+1;
    frm.category.options[0].text = "Select Category";
    frm.category.options[0].value = "none";
    frm.category.options[0].selected = true;
     for (var i=0; i<cats.length; i++)
    {
        frm.category.options[i+1].text = cats[i];
        frm.category.options[i+1].value = cats[i];
    }
    SetSubcatList();
}
function SelectCategory(cat)
{
    catidx=cat;
    frm = document.categoryForm;
    frm.category.options[catidx].selected = true;
    SetSubcatList();
}

function SelectSubcategory(subcat)
{
    subcatidx=subcat;
    frm = document.categoryForm;
    frm.subcategory.options[subcatidx].selected = true;
    DisplayLinks(frm.subcategory.options[subcatidx].value);
}

function SetSubcatList()
{
    frm = document.categoryForm;
    catidx = frm.category.selectedIndex;
    subcatidx=0;
    var cat = catidx-1;
    var listlen = 1;        // if selection is only "Select Subcategory"
    if (cat>=0)    // if "Select Category", cat=-1
        listlen = subcats[cat].length+2;
    frm.subcategory.length=listlen;
    frm.subcategory.options[0].text = "Select Subcategory";
    frm.subcategory.options[0].value = "none";
    if (cat>=0)
    {
        frm.subcategory.options[1].text = "All Subcategories";
        frm.subcategory.options[1].value = "all";
         for (var i=2; i<listlen; i++)
        {
            frm.subcategory.options[i].text = subcats[cat][i-2];
            frm.subcategory.options[i].value = subcats[cat][i-2];
        }
    }
}

function DisplayLinks()
{
    frm = document.categoryForm;
    catsel = frm.category.selectedIndex;
    catstr = frm.category.options[catsel].value;
    subcatsel = frm.subcategory.selectedIndex;
    subcatstr = frm.subcategory.options[subcatsel].value;
    if (subcatstr=="all")
    {
        page = "SearchByCategory.php?category=";
        page += catstr;
    }
    else
    {
        page = "SearchBySubcategory.php?subcategory=";
        page += escape(subcatstr);
        alert("Search by subcategory "+page);
    }
    window.location=page;
}
</script>
</head>
<body onLoad="LoadArrays()">
<h3>&lt;Organization Name&gt; Member Directory</h3>
<div class="byinitial">
<p>Search Alphabetically:</p>
<ul>
<li><a href="SearchByInitial.php?init=A">A</a><br></li>
<li><a href="SearchByInitial.php?init=B">B</a><br></li>
<li><a href="SearchByInitial.php?init=C">C</a><br></li>
<li><a href="SearchByInitial.php?init=D">D</a><br></li>
<li><a href="SearchByInitial.php?init=E">E</a><br></li>
<li><a href="SearchByInitial.php?init=F">F</a><br></li>
<li><a href="SearchByInitial.php?init=G">G</a><br></li>
<li><a href="SearchByInitial.php?init=H">H</a><br></li>
<li><a href="SearchByInitial.php?init=I">I</a><br></li>
<li><a href="SearchByInitial.php?init=J">J</a><br></li>
<li><a href="SearchByInitial.php?init=K">K</a><br></li>
<li><a href="SearchByInitial.php?init=L">L</a><br></li>
<li><a href="SearchByInitial.php?init=M">M</a><br></li>
<li><a href="SearchByInitial.php?init=N">N</a><br></li>
<li><a href="SearchByInitial.php?init=O">O</a><br></li>
<li><a href="SearchByInitial.php?init=P">P</a><br></li>
<li><a href="SearchByInitial.php?init=Q">Q</a><br></li>
<li><a href="SearchByInitial.php?init=R">R</a><br></li>
<li><a href="SearchByInitial.php?init=S">S</a><br></li>
<li><a href="SearchByInitial.php?init=T">T</a><br></li>
<li><a href="SearchByInitial.php?init=U">U</a><br></li>
<li><a href="SearchByInitial.php?init=V">V</a><br></li>
<li><a href="SearchByInitial.php?init=W">W</a><br></li>
<li><a href="SearchByInitial.php?init=X">X</a><br></li>
<li><a href="SearchByInitial.php?init=Y">Y</a><br></li>
<li><a href="SearchByInitial.php?init=Z">Z</a><br></li>
<li><a href="SearchByInitial.php?init=0">0</a><br></li>
<li><a href="SearchByInitial.php?init=1">1</a><br></li>
<li><a href="SearchByInitial.php?init=2">2</a><br></li>
<li><a href="SearchByInitial.php?init=3">3</a><br></li>
<li><a href="SearchByInitial.php?init=4">4</a><br></li>
<li><a href="SearchByInitial.php?init=5">5</a><br></li>
<li><a href="SearchByInitial.php?init=6">6</a><br></li>
<li><a href="SearchByInitial.php?init=7">7</a><br></li>
<li><a href="SearchByInitial.php?init=8">8</a><br></li>
<li><a href="SearchByInitial.php?init=9">9</a><br></li>
</ul>
</div>

<div class="byname">
<p>Search By Name:</p>
<form name="nameForm" method="get" action="SearchByName.php">
<input type="text" name="name">
<input type="submit" name="Submit" value="Search">
</form>
</div>

<div class="bycategory">
<p>Search By Category:</p>
<form name="categoryForm">
<select name="category" size="1" onChange="SetSubcatList()">
<option value="none">Select Category
</select>
<select name="subcategory" size="1" onChange="DisplayLinks()">
<option value="none">Select Subcategory
</select>
</form>
</div>

</body>
</html>
