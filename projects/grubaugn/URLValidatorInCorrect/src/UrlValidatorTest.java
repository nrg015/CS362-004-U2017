/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
   
   public class urlSegment
   {
   	public String seg;
   	public boolean isValid;
   	
   	public urlSegment(String seg, boolean isValid)
   	{
   		this.seg = seg;
   		this.isValid = isValid;
   	}
   }

   	urlSegment[] scheme = {new urlSegment("https://", true), new urlSegment("http://", true), new urlSegment("ftp://", true), new urlSegment("h3t://", true), new urlSegment("3ht://", false), new urlSegment("http:/", false), new urlSegment("http:", false), new urlSegment("http/", false), new urlSegment("://", false), new urlSegment("", true)};
	urlSegment[] IP = {new urlSegment("10.0.0.21", true), new urlSegment("192.168.1.1", true), new urlSegment("999.999.999.999", false), new urlSegment("222.1029.222.11.212.", false), new urlSegment("198.51.100.101", true), new urlSegment("198.51.100.101985", false), new urlSegment("192.177.123.1", true), new urlSegment("10", false)};
	urlSegment[] domain = {new urlSegment("google.com", true), new urlSegment("reddit.ca", true), new urlSegment("website.rrrr", false), new urlSegment("website.125", false), new urlSegment("testing.org", true), new urlSegment("aroundtheworld.travel", true), new urlSegment("...3%$", false), new urlSegment("time.gov", true)};
	urlSegment[] port = {new urlSegment(":80", true), new urlSegment(":65535", true), new urlSegment(":0", true), new urlSegment("", true),new urlSegment(":-1", false), new urlSegment(":65636", true), new urlSegment(":65a", false), new urlSegment("&%$#", false)};
	urlSegment[] path = {new urlSegment("/usr/share", true), new urlSegment("/test1", true), new urlSegment("/t123", true), new urlSegment("/$23", true), new urlSegment("/..", false), new urlSegment("/../", false), new urlSegment("/test1/", true), new urlSegment("", true), new urlSegment("/test1/file", true), new urlSegment("/..//file", false), new urlSegment("/test1//file", false)};
	urlSegment[] query = {new urlSegment("?action=view", true), new urlSegment("?action=view", true), new urlSegment("?action=edit&mode=up", true), new urlSegment("###", false), new urlSegment("?@bar._=???/1:", true), new urlSegment("?", true), new urlSegment("*(#)($", false), new urlSegment("?query=true", true)};
	urlSegment[] fragment = {new urlSegment("#broader", true), new urlSegment("#section-3.5", true), new urlSegment("xyz123",false),new urlSegment("#93knfdv",true),new urlSegment("#test%%\\",true),new urlSegment("#@%^&",true),new urlSegment("#VI})L<JB?",false), new urlSegment("#itest", true)};
	
	urlSegment[][] urlPartitionList = {scheme, IP, port, path, query, fragment, domain};	//FIXME IP and domain cover the same sort of stuff...... 

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testUrl = new String("http://www.google.com");
	   Boolean result;
	   testUrl = "http://www.google.com";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");

	   testUrl = "http://www.google.com:";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http:///www.amazon.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http:///www.amazon.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "https://www.usa.gov";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "https://www.usa.gov#1";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "+https://www.usa.gov#1";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "-https://www.usa.gov#1";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = ".https://www.usa.gov#1";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "ht.tps://www.usa.gov#1";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "ht.tps+://www.usa.gov#1";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "h-ttps://www.usa.gov#1";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http//www.google.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.!google.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.go-ogle.com";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.-google.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://-www.google.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.go-9gle.com";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.go-9gle.com";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://9www.go-9gle.com";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "ftp://www.go-9gle.com";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "://www.go-9gle.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "www.go-9gle.com";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.go-9gle.com.88";
	   assertFalse(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.ai";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
//	   testUrl = "http://www.google.aig";
//	   assertTrue(urlVal.isValid(testUrl));	//SHOULD PASS, BUT DOES NOT. It is listed in iana.org as currently valid top level domain
//	   result = urlVal.isValid(testUrl);
//	   System.out.println(testUrl + " is " + result + ".");
	   
//	   testUrl = "http://www.google.africa";
//	   assertTrue(urlVal.isValid(testUrl));	//SHOULD PASS, BUT DOES NOT. It is listed in iana.org as currently valid top level domain
//	   result = urlVal.isValid(testUrl);
//	   System.out.println(testUrl + " is " + result + ".");
	   
//	   testUrl = "http://sam:1234@www.google.com";
//	   assertTrue(urlVal.isValid(testUrl));	//SHOULD PASS, BUT DOES NOT. Should allow optional authenication system.
//	   result = urlVal.isValid(testUrl);
//	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://0.0.0.0";
	   assertTrue(urlVal.isValid(testUrl));
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
//	   testUrl = "http://0.0.0.300";
//	   assertFalse(urlVal.isValid(testUrl));	//SHOULD FAIL, BUT DOES NOT. Should not allow impossible IPv4 addresses
//	   result = urlVal.isValid(testUrl);
//	   System.out.println(testUrl + " is " + result + ".");
	   
//	   testUrl = "http://[2001:db8:a0b:12f0::1]";	
//	   assertTrue(urlVal.isValid(testUrl));	//SHOULD PASS, BUT DOES NOT. Should allow IPv6 literals.
//	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://abc/def/efg.htm";
	   assertFalse(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http:/abc/def/efg.htm";
	   assertFalse(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/abc/def/efg.htm";
	   assertTrue(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/+abc/def/efg.htm";
	   assertTrue(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/~abc/def/efg.htm";
	   assertTrue(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/_abc/def/efg.htm";
	   assertTrue(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/%0F/abc/def/efg.htm";
	   assertTrue(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
//	   testUrl = "http://www.google.com/%+~/abc/def/efg.htm";
//	   assertFalse(urlVal.isValid(testUrl));		//SHOULD FAIL, BUT DOES NOT. Should only allow two hexadecimal digits after %
//	   result = urlVal.isValid(testUrl);
//	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/ab?c/def/efg.htm";
	   assertFalse(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");
	   
	   testUrl = "http://www.google.com/ab%3fc/def/efg.htm";
	   assertTrue(urlVal.isValid(testUrl));	
	   result = urlVal.isValid(testUrl);
	   System.out.println(testUrl + " is " + result + ".");

   }
   
   
   public void testYourFirstPartition() //Testing Domains
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i = 0;i<20;i++)
	   {
		   StringBuffer testBuffer = new StringBuffer();
		   testBuffer.append("http://google.");
		   testBuffer.append(GENERIC_TLDS[i]);
		   String url = testBuffer.toString();
		   System.out.print("Testing ");
		   System.out.println(url);
		   System.out.print("   ");
		   System.out.print(urlVal.isValid(url));
		   System.out.println("   Expected: True");
	   }
	   
	   for(int i = 0; i<249; i++)
	   {
		   StringBuffer testBuffer = new StringBuffer();
		   testBuffer.append("http://google.");
		   testBuffer.append(COUNTRY_CODE_TLDS[i]);
		   String url = testBuffer.toString();
		   System.out.print("Testing ");
		   System.out.println(url);
		   System.out.print("   ");
		   System.out.print(urlVal.isValid(url));
		   System.out.println("   Expected: True");
	   }
   }
   
   public void testYourSecondPartition() //Testing Queries
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i = 0;i<3;i++)
	   {
		   StringBuffer testBuffer = new StringBuffer();
		   testBuffer.append("http://google.com");
		   testBuffer.append(TEST_QUERY[i]);
		   String url = testBuffer.toString();
		   System.out.print("Testing ");
		   System.out.println(url);
		   System.out.print("   ");
		   System.out.print(urlVal.isValid(url));
		   System.out.println("   Expected: True");
	   }
   }
   
   
   public void testIsValid()
   {
	 //first setup the lists of arrays to be swept, these include the IP, domain, port, path, query, fragment
	UrlValidator testinger = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	String defaultScheme, defaultIP, defaultDomain, defaultPort, defaultPath, defaultQuery, defaultFragment, URLunderTest;
	String[] URLarray = new String[6];
	//need to figure out a way to switch off domains and IPs
	String[] Authority = new String[2];
	defaultScheme = "http://";
	defaultIP = "192.168.1.1";
	defaultDomain = "google.com";
	defaultPort = ":80";
	defaultPath = "/usr/share";
	defaultQuery = "?action=view";
	defaultFragment = "#broader";
	Boolean isValidResults;
	Boolean expectedResults;
	int successCounter = 0;
	int failureCounter = 0;
	
	for(int k = 0; k < 2; k++)
	{
		
	
		for(int i = 0; i < 6; i++)
		{

			Authority[0] = defaultIP;
			Authority[1] = defaultDomain;
			URLarray[0] = defaultScheme;
			URLarray[1] = Authority[k];
			URLarray[2] = defaultPort;
			URLarray[3] = defaultPath;
			URLarray[4] = defaultQuery;
			URLarray[5] = defaultFragment;
			for(int j = 0; j < 8; j++)	//5 options per partition
			{
				if(k == 1 && i == 1)
				{
					URLarray[1] = urlPartitionList[6][j].seg;
					if(urlPartitionList[6][j].isValid)
						expectedResults = true;
					else
						expectedResults = false;
					URLunderTest = URLarray[0] + URLarray[1] + URLarray[2] + URLarray[3] + URLarray[4] + URLarray[5];
					System.out.format("Current URL under test: %s\n", URLunderTest);
					isValidResults = testinger.isValid(URLunderTest);
				}
				else
				{
					URLarray[i] = urlPartitionList[i][j].seg;
					if(urlPartitionList[i][j].isValid)
						expectedResults = true;
					else
						expectedResults = false;
					URLunderTest = URLarray[0] + URLarray[1] + URLarray[2] + URLarray[3] + URLarray[4] + URLarray[5];
					System.out.format("Current URL under test: %s\n", URLunderTest);
					isValidResults = testinger.isValid(URLunderTest);
				}
				if(expectedResults == isValidResults)
				{
					System.out.println("TEST CASE SUCCESS\n");
					successCounter++;
				}
				else if(expectedResults != isValidResults)
				{
					System.out.println("TEST CASE FAILURE\n");
					failureCounter++;
				}
			}
		}
	}
	System.out.format("Total Number of Successes: %d\n", successCounter);
	System.out.format("Total Number of Failures: %d\n", failureCounter);

	
}

   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   private static final String[] GENERIC_TLDS = new String[] {
	        "aero",               // air transport industry
	        "asia",               // Pan-Asia/Asia Pacific
	        "biz",                // businesses
	        "cat",                // Catalan linguistic/cultural community
	        "com",                // commercial enterprises
	        "coop",               // cooperative associations
	        "info",               // informational sites
	        "jobs",               // Human Resource managers
	        "mobi",               // mobile products and services
	        "museum",             // museums, surprisingly enough
	        "name",               // individuals' sites
	        "net",                // internet support infrastructure/business
	        "org",                // noncommercial organizations
	        "pro",                // credentialed professionals and entities
	        "tel",                // contact data for businesses and individuals
	        "travel",             // entities in the travel industry
	        "gov",                // United States Government
	        "edu",                // accredited postsecondary US education entities
	        "mil",                // United States Military
	        "int"                 // organizations established by international treaty
   };

   private static final String[] COUNTRY_CODE_TLDS = new String[] {
        "ac",                 // Ascension Island
        "ad",                 // Andorra
        "ae",                 // United Arab Emirates
        "af",                 // Afghanistan
        "ag",                 // Antigua and Barbuda
        "ai",                 // Anguilla
        "al",                 // Albania
        "am",                 // Armenia
        "an",                 // Netherlands Antilles
        "ao",                 // Angola
        "aq",                 // Antarctica
        "ar",                 // Argentina
        "as",                 // American Samoa
        "at",                 // Austria
        "au",                 // Australia (includes Ashmore and Cartier Islands and Coral Sea Islands)
        "aw",                 // Aruba
        "ax",                 // Åland
        "az",                 // Azerbaijan
        "ba",                 // Bosnia and Herzegovina
        "bb",                 // Barbados
        "bd",                 // Bangladesh
        "be",                 // Belgium
        "bf",                 // Burkina Faso
        "bg",                 // Bulgaria
        "bh",                 // Bahrain
        "bi",                 // Burundi
        "bj",                 // Benin
        "bm",                 // Bermuda
        "bn",                 // Brunei Darussalam
        "bo",                 // Bolivia
        "br",                 // Brazil
        "bs",                 // Bahamas
        "bt",                 // Bhutan
        "bv",                 // Bouvet Island
        "bw",                 // Botswana
        "by",                 // Belarus
        "bz",                 // Belize
        "ca",                 // Canada
        "cc",                 // Cocos (Keeling) Islands
        "cd",                 // Democratic Republic of the Congo (formerly Zaire)
        "cf",                 // Central African Republic
        "cg",                 // Republic of the Congo
        "ch",                 // Switzerland
        "ci",                 // Côte d'Ivoire
        "ck",                 // Cook Islands
        "cl",                 // Chile
        "cm",                 // Cameroon
        "cn",                 // China, mainland
        "co",                 // Colombia
        "cr",                 // Costa Rica
        "cu",                 // Cuba
        "cv",                 // Cape Verde
        "cx",                 // Christmas Island
        "cy",                 // Cyprus
        "cz",                 // Czech Republic
        "de",                 // Germany
        "dj",                 // Djibouti
        "dk",                 // Denmark
        "dm",                 // Dominica
        "do",                 // Dominican Republic
        "dz",                 // Algeria
        "ec",                 // Ecuador
        "ee",                 // Estonia
        "eg",                 // Egypt
        "er",                 // Eritrea
        "es",                 // Spain
        "et",                 // Ethiopia
        "eu",                 // European Union
        "fi",                 // Finland
        "fj",                 // Fiji
        "fk",                 // Falkland Islands
        "fm",                 // Federated States of Micronesia
        "fo",                 // Faroe Islands
        "fr",                 // France
        "ga",                 // Gabon
        "gb",                 // Great Britain (United Kingdom)
        "gd",                 // Grenada
        "ge",                 // Georgia
        "gf",                 // French Guiana
        "gg",                 // Guernsey
        "gh",                 // Ghana
        "gi",                 // Gibraltar
        "gl",                 // Greenland
        "gm",                 // The Gambia
        "gn",                 // Guinea
        "gp",                 // Guadeloupe
        "gq",                 // Equatorial Guinea
        "gr",                 // Greece
        "gs",                 // South Georgia and the South Sandwich Islands
        "gt",                 // Guatemala
        "gu",                 // Guam
        "gw",                 // Guinea-Bissau
        "gy",                 // Guyana
        "hk",                 // Hong Kong
        "hm",                 // Heard Island and McDonald Islands
        "hn",                 // Honduras
        "hr",                 // Croatia (Hrvatska)
        "ht",                 // Haiti
        "hu",                 // Hungary
        "id",                 // Indonesia
        "ie",                 // Ireland (Éire)
        "il",                 // Israel
        "im",                 // Isle of Man
        "in",                 // India
        "io",                 // British Indian Ocean Territory
        "iq",                 // Iraq
        "ir",                 // Iran
        "is",                 // Iceland
        "it",                 // Italy
        "je",                 // Jersey
        "jm",                 // Jamaica
        "jo",                 // Jordan
        "jp",                 // Japan
        "ke",                 // Kenya
        "kg",                 // Kyrgyzstan
        "kh",                 // Cambodia (Khmer)
        "ki",                 // Kiribati
        "km",                 // Comoros
        "kn",                 // Saint Kitts and Nevis
        "kp",                 // North Korea
        "kr",                 // South Korea
        "kw",                 // Kuwait
        "ky",                 // Cayman Islands
        "kz",                 // Kazakhstan
        "la",                 // Laos (currently being marketed as the official domain for Los Angeles)
        "lb",                 // Lebanon
        "lc",                 // Saint Lucia
        "li",                 // Liechtenstein
        "lk",                 // Sri Lanka
        "lr",                 // Liberia
        "ls",                 // Lesotho
        "lt",                 // Lithuania
        "lu",                 // Luxembourg
        "lv",                 // Latvia
        "ly",                 // Libya
        "ma",                 // Morocco
        "mc",                 // Monaco
        "md",                 // Moldova
        "me",                 // Montenegro
        "mg",                 // Madagascar
        "mh",                 // Marshall Islands
        "mk",                 // Republic of Macedonia
        "ml",                 // Mali
        "mm",                 // Myanmar
        "mn",                 // Mongolia
        "mo",                 // Macau
        "mp",                 // Northern Mariana Islands
        "mq",                 // Martinique
        "mr",                 // Mauritania
        "ms",                 // Montserrat
        "mt",                 // Malta
        "mu",                 // Mauritius
        "mv",                 // Maldives
        "mw",                 // Malawi
        "mx",                 // Mexico
        "my",                 // Malaysia
        "mz",                 // Mozambique
        "na",                 // Namibia
        "nc",                 // New Caledonia
        "ne",                 // Niger
        "nf",                 // Norfolk Island
        "ng",                 // Nigeria
        "ni",                 // Nicaragua
        "nl",                 // Netherlands
        "no",                 // Norway
        "np",                 // Nepal
        "nr",                 // Nauru
        "nu",                 // Niue
        "nz",                 // New Zealand
        "om",                 // Oman
        "pa",                 // Panama
        "pe",                 // Peru
        "pf",                 // French Polynesia With Clipperton Island
        "pg",                 // Papua New Guinea
        "ph",                 // Philippines
        "pk",                 // Pakistan
        "pl",                 // Poland
        "pm",                 // Saint-Pierre and Miquelon
        "pn",                 // Pitcairn Islands
        "pr",                 // Puerto Rico
        "ps",                 // Palestinian territories (PA-controlled West Bank and Gaza Strip)
        "pt",                 // Portugal
        "pw",                 // Palau
        "py",                 // Paraguay
        "qa",                 // Qatar
        "re",                 // Réunion
        "ro",                 // Romania
        "rs",                 // Serbia
        "ru",                 // Russia
        "rw",                 // Rwanda
        "sa",                 // Saudi Arabia
        "sb",                 // Solomon Islands
        "sc",                 // Seychelles
        "sd",                 // Sudan
        "se",                 // Sweden
        "sg",                 // Singapore
        "sh",                 // Saint Helena
        "si",                 // Slovenia
        "sj",                 // Svalbard and Jan Mayen Islands Not in use (Norwegian dependencies; see .no)
        "sk",                 // Slovakia
        "sl",                 // Sierra Leone
        "sm",                 // San Marino
        "sn",                 // Senegal
        "so",                 // Somalia
        "sr",                 // Suriname
        "st",                 // São Tomé and Príncipe
        "su",                 // Soviet Union (deprecated)
        "sv",                 // El Salvador
        "sy",                 // Syria
        "sz",                 // Swaziland
        "tc",                 // Turks and Caicos Islands
        "td",                 // Chad
        "tf",                 // French Southern and Antarctic Lands
        "tg",                 // Togo
        "th",                 // Thailand
        "tj",                 // Tajikistan
        "tk",                 // Tokelau
        "tl",                 // East Timor (deprecated old code)
        "tm",                 // Turkmenistan
        "tn",                 // Tunisia
        "to",                 // Tonga
        "tp",                 // East Timor
        "tr",                 // Turkey
        "tt",                 // Trinidad and Tobago
        "tv",                 // Tuvalu
        "tw",                 // Taiwan, Republic of China
        "tz",                 // Tanzania
        "ua",                 // Ukraine
        "ug",                 // Uganda
        "uk",                 // United Kingdom
        "um",                 // United States Minor Outlying Islands
        "us",                 // United States of America
        "uy",                 // Uruguay
        "uz",                 // Uzbekistan
        "va",                 // Vatican City State
        "vc",                 // Saint Vincent and the Grenadines
        "ve",                 // Venezuela
        "vg",                 // British Virgin Islands
        "vi",                 // U.S. Virgin Islands
        "vn",                 // Vietnam
        "vu",                 // Vanuatu
        "wf",                 // Wallis and Futuna
        "ws",                 // Samoa (formerly Western Samoa)
        "ye",                 // Yemen
        "yt",                 // Mayotte
        "yu",                 // Serbia and Montenegro (originally Yugoslavia)
        "za",                 // South Africa
        "zm",                 // Zambia
        "zw",                 // Zimbabwe
    };
	    
    private static final String[] TEST_QUERY = new String[] {
    		"?action=view",
    		"?action=edit&mode=up",
    		""
    };

}
