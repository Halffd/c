#include <stdio.h>
#include <stdlib.h>

// Prototype of recursive function
void mover(int n, char Orig, char Temp, char Dest, int depth);

int main() {
    mover(3, 'O', 'T', 'D', 0); // 'O' = Origem, 'T' = Temporária, 'D' = Destino
    system("pause");
    return 0;
}

void mover(int n, char Orig, char Temp, char Dest, int depth) {
    for (int i = 0; i < depth; i++) printf("  "); // Indentation for clarity
    printf("[Depth %d] Called mover(%d, %c, %c, %c)\n", depth, n, Orig, Temp, Dest);

    if (n == 1) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("Move disk 1 from %c to %c\n", Orig, Dest);
    } else {
        mover(n - 1, Orig, Dest, Temp, depth + 1);
        
        for (int i = 0; i < depth; i++) printf("  ");
        printf("Move disk %d from %c to %c\n", n, Orig, Dest);
        
        mover(n - 1, Temp, Orig, Dest, depth + 1);
    }

    for (int i = 0; i < depth; i++) printf("  ");
    printf("[Depth %d] Exiting mover(%d, %c, %c, %c)\n", depth, n, Orig, Temp, Dest);
}
