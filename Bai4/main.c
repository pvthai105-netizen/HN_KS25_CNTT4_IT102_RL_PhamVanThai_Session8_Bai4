#include <stdio.h>

struct Subscription {
    int user_id;
    char account_name[31];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
};

int main(void) {
    struct Subscription users[50];
    int n;
    int i;
    int downgraded_count = 0;
    int violation_count = 0;
    const char *plan_name;

    do {
        printf("Nhap so luong tai khoan (1-50): ");
        scanf("%d", &n);

        if (n < 1 || n > 50) {
            printf("So luong khong hop le. Nhap lai!\n");
        }
    } while (n < 1 || n > 50);

    /* Nhap du lieu */
    for (i = 0; i < n; i++) {
        printf("\n--- Tai khoan %d ---\n", i + 1);

        printf("User ID: ");
        scanf("%d", &users[i].user_id);

        printf("Account name: ");
        scanf("%30s", users[i].account_name);

        printf("Plan type (1-Free, 2-Individual, 3-Family): ");
        scanf("%d", &users[i].plan_type);

        while (users[i].plan_type < 1 || users[i].plan_type > 3) {
            printf("Plan khong hop le. Nhap lai: ");
            scanf("%d", &users[i].plan_type);
        }

        printf("Active devices: ");
        scanf("%d", &users[i].active_devices);

        printf("Days overdue: ");
        scanf("%d", &users[i].days_overdue);

        users[i].account_status = 1;

        /* Xac dinh gioi han thiet bi */
        if (users[i].plan_type == 1) {
            users[i].max_devices = 1;
        } else if (users[i].plan_type == 2) {
            users[i].max_devices = 1;
        } else {
            users[i].max_devices = 5;
        }
    }

    /* Xu ly nghiep vu */
    for (i = 0; i < n; i++) {

        /* No qua 3 ngay -> ha cap Free */
        if (users[i].days_overdue > 3) {
            users[i].plan_type = 1;
            users[i].max_devices = 1;
            users[i].account_status = 0;
            downgraded_count++;
        }

        /* Kiem tra vi pham thiet bi sau khi ha cap */
        if (users[i].active_devices > users[i].max_devices) {
            violation_count++;
        }
    }

    /* Bao cao */
    printf("\n====================================================================\n");
    printf("             STREAMFLIX SUBSCRIPTION AUDIT REPORT\n");
    printf("====================================================================\n");

    printf("%-8s %-20s %-12s %-15s %-12s %-12s\n",
           "User ID", "Account Name", "Plan",
           "Devices", "Overdue", "Status");

    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {

        if (users[i].plan_type == 1) {
            plan_name = "Free";
        } else if (users[i].plan_type == 2) {
            plan_name = "Individual";
        } else {
            plan_name = "Family";
        }

        printf("%-8d %-20s %-12s %d/%-11d %-12d %-12s\n",
               users[i].user_id,
               users[i].account_name,
               plan_name,
               users[i].active_devices,
               users[i].max_devices,
               users[i].days_overdue,
               users[i].account_status == 1 ? "Active" : "Downgraded");
    }

    printf("--------------------------------------------------------------------\n");
    printf("Tong tai khoan da ra soat: %d\n", n);
    printf("So tai khoan bi ha cap: %d\n", downgraded_count);
    printf("So tai khoan vi pham thiet bi: %d\n", violation_count);

    return 0;
}
