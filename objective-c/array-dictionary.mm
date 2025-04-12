#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Create an NSArray of fruits
        NSArray *fruits = @[@"Apple", @"Banana", @"Cherry", @"Date"];
        
        // Print the array
        NSLog(@"Fruits Array:");
        for (NSString *fruit in fruits) {
            NSLog(@"%@", fruit);
        }

        // Create an NSDictionary of student grades
        NSDictionary *grades = @{
            @"Alice": @90,
            @"Bob": @85,
            @"Charlie": @92
        };
        
        // Print the dictionary
        NSLog(@"\nStudent Grades:");
        for (NSString *student in grades) {
            NSLog(@"%@: %@", student, grades[student]);
        }

        // Accessing a specific fruit
        NSString *firstFruit = fruits[0];
        NSLog(@"\nFirst fruit in the array: %@", firstFruit);

        // Accessing a specific grade
        NSNumber *aliceGrade = grades[@"Alice"];
        NSLog(@"Alice's grade: %@", aliceGrade);
    }
    return 0;
}
