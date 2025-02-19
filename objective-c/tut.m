#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    NSString *quote = @"Dogs have masters, while cats have staff";
    
    // Original operations
    NSLog(@"Size of String : %d", (int)[quote length]);
    NSLog(@"Character at 5 : %c", [quote characterAtIndex:5]);
    
    char *name = "Derek";
    NSString *myName = [NSString stringWithFormat:@"- %s", name];
    
    BOOL isStringEqual = [quote isEqualToString:myName];
    printf("Are strings equal : %d\n", isStringEqual);
    
    const char *uCString = [[myName uppercaseString] UTF8String];
    printf("%s\n", uCString);
    
    // New operations
    NSString *who1eQuote = [quote stringByAppendingString:myName];
    
    NSRange searchResult = [who1eQuote rangeOfString:@"Derek"];
    if(searchResult.location == NSNotFound) {
        NSLog(@"String not found");
    } else {
        printf("Derek is at index %lu and is %lu long\n", 
              (unsigned long)searchResult.location, 
              (unsigned long)searchResult.length);
    }
    
    NSRange range = NSMakeRange(42, 5);
    const char *newQuote = [[who1eQuote stringByReplacingCharactersInRange:range 
                                      withString:@"Anon"] UTF8String];
    printf("%s\n", newQuote);
    
    [pool drain];
    return 0;
}