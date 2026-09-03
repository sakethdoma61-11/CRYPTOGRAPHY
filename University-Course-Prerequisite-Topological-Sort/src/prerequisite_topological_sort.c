#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 10
#define MAX_NAME 50
#define TICKET_LIFETIME 300

/* User database */
typedef struct {
    char username[MAX_NAME];
    char password[MAX_NAME];
} User;

/* Ticket Granting Ticket */
typedef struct {
    char username[MAX_NAME];
    char sessionKey[MAX_NAME];
    time_t issueTime;
    time_t expiryTime;
    int valid;
} TGT;

/* Service Ticket */
typedef struct {
    char username[MAX_NAME];
    char serviceName[MAX_NAME];
    char sessionKey[MAX_NAME];
    time_t issueTime;
    time_t expiryTime;
    int valid;
} ServiceTicket;

/* Global user database */
User users[MAX_USERS] = {
    {"saketh", "crypto123"},
    {"admin", "admin123"},
    {"employee1", "emp123"}
};

int userCount = 3;

/* Generate a simple session key for demonstration */
void generateSessionKey(char *key, const char *username)
{
    sprintf(key, "SK_%s_%ld", username, (long)time(NULL));
}

/* Find user in database */
int authenticateUser(const char *username, const char *password)
{
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }

    return 0;
}

/* Authentication Server generates TGT */
TGT authenticationServer(const char *username)
{
    TGT ticket;

    strcpy(ticket.username, username);

    generateSessionKey(ticket.sessionKey, username);

    ticket.issueTime = time(NULL);
    ticket.expiryTime = ticket.issueTime + TICKET_LIFETIME;
    ticket.valid = 1;

    printf("\n============================================\n");
    printf(" AUTHENTICATION SERVER (AS)\n");
    printf("============================================\n");

    printf("User authenticated successfully.\n");
    printf("TGT generated for user: %s\n", ticket.username);
    printf("Session Key: %s\n", ticket.sessionKey);
    printf("Ticket Lifetime: %d seconds\n", TICKET_LIFETIME);

    return ticket;
}

/* Check whether TGT is valid */
int validateTGT(TGT *tgt)
{
    time_t currentTime = time(NULL);

    if (!tgt->valid) {
        return 0;
    }

    if (currentTime > tgt->expiryTime) {
        tgt->valid = 0;
        return 0;
    }

    return 1;
}

/* Ticket Granting Server generates service ticket */
ServiceTicket ticketGrantingServer(TGT *tgt, const char *serviceName)
{
    ServiceTicket ticket;

    strcpy(ticket.username, tgt->username);
    strcpy(ticket.serviceName, serviceName);

    generateSessionKey(ticket.sessionKey, tgt->username);

    ticket.issueTime = time(NULL);
    ticket.expiryTime = ticket.issueTime + TICKET_LIFETIME;
    ticket.valid = 1;

    printf("\n============================================\n");
    printf(" TICKET GRANTING SERVER (TGS)\n");
    printf("============================================\n");

    printf("TGT validated successfully.\n");
    printf("Service requested: %s\n", serviceName);
    printf("Service ticket generated.\n");
    printf("Service Session Key: %s\n", ticket.sessionKey);

    return ticket;
}

/* Application server validates service ticket */
int applicationServer(ServiceTicket *ticket)
{
    time_t currentTime = time(NULL);

    printf("\n============================================\n");
    printf(" APPLICATION / SERVICE SERVER\n");
    printf("============================================\n");

    if (!ticket->valid) {
        printf("ACCESS DENIED: Invalid service ticket.\n");
        return 0;
    }

    if (currentTime > ticket->expiryTime) {
        ticket->valid = 0;
        printf("ACCESS DENIED: Service ticket has expired.\n");
        return 0;
    }

    printf("Service ticket validated successfully.\n");
    printf("User: %s\n", ticket->username);
    printf("Service: %s\n", ticket->serviceName);
    printf("ACCESS GRANTED.\n");

    return 1;
}

