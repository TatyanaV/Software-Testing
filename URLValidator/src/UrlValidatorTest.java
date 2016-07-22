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


import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
 //  First just do manual testing. Call the valid method of URLValidator with different possible valid/invalid inputs and see if you find a failure. (2 points)
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nAllowing ALLOW_ALL_SCHEMES: \n");
	   
	   //VALIDATIONG ALL SCHEMES
	   //testing VALID scheme, VALID authority, valid port
	   //EXPECTED RESULT: true
	   System.out.println("\nShould Validate these schema AND Authotiry:");
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   System.out.println(urlVal.isValid("http://ww.amazon.com"));
	   System.out.println(urlVal.isValid("www.amazon.com")); //for some reason this failed??
	   System.out.println(urlVal.isValid("h3tp://www.amazon.com"));
	   System.out.println(urlVal.isValid("htt://www.amazon.com"));
	  
	   
	   //testing INVALID scheme, valid authority, valid port
	   //EXPECTED RESULT: false
	   System.out.println("\nShould NOT Validate these schema:");
	   System.out.println(urlVal.isValid("hhhh:/www.amazon.com"));
	   System.out.println(urlVal.isValid("://ww.amazon.com"));
	   System.out.println(urlVal.isValid("http:/www.amazon.com"));
	   System.out.println(urlVal.isValid("amazon.com"));


	   //testing valid scheme, valid authority, valid port, VALID path
	   //EXPECTED RESULT: true
	   System.out.println("\nShould Validate this path:");
	   System.out.println(urlVal.isValid("http://www.amazon.com/gp/goldbox/ref=nav_cs_gb"));
	   System.out.println(urlVal.isValid("http://www.amazon.com/"));
	   
	   //testing valid scheme, valid authority, valid port, INVALID path
	   //EXPECTED RESULT: false
	   System.out.println("\nShould NOT Validate this path:");
	   System.out.println(urlVal.isValid("http://www.amazon.com//"));
	   System.out.println(urlVal.isValid("http://www.amazon.com/...."));
	   
	   //testing valid scheme, valid authority, VALID port
	   //EXPECTED RESULT: true
	   System.out.println("\nShould Validate the following ports:");	   
	   System.out.println(urlVal.isValid("http://www.amazon.com:80"));
	   System.out.println(urlVal.isValid("http://www.amazon.com:400"));
	   System.out.println(urlVal.isValid("http://www.amazon.com:6553"));
	   System.out.println(urlVal.isValid("http://www.amazon.com:65535"));
	   
	   //testing valid scheme, valid authority, INVALID port
	   //EXPECTED RESULT: false
	   System.out.println("\nShould NOT Validate the following ports:");	   
	   System.out.println(urlVal.isValid("http://www.amazon.com:-80"));
	   System.out.println(urlVal.isValid("http://www.amazon.com:A80"));
	   
	   //testing valid scheme, INVALID authority, valid port, valid path
	   //EXPECTED RESULT: false
	   System.out.println("\nShould NOT Validate these authority:");
	   System.out.println(urlVal.isValid("https://www.amoz5454___   dsa.com/index_2_4.html"));
	   System.out.println(urlVal.isValid("https:// /index_2_4.html"));
	   
   
	   //testing valid scheme, valid authority, VALID query
	   //EXPECTED RESULT: true
	   System.out.println("\nShould Validate the following queries:");	   
	   System.out.println(urlVal.isValid("http://www.amazon.com/?action=view"));
	   System.out.println(urlVal.isValid("http://www.amazon.com/?action"));
	   System.out.println(urlVal.isValid("http://www.amazon.com/?action="));
	   System.out.println(urlVal.isValid("http://www.amazon.com/?"));
	   
	   //testing valid scheme, valid authority, INVALID query
	   //EXPECTED RESULT: FALSE
	   System.out.println("\nShould NOT Validate the following queries:");	   
	   System.out.println(urlVal.isValid("http://www.amazon.com/?action="));
	   System.out.println(urlVal.isValid("http://www.amazon.com/?action22=view"));
	   
	   // Test for 2 slashes in paths (allowed).
	   System.out.println("Allow two slashes in the path component of the URL.");
	    /**
	     * Allow two slashes in the path component of the URL.
	     */
	 //EXPECTED RESULT: true
	   urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
	   System.out.println("\nShould Validate the following 2 slashes in the path componenet of the URL:");
	   System.out.println(urlVal.isValid("http://www.amazon.com//path"));
	 //EXPECTED RESULT: false
	   System.out.println("\nShould NOT Validate the following 2 slashes in the componenet other than path of the URL:");
	   System.out.println(urlVal.isValid("http:///www.amazon.com//path"));
	   System.out.println("\nShould NOT Validate the following 3 slashes in the path of the URL:");
	   System.out.println(urlVal.isValid("http:///www.amazon.com///path"));
	   
	   
   }
   

   
 
   
   //scheme partitioning
   //declare some variables
   //Declare known valid URL components.
   String validAuthority = "www.amazon.com";
   String validScheme = "http://";
   String validPort = ":80";
   String validPath = "/path";
   String validQuery = "?action=view";
   
   
 public void testYourFirstPartition()
   {
	    System.out.println("\nTESTING Valid SCHEME:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be true:\n");
	    String[] listOfValidSchemes = {"http://","https://","","h3tp://","ftp://"};
	    UrlValidator urlVal = new UrlValidator();
	    for (int i = 0; i < listOfValidSchemes.length; i++) {
	      String curScheme = listOfValidSchemes[i] + validAuthority + validPort + validPath;
	      System.out.println("Testing " + curScheme);
	      System.out.println(urlVal.isValid(curScheme));
  	    }
	    
	    System.out.println("\nTESTING InValid SCHEME:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be false:\n");
	    String[] listOfInValidSchemes = {"3ht://","http:/","http:","http/","://"};
	    for (int i = 0; i < listOfInValidSchemes.length; i++) {
	      String curScheme2 = listOfInValidSchemes[i] + validAuthority + validPort + validPath;
	      System.out.println("Testing " + curScheme2);
	      System.out.println(urlVal.isValid(curScheme2));
  	    } 
	   
   }
   
 //authority partitioning
 public void testYourSecondPartition(){
	    System.out.println("\nTESTING Valid AUTHORITY:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be true:\n");
	    String[] listOfValidAuthority = {"www.amazon.com","amazon.com","amazon.org","amazon.edu"};
	    UrlValidator urlVal2 = new UrlValidator();
	    for (int i = 0; i < listOfValidAuthority.length; i++) {
	      String curAuthority = validScheme + listOfValidAuthority[i] + validPort + validPath;
	      System.out.println("Testing " + curAuthority);
	      System.out.println(urlVal2.isValid(curAuthority));
	    }
	    
	    System.out.println("\nTESTING InValid AUTHORITY:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be false:\n");
	    String[] listOfInValidAuthority = {""," ","ppp.amazon.com","www.amazon%.com","www.amazon"};
	    
	    for (int i = 0; i < listOfInValidAuthority.length; i++) {
	      String curAuthority2 = validScheme + listOfInValidAuthority[i] + validPort + validPath;
	      System.out.println("Testing " + curAuthority2);
	      System.out.println(urlVal2.isValid(curAuthority2));
	    }
	   
 	}
 
 //port partitioning
 public void testYourThirdPartition(){
	    System.out.println("\nTESTING Valid PORT:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be true:\n");
	    String[] listOfValidPort = {":0", ":11", ":52", ":89", ":125", ":265", ":935", ":1115", ":5858",":15455", ":65530"};
	    UrlValidator urlVal2 = new UrlValidator();
	    for (int i = 0; i < listOfValidPort.length; i++) {
	      String curPort = validScheme + validAuthority + listOfValidPort[i] + validPath;
	      System.out.println("Testing " + curPort);
	      System.out.println(urlVal2.isValid(curPort));
	    }
	    
	    System.out.println("\nTESTING InValid PORT:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be false:\n");
	    String[] listOfInValidPort = {":-0", ":a11", ":52a", ":", ":154578787", ":65539"};
	    
	    for (int i = 0; i < listOfInValidPort.length; i++) {
	      String curPort2 = validScheme + validAuthority + listOfInValidPort[i] + validPath;
	      System.out.println("Testing " + curPort2);
	      System.out.println(urlVal2.isValid(curPort2));
	    }
	   
	}

 //port query
 public void testYourFourthPartition(){
	    System.out.println("\nTESTING Valid QUERY:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be true:\n");
	    String[] listOfValidQuery = {"?action=edit&mode=up", "?newwindow=1&q=url+query", "?action=edit&mode=up", " "};
	    UrlValidator urlVal2 = new UrlValidator();
	    for (int i = 0; i < listOfValidQuery.length; i++) {
	      String curQuery = validScheme  + validAuthority + validPort + validPath + listOfValidQuery[i];
	      System.out.println("Testing " + curQuery);
	      System.out.println(urlVal2.isValid(curQuery));
	    }
	    
	    System.out.println("\nTESTING InValid QUERY:\n");
	    System.out.println("\n*********************************************\n");
	    System.out.println("\nEverything should be false:\n");
	    String[] listOfInValidQuery = {"/ ","??action=view"};
	    
	    for (int i = 0; i < listOfInValidQuery.length; i++) {
	      String curQuery2 = validScheme  + validAuthority + validPort + validPath + listOfInValidQuery[i];
	      
	      System.out.println("Testing " + curQuery2);
	      System.out.println(urlVal2.isValid(curQuery2));
	    }
	   
	}   
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
 * @throws FileNotFoundException 
    */

   public void testValidURL() throws FileNotFoundException{
	   String[] listOfValidSchemes = {"http://","https://","ftp://"};//true
	   //String[] listOfInValidSchemes = {"3ht://","http:/","http:","http/","://"};//false
	   String[] listOfValidAuthority = {"www.amazon.com","amazon.com","amazon.org","amazon.edu"};//true
	  // String[] listOfInValidAuthority = {"","  ", "ppp.amazon.com","www.amazon%.com","www.amazon"};//false
	   String[] listOfValidPort = {":0", ":11", ":52", ":89", ":125", ":265", ":935", ":1115", ":5858",":15455", ":65530"};//true
	   //String[] listOfInValidPort = {":-0", ":a11", ":52a", ":", "154578787", "65539"};//false
	   String[] listOfValidPath = {"","/path","/path/","/path2/../path1" };//true
	   //String[] listOfInValidPath = {"/path2/..path1222","noslashes","/////too maany slashes",};//false
	   String[] listOfValidQuery = {"?action=edit&mode=up", "?newwindow=1&q=url+query", "?action=edit&mode=up", " "};//true
	  // String[] listOfInValidQuery = {"/ ","??action=view"};//false
	   UrlValidator urlVal3 = new UrlValidator();
	   //String[] badUrls = new String[1000000000];

	   System.out.println("\nTesting all possible permutations of their combinations VALID URLs:\n");
	   System.out.println("\nlistOfValidSchemes+listOfValidAuthority+listOfValidPort+listOfValidPath\n");
	   for (int i = 0; i < listOfValidSchemes.length; i++) {
	    	for (int k = 0; k < listOfValidAuthority.length; k++) {
	    		for (int j = 0; j < listOfValidPort.length;j++) {
	    			for (int m = 0; m < listOfValidPath.length; m++) {
	    				      String validURL = listOfValidSchemes[i]  + listOfValidAuthority[k] + listOfValidPort[j] + listOfValidPath[m];
	    				      System.out.println("Testing " + validURL);
	    				      System.out.println(urlVal3.isValid(validURL));
					
	    			}
	    		}
	    	}
	    }
	  }

   }
