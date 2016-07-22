import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import junit.framework.Assert;
import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase{

 //PUBLIC:

	public UrlValidatorTest(String testName){
		super(testName);
	}

   public void testManually(){
      UrlValidator manTest = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
      boolean valid = manTest.isValid("http://www.facebook.com");
      assertTrue(valid);
      valid = manTest.isValidAuthority("www.google.com:6553");
      assertTrue(valid);
      valid = manTest.isValidAuthority("www.google.com::::");
      assertTrue(!valid);
      valid = manTest.isValid("one://falsehost.falseTLD/");
      assertTrue(!valid);
      valid = manTest.isValid("fake://org.org");
      assertTrue(valid);
      valid = manTest.isValid("fake://org.org.org/pathname");
      assertTrue(valid);
      valid = manTest.isValid("fake://org.org.org//pathname");
      assertTrue(!valid);
      valid = manTest.isValid("fake://org.org.org:90/pathname");
      assertTrue(valid);
      valid = manTest.isValid("alFake+still://org.org.org:90");
      assertTrue(valid);
      valid = manTest.isValid("fake://org.org.org:-1");
      assertTrue(!valid);
      valid = manTest.isValid("fake://org.org.org:65535/pathname/subdir.doc");
      assertTrue(valid);
      valid = manTest.isValid("fake://org.org.org:65535/pathname/subdir?key=val");
      assertTrue(valid);
      valid = manTest.isValid("www.google.com");
      assertTrue(!valid);
      valid = manTest.isValid("google.com");
      assertTrue(!valid);
      valid = manTest.isValid("google.com:80");
      assertTrue(!valid);
      valid = manTest.isValid("http://www.google.com:65535");
      assertTrue(valid);
      valid = manTest.isValid("http://www.google.com:99999");
      assertTrue(!valid);
      valid = manTest.isValid("http://www.google.com:999990");
      assertTrue(!valid);
      valid = manTest.isValid("https://localhost:80/");
      assertTrue(valid);
    
   }
   
   public void testPartitions(){
	   UrlValidator parValDef = new UrlValidator();
	   UrlValidator parValAll = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   String testString = "";
	   
	   boolean valid = true;
	   String[] DefAllowed = {"http", "https", "ftp"};
	   for(int i = 0; i < testSchemes.length; i++){
		   //Default Schemes sub-method isValidScheme
		   valid = parValDef.isValidScheme(testSchemes[i].item);
		   boolean found = false;
		   for(int j = 0; j < DefAllowed.length; j++){
			   if(testSchemes[i].item == DefAllowed[j]){
				   found = true;
			   }
		   }
		   //Allows test to continue; Checks if Default Constructed
		   		//UrlValidator only allows http, https, ftp
		   if(!found){
			   Assert.assertEquals(false, valid);
		   } else {
			   Assert.assertEquals(testSchemes[i].valid, valid);
		   }
		   //All Schemes sub-method isValidScheme
		   valid = parValAll.isValidScheme(testSchemes[i].item);
		   Assert.assertEquals(testSchemes[i].valid, valid);  
		   //Default Schemes isValid
		   valid = parValDef.isValid(testSchemes[i].item);
		   Assert.assertEquals(false, valid);
		   //All Schemes isValid
		   valid = parValAll.isValid(testSchemes[i].item);
		   Assert.assertEquals(false, valid);
	   }

	   for(int i = 0; i < testPorts.length; i++){
		   for(int j = 0; j < testHosts.length; j++){
			   testString = testHosts[j].item;
			   
			   if(testPorts[i].item != ""){
				   testString += ':' + testPorts[i].item;
			   }
			   boolean testBool = testHosts[j].valid && testPorts[i].valid;
			   valid = parValDef.isValidAuthority(testString);
			   Assert.assertEquals(testBool, valid);
			   valid = parValAll.isValidAuthority(testString);
			   Assert.assertEquals(testBool, valid);
			   valid = parValDef.isValid(testString);
			   Assert.assertEquals(false, valid);
			   valid = parValAll.isValid(testString);
			   Assert.assertEquals(false, valid);
		   }
	   }
	   
	   for(int i = 0; i < testPaths.length; i++){
		   valid = parValDef.isValidPath(testPaths[i].item);
		   Assert.assertEquals(testPaths[i].valid, valid);
		   valid = parValAll.isValidPath(testPaths[i].item);
		   Assert.assertEquals(testPaths[i].valid, valid);
		   valid = parValDef.isValid(testPaths[i].item);
		   Assert.assertEquals(false, valid);
		   valid = parValAll.isValid(testPaths[i].item);
		   Assert.assertEquals(false, valid);
	   }
	   for(int i = 0; i < testQueries.length; i++){
		   valid = parValDef.isValidQuery(testQueries[i].item);
		   Assert.assertEquals(testQueries[i].valid, valid);
		   valid = parValAll.isValidQuery(testQueries[i].item);
		   Assert.assertEquals(testQueries[i].valid, valid);
		   valid = parValDef.isValid(testQueries[i].item);
		   Assert.assertEquals(false, valid);
		   valid = parValAll.isValid(testQueries[i].item);
		   Assert.assertEquals(false, valid);
	   }
	   
   }
   public void testProgram(){
	   int[] counter = {0,0,0,0,0};
	   //UrlValidator progValDef = new UrlValidator();
	   UrlValidator progValAll = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   while(counter[0] < testSchemes.length){
		   String testString = "";
		   boolean testBool = true;
		   if(testSchemes[counter[0]].item != ""){

			   testString += testSchemes[counter[0]].item + "://";
		   }
		   testBool &= testSchemes[counter[0]].valid;
		   testString += testHosts[counter[1]].item;
		   testBool &= testHosts[counter[1]].valid;
		   if(testPorts[counter[2]].item != ""){
			   testString += ":" + testPorts[counter[2]].item;
		   }
		   testBool &= testPorts[counter[2]].valid;
		   testString += testPaths[counter[3]].item;
		   testBool &= testPaths[counter[3]].valid;
		   if(testQueries[counter[4]].item != ""){
			   testString += "?" + testQueries[counter[4]].item;
		   }
		   
		   testBool &= testQueries[counter[4]].valid;
		   
		   //boolean defVal = progValDef.isValid(testString);
		   boolean allVal = progValAll.isValid(testString);
		   
		   /*if(testBool != defVal){
			   System.out.println(testString + " " + testBool + " " + defVal);
		   }
		   */
		   if(testBool != allVal){
			   System.out.println(testString + " " + testBool + " " + allVal);
			   System.out.println("scheme: " + progValAll.isValidScheme(testSchemes[counter[0]].item));
			   System.out.println("auth: " + progValAll.isValidAuthority(testHosts[counter[1]].item + ":" + testPorts[counter[2]].item));
			   System.out.println("path: " + progValAll.isValidPath(testPaths[counter[3]].item));
			   System.out.println("query: " + progValAll.isValidQuery(testQueries[counter[4]].item));
			 
		   }
		   //Assert.assertEquals(testBool, defVal);
		   Assert.assertEquals(testBool, allVal);
		   
		   counter[4]++;
		   if(counter[4] == testQueries.length){

			   counter[3]++;
			   counter[4] = 0;
		   }
		   if(counter[3] == testPaths.length){
			   counter[2]++;
			   counter[3] = 0;
		   }
		   if(counter[2] == testPorts.length){
			   counter[1]++;
			   counter[2] = 0;
		   }
		   if(counter[1] == testHosts.length){
			   counter[0]++;
			   counter[1] = 0;
		   }

	   }
	   
   }
   ResultPair[] testSchemes =	 {  new ResultPair("http", true),	//Valid common inet
		    new ResultPair("https", true),		//Valid common inet
		    new ResultPair("file", true),		//Valid common local
		    new ResultPair("ftp", true),		//Valid common inet
		    new ResultPair("data", true),		//Valid common inet
		    new ResultPair("mailto", true),		//Valid common inet
		    new ResultPair("h-+.ps", true),		//Valid, '+', '-', '.' OK 
		    new ResultPair("ABC", true),		//Valid, capitols OK
		    new ResultPair("", true),			//Valid empty string
		    new ResultPair("https:", false),	//Invalid colon   
		    new ResultPair("http&", false),		//Invalid, '&' invalid scheme char
		    new ResultPair("123", false),		//Invalid, can't start with num
		    new ResultPair("+http", false),		//Invalid begin with alpha char
		    new ResultPair("-http", false),		//Invalid begin with alpha char
		    new ResultPair("a%%%:", false)		//Invalid, '%' not valid
		 };

ResultPair[] testHosts =	 {  new ResultPair("www.google.com", true),   //Valid host
		    new ResultPair("google.com", true),	    	//Valid host
		    new ResultPair("12345.org", true),	    	//Valid host
		    new ResultPair("www.12.org", true),	    	//Valid host
		    new ResultPair("localhost", true),
		    new ResultPair("test.", false),	      		//Invalid no TLD
		    new ResultPair(".test", false),	      		//Invalid host
		    new ResultPair("test", false),	      		//Invalid no TLD
		    new ResultPair("google.falseTLD", false),	//Invalid fake TLD
		    new ResultPair("123.012.123.230", true),	//Valid IP
		    new ResultPair("0.0.0.0", true),	    	//Valid IP
		    new ResultPair("255.255.255.255", true),	//Valid IP
		    new ResultPair("256.255.255.255", false),	//Invalid IP, 256
		    new ResultPair("255.256.255.255", false),	//Invalid IP, 256
		    new ResultPair("255.255.256.255", false), 	//Invalid IP, 256
		    new ResultPair("255.255.255.256", false), 	//Invalid IP, 256
		    new ResultPair("1.2.3.4.5", false),	      	//Invalid too large
		    new ResultPair("123.123.123", false),     	//Invalid too small
		    new ResultPair("", false),		      		//Invalid No empty host
		    new ResultPair(".123.123.123.123", false) 	//Invalid start char '.'
		    
	         };

ResultPair[] testPorts =	 {  new ResultPair("0", true),	//Valid port (low)
		    new ResultPair("3000", true),    //Valid port (mid)
		    new ResultPair("65535", true),   //Valid port (high)
		    new ResultPair("", true),		 //Valid, unspecified port
		    new ResultPair("-1", false),     //Invalid, non-negative
		    new ResultPair("65536", false),  //Invalid, out of range
		    new ResultPair("000123", false), //Invalid, too many digits
		    new ResultPair("ABC", false),    //Invalid, unsigned int
		    new ResultPair(":::", false)     //Invalid, unsigned int
		 };

ResultPair[] testPaths =	 {  new ResultPair("", true),	//Valid path-abempty
		    new ResultPair("/", true),		      			//Valid path-abempty
		    new ResultPair("/down/the/rabbit/hole", true), 	//Valid absolute
		    new ResultPair("/document.doc", true),    		//Valid rel file path
		    new ResultPair("//", false),	      			//Invalid no double '/'
		    new ResultPair("./test", false),	      		//Invalid no '.'
		    new ResultPair("../test", false)	      		//Invalid no double '.'
		 };

ResultPair[] testQueries =	 {  new ResultPair("", true),	//Valid no query
		    new ResultPair("key=val", true),	      		//Valid key/val
		    new ResultPair("ke1=va1&ke2=va2", true),  		//Valid multi key/val
		    new ResultPair("ke_1=va_1", true),	      		//Valid key/val
		    new ResultPair("un1qu37r4cking", true),   		//Valid tracking query
		    new ResultPair("key=val=key=val", true), 		//Invalid multi key/val
		    new ResultPair("key#val", false)	      		//Invalid '#' is query end
		 };

};
