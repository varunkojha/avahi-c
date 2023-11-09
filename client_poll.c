/*
 * To demonstrates a simple service discovery scenario. 
 * It creates an Avahi client and a service resolver to look for services with the type _varun_tv._tcp using mDNS. 
 * The resolve_callback function is triggered upon finding a printer service.
 */
#include <avahi-client/client.h>
#include <avahi-client/publish.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/thread-watch.h>
#include <stdio.h>

// Callback function for service resolution
static void resolve_callback(
    AvahiServiceResolver *r,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *address,
    uint16_t port,
    AvahiStringList *txt,
    AvahiLookupResultFlags flags,
    void *userdata
) {
    // Handling service resolution
    if (event == AVAHI_RESOLVER_FOUND) {
        printf("Resolved service: %s, %s, %s, %s:%u\n", name, type, domain, host_name, port);
        // Handle the discovered service here
	//
	// PENDING
    }
}

int main() {
    AvahiSimplePoll *poll = avahi_simple_poll_new();
    AvahiClient *client = avahi_client_new(avahi_simple_poll_get(poll), 0, NULL, NULL, NULL);

    if (!client) {
        fprintf(stderr, "Error creating Avahi client.\n");
        return 1;
    }

    AvahiServiceResolver *resolver = avahi_service_resolver_new(
        client,
        AVAHI_IF_UNSPEC,
        AVAHI_PROTO_UNSPEC,
        "_varun_tv._tcp", // Looking for a printer service
        NULL,
        AVAHI_PROTO_UNSPEC,
        AVAHI_LOOKUP_USE_MULTICAST, // Using multicast DNS
        resolve_callback,
        NULL
    );

    if (!resolver) {
        fprintf(stderr, "Error creating Avahi service resolver.\n");
        return 1;
    }

    // Run the Avahi event loop
    avahi_simple_poll_loop(poll);

    // Cleanup
    avahi_service_resolver_free(resolver);
    avahi_client_free(client);
    avahi_simple_poll_free(poll);

    return 0;
}