/* Demonstrate ticket information */
void displayTicketInformation(TGT *tgt, ServiceTicket *serviceTicket)
{
    printf("\n============================================\n");
    printf(" TICKET INFORMATION\n");
    printf("============================================\n");

    printf("\n--- Ticket Granting Ticket (TGT) ---\n");
    printf("Username       : %s\n", tgt->username);
    printf("Session Key    : %s\n", tgt->sessionKey);
    printf("Issue Time     : %s", ctime(&tgt->issueTime));
    printf("Expiry Time    : %s", ctime(&tgt->expiryTime));
    printf("Status         : %s\n",
           tgt->valid ? "VALID" : "INVALID");

    printf("\n--- Service Ticket ---\n");
    printf("Username       : %s\n", serviceTicket->username);
    printf("Service        : %s\n", serviceTicket->serviceName);
    printf("Session Key    : %s\n", serviceTicket->sessionKey);
    printf("Issue Time     : %s", ctime(&serviceTicket->issueTime));
    printf("Expiry Time    : %s", ctime(&serviceTicket->expiryTime));
    printf("Status         : %s\n",
           serviceTicket->valid ? "VALID" : "INVALID");
}

/* Replay attack demonstration */
void replayAttackTest(ServiceTicket *ticket)
{
    printf("\n============================================\n");
    printf(" REPLAY ATTACK DETECTION TEST\n");
    printf("============================================\n");

    /*
     * Simulate an already-used/invalid ticket.
     * In a real Kerberos system, authenticators,
     * timestamps and replay caches are used.
     */

    ticket->valid = 0;

    printf("Attacker attempts to reuse the service ticket...\n");

    if (!ticket->valid) {
        printf("REPLAY DETECTED.\n");
        printf("ACCESS DENIED.\n");
    } else {
        printf("ACCESS GRANTED.\n");
    }
}

/* Main function */
int main()
{
    char username[MAX_NAME];
    char password[MAX_NAME];
    char serviceName[MAX_NAME];

    TGT tgt;
    ServiceTicket serviceTicket;

    printf("====================================================\n");
    printf("      KERBEROS ENTERPRISE AUTHENTICATION SYSTEM\n");
    printf("====================================================\n");

    printf("\nEnter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    /* Step 1: Client Authentication */
    printf("\n[CLIENT]\n");
    printf("Sending authentication request to Authentication Server...\n");

    /* Step 2: Authentication Server */
    if (!authenticateUser(username, password)) {

        printf("\n============================================\n");
        printf(" AUTHENTICATION FAILED\n");
        printf("============================================\n");

        printf("Invalid username or password.\n");
        printf("ACCESS DENIED.\n");

        return 0;
    }

    tgt = authenticationServer(username);

    /* Step 3: Client requests service */
    printf("\n[CLIENT]\n");
    printf("TGT received from Authentication Server.\n");

    printf("\nEnter service to access: ");
    scanf("%49s", serviceName);

    printf("\n[CLIENT -> TGS]\n");
    printf("Requesting service ticket...\n");

    /* Step 4: Validate TGT */
    if (!validateTGT(&tgt)) {
        printf("\nTGT is invalid or expired.\n");
        printf("Service ticket cannot be generated.\n");
        return 0;
    }

    /* Step 5: TGS generates service ticket */
    serviceTicket =
        ticketGrantingServer(&tgt, serviceName);

    /* Step 6: Client sends service ticket */
    printf("\n[CLIENT -> APPLICATION SERVER]\n");
    printf("Sending service ticket...\n");

    /* Step 7: Application server grants access */
    applicationServer(&serviceTicket);

    /* Display ticket details */
    displayTicketInformation(&tgt, &serviceTicket);

    /* Demonstrate replay detection */
    replayAttackTest(&serviceTicket);

    printf("\n====================================================\n");
    printf("              KERBEROS PROCESS COMPLETED\n");
    printf("====================================================\n");

    return 0;
}
