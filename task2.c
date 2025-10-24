#include <stdio.h>
#include <ctype.h>
float toCelsius(float temp, char scale) {
    switch (toupper(scale)) {
        case 'C': return temp;
        case 'F': return (temp - 32) * 5.0 / 9.0;
        case 'K': return temp - 273.15;
        default: return 0.0;
    }
}

float fromCelsius(float celsius, char scale) {
    switch (toupper(scale)) {
        case 'C': return celsius;
        case 'F': return (celsius * 9.0 / 5.0) + 32;
        case 'K': return celsius + 273.15;
        default: return 0.0;
    }
}

void getCategory(float celsius, char *category, const char **advisory) {
    if (celsius < 0) {
        *category = 'F';
        *advisory = "Wear a heavy coat!";
    } else if (celsius < 10) {
        *category = 'C';
        *advisory = "Wear a jacket.";
    } else if (celsius < 25) {
        *category = 'O';
        *advisory = "Enjoy the weather!";
    } else if (celsius < 35) {
        *category = 'H';
        *advisory = "Drink lots of water!";
    } else {
        *category = 'E';
        *advisory = "Stay indoors and stay cool!";
    }
}

int main(void) {
    float temp, converted;
    char fromScale, toScale, category;
    const char *advisory;

    printf("Enter the temperature value: ");
    scanf("%f", &temp);

    printf("Enter the original scale (C, F, or K): ");
    scanf(" %c", &fromScale);

    printf("Enter the scale to convert to (C, F, or K): ");
    scanf(" %c", &toScale);

    float celsius = toCelsius(temp, fromScale);
    converted = fromCelsius(celsius, toScale);

    getCategory(celsius, &category, &advisory);

    printf("Converted temperature: %.2f %c\n", converted, toupper(toScale));

    switch (category) {
        case 'F': printf("Temperature category: Freezing\n"); break;
        case 'C': printf("Temperature category: Cold\n"); break;
        case 'O': printf("Temperature category: Comfortable\n"); break;
        case 'H': printf("Temperature category: Hot\n"); break;
        case 'E': printf("Temperature category: Extreme Heat\n"); break;
    }

    printf("Weather advisory: %s\n", advisory);

    return 0;
}
