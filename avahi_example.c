#include <avahi-client/client.h>
#include <avahi-client/publish.h>
#include <avahi-common/simple-watch.h>
#include <stdio.h>

// Callback function when the service is successfully published
static void entry_group_callback(AvahiEntryGroup *g, AvahiEntryGroupState state, void *userdata) {
    if (state == AVAHI_ENTRY_GROUP_ESTABLISHED) {
        printf("Service '%s' successfully published.\n", (const char *)userdata);
    }
}

int main() {
    AvahiSimplePoll *poll = avahi_simple_poll_new();
    if (!poll) {
        fprintf(stderr, "Failed to create Avahi poll object.\n");
        return 1;
    }

    AvahiClient *client = avahi_client_new(avahi_simple_poll_get(poll), 0, NULL, NULL, NULL);
    if (!client) {
        fprintf(stderr, "Failed to create Avahi client.\n");
        return 1;
    }

    AvahiEntryGroup *group = avahi_entry_group_new(client, entry_group_callback, "MyService");
    if (!group) {
        fprintf(stderr, "Failed to create Avahi entry group.\n");
        return 1;
    }

    // Publish the service
    avahi_entry_group_add_service(group, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, 0, "MyService", "_example._tcp", NULL, NULL, 12345, NULL);
    avahi_entry_group_commit(group);

    // Run the Avahi event loop
    avahi_simple_poll_loop(poll);

    // Cleanup
    avahi_entry_group_free(group);
    avahi_client_free(client);
    avahi_simple_poll_free(poll);

    return 0;
}
/*
 * avahi_simple_poll_new function is used to create an Avahi event loop, represented by AvahiSimplePoll. The event loop allows handling asynchronous Avahi events.

AvahiClient Initialization: The avahi_client_new function is used to create an Avahi client. The client is necessary for interacting with the Avahi system. It's associated with the event loop created earlier.

AvahiEntryGroup Initialization: An Avahi entry group is created using the avahi_entry_group_new function. This group is essential for publishing a service. The entry_group_callback function will be called when the service is established.
 *
 *
 * The code publishes a service named "MyService" of type "_example._tcp" on all network interfaces and protocols (IPv4 and IPv6) on port 12345. This service can be discovered on the local network.
 *
 *
 */


