#import <Foundation/Foundation.h>

// Declaração da sub-rotina
NSInteger soma(NSInteger a, NSInteger b) {
    NSInteger resultado = a + b;
    return resultado;
}

int main(int argc, const char * argv[]) {
        NSInteger n = 8;
        NSInteger m = 4;
        NSLog(@"%ld", (long)soma(n, m)); // Chamada da sub-rotina (soma)
    return 0;
}
