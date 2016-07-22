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


import org.junit.Test;

import junit.framework.TestCase;
import junit.framework.Assert;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
@SuppressWarnings("deprecation")
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
   
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   @Test
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   boolean resultStatus;
	   boolean expected;
	   resultStatus = urlVal.isValid("http://www.amazon.com");
	   expected = true;
	   if(expected != resultStatus){
		   System.out.println("http://www.amazon.com");
		   System.out.println("isValid() = " + resultStatus + ", expected " + expected);
	   }
	   
	   resultStatus = urlVal.isValid("https://www.google.com/webhp?hl=en");
	   expected = true;
	   if(expected != resultStatus){
		   System.out.println("https://www.google.com/webhp?hl=en");
		   System.out.println("isValid() = " + resultStatus + ", expected " + expected);
	   }
	   
	   resultStatus = urlVal.isValid("https:///////www.yahoo.com/");
	   expected = true;
	   if(expected != resultStatus){
		   System.out.println("https:///////www.yahoo.com/");
		   System.out.println("isValid() = " + resultStatus + ", expected " + expected);
	   }
	   
	   resultStatus = urlVal.isValid("http://oregonstate.edu/");
	   expected = true;
	   if(expected != resultStatus){
		   System.out.println("http://oregonstate.edu/");
		   System.out.println("isValid() = " + resultStatus + ", expected " + expected);
	   }
	  
	   resultStatus = urlVal.isValid("https://w/#$\reddit.com");
	   expected = false;
	   if(expected != resultStatus){
		   System.out.println("http://oregonstate.edu/");
		   System.out.println("isValid() = " + resultStatus + ", expected " + expected);
	   }
	   
   }
   
   @Test
   public void testYourFirstPartition()
   {
	   
	   System.out.println("Testing Schemes");
	   ResultPair[] testCases = {new ResultPair("Http://", true),
			   				new ResultPair("6ttp://", false),
			   				new ResultPair("scheme1:", true),
			   				new ResultPair("ftp://", true),
			   				new ResultPair("+http://", false),
			   				new ResultPair("a234://", true),
			   				new ResultPair("-$ftp:", false),
			   				new ResultPair("$_#=", false)};
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i=0; i<testCases.length; i++){
		   boolean expected = testCases[i].valid;
		   boolean resultStatus = urlVal.isValidScheme(testCases[i].item);
		   String testCase = testCases[i].item;
		   if(expected != resultStatus){
			   System.out.println(testCase);
			   System.out.println("isValidSchemes() = " + resultStatus + ", expected " + expected);
		   }
		   
	   }
	   
	   
   }
   @Test
   public void testYourSecondPartition(){
	   System.out.println("Testing Authority");
	   ResultPair[] testCases = {new ResultPair("google.com", true),
			   				new ResultPair("yahoo.com", true),
			   				new ResultPair("255.com", true),
			   				new ResultPair("aaa.424", false),
			   				new ResultPair("gfx.cc", true),
			   				new ResultPair("gfx.au", true),
			   				new ResultPair("0.0.0.0", true),
			   				new ResultPair("google.d", false),
			   				new ResultPair("Google.c1m", false),
			   				new ResultPair("", false)
			   	   };
	   UrlValidator urlVal = new UrlValidator();
	   String testCase;
	   boolean result;
	   for(int i=0; i<testCases.length; i++){
		   boolean assertTestValue = testCases[i].valid;
		   result = urlVal.isValidAuthority(testCases[i].item);
		   testCase = testCases[i].item;
		   if(assertTestValue != result){
			   System.out.println(testCase);
			   System.out.println("isValidAuthority() = " + result + ", expected " + assertTestValue);
		   }
		   
	   }
	   
   }
   
   @Test
   public void testIsValid()
   {
	   ResultPair[] authorityCases = {new ResultPair((String) "google.com", true),
  				new ResultPair("yahoo.com", true),
  				new ResultPair("255.com", true),
  				new ResultPair("aaa.424", false),
  				new ResultPair("gfx.cc", true),
  				new ResultPair("gfx.au", true),
  				new ResultPair("0.0.0.0", true),
  				new ResultPair("google.d", false),
  				new ResultPair("Google.c1m", false),
  				new ResultPair("", false)
  	   };
	   ResultPair[] schemeCases = {new ResultPair("Http://", true),
  				new ResultPair("6ttp://", false),
  				new ResultPair("scheme1://", true),
  				new ResultPair("ftp://", true),
  				new ResultPair("+http://", false),
  				new ResultPair("a234://", true),
  				new ResultPair("-$ftp:", false),
  				new ResultPair("$_#=", false)};
	   ResultPair[] portCases = {new ResultPair(":21", true),
			   	new ResultPair(":80", true),
			   	new ResultPair(":443", true),
			   	new ResultPair(":123456", false)
	   };
	   ResultPair[] pathCases = {new ResultPair("//badpath", false),
			   new ResultPair("/path", true),
			   new ResultPair("/", true),
			   new ResultPair("//", false)	    		   
	   };
	   ResultPair[] queryCases = {new ResultPair("/?key1=val1", false),
			   new ResultPair("?trueQuery=1", true),
			   new ResultPair("/?/?badquery=2", false)
	   };
	   ResultPair[] fragmentCases = {new ResultPair("#truefrag", true),
			   new ResultPair("#", true)
	   };
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testUrl;
	   boolean result;
	   boolean assertTestValue;
	   for(int schemeIdx = 0; schemeIdx < schemeCases.length; schemeIdx++){
		   for(int authIdx = 0; authIdx < authorityCases.length; authIdx++){
			   for(int portIdx = 0; portIdx < portCases.length; portIdx++){
				   for(int pathIdx = 0; pathIdx < pathCases.length; pathIdx++){
					   for(int queryIdx = 0; queryIdx < queryCases.length; queryIdx++){
						   for(int fragIdx = 0; fragIdx < fragmentCases.length; fragIdx++){
							   testUrl = schemeCases[schemeIdx].item + authorityCases[authIdx].item + portCases[portIdx].item + pathCases[pathIdx].item + queryCases[queryIdx].item + fragmentCases[fragIdx].item;
							   assertTestValue = schemeCases[schemeIdx].valid & authorityCases[authIdx].valid & portCases[portIdx].valid & pathCases[pathIdx].valid & queryCases[queryIdx].valid & fragmentCases[fragIdx].valid;
							   result = urlVal.isValid(testUrl);
							   if(assertTestValue != result){
								   System.out.println(testUrl);
								   System.out.println("isValid() = " + result + ", expected " + assertTestValue);
							   }
						   }
					   }
				   }
			   }
		   }
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
    */
   

}
