# MemberDatabase
This is a PHP library to support access to a membership database, including contact information and other data about members. Since this library was originally created for a web-based business directory, membership data includes categories and subcategories of member businesses of a singular member name, with the first and last name of the person in that business to contact. With that contact information, this library could also easily support a membership of individuals, rather than businesses.

# Usage

To use this library, you'll need to:

* Set up a database called "memberdb" and add a user. This library was created for use with MySQL, but could easily be adapted to use others, (and will be in a future release. See [Coming Attractions](#Coming Attractions))

* Populate the database with member data. This library was originally created
to display membership data transcribed from an external source. (See [Historical Notes](#Historical Notes)) Support for adding and modify data is planned. (See [Coming Attractions](#Coming Attractions))

* Move the file `dbinfo.inc` outside the webroot directory and set the db host, user, and password to match your database and user created in a previous step. Typical usage has the library files in webroot and the `dbinfo.inc` file in its parent directory. If this won't work for you, put `dbinfo.inc` in a secure location and modify `MemberDb.inc` to include `dbinfo.inc` from its actual path.

* Create pages to retrieve and display data as needed. Template pages are included in this repo to verify installation and to use as a starting point for your own applications. See [Files](#Files) below.

* Test and enjoy.


# Files

* **DeeDubUtils.inc**: Contains some utility functions to format phone numbers for display, plus a function used in the original application to strip nested quotes when ingesting data.

* **Member.inc**: Defines the cMember class, representing a single member of the organization.

* **MemberDb.inc**: Encapsulates client interaction with the database, including connecting, executing queries, and transcribing data to and from cMember objects.

* **directory.php**: An example of multiple data retrieval methods supported by this library. It presents suggested user interface elements for retrieving member data in various ways.

* **SearchByCategory.php**: An example of a page that uses this library to retrieve members by category. You can use this page directly by including the HTTP GET parameter "category". Alternatively, you can construct a menu of categories as exemplified in `directory.php` for a user to select a category, then retrieve a page based on `SearchByCategory.php` or generate an AJAX query to a PHP script derived from it.

* **SearchByInitial.php**: An example of a page that uses this library to retrieve members by first initial of the member name. You can use this page directly by including the HTTP GET parameter "init" as exemplified in `directory.php` or generate an AJAX query to a PHP script derived from `SearchByInitial.php`.

* **SearchByName.php**: An example of a page that uses this library to retrieve members by name. You can use this page directly by including the HTTP GET parameter "name" as exemplified in `directory.php` or generate an AJAX query to a PHP script derived from `SearchByName.php`.

* **SearchBySubcategory.php**: An example of a page that uses this library to retrieve members by subcategory. You can use this page directly by including the HTTP GET parameter "subcategory". Alternatively, you can construct a menu of categories and subcategories as exemplified in `directory.php` for a user to select a subcategory, then retrieve a page based on `SearchBySubcategory.php` or generate an AJAX query to a PHP script derived from `SearchBySubcategory.php`. Note that the MemberDB.SelectBySubcategory method as currently implemented doesn't filter on category, so members of a subcategory that's shared between categories will be returned for all categories.

# Database Schema

<pre>
 ----------------------------------          -------------------------
| members                          |        | subcategories           |
| ---------                        |        | ---------------         |
| memid       unsigned primary key |    --->| id  int(11) primary key |
| company     char(70)             |   |  --| cid int(11) foreign key |
| status      char(1)              |   | |  | name varchar(70)        |
| address     char(40)             |   | |   -------------------------
| address2    char(40)             |   | |
| city        char(28)             |   | |
| state       char(2)              |   | |
| zip         char(10)             |   | |
| phone       char(10)             |   | |
| extn        char(4)              |   | |
| fax         char(10)             |   | |
| website     varchar(70)          |   | |
| email       varchar(40)          |   | |   -------------------------
| description longtext             |   | |  | categories              |
| firstname   varchar(20)          |   | |  | ---------------         |
| lastname    varchar(20)          |   |  ->| id  int(11) primary key |
| repphone    char(10)             |   | |  | name varchar(70) unique |
| repextn     char(4)              |   | |   -------------------------
| repfax      char(10)             |   | |
| repemail    varchar(40)          |   | |
| subcategory int(11) foreign key  |---  |
| category    int(11) foreign key  |-----
 ----------------------------------
</pre>
# Coming Attractions

*Support for Multiple DBMSes*

The class cMemberDb was implemented with the MySQL API, a requirement
for the app from which this library originated. We're planning to
support PostgreSQL, Sqlite3, and MongoDB in the near future.

*Add and Modify Member Data*

The app from which this library originated provided a directory of
members, but didn't require editing of membership data. Hence, the
cMemberDb interface includes no provisions for record insertion,
deletion, or modification. These will be added.

*Category Constraint on Subcategory Searches*

The membership directory for which this library was first used had
very unique member subcategories, so there were no problems with
retrieving members by subcategory and getting multiple categories.
This could be an issue in applications that have the same subcategory
name in multiple categories. For example, subcategory "Consultant" in 
categories "Engineering" and "Medical". So subcategory retrieval will
include an optional category constraint.

# Historical Notes

This library originated as a backend solution for a Chamber of Commerce
business directory. The original developer provided code snippets in php
tags for the website designers to integrate into their pages, along with 
the library script files to be placed on the site host. 

The Chamber of Commerce for the city that commissioned the work maintained
their member database in a commercial desktop application that, at that time, 
had no web-based capability, so the website maintainers exported data from
that application in tab-delimited format, uploaded to the site host, and 
ingested the data into a MySQL database on the website using a tool provided 
by the developer for that purpose. (That tool isn't included in this repo as 
it was very specific to the desktop application and won't likely be useful to 
many.)

Years later, the developer found the original implementation on a backup
drive and realized it might be useful to somebody. Since the developer
never relinquished rights to this code, he saw no reason not to publish it.
To that end, he removed the table-based layout and formatting needed to 
integrate into the original application as a first step toward providing a 
generalized, open-source library. 
