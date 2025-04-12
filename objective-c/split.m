#import <Foundation/Foundation.h>

NSArray *splitBySpace(NSString *str) {
 return [str componentsSeparatedByString:@" "];
}

int main (int argc, const char * argv[])
{
 NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
 
 NSArray *words = splitBySpace(@"hello how are you");
 for (NSString *word in words) {
 NSLog(@"%@\n", word);
 }
 
 [pool drain];
 return 0;
}