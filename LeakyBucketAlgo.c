#include <stdio.h>

int main() {
    int bucket_size, leak_rate;
    int bucket = 0;
    int incoming, time;

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);

    printf("Enter leak rate (packets per time unit): ");
    scanf("%d", &leak_rate);

    printf("Enter number of time units to simulate: ");
    scanf("%d", &time);

    for (int t = 1; t <= time; t++) {
        printf("\nTime %d\n", t);

        printf("Enter incoming packets: ");
        scanf("%d", &incoming);

        // Add packets to bucket
        if (incoming + bucket <= bucket_size) {
            bucket += incoming;
            printf("Accepted packets: %d\n", incoming);
            printf("Dropped packets: 0\n");
        } else {
            int dropped = (incoming + bucket) - bucket_size;
            int accepted = incoming - dropped;
            bucket = bucket_size;
            printf("Accepted packets: %d\n", accepted);
            printf("Dropped packets: %d\n", dropped);
        }

        // Leak packets
        if (bucket >= leak_rate) {
            bucket -= leak_rate;
            printf("Leaked packets: %d\n", leak_rate);
        } else {
            printf("Leaked packets: %d\n", bucket);
            bucket = 0;
        }

        printf("Packets remaining in bucket: %d\n", bucket);
    }

    return 0;
}

