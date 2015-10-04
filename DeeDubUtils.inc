<?php
///////////////////////////////////////////////////////////
// File: DeeDubUtils.inc
// Purpose: Various application-independent utility 
//          functions 
// Revision History:
// Date      Pgmr Descr
//  4/14/02  ddw  Created
///////////////////////////////////////////////////////////

// allow this file to be included only once
//
//-------------------------------------------------------
if (!IsSet($DeeDubUtilsInc))
{
    // set variable to prevent this being included
    // more than once
    //
    global $DeeDubUtilsInc;
    $DeeDubUtilsInc = true;

    // global variables
    //
    global $PAREN_STYLE;   // (aaa)nnn-nnnn
    global $HYPHEN_STYLE;  // aaa-nnn-nnnn
    global $DOT_STYLE;     // aaa.nnn.nnnn
    $PAREN_STYLE = 1;   // (aaa)nnn-nnnn
    $HYPHEN_STYLE = 2;  // aaa-nnn-nnnn
    $DOT_STYLE = 3;     // aaa.nnn.nnnn
    
    //--------------------------------------------------------
    // include stuff below...

    ///////////////////////////////////////////////////////////
    // Function: FormatPhone
    // Description: 
    //     Format a telephone number, inserting hyphens or
    //     parentheses as indicated by format parameter
    //     and length, (i.e., 7 digits versus 10)
    // Notes:
    // - $number must contain only the 7 or 10 digits of
    //   a phone number
    //   - if not, a blank string is returned
    //   - this function doesn't verify that each character
    //     is a numerical digit; any ascii character will
    //     be accepted.
    // - $format must be one of $PAREN_STYLE,
    //   $HYPHEN_STYLE, or $DOT_STYLE
    //   - if not, a blank string is returned
    //   - $PAREN_STYLE doesn't apply to 7-digit numbers
    //     (the parens surround the area code) except insofar
    //     as it includes a hyphen between the exchange and
    //     number
    ///////////////////////////////////////////////////////////
    function formatPhone($number, $format)
    {
    global $PAREN_STYLE;   // (aaa)nnn-nnnn
    global $HYPHEN_STYLE;  // aaa-nnn-nnnn
    global $DOT_STYLE;     // aaa.nnn.nnnn
        $formatted = "";
        $sepchar = "";
        $len = strlen($number);
        if ($len == 7)
        {
            // 7-digit number can only be $HYPHEN_STYLE
            // or $DOT_STYLE, since it has no area code;
            // $PAREN_STYLE is same as $HYPHEN_STYLE for
            // the 7-digit number
            //
            if ($format==$HYPHEN_STYLE || $format==$PAREN_STYLE)
            {
                $sepchar = "-";
            }
            else if ($format == $DOT_STYLE)
            {
                $sepchar = ".";
            }

            // each of the format types consists of the
            // first 3 and last 4 digits separated by
            // the specified character, i.e., hyphen or
            // dot
            //
            $formatted = substr($number, 0,3) . $sepchar 
                       . substr($number, 3,4);
       }
        else if ($len == 10)
        {
            // 10-digit number can be $HYPEN_STYLE,
            // $DOT_STYLE, or $PAREN_STYLE
            //
            $lparen = "";
            $rparen = "";
            $sepchar = "";
            switch ($format)
            {
                case $HYPHEN_STYLE:
                    $sepchar = "-";
                    $rparen = $sepchar;
                    break;
                case $DOT_STYLE:
                    $sepchar = ".";
                    $rparen = $sepchar;
                    break;
                case $PAREN_STYLE:
                    $sepchar = "-";
                    $lparen = "(";
                    $rparen = ")";
                    break;
            }
            
            $formatted = $lparen  . substr($number, 0,3)
                       . $rparen  . substr($number, 3,3) 
                       . $sepchar . substr($number, 6,4);
        }

        return $formatted;
    }

    ///////////////////////////////////////////////////////////
    // Function: UnformatPhone
    // Description: 
    //     Remove format characters from a telephone number, 
    //     including hyphens, dots, or parentheses.
    // Notes:
    // - if $number is not a valid phone number, e.g.,
    //   (aaa)nnn-nnnn, aaa-nnn-nnnn, or aaa.nnn.nnnn, the
    //   returned string is whatever was given, sans any
    //   hyphens, periods, or parentheses
    ///////////////////////////////////////////////////////////
    function unformatPhone($number)
    {
    global $PAREN_STYLE;   // (aaa)nnn-nnnn
    global $HYPHEN_STYLE;  // aaa-nnn-nnnn
    global $DOT_STYLE;     // aaa.nnn.nnnn
        // replace any separator characters with 
        // empty string
        //
        $unformatted = str_replace("-", "", $number);
        $unformatted = str_replace(".", "", $unformatted);
        $unformatted = str_replace("(", "", $unformatted);
        $unformatted = str_replace(")", "", $unformatted);
        
        return $unformatted;
    }

    ///////////////////////////////////////////////////////////
    // Function: Unquote
    // Description: 
    //     Remove leading and trailing double quotes.
    // Notes:
    // - Works only for "normal" quotes (ascii 34), not 
    //   left and right double quotes
    // - Removes *all* leading and trailing quotes
    //   - There was one record in the database that
    //     had 3(!!!) pairs of quotes!
    ///////////////////////////////////////////////////////////
    function unquote($quoted)
    {
        // preserve the original
        //
        $unquoted = $quoted;
        
        if (!strlen($unquoted))
            return $quoted;
        // if the leading character is double quote,
        // remove
        //
        if ($unquoted[0] == '"')
        {
            while($unquoted[0] == '"')
                $unquoted = substr($unquoted, 1);
        }
            
        // if the trailing character is double quote,
        // remove
        //
        if ($unquoted[strlen($unquoted)-1] == '"')
        {
            while($unquoted[strlen($unquoted)-1]=='"')
                $unquoted = substr($unquoted, 0, -1);
        }
        return $unquoted;
    }

    // include stuff above...
    //--------------------------------------------------------

} // end if this file has not been included before
?>

