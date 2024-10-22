#include <stdio.h>

#ifdef RASPBERRY_PI
#include "IT8951.h" // Include the IT8951 header
#else
#endif

void initializeIT8951Display() {
#ifdef RASPBERRY_PI
    // Initialize the IT8951 display
    if (IT8951_Init()) {
        std::cerr << "IT8951_Init error" << std::endl;
        exit(1);
    }
    IT8951_BMP_Example(1200, 1600, bmpPath);
    IT8951_Cancel();
#else
printf("Non-Raspberry Pi environment detected. Skipping IT8951 initialization.\n");
#endif
}

int main(int argc, char *argv[]) {
    initializeIT8951Display();
    return 0;
}

