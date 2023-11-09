#include <avahi-client/client.h>
#include <avahi-client/publish.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/error.h>

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#define SERVICE_NAME "My Test Service"
#define SERVICE_TYPE "_http._tcp"
#define SERVICE_PORT 8000

void client_callback(AvahiClient *client, AvahiClientState state, void *userdata)
{
    AvahiSimplePoll *poll = (AvahiSimplePoll *)userdata;

    switch (state)
    {
    case AVAHI_CLIENT_S_RUNNING:
        std::cout << "Avahi client running" << std::endl;
        break;
    case AVAHI_CLIENT_FAILURE:
        std::cerr << "Avahi client failure: " << avahi_strerror(avahi_client_errno(client)) << std::endl;
        avahi_simple_poll_quit(poll);
        break;
    case AVAHI_CLIENT_S_COLLISION:
        std::cerr << "Avahi client collision" << std::endl;
        avahi_simple_poll_quit(poll);
        break;
    case AVAHI_CLIENT_S_REGISTERING:
        std::cout << "Avahi client registering" << std::endl;
        break;
    case AVAHI_CLIENT_CONNECTING:
        std::cout << "Avahi client connecting" << std::endl;
        break;
    }
}

void resolve_callback(AvahiServiceResolver *resolver, AvahiIfIndex interface, AvahiProtocol protocol,
                      AvahiResolverEvent event, const char *name, const char *type,
                      const char *domain, const char *host_name, const AvahiAddress *address,
                      uint16_t port, AvahiStringList *txt, AvahiLookupResultFlags flags, void *userdata)
{
    if (event == AVAHI_RESOLVER_FAILURE)
    {
        std::cerr << "Avahi resolver failure: " << avahi_strerror(avahi_client_errno(avahi_service_resolver_get_client(resolver))) << std::endl;
        return;
    }

    char address_str[AVAHI_ADDRESS_STR_MAX];
    avahi_address_snprint(address_str, sizeof(address_str), address);

    std::cout << "Resolved " << name << " on " << address_str << ":" << port << std::endl;
}

int main()
{
    AvahiSimplePoll *poll = avahi_simple_poll_new();
    if (!poll)
    {
        cerr << "Error creating Avahi poll object" << endl;
        exit(EXIT_FAILURE);
    }

    AvahiClient *client1 = avahi_client_new(avahi_simple_poll_get(poll), (AvahiClientFlags)0, nullptr, nullptr, nullptr);
    if (!client1)
    {
        cerr << "Error creating Avahi client object for network 1 \n"
             << endl;
        exit(EXIT_FAILURE);
    }

    AvahiClient *client2 = avahi_client_new(avahi_simple_poll_get(poll), (AvahiClientFlags)0, nullptr, nullptr, nullptr);
    if (!client2)
    {
        cerr << "Error creating Avahi client object for network 2 \n"
             << endl;
        exit(EXIT_FAILURE);
    }

    AvahiServiceBrowser *sb1 = avahi_service_browser_new(
        client1, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, SERVICE_TYPE, nullptr, (AvahiLookupFlags)0, [](AvahiServiceBrowser *sb, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain, AvahiLookupResultFlags flags, void *userdata)
        { cout << "Service " << name << " of type " << type << " found on network 1" << endl; },
        nullptr);

    if (!sb1)
    {
        cerr << "Error creating Avahi service browser for network 1" << endl;
        exit(EXIT_FAILURE);
    }

    AvahiServiceBrowser *sb2 = avahi_service_browser_new(
        client2, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, SERVICE_TYPE, nullptr, (AvahiLookupFlags)0, [](AvahiServiceBrowser *sb, AvahiIfIndex interface, AvahiProtocol protocol, const char *name, const char *type, const char *domain, AvahiLookupResultFlags flags, void *userdata)
        { cout << "Service " << name << " of type " << type << " found on network 2" << endl; },
        nullptr);

    if (!sb2)
    {
        cerr << "Error creating Avahi service browser for network 2" << endl;
        exit(EXIT_FAILURE);
    }

    avahi_simple_poll_loop(poll);

    // avahi_service_browser_free(sb1);
    // avahi_service_browser_free(sb2);
    avahi_client_free(client1);
    avahi_client_free(client2);
    avahi_simple_poll_free(poll);

    return EXIT_SUCCESS;
}
