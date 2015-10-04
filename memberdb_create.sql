/* Member Database Creation
 * Assumes database 'memberdb' already exists
 */

--
-- Table structure for table categories
--

DROP TABLE IF EXISTS categories;
CREATE TABLE categories (
  id int(11) NOT NULL auto_increment,
  name varchar(70) NOT NULL,
  PRIMARY KEY  (id),
  UNIQUE KEY name (name)
) ENGINE=MyISAM CHARSET=latin1;


--
-- Table structure for table subcategories
--

DROP TABLE IF EXISTS subcategories;
CREATE TABLE subcategories (
  id int(11) NOT NULL auto_increment,
  cid int(11) default NULL,
  name varchar(70) NOT NULL,
  PRIMARY KEY  (id),
  UNIQUE KEY name (name),
  FOREIGN KEY (cid)
      REFERENCES categories(id)
      ON DELETE CASCADE
) ENGINE=MyISAM CHARSET=latin1;

--
-- Table structure for table members
--

DROP TABLE IF EXISTS members;
CREATE TABLE members (
  memid int(10) unsigned NOT NULL,
  company char(70) default NULL,
  status char(1) default NULL,
  address char(40) default NULL,
  address2 char(40) default NULL,
  city char(28) default NULL,
  state char(2) default NULL,
  zip char(10) default NULL,
  phone char(10) default NULL,
  extn char(4) default NULL,
  fax char(10) default NULL,
  website varchar(70) default NULL,
  email varchar(40) default NULL,
  description longtext,
  firstname varchar(20) default NULL,
  lastname varchar(20) default NULL,
  repphone char(10) default NULL,
  repextn char(4) default NULL,
  repfax char(10) default NULL,
  repemail varchar(40) default NULL,
  subcategory int(11) default NULL,
  category int(11) default NULL,
  PRIMARY KEY  (memid)
  FOREIGN KEY (category)
      REFERENCES categories(id)
      ON DELETE CASCADE
  FOREIGN KEY (subcategory)
      REFERENCES subcategories(id)
      ON DELETE CASCADE
) ENGINE=MyISAM CHARSET=latin1;


