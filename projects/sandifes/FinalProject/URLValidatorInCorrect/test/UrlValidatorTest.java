

import junit.framework.TestCase;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //Programming based testing

	   int bugsFound = 0;

	   System.out.println("  ****Programming based testing****");
	   System.out.println("Testing with invalid URLs:");

	   String[] urlSchemeFalse = {"http;://", "http", "http:://", "http:::"};
	   String[] urlAuthorityFalse = {"www.fun", ".com", "!!!.google.com", "www.google.!!!"};
	   String[] urlPortFalse = {":squid", ":1squid2", ":-2222", ":123456789"};
	   String[] urlPathFalse = {"//bugs", "/bugs//", "/|bugs", "/b/u//g/s"};
	   String[] urlPathOptionsFalse = {"//buttons", "/buttons///", "/buttons/?$&", "/b/u/tto//ns"};
	    
	   String[] urlSchemeTrue = {"http://", "http://", "", ""}; //code fails when https://, h3t://, or ftp:// are used
	   String[] urlAuthorityTrue = {"www.google.com", "yahoo.com", "www.byte.us.com", "byte.au"};
	   String[] urlPortTrue = {":80", ":8080", ":1234", ""};
	   String[] urlPathTrue = {"/tic", "/tic/tac", "/tic~tac", ""};
	   String[] urlPathOptionsTrue = {"/cake", "/cake?pie=100", "/search?p=cake+pie", "/search?q=valid+url+path+characters"};	   	
	   
		
	   	System.out.println("Test Known False Scheme...");
	   	for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeFalse[i] + urlAuthorityTrue[j] + urlPortTrue[k] + urlPathTrue[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);
							
							  if ( myTest8 != false ) {
								  bugsFound++;
							
								  System.out.println("Bug found, expected false: " + myUrl);
							
							  }
						}
					}
				}
	
			}
	   	}
	   	
	   	System.out.println("Test Known False Authority...");
	   	for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityFalse[j] + urlPortTrue[k] + urlPathTrue[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);
							
							  if ( myTest8 != false ) {
								  bugsFound++;
							
								  System.out.println("Bug found, expected false: " + myUrl);
							
							  }
						}
					}
				}
	
			}
	   	}
	   	
	   	System.out.println("Test Known False Port...");
	   	for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityTrue[j] + urlPortFalse[k] + urlPathTrue[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);
							
							  if ( myTest8 != false ) {
								  bugsFound++;
							
								  System.out.println("Bug found, expected false: " + myUrl);
							
							  }
						}
					}
				}
	
			}
	   	}

	   	System.out.println("Test Known False Path...");
	   	for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityTrue[j] + urlPortTrue[k] + urlPathFalse[l] + urlPathOptionsTrue[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);
							
							  if ( myTest8 != false ) {
								  bugsFound++;
							
								  System.out.println("Bug found, expected false: " + myUrl);
							
							  }
						}
					}
				}
	
			}
	   	}
	   	
	   	System.out.println("Test Known False Path Options/Queries...");
	   	for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++) {
					for(int l = 0; l < 4; l++) {
						for(int m = 0; m < 4; m++) {
							String myUrl = urlSchemeTrue[i] + urlAuthorityTrue[j] + urlPortTrue[k] + urlPathTrue[l] + urlPathOptionsFalse[m] ;	
							UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
							boolean myTest8 = urlVal.isValid(myUrl);
							
							  if ( myTest8 != false ) {
								  bugsFound++;
							
								  System.out.println("Bug found, expected false: " + myUrl);
							
							  }
						}
					}
				}
	
			}
	   	}
	   	System.out.println("Total bugs found: " + bugsFound);	   	
	   	
  }
   
}
